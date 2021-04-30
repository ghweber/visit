// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

// ************************************************************************* //
//                           avtANARIDevice.h                                //
// ************************************************************************* //

#ifndef AVT_ANARI_DEVICE_H
#define AVT_ANARI_DEVICE_H

#include <anari/anari_cpp.h>

namespace avt 
{
    namespace anari 
    {
        enum class DataType 
        {
            GEOMETRY,
            VOLUME
        };

        enum class RendererType
        {
            SCIVIS,
            AO,
            PATHTRACER
        };
    }   // namespace anari
}   // namespace avt

class avtANARIDevice
{
public:
    virtual ~avtANARIDevice() = default;
    virtual const char  *GetDeviceType() = 0;
};

#endif