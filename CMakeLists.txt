cmake_minimum_required(VERSION 2.8)
 
PROJECT(ExtractLabelSurfaces)
option(BUILD_TESTING "Build the testing tree" OFF)

find_package(RapidJSON REQUIRED)
include_directories("${RAPIDJSON_INCLUDE_DIRS}")

# Find SlicerExecutionModel
find_package(SlicerExecutionModel REQUIRED)
include(${SlicerExecutionModel_USE_FILE})

#Find VTK 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})


set(ExtractLabelSurfaces_SOURCE ExtractLabelSurfaces.cxx)

set(ExtractLabelSurfaces_HEADER ExtractLabelSurfaces.h)

SEMMacroBuildCLI(
  NAME ExtractLabelSurfaces
  EXECUTABLE_ONLY
  ADDITIONAL_SRCS ${ExtractLabelSurfaces_SOURCE}
  TARGET_LIBRARIES ${VTK_LIBRARIES}
  )

if(BUILD_TESTING)
 include(CTest)
 add_subdirectory(Testing)
endif()

