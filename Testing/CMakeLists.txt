
list(APPEND ExternalData_URL_TEMPLATES
  "http://slicer.kitware.com/midas3/api/rest?method=midas.bitstream.download&checksum=%(hash)"
  )
add_test(
    NAME NoArgs
    COMMAND $<TARGET_FILE:ExtractLabelSurfaces>
)
set_tests_properties(NoArgs PROPERTIES WILL_FAIL true)

add_test(
    NAME WrongArg
    COMMAND $<TARGET_FILE:ExtractLabelSurfaces> --loopcheck
)
set_tests_properties(WrongArg PROPERTIES WILL_FAIL true)

add_test(
    NAME PrintHelp
    COMMAND $<TARGET_FILE:ExtractLabelSurfaces> --help
)
add_executable(ExtractLabelSurfacesTest vtkTest.cxx)
target_link_libraries(ExtractLabelSurfacesTest ExtractLabelSurfacesLib)

#add_test(NAME CheckOutputTool1 COMMAND $<TARGET_FILE:ExtractLabelSurfacesTest>
#  --compare
#    DATA{Data/lh_neo-576_labelListName_model.txt}
#    ${CMAKE_CURRENT_BINARY_DIR}/lh.labelList.txt
#  ModuleEntryPoint
#    --extractPointData
#    --labelNameInfo lh.labelList.txt
#    -a colour
#    --vtkLabelFile DATA{Data/neo-0576-1-1-1year-SW-T1-cere-seg.img.lh-rev.img.MiddleSurf.Reg.vtk.AALcolor.vtk}
#)

