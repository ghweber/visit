// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

// ************************************************************************* //
//                           avtANARIOSPRayDevice.h                          //
// ************************************************************************* //

#ifndef AVT_ANARI_OSPRAY_DEVICE_H
#define AVT_ANARI_OSPRAY_DEVICE_H

#include <filters_exports.h>

#include <avtANARIDevice.h>
#include <avtRayTracerBase.h>
#include <LightList.h>

#include <memory>

using DataType = avt::anari::DataType;
using RendererType = avt::anari::RendererType;

class AVTFILTERS_API avtANARIOSPRayDevice : public avtANARIDevice, public avtRayTracerBase
{
public:
                            avtANARIOSPRayDevice();
    virtual                 ~avtANARIOSPRayDevice() = default;

    virtual const char      *GetType() override         { return "avtANARIOSPRayDevice"; }
    virtual const char      *GetDescription() override  { return "ANARI OSPRay Back-end Device"; }
    virtual const char      *GetDeviceType() override   { return DEVICE_TYPE_STR.c_str(); }

    void SetRenderingType(const DataType dt)       { m_dataType = dt; }

     // VisIt options
    void SetActiveVariable(const char *s)       { m_activeVariablePtr = s; }
    void SetLightInfo(const LightList& l)       { m_lightList = l; }

    // OSPRay Options
    void SetLighting(const bool b)              { m_lightingEnabled = b; }
    void SetShadowsEnabled(const bool b)        { m_shadowsEnabled = b; }
    void SetUseGridAccelerator(const bool l)    { m_useGridAccelerator = l; }
    void SetPreIntegration(const bool l)        { m_preIntegration = l; }
    void SetSingleShade(const bool l)           { m_singleShade = l; }
    void SetOneSidedLighting(const bool l)      { m_oneSidedLighting = l; }
    void SetAoTransparencyEnabled(const bool l) { m_aoTransparencyEnabled = l; }
    void SetAoSamples(const int v)              { m_aoSamples = v; }
    void SetSamplesPerPixel(const int v)        { m_samplesPerPixel = v; }
    void SetAoDistance(const float v)           { m_aoDistance = v; }
    void SetMinContribution(const float v)      { m_minContribution = v; }

    // Ray Casting Options
    void SetSamplingRate(const float v)         { m_samplingRate = v; }
    // Maximum reay recursion depth
    void SetSamplesPerRay(const int s)          { m_samplesPerRay = s; }

    // Lighting and Material Properties    
    void SetMatProperties(const double[4]);
    void SetViewDirection(const double[3]);

    // ANARI Callback Functions
    static void         ErrorCallback(void *, ANARIError, const char *);
    static void         StatusCallback(void *, const char *);
    
    static std::string  GetANARIErrorString(const ANARIError);

protected:
    virtual void            Execute(void) override;

    DataType                m_dataType;

// TODO: Create structs to hold most of these 
//
    const char*             m_activeVariablePtr;
    // VisIt has 8 lights that can be setup
    LightList               m_lightList; 
    bool                    m_lightingEnabled;
    // Whether to compute (hard) shadows
    bool                    m_shadowsEnabled;
    bool                    m_useGridAccelerator;
    bool                    m_preIntegration;
    bool                    m_singleShade;
    bool                    m_oneSidedLighting;
    bool                    m_aoTransparencyEnabled;
    // Number of rays per sample to compute ambient occlusion
    int                     m_aoSamples;
    // Samples per pixel
    int                     m_samplesPerPixel;
    // Maximum distance to consider for ambient occlusion
    float                   m_aoDistance;
    // Sample contributions below this value will be neglected
    // to speed up rendering. 
    float                   m_minContribution;

    int                     m_samplesPerRay;
    // Sampling rate for volumes
    float                   m_samplingRate;

    std::unique_ptr<float[]>   m_materialPropertiesPtr;
    std::unique_ptr<float[]>   m_viewDirectionPtr;

    // TODO: Add these? They are in the ANARI Spec
    // float varianceThreshold; default=0
    //      threshold for adaptive accumulation

    // uchar pixelFilter - filter for antialiasing
    //      ANARI_PIXELFILTER_GAUSS (default) (POINT,BOX,GAUSS,MITCHELL,BLACKMAN_HARRIS)

    // avtOSPRayImageCompositor imgComm;

private:
    void                    ExecuteVolume();
    void                    ExecuteSurface();

    void                    CreateDevice(const ANARIModule, const char *);
    ANARICamera             CreateCamera();
    ANARIVolume             CreateStructuredRegularVolume();
    ANARITransferFunction   CreateTransferFunction();
    ANARIVolumetricModel    CreateVolumetricModel();
    ANARIInstance           CreateInstance();
    ANARIWorld              CreateWorld();
    ANARIRenderer           CreateRenderer(const RendererType);
    std::vector<ANARILight> CreateLights();
    ANARIFrameBuffer        CreateFrameBuffer(const ANARIFrameBufferFormat,
                                              int  width,
                                              int  height,
                                              bool channelColor = true,
                                              bool channelAccum = false,
                                              bool channelDepth = false,
                                              bool channelAlbedo = false);

    ANARIDataType           GetANARITypeFromVTKType(const int);
    
    // TODO: change to MODULE_NAME
    static const std::string    DEVICE_TYPE_STR;
    ANARIModule                 m_module;
    ANARIDevice                 m_device;
};


#endif