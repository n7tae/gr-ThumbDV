INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_THUMBDV ThumbDV)

FIND_PATH(
    THUMBDV_INCLUDE_DIRS
    NAMES ThumbDV/api.h
    HINTS $ENV{THUMBDV_DIR}/include
        ${PC_THUMBDV_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    THUMBDV_LIBRARIES
    NAMES gnuradio-ThumbDV
    HINTS $ENV{THUMBDV_DIR}/lib
        ${PC_THUMBDV_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(THUMBDV DEFAULT_MSG THUMBDV_LIBRARIES THUMBDV_INCLUDE_DIRS)
MARK_AS_ADVANCED(THUMBDV_LIBRARIES THUMBDV_INCLUDE_DIRS)

