// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

// ************************************************************************* //
//                       avtANARIRenderer.C                            //
// ************************************************************************* //

#include <avtANARIRenderer.h>
#include <avtANARIOSPRayDevice.h>
// #include <avtANARIUSDDevice.h>
// #include <avtANARIOptIxDevice.h>
// #include <avtANARINVGLDevice.h>
// #include <avtANARIVulcanDevice.h>

#include <string>

DeviceType avtANARIRenderer::m_deviceType = DeviceType::NONE;
std::unique_ptr<avtANARIDevice> avtANARIRenderer::m_devicePtr(nullptr);

// ****************************************************************************
//  Method: avtANARIRenderer::SetDeviceType
//
//  Purpose:
//
//  Arguments:
//      deviceType  the backend rendering device
//      
//  Throws a VisIt exception if the device type specified by deviceType is not 
//  supported. 
//
//  Programmer: Kevin Griffin
//  Creation:   February 22, 2021
//
// ****************************************************************************

void
avtANARIRenderer::SetDeviceType(const DeviceType deviceType) 
{
    if(m_deviceType != deviceType)
    {
        m_deviceType = deviceType;

        switch(deviceType) 
        {
            case DeviceType::OSPRAY:
                #ifdef VISIT_OSPRAY2
                    m_devicePtr.reset(new avtANARIOSPRayDevice());
                #else
                    // throw std::invalid_argument("OSPRay Device is not supported");
                    EXCEPTION1(VisItException, "[ANARI] OSPRay Device is not supported");
                #endif
                break;
            case DeviceType::USD:
                // TODO: create avtUSDDevice
                EXCEPTION1(VisItException, "[ANARI] USD Device is not supported");
                break;
            case DeviceType::NVGL:
                // TODO: create avtNVGLDevice
                EXCEPTION1(VisItException, "[ANARI] NVGL Device is not supported");
                break;
            case DeviceType::OPTIX:
                // TODO: create avtOptiXDevice
                EXCEPTION1(VisItException, "[ANARI] OptiX Device is not supported");
                break;
            case DeviceType::NONE: case DeviceType::UNKNOWN:
                if(m_devicePtr) 
                {
                    m_devicePtr.reset(nullptr);            
                }
                break;
            default:
                char msg[50];
                int retVal = snprintf(msg, 50, "[ANARI] Unsupported device type: %d", static_cast<int>(deviceType));

                if(retVal > 0) 
                {
                    EXCEPTION1(VisItException, msg);
                }
                else
                {
                    EXCEPTION1(VisItException, "[ANARI] Unsupported device type");
                }
        }
    }
}

// ****************************************************************************
//  Method: avtANARIRenderer::GetDeviceType
//
//  Purpose:
//
//  Returns:      
//
//  Programmer: Kevin Griffin
//  Creation:   February 22, 2021
//
// ****************************************************************************

DeviceType
avtANARIRenderer::GetDeviceType()
{
    if(m_devicePtr) 
    {
        std::string typeStr(m_devicePtr->GetDeviceType());

        if(typeStr.compare("ospray") == 0) 
            return DeviceType::OSPRAY;
        else if(typeStr.compare("usd") == 0)
            return DeviceType::USD;
        else if(typeStr.compare("nvgl") == 0)
            return DeviceType::NVGL;
        else if(typeStr.compare("optix") == 0)
            return DeviceType::OPTIX;
        else 
            return DeviceType::UNKNOWN;
    }
    
    return DeviceType::NONE;
}

// ****************************************************************************
//  Method: avtANARIRenderer::GetDeviceTypeStr
//
//  Purpose:
//
//  Returns:      
//
//  Programmer: Kevin Griffin
//  Creation:   February 22, 2021
//
// ****************************************************************************

const char *
avtANARIRenderer::GetDeviceTypeStr()
{
    if(m_devicePtr)
        return m_devicePtr->GetDeviceType();

    return nullptr;
}

// ****************************************************************************
//  Method: avtANARIRenderer::GetDevice
//
//  Purpose:
//
//  Returns:      
//
//  Programmer: Kevin Griffin
//  Creation:   February 22, 2021
//
// ****************************************************************************

avtANARIDevice  *
avtANARIRenderer::GetDevice() 
{ 
    if(m_devicePtr) 
        return m_devicePtr.get(); 

    return nullptr;
}

#ifndef CLAMP
# define CLAMP(x, l, h) (x > l ? x < h ? x : h : l)
#endif

// ****************************************************************************
//  Method: avtANARIRenderer::WriteArrayToPPM
//
//  Purpose:
//
//  Returns:      
//
//  Programmer: Kevin Griffin
//  Creation:   February 22, 2021
//
// ****************************************************************************

void
avtANARIRenderer::WriteArrayToPPM(std::string filename, 
                                  const float * image, 
                                  int dimX, int dimY)
{
    std::ofstream outputFile((filename + ".ppm").c_str(), 
                             std::ios::out | std::ios::binary);
    outputFile <<  "P6\n" << dimX << "\n" << dimY << "\n" << 255 << "\n"; 
    for (int y=dimY-1; y>=0; --y)
    {
        for (int x=0; x<dimX; ++x)
        {
            int index = (y * dimX + x)*4;
            char color[3];
            float alpha = image[index + 3];
            color[0] = CLAMP(image[index + 0]*alpha, 0.0f, 1.0f) * 255;
            color[1] = CLAMP(image[index + 1]*alpha, 0.0f, 1.0f) * 255;
            color[2] = CLAMP(image[index + 2]*alpha, 0.0f, 1.0f) * 255;
            outputFile.write(color,3);
        }
    } 
    outputFile.close();
}