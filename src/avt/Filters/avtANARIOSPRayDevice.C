// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

// ************************************************************************* //
//                       avtANARIOSPRayDevice.C                              //
// ************************************************************************* //

#include <avtANARIOSPRayDevice.h>
#include <avtANARIRenderer.h>

#include <DebugStream.h>
#include <TimingsManager.h>
#include <StackTimer.h>

#include <vtkImageData.h>
#include <vtkCellData.h>
#include <vtkPointData.h>
#include <vtkDataArray.h>
#include <vtkDataObject.h>
#include <vtkRectilinearGrid.h>

const std::string avtANARIOSPRayDevice::DEVICE_TYPE_STR{"ospray"};

// ****************************************************************************
//  Method: avtANARIOSPRayDevice constructor
//
//  Programmer: Kevin Griffin
//  Creation:   March 4, 2021
//
//  Modifications:
//
// ****************************************************************************

avtANARIOSPRayDevice::avtANARIOSPRayDevice() : avtRayTracerBase(),
    m_dataType(DataType::GEOMETRY),
    m_activeVariablePtr(nullptr),
    m_lightList(),
    m_lightingEnabled(false),
    m_shadowsEnabled(false),
    m_useGridAccelerator(false),
    m_preIntegration(false),
    m_singleShade(false),
    m_oneSidedLighting(false),
    m_aoTransparencyEnabled(false),
    m_aoSamples(0),
    m_samplesPerPixel(1),
    m_aoDistance(100000.0f),
    m_minContribution(0.001f),
    m_samplesPerRay(500),
    m_samplingRate(3.0f),
    m_materialPropertiesPtr(nullptr),
    m_viewDirectionPtr(nullptr),
    m_module(nullptr),
    m_device(nullptr)
{ }

// ****************************************************************************
//  Method: avtANARIOSPRayDevice::SetMatProperties
//
//  Purpose:
//
//  Arguments:
//      props  
//
//  Programmer: Kevin Griffin
//  Creation:   February 22, 2021
//
// ****************************************************************************

void
avtANARIOSPRayDevice::SetMatProperties(const double props[4])
{
    if(!m_materialPropertiesPtr)
        m_materialPropertiesPtr.reset(new float[4]);

    for(int i=0; i<4; i++)
        m_materialPropertiesPtr[i] = static_cast<float>(props[i]);
}

// ****************************************************************************
//  Method: avtANARIOSPRayDevice::SetViewDirection
//
//  Purpose:
//
//  Arguments:
//      direction  
//
//  Programmer: Kevin Griffin
//  Creation:   February 22, 2021
//
// ****************************************************************************

void
avtANARIOSPRayDevice::SetViewDirection(const double direction[3])
{
    if(!m_viewDirectionPtr)
        m_viewDirectionPtr.reset(new float[3]);

    for(int i=0; i<3; i++)
        m_viewDirectionPtr[i] = static_cast<float>(direction[i]);
}

// ****************************************************************************
//  Method: avtANARIOSPRayDevice::ErrorCallback
//
//  Purpose:
//
//  Arguments:
//      userData
//      err - ANARI errors which can be of the following type:
//            ANARI_NO_ERROR          0 - No error has been recorded
//            ANARI_UNKNOWN_ERROR     1 - An unknown error has occurred
//            ANARI_INVALID_ARGUMENT  2 - An invalid argument is specified
//            ANARI_INVALID_OPERATION 3 - The operation is not allowed for the 
//                                        specified object
//            ANARI_OUT_OF_MEMORY     4 - There is not enough memory left to 
//                                        execute the command
//            ANARI_UNSUPPORTED_CPU   5 - The CPU is not supported as it does 
//                                        not support SSE4.1
//            ANARI_VERSION_MISMATCH  6 - A module could not be loaded due to 
//                                        mismatching version
//      details  
//
//  Programmer: Kevin Griffin
//  Creation:   March 8, 2021
//
// ****************************************************************************

void
avtANARIOSPRayDevice::ErrorCallback(void *userData, ANARIError err, const char *details)
{
    debug5 << "[ANARI::OSPRay] " << GetANARIErrorString(err) << ": " << details << std::endl;
}

// ****************************************************************************
//  Method: avtANARIOSPRayDevice::StatusCallback
//
//  Purpose:
//
//  Arguments:
//      userData
//      details  
//
//  Programmer: Kevin Griffin
//  Creation:   March 8, 2021
//
// ****************************************************************************

void
avtANARIOSPRayDevice::StatusCallback(void *userData, const char *details)
{
    debug5 << "[ANARI::OSPRay] Status: " << details << std::endl;
}

// ****************************************************************************
//  Method: avtANARIOSPRayDevice::GetANARIErrorString
//
//  Purpose:
//      Utility method that converts an ANARIError into a string
//
//  Arguments:
//      err    error code returned from ANARI
//
//  Programmer: Kevin Griffin
//  Creation:   March 8, 2021
//
// ****************************************************************************

std::string
avtANARIOSPRayDevice::GetANARIErrorString(const ANARIError err)
{
    switch(err) 
    {
        case ANARI_NO_ERROR:
            return "";
        case ANARI_UNKNOWN_ERROR:
            return "Unknown Error";
        case ANARI_INVALID_ARGUMENT:
            return "Invalid Argument";
        case ANARI_INVALID_OPERATION:
            return "Invalid Operation";            
        case ANARI_OUT_OF_MEMORY:
            return "Out of Memory";            
        case ANARI_UNSUPPORTED_CPU:
            return "Unsupported CPU";
        case ANARI_VERSION_MISMATCH:
            return "Version Mismatch";
        default:
            return "Unknown Error";
    }
}

// ****************************************************************************
//  Method: avtANARIOSPRayDevice::GetANARITypeFromVTKType
//
//  Purpose:
//      Utility method that returns an ANARI type from a VTK type.
//
//  Arguments:
//      type    VTK type returned by GetDataType to indicate pixel type.
//
//  Programmer: Kevin Griffin
//  Creation:   March 8, 2021
//
// ****************************************************************************

ANARIDataType 
avtANARIOSPRayDevice::GetANARITypeFromVTKType(const int type) 
{
    std::cout << "VTK Type: " << type << std::endl;
    switch(type) {        
        case VTK_UNSIGNED_CHAR:
            return ANARI_UCHAR;
        case VTK_SHORT:
            return ANARI_SHORT;
        case VTK_UNSIGNED_SHORT:
            return ANARI_USHORT;
        case VTK_FLOAT:
            return ANARI_FLOAT;
        case VTK_DOUBLE:
            return ANARI_DOUBLE;
        default:
            return ANARI_UCHAR;
    }
}

// ****************************************************************************
//  Method: avtANARIOSPRayDevice::CreateCamera
//
//  Purpose:
//      The perspective camera implements a simple thin lens camera for
//      perspective rendering, supporting optionally depth of field and stereo
//      rendering, but not motion blur. 
//
//      The orthographic camera implements a simple camera with orthographic
//      projection, without support for depth of field or motion blur. 
//
//  Programmer: Kevin Griffin
//  Creation:   March 8, 2021
//
// ****************************************************************************

ANARICamera
avtANARIOSPRayDevice::CreateCamera() 
{
    float aspect = 1.0f;

    if(screen[1] > 0) 
    {
        aspect = static_cast<float>(screen[0]) / static_cast<float>(screen[1]);
    }

    float cameraPosition[3] = {static_cast<float>(view.camera[0]), 
                               static_cast<float>(view.camera[1]), 
                               static_cast<float>(view.camera[2])};

    float cameraUp[3] = {static_cast<float>(view.viewUp[0]), 
                         static_cast<float>(view.viewUp[1]), 
                         static_cast<float>(view.viewUp[2])};

    float cameraDirection[3];
    if(m_viewDirectionPtr) 
    {
        cameraDirection[0] = m_viewDirectionPtr[0];
        cameraDirection[1] = m_viewDirectionPtr[1];
        cameraDirection[2] = m_viewDirectionPtr[2];
    }
    else
    {
        double viewDirection[3];
        viewDirection[0] = view.focus[0] - view.camera[0];
        viewDirection[1] = view.focus[1] - view.camera[1];
        viewDirection[2] = view.focus[2] - view.camera[2];
        double mag = sqrt(viewDirection[0]*viewDirection[0] + 
                          viewDirection[1]*viewDirection[1] +
                          viewDirection[2]*viewDirection[2]);
        if (mag != 0) // only 0 if focus and camera are the same
        {
            viewDirection[0] /= mag;
            viewDirection[1] /= mag;
            viewDirection[2] /= mag;
        }

        cameraDirection[0] = static_cast<float>(viewDirection[0]); 
        cameraDirection[1] = static_cast<float>(viewDirection[1]);
        cameraDirection[2] = static_cast<float>(viewDirection[2]);
    }
    
    ANARICamera camera = nullptr;

    if(!view.orthographic)
    {
        camera = anariNewCamera(m_device, "perspective");
        anari::setParam(m_device, camera, "fovy", static_cast<float>(view.viewAngle));
        anari::setParam(m_device, camera, "aspect", aspect);
        anari::setParam(m_device, camera, "position", cameraPosition);
        anari::setParam(m_device, camera, "direction", cameraDirection);
        anari::setParam(m_device, camera, "up", cameraUp);
        anari::setParam(m_device, camera, "nearClip", static_cast<float>(view.nearPlane));
    }
    else 
    {
        camera = anariNewCamera(m_device, "orthographic");
        anari::setParam(m_device, camera, "height", static_cast<float>(screen[1]));
        anari::setParam(m_device, camera, "aspect", aspect);
    }

    return camera;
}

// ****************************************************************************
//  Method: avtANARIOSPRayDevice::CreateStructuredRegularVolume
//
//  Purpose:
//      Structured regular volumes only need to store the values of the samples
//      because their addresses in memory can be computed from a 3D position. 
//
//  Programmer: Kevin Griffin
//  Creation:   March 8, 2021
//
// ****************************************************************************

ANARIVolume
avtANARIOSPRayDevice::CreateStructuredRegularVolume()
{
    ANARIVolume volume = anariNewVolume(m_device, "structuredRegular");

    // TODO: Merge datasets
    // Get volume data
    auto inputTree = GetInputDataTree();
    int nsets = 0;
    vtkDataSet **dataSets = inputTree->GetAllLeaves(nsets);
    std::cout << "nsets: " << nsets << std::endl;
    std::cout << "activeVar: " << m_activeVariablePtr << std::endl;
    
    vtkRectilinearGrid *rgrid = (vtkRectilinearGrid *)dataSets[0];

    // Origin of the grid in object-space
    double bounds[6];
    rgrid->GetBounds(bounds);
    double origin[3] = {bounds[0], bounds[2], bounds[4]};
    
    float gridOrigin[3] = {static_cast<float>(origin[0]),
                           static_cast<float>(origin[1]),
                           static_cast<float>(origin[2])};
    anari::setParam(m_device, volume, "gridOrigin", gridOrigin);
    debug5 << "[ANARI::OSPRay] Grid Origin: {" << gridOrigin[0] << " " << gridOrigin[1] << " " << gridOrigin[2] << "} " << std::endl;

    double spacing[3];
    spacing[0] = rgrid->GetXCoordinates()->GetTuple1(1) - rgrid->GetXCoordinates()->GetTuple1(0);
    spacing[1] = rgrid->GetYCoordinates()->GetTuple1(1) - rgrid->GetYCoordinates()->GetTuple1(0);
    spacing[2] = rgrid->GetZCoordinates()->GetTuple1(1) - rgrid->GetZCoordinates()->GetTuple1(0);
    // Size of the grid cells in object-space
    float gridSpacing[3] = {static_cast<float>(spacing[0]),
                            static_cast<float>(spacing[1]),
                            static_cast<float>(spacing[2])};
    anari::setParam(m_device, volume, "gridSpacing", gridSpacing);
    debug5 << "[ANARI::OSPRay] Grid Spacing: {" << gridSpacing[0] << " " << gridSpacing[1] << " " << gridSpacing[2] << "} " << std::endl;

    int dims[3];
    rgrid->GetDimensions(dims);
    std::cout << "Dims: " << dims[0] << " " << dims[1] << " " << dims[2] << std::endl;
    int numItems = dims[0] * dims[1] * dims[2];
    debug5 << "[ANARI::OSPRay] Data size: " << numItems << std::endl;

    vtkDataArray *primVar = rgrid->GetPointData()->GetArray(m_activeVariablePtr);

    if(primVar == NULL) {
        primVar = rgrid->GetCellData()->GetArray(m_activeVariablePtr);
        std::cout << "Num cells: " << rgrid->GetNumberOfCells() << std::endl;
    } else {
        std::cout << "Num points: " << rgrid->GetNumberOfPoints() << std::endl;
    }
    
    anari::setAndReleaseParam(m_device, volume, "data", anari::makeCopiedData(m_device, (float *)primVar->GetVoidPointer(0), dims));
    
    return volume;
}

// ****************************************************************************
//  Method: avtANARIOSPRayDevice::CreateTransferFunction
//
//  Purpose:
//      Transfer functions map the scalar values of volumes to colors and
//      opacity and thus they can be used to visually emphasize certain
//      features of the volume.
//
//  Programmer: Kevin Griffin
//  Creation:   March 8, 2021
//
// ****************************************************************************

ANARITransferFunction
avtANARIOSPRayDevice::CreateTransferFunction() 
{
    // TODO: Types of tranfere functions??
    ANARITransferFunction transferFunction = anariNewTransferFunction(m_device, "piecewiseLinear");
    const RGBAF *transferTable = transferFn1D->GetTableFloat();
    // const RGBA *transferTable = transferFn1D->GetTable();
    
    int tableSize = transferFn1D->GetNumberOfTableEntries();
    std::unique_ptr<float[]> tableColors(new float[3*tableSize]);
    std::unique_ptr<float[]> tableOpacity(new float[tableSize]);
    int index;

    for(int i=0; i<tableSize; i++)
    {
        index = i*3;

        tableColors[index] = transferTable[i].R;
        tableColors[index+1] = transferTable[i].G;
        tableColors[index+2] = transferTable[i].B;
  
        tableOpacity[i] = transferTable[i].A;
    }

    ANARIData data = anariNewSharedData(m_device, tableColors.get(), ANARI_VEC3F, tableSize);
    anariCommit(m_device, data);
    anari::setAndReleaseParam(m_device, transferFunction, "color", data);

    data = anariNewSharedData(m_device, tableOpacity.get(), ANARI_FLOAT, tableSize);
    anariCommit(m_device, data);
    anari::setAndReleaseParam(m_device, transferFunction, "opacity", data);

    float valueRange[] = {static_cast<float>(transferFn1D->GetMin()), 
                          static_cast<float>(transferFn1D->GetMax())};
    
    //float valueRange[] = {0.0f, 35.0f};
    anari::setParam(m_device, transferFunction, "valueRange", valueRange);

    return transferFunction;
}

// ****************************************************************************
//  Method: avtANARIOSPRayDevice::CreateVolumetricModel
//
//  Purpose:
//      Create a VolumetricModel. A VolumetricModel contains the rendering 
//      appearance information for a given volume. This decouples the physical 
//      representation of the volume with the rendering-specific parameters.
//
//
//  Programmer: Kevin Griffin
//  Creation:   March 8, 2021
//
// ****************************************************************************

ANARIVolumetricModel
avtANARIOSPRayDevice::CreateVolumetricModel()
{
    // Create Structured Regular Volume
    ANARIVolume volume = CreateStructuredRegularVolume();
    anariCommit(m_device, volume);    // commit each object to indicate mods are done

    // Transfer function
    ANARITransferFunction transferFunction = CreateTransferFunction();
    anariCommit(m_device, transferFunction);

    // Volumetric Model
    ANARIVolumetricModel volumetricModel = anariNewVolumetricModel(m_device, "density");
    anari::setAndReleaseParam(m_device, volumetricModel, "volume", volume);
    anari::setAndReleaseParam(m_device, volumetricModel, "transferFunction", transferFunction);

    return volumetricModel;
}

// ****************************************************************************
//  Method: avtANARIOSPRayDevice::CreateLights
//
//  Purpose:
//      Create up to 8 ANARI light sources based on the active lights 
//      configured in VisIt. VisIt supports a maximum of 8 lights so the vector
//      returned will have a maximum of 8 light sources if all of the lights
//      are enabled.
//
//  Returns:
//      A vector containing up to 8 ANARI light sources
//
//  Programmer: Kevin Griffin
//  Creation:   March 8, 2021
//
// ****************************************************************************

std::vector<ANARILight>
avtANARIOSPRayDevice::CreateLights()
{
    std::vector<ANARILight> lights;

    // VisIt has 8 lights
    for(int i=0; i<8; i++) 
    {
        auto lightAttributes = m_lightList.GetLight(i);

        if(lightAttributes.GetEnabledFlag()) 
        {
            LightAttributes::LightType type = lightAttributes.GetType();
            ANARILight light = nullptr;

            if(type == LightAttributes::Ambient) 
            {
                light = anariNewLight(m_device, "ambient");                
            }
            else    // Treat as a directional/distant light
            {
                light = anariNewLight(m_device, "distant");
                
                // direction
                float direction[] = {static_cast<float>(lightAttributes.GetDirection()[0]),
                                     static_cast<float>(lightAttributes.GetDirection()[1]),
                                     static_cast<float>(lightAttributes.GetDirection()[2])};
                anari::setParam(m_device, light, "direction", direction);

                // Angular Diameter
                anari::setParam(m_device, light, "angularDiameter", 0.0f);
            }

            // color
            float color[] = {static_cast<float>(lightAttributes.GetColor().Red()) / 255.0f,
                             static_cast<float>(lightAttributes.GetColor().Green()) / 255.0f,
                             static_cast<float>(lightAttributes.GetColor().Blue()) / 255.0f};
            anari::setParam(m_device, light, "color", color);

            // intensity
            anari::setParam(m_device, light, "intensity", static_cast<float>(lightAttributes.GetBrightness()));
            
            lights.push_back(light);
        }
    }

    return lights;
}

// ****************************************************************************
//  Method: avtANARIOSPRayDevice::CreateInstance
//
//  Purpose:
//      Instances in ANARI represent collections of GeometricModels and 
//      VolumetricModels which share a common local-space coordinate system.
//
//  Programmer: Kevin Griffin
//  Creation:   March 8, 2021
//
// ****************************************************************************

ANARIInstance
avtANARIOSPRayDevice::  CreateInstance()
{
    ANARIInstance instance = anariNewInstance(m_device);

    if(m_dataType == DataType::VOLUME)
    {
        // Create Volumetric Model
        ANARIVolumetricModel volumetricModel = CreateVolumetricModel();
        anariCommit(m_device, volumetricModel);

        ANARIData data = anariNewSharedData(m_device, &volumetricModel, ANARI_VOLUMETRIC_MODEL, 1);
        anariCommit(m_device, data);
        anari::setParam(m_device, instance, "volume", data);
        
        anariRelease(m_device, volumetricModel);
        anariRelease(m_device, data);
    }
    else 
    {
        // TODO: Create an ANARIGeometricModel
    }
    
    // Create lights
    if(m_lightingEnabled)   // OSPRay doesn't support instance lighting 
    {
        std::vector<ANARILight> lights = CreateLights();
        int lightCount = lights.size();
        
        if(lightCount > 0) 
        {
            // Commit Lights
            for(int i=0; i<lightCount; i++) 
            {
                anariCommit(m_device, lights[i]);
            }

            // Add lights to instance
            ANARIData data = anariNewSharedData(m_device, lights.data(), ANARI_LIGHT, lightCount);
            anariCommit(m_device, data);
            anari::setParam(m_device, instance, "light", data);
            
            // Release lights
            for(int i=0; i<lightCount; i++)
            {
                anariRelease(m_device, lights[i]);
            }

            anariRelease(m_device, data);
        }
    }

    return instance;
}

// ****************************************************************************
//  Method: avtANARIOSPRayDevice::CreateRenderer
//
//  Purpose:
//      A renderer is the central object for rendering in ANARI. Different 
//      renderers implement different features, rendering algorithms, and 
//      support different materials. 
//
//      ANARI supports three rendering subtypes: SciVis, Ambient Occlusion,
//      and Path Tracer.
//
//  Arguments:
//      type    the renderer subtype: SCIVIS, AO, or PATHTRACER
//
//  Programmer: Kevin Griffin
//  Creation:   March 8, 2021
//
// ****************************************************************************

ANARIRenderer
avtANARIOSPRayDevice::CreateRenderer(const RendererType type) 
{
    debug5 << "[ANARI::OSPRay] Setting up renderer..." << std::endl;    
    float bgColor[] = {static_cast<float>(background[0])/255.0f,
                       static_cast<float>(background[1])/255.0f,
                       static_cast<float>(background[2])/255.0f};
    debug5 << "[ANARI::OSPRay] Background color: {" << bgColor[0] << " " << bgColor[1] << " " << bgColor[2] << "}" << std::endl;

    ANARIRenderer renderer = nullptr;

    if(type == RendererType::SCIVIS)
    {
        renderer = anariNewRenderer(m_device, "scivis");
        anari::setParam(m_device, renderer, "pixelSamples", m_samplesPerPixel);
        anari::setParam(m_device, renderer, "maxPathLength", m_samplesPerRay);
        anari::setParam(m_device, renderer, "minContribution", m_minContribution);
        anari::setParam(m_device, renderer, "backgroundColor", bgColor);
        anari::setParam(m_device, renderer, "shadows", m_shadowsEnabled);
        anari::setParam(m_device, renderer, "aoSamples", m_aoSamples);
        anari::setParam(m_device, renderer, "aoDistance", m_aoDistance);
        anari::setParam(m_device, renderer, "volumeSamplingRate", m_samplingRate);        
    }
    else if(type == RendererType::AO)
    {
        renderer = anariNewRenderer(m_device, "ao");
        anari::setParam(m_device, renderer, "pixelSamples", m_samplesPerPixel);
        anari::setParam(m_device, renderer, "maxPathLength", m_samplesPerRay);
        anari::setParam(m_device, renderer, "minContribution", m_minContribution);
        anari::setParam(m_device, renderer, "backgroundColor", bgColor);
        anari::setParam(m_device, renderer, "aoSamples", m_aoSamples);
        anari::setParam(m_device, renderer, "aoDistance", m_aoDistance);
        anari::setParam(m_device, renderer, "volumeSamplingRate", m_samplingRate);
    }
    else    // RendererType::PATHTRACER
    {
        renderer = anariNewRenderer(m_device, "pathtracer");
        anari::setParam(m_device, renderer, "pixelSamples", m_samplesPerPixel);
        anari::setParam(m_device, renderer, "maxPathLength", m_samplesPerRay);
        anari::setParam(m_device, renderer, "minContribution", m_minContribution);
        anari::setParam(m_device, renderer, "backgroundColor", bgColor);
    }

    return renderer;
}

// ****************************************************************************
//  Method: avtANARIOSPRayDevice::CreateFrameBuffer
//
//  Purpose:
//      The framebuffer holds the rendered 2D image and optionally auxillary
//      information associated with pixels.
//
//  Arguments: 
//      format  describes the format the color buffer has on the host that
//              ANARI will eventually return
//      channelColor    enable the color channel buffer for mapping
//      channelAccum    enable the accumulation channel buffer for mapping
//      channelDepth    enable the depth channel buffer for mapping
//      channelAlbedo   enable the albedo channel buffer for mapping
//
//  Programmer: Kevin Griffin
//  Creation:   March 8, 2021
//
// ****************************************************************************

ANARIFrameBuffer
avtANARIOSPRayDevice::CreateFrameBuffer(const ANARIFrameBufferFormat format,
                                   int width,
                                   int height,
                                   bool channelColor,
                                   bool channelAccum,
                                   bool channelDepth,
                                   bool channelAlbedo)
{
    ANARIFrameBuffer frameBuffer = anariNewFrameBuffer(m_device);
    anari::setParam(m_device, frameBuffer, "width", width);
    anari::setParam(m_device, frameBuffer, "height", height);
    anari::setParam(m_device, frameBuffer, "format", format);
    anari::setParam(m_device, frameBuffer, "channelColor", channelColor);
    anari::setParam(m_device, frameBuffer, "channelAccum", channelAccum);
    anari::setParam(m_device, frameBuffer, "channelDepth", channelDepth);
    anari::setParam(m_device, frameBuffer, "channelAlbedo", channelAlbedo);

    return frameBuffer;
} 

// ****************************************************************************
//  Method: avtANARIOSPRayDevice::CreateDevice
//
//  Purpose:
//      The OSPRay device uses the OSPRay API for rendering.
//
//  Arguments: 
//      type the device type (e.g. ospray, optix, nvgl)
//
//  Programmer: Kevin Griffin
//  Creation:   March 8, 2021
//
// ****************************************************************************

void
avtANARIOSPRayDevice::CreateDevice(const ANARIModule anariModule, const char *type)
{
    m_device = anariNewDevice(anariModule, type);

    if(m_device) 
    {
        // Callbacks
        anariDeviceSetStatusCallback(m_device, avtANARIOSPRayDevice::StatusCallback, nullptr);
        anariDeviceSetErrorCallback(m_device, avtANARIOSPRayDevice::ErrorCallback, nullptr);
        anari::setParam(m_device, m_device, "debug", true);

        anariCommit(m_device, m_device);
    }
}

// ****************************************************************************
//  Method: avtANARIOSPRayDevice::CreateWorld
//
//  Purpose:
//      Worlds are a container of scene data represented by instances.
//
//  Programmer: Kevin Griffin
//  Creation:   March 8, 2021
//
// ****************************************************************************

ANARIWorld
avtANARIOSPRayDevice::CreateWorld()
{
    // Create Instance
    ANARIInstance instance = CreateInstance();
    anariCommit(m_device, instance);

    debug5 << "[ANARI::OSPRay] Done creating instance" << std::endl;

    // Create World
    ANARIWorld world = anariNewWorld(m_device);

    ANARIData data = anariNewSharedData(m_device, &instance, ANARI_INSTANCE, 1);
    anariCommit(m_device, data);
    anari::setParam(m_device, world, "instance", data);

    anariRelease(m_device, instance);
    anariRelease(m_device, data); 
    
    return world;
}
    
// ****************************************************************************
//  Method: avtANARIOSPRayDevice::Execute
//
//  Purpose:
//      Executes the OSPRay Rendering backend.  
//      This means:
//      - Put the input mesh through a transform so it is in camera space.
//      - Get the sample points.
//      - Communicate the sample points (parallel only).
//      - Composite the sample points along rays.
//      - Communicate the pixels from each ray (parallel only).
//      - Output the image.
//
//  Programmer: Kevin Griffin
//  Creation:   March 8, 2021
//
//  Modifications:
//
// ****************************************************************************

void 
avtANARIOSPRayDevice::Execute()
{
    StackTimer t0("ANARI::OSPRay Rendering");

    if(m_device != nullptr)
    {
        anariRelease(m_device, m_device);
    } 

    const char *moduleName = GetDeviceType();
    m_module = anariLoadModule(moduleName);
    CreateDevice(m_module, "default");
    
    if(m_device != nullptr) 
    {
        debug5 << "[ANARI::OSPRay] Done loading module and creating device" << std::endl;
        if(m_dataType == DataType::VOLUME) 
            ExecuteVolume();
        else
            ; // TODO: Implement ExecuteSurface();
    }
    else
    {
        std::string msg("[ANARI::OSPRay] Could not load default device for OSPRay module.");        
        EXCEPTION1(VisItException, msg);
    }
}

// ****************************************************************************
//  Method: avtANARIOSPRayDevice::ExecuteVolume
//
//  Purpose:
//      Executes Volume Rendering using the OSPRay Rendering backend.  
//      
//
//  Programmer: Kevin Griffin
//  Creation:   March 8, 2021
//
//  Modifications:
//
// ****************************************************************************

void
avtANARIOSPRayDevice::ExecuteVolume() 
{
    // Create camera
    ANARICamera camera = CreateCamera();        
    anariCommit(m_device, camera);

    debug5 << "[ANARI::OSPRay] Done setting up camera" << std::endl;

    // Create world
    ANARIWorld world = CreateWorld();
    anariCommit(m_device, world);

    debug5 << "[ANARI::OSPRay] Done creating the world" << std::endl;
    
    // ANARIBounds worldBounds = anariGetBounds(m_device, world);
    float worldBounds[6];
    if(anariGetProperty(m_device, 
                        world, 
                        "bounds", 
                        ANARI_BOX3F, 
                        worldBounds, 
                        sizeof(worldBounds),
                        ANARI_WAIT)) 
    {
        debug5 << "[ANARI::OSPRay] World Bounds: " 
           << "{" << worldBounds[0] << ", " << worldBounds[1] << ", " << worldBounds[2] << "}, " 
           << "{" << worldBounds[3] << ", " << worldBounds[4] << ", " << worldBounds[5] << "}" << std::endl;
    } else {
        debug5 << "[ANARI::OSPRay] World bounds not returned" << std::endl;
    }

    // Create renderer
    ANARIRenderer renderer = CreateRenderer(RendererType::AO);
    anariCommit(m_device, renderer);

    int width = screen[0];
    int height = screen[1];
    // opaqueImage->GetSize(&width, &height); 

    // Create framebuffer
    ANARIFrameBuffer frameBuffer = CreateFrameBuffer(ANARI_FB_SRGBA, width, height);
    anariCommit(m_device, frameBuffer);

    // Render 
    ANARIFuture future = anariRenderFrame(m_device, frameBuffer, renderer, camera, world);
    anariWait(m_device, future, ANARI_TASK_FINISHED);
    anariRelease(m_device, future);

    // Map framebuffer
    auto renderedFrameBuffer = anariMapFrameBuffer(m_device, frameBuffer, "color");

    // Copy image to VisIt
    const int colorChannels = 4;    // RGBA
    avtImage_p finalImage = new avtImage(this);
    finalImage->GetImage() = avtImageRepresentation::NewImage(width, height, colorChannels);
    auto finalImageColorBuffer = finalImage->GetImage().GetRGBBuffer();
    
    size_t bytesToCopy = width * height * colorChannels;
    debug5 << "[ANARI::OSPRay] Bytes To Copy: " << bytesToCopy << std::endl;
    
    memcpy(finalImageColorBuffer, renderedFrameBuffer, bytesToCopy);
    
    debug5 << "[ANARI::OSPRay] Copy Completed" << std::endl;
    // avtANARIRenderer::WriteArrayToPPM("test", renderedFrameBuffer, screen[0], screen[1]);

    // Cleanup
    anariUnmapFrameBuffer(m_device, frameBuffer, "color");

    anariRelease(m_device, renderer);
    anariRelease(m_device, camera);
    anariRelease(m_device, frameBuffer);
    anariRelease(m_device, world);

    anariRelease(m_device, m_device);
    anariUnloadModule(m_module);
    debug5 << "[ANARI::OSPRay] Done!" << std::endl;

    SetOutput(finalImage);
}
