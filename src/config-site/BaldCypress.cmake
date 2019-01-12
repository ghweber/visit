include(${VISIT_SOURCE_DIR}/config-site/windows.cmake)

# disable some warnings
# 4244 conversion double to float etc
# 4305 truncation from 'double' to 'float', etc
# 4800 'int' forcing value to bool (performance warning)
#ADD_DEFINITIONS(/wd4244 /wd4305 /wd4800)

VISIT_OPTION_DEFAULT(VISIT_INSTALL_PROFILES_TO_HOSTS "llnl" TYPE STRING)
VISIT_OPTION_DEFAULT(VISIT_INSTALL_THIRD_PARTY ON TYPE BOOL)
VISIT_OPTION_DEFAULT(VISIT_PARALLEL OFF TYPE BOOL)
VISIT_OPTION_DEFAULT(VISIT_WINDOWS_APPLICATION OFF TYPE BOOL)
VISIT_OPTION_DEFAULT(VISIT_USE_7ZIP OFF TYPE BOOL)
VISIT_OPTION_DEFAULT(VISIT_NO_ALLBUILD ON TYPE BOOL)
VISIT_OPTION_DEFAULT(VISIT_MSMPI_VERSION "8" TYPE STRING)

SET(CMAKE_SUPPRESS_REGENERATION TRUE)
SET(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY TRUE)
