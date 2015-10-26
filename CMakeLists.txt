cmake_minimum_required(VERSION 2.8)
 
PROJECT(ExtractLabelSurfaces)
option(BUILD_TESTING "Build the testing tree" OFF)

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
 
if(VTK_LIBRARIES)
  target_link_libraries(ExtractLabelSurfaces ${VTK_LIBRARIES})
else()
  target_link_libraries(ExtractLabelSurfaces vtkHybrid vtkWidgets)
endif()

if(BUILD_TESTING)
 include(CTest)
 ADD_SUBDIRECTORY(Testing)
endif()

