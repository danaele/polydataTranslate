cmake_minimum_required(VERSION 2.8)
 
PROJECT(PolydataTranslate)
option(BUILD_TESTING "Build the testing tree" OFF)

# Find SlicerExecutionModel
find_package(SlicerExecutionModel REQUIRED)
include(${SlicerExecutionModel_USE_FILE})

#Find VTK 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})


set(PolydataTranslate_SOURCE PolydataTranslate.cxx)

set(PolydataTranslate_HEADER PolydataTranslate.h)

SEMMacroBuildCLI(
  NAME PolydataTranslate
  EXECUTABLE_ONLY
  ADDITIONAL_SRCS ${PolydataTranslate_SOURCE}
  TARGET_LIBRARIES ${VTK_LIBRARIES}
  )

if(BUILD_TESTING)
 include(CTest)
 add_subdirectory(Testing)
endif()

