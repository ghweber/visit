// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

// ************************************************************************* //
//                           avtANARIRenderer.h                              //
// ************************************************************************* //

#ifndef AVT_ANARI_RENDERER_H
#define AVT_ANARI_RENDERER_H

#include <filters_exports.h>

#include <avtANARIDevice.h>

#include <memory>

namespace avt
{
    namespace anari
    {
        // Device Scoped Enums
        enum class DeviceType 
        {
            OSPRAY,
            USD,
            NVGL,
            OPTIX,
            NONE,
            UNKNOWN
        };
    }
}

using DeviceType = avt::anari::DeviceType;

// ****************************************************************************
//  Class: avtANARIVolumeRenderer
//
//  Purpose:
//      
//
//  Programmer: Kevin Griffin
//  Creation:   February 22, 2021
//
//  Modifications:
//
//
// ****************************************************************************

class AVTFILTERS_API avtANARIRenderer
{
public:
    static avtANARIDevice   *GetDevice();
    static void             SetDeviceType(const DeviceType);
    static DeviceType       GetDeviceType();
    static const char       *GetDeviceTypeStr();
    static void             WriteArrayToPPM(std::string, const float *, int, int);

private:
    static DeviceType m_deviceType;
    static std::unique_ptr<avtANARIDevice> m_devicePtr;
};

#endif
