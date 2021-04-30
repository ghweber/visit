# Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
# Project developers.  See the top-level LICENSE file for dates and other
# details.  No copyright assignment is required to contribute to VisIt.

#****************************************************************************
# Modifications:
#
#*****************************************************************************

IF(VISIT_ANARI) 
    # Find and load ANARI settings using Config mode which will skip module 
    # mode and immediately look for the anariConfig.cmake file
    FIND_PACKAGE(anari REQUIRED 
                 CONFIG
                 PATHS ${ANARI_DIR}/lib/cmake/anari-${ANARI_VERSION}
                 NO_DEFAULT_PATH)
    ADD_DEFINITIONS(-DVISIT_ANARI)

    IF(NOT VISIT_ANARI_SKIP_INSTALL)
        # Install libraries
        THIRD_PARTY_INSTALL_LIBRARY(${ANARI_DIR}/lib/libanari.so)
        #SET(anari_libs libanari_module_ospray.so libanari.so)
        SET(backends ospray)
        FOREACH(module ${backends})
            THIRD_PARTY_INSTALL_LIBRARY(${ANARI_DIR}/lib/libanari_module_${module}.so)
        ENDFOREACH()
        # Install Headers
        INSTALL(DIRECTORY ${ANARI_DIR}/include/anari
            DESTINATION ${VISIT_INSTALLED_VERSION_INCLUDE}
            FILE_PERMISSIONS OWNER_WRITE OWNER_READ
                             GROUP_WRITE GROUP_READ
                                         WORLD_READ
            DIRECTORY_PERMISSIONS OWNER_WRITE OWNER_READ OWNER_EXECUTE
                                  GROUP_WRITE GROUP_READ GROUP_EXECUTE
                                              WORLD_READ WORLD_EXECUTE) 
        # Add ANARI archives (lib*.a)
        FILE(GLOB ANARI_ARCHIVES "${ANARI_DIR}/lib/*.a")
        FOREACH(T ${ANARI_ARCHIVES})
            INSTALL(FILES ${T}
                DESTINATION ${VISIT_INSTALLED_VERSION_ARCHIVES}
                PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
                            GROUP_READ GROUP_WRITE GROUP_EXECUTE
                            WORLD_READ             WORLD_EXECUTE
                CONFIGURATIONS "" None Debug Release RelWithDebInfo MinSizeRel)
        ENDFOREACH(T)       
    ENDIF(NOT VISIT_ANARI_SKIP_INSTALL)

    # Debug
    GET_TARGET_PROPERTY(ilr anari::anari IMPORTED_LOCATION_RELEASE)
    MESSAGE(STATUS "ANARI_ILR: " ${ilr})
    MESSAGE(STATUS "ANARI_LIBRARIES: " ${ANARI_LIBRARIES})
    MESSAGE(STATUS "ANARI for VisIt: ON")
ELSE(VISIT_ANARI)
    MESSAGE(STATUS "ANARI for VisIt: OFF")
ENDIF(VISIT_ANARI)