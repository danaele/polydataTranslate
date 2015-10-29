cmake_minimum_required(VERSION 2.8)

#File to compare
#add_executable(CompareFiles CompareFiles.cxx)

#File exists
#add_executable(FileExistTestMain FileExistTestMain.cxx)

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
#add_test(
#    NAME
#    COMMAND

#)


##This test should fail
#add_test(
#    NAME
#    COMMAND

#)
# set_tests_properties(WrongFileToCompare PROPERTIES WILL_FAIL true)
