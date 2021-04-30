# Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
# Project developers.  See the top-level LICENSE file for dates and other
# details.  No copyright assignment is required to contribute to VisIt.

#****************************************************************************
# Modifications:
#   Kevin Griffin, Fri May 3 18:44:57 PDT 2019
#   Add logic to install libraries on OSX correctly.
#
#   Kathleen Biagas, Thu Jul 18 10:41:50 PDT 2019
#   Add special handling of tbb and embree installs for linux.
#  
#   Kevin Griffin, Wed Feb 24 148:31:46 PDT 2021
#   Updated for OSPRay 2.5.0
#
#*****************************************************************************

IF(VISIT_OSPRAY2)
    # -- this is a hack for TBB_ROOT
    IF(NOT DEFINED TBB_ROOT)
      SET(TBB_ROOT ${VISIT_TBB_ROOT})
    ENDIF()
    SET(embree_DIR ${EMBREE_DIR}/lib/cmake/embree-${EMBREE_VERSION})
    SET(rkcommon_DIR ${RKCOMMON_DIR}/lib/cmake/rkcommon-${RKCOMMON_VERSION})
    SET(openvkl_DIR ${OPENVKL_DIR}/lib/cmake/openvkl-${OPENVKL_VERSION})
    MARK_AS_ADVANCED(ospray_DIR)
    MARK_AS_ADVANCED(embree_DIR)
    MARK_AS_ADVANCED(rkcommon_DIR)
    MARK_AS_ADVANCED(openvkl_DIR)

    # setup ospray
    # we have to search for the osprayConfig.cmake file in the ospray install
    # folder. Because ospray sometimes install its library in <...>/lib64
    # folder instead of the <...>/lib folder, we have to check both
    # possibilities
    FIND_PACKAGE(ospray REQUIRED
                 PATHS 
                  ${OSPRAY2_DIR}/lib/cmake/ospray-${OSPRAY2_VERSION}
                  NO_DEFAULT_PATH)
    ADD_DEFINITIONS(-DVISIT_OSPRAY2)
    
    # ospray tries to dlopen the ispc libs at runtime
    # so we need ot make sure those libs exist in
    # ${VISIT_BINARY_DIR}/lib/
    # so developer builds can load them
    # IF( NOT WIN32 )
    #     FOREACH(ospray_lib ${OSPRAY_LIBRARIES})
    #         IF( "${ospray_lib}" MATCHES "ispc")
    #             execute_process(COMMAND ${CMAKE_COMMAND} -E copy
    #                                     ${ospray_lib}
    #                                     ${VISIT_BINARY_DIR}/lib/)
    #         ENDIF()
    #     ENDFOREACH()
    # ENDIF()

    FILE(GLOB OSPRAY_LIBRARIES "${LIBRARY_PATH_PREFIX}*${LIBRARY_SUFFIX}")
    # install ospray libs follow visit's standard
    #
    # -- OSPRAY_LIBRARIES contains also libtbb and libembree, so we dont
    #    have to handle embree and tbb seperately. As for ISPC, since ISPC
    #    is only a compiler and will only be needed when we are compiling
    #    ospray source, we dont have to install ISPC at all here for VisIt.
    #
    # on linux ospray have libraries in a form of:
    #      libospray[xxx].so
    #      libospray[xxx].so.0
    #      libospray[xxx].so.[version]
    #
    # on mac ospray have libraries in a form of:
    #      libospray[xxx].dylib
    #      libospray[xxx].0.dylib
    #      libospray[xxx].[version].dylib
    #
    # on windows
    #      libospray[xxx].lib
    #      libospray[xxx].dll
    #
    IF(NOT VISIT_OSPRAY2_SKIP_INSTALL)
      # -- installing headers  
      INSTALL(DIRECTORY ${OSPRAY2_DIR}/include/ospray
        DESTINATION ${VISIT_INSTALLED_VERSION_INCLUDE}
        FILE_PERMISSIONS OWNER_WRITE OWNER_READ
                         GROUP_WRITE GROUP_READ
                                     WORLD_READ
        DIRECTORY_PERMISSIONS OWNER_WRITE OWNER_READ OWNER_EXECUTE
                              GROUP_WRITE GROUP_READ GROUP_EXECUTE
                                          WORLD_READ WORLD_EXECUTE
        PATTERN ".svn" EXCLUDE)
      # -- installing libs
      FOREACH(l ${OSPRAY_LIBRARIES})
        THIRD_PARTY_INSTALL_LIBRARY(${l})
      ENDFOREACH()
    ENDIF()

    # debug
    MESSAGE(STATUS "OSPRAY2_INCLUDE_DIR: " ${OSPRAY_INCLUDE_DIR})
    MESSAGE(STATUS "OSPRAY2_LIBRARIES: " ${OSPRAY_LIBRARIES})
    MESSAGE(STATUS "OSPRay2 for VisIt: ON")

ELSE(VISIT_OSPRAY2)
    MESSAGE(STATUS "OSPRay2 for VisIt: OFF")
ENDIF(VISIT_OSPRAY2)


