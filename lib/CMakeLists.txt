# Copyright 2011,2012,2016 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.

########################################################################
# Setup library
########################################################################
include(GrPlatform) #define LIB_SUFFIX

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})

list(APPEND ThumbDV_sources
    Encode_sb_impl.cc
    Decode_bs_impl.cc
    DV3000U.cc
)

set(ThumbDV_sources "${ThumbDV_sources}" PARENT_SCOPE)
if(NOT ThumbDV_sources)
	MESSAGE(STATUS "No C++ sources... skipping lib/")
	return()
endif(NOT ThumbDV_sources)

add_library(gnuradio-ThumbDV SHARED ${ThumbDV_sources})
target_link_libraries(gnuradio-ThumbDV ${Boost_LIBRARIES} ${GNURADIO_ALL_LIBRARIES})
set_target_properties(gnuradio-ThumbDV PROPERTIES DEFINE_SYMBOL "gnuradio_ThumbDV_EXPORTS")

if(APPLE)
    set_target_properties(gnuradio-ThumbDV PROPERTIES
        INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/lib"
    )
endif(APPLE)

########################################################################
# Install built library files
########################################################################
include(GrMiscUtils)
GR_LIBRARY_FOO(gnuradio-ThumbDV RUNTIME_COMPONENT "ThumbDV_runtime" DEVEL_COMPONENT "ThumbDV_devel")

########################################################################
# Build and register unit test
########################################################################
include(GrTest)

include_directories(${CPPUNIT_INCLUDE_DIRS})

list(APPEND test_ThumbDV_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/test_ThumbDV.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_ThumbDV.cc
)

add_executable(test-ThumbDV ${test_ThumbDV_sources})

target_link_libraries(
  test-ThumbDV
  ${GNURADIO_RUNTIME_LIBRARIES}
  ${Boost_LIBRARIES}
  ${CPPUNIT_LIBRARIES}
  gnuradio-ThumbDV
)

GR_ADD_TEST(test_ThumbDV test-ThumbDV)

########################################################################
# Print summary
########################################################################
message(STATUS "Using install prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "Building for version: ${VERSION} / ${LIBVER}")

