# 'Google_test' is the subproject name

# 'lib' is the folder with Google Test sources
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_subdirectory(Google_tests) # это строчка не нужна


file(GLOB CompMathFiles "*Tests.cpp" )
file(GLOB SpecificTasksFiles "*TestsST.cpp" )
foreach(filename ${CompMathFiles})
    get_filename_component (TName ${filename} NAME_WE)
    add_executable("${TName}" ${filename})
    add_test(NAME "${TName}" COMMAND ${filename})
    target_link_libraries(${TName} CompMath gtest gtest_main)
endforeach()

foreach(filename ${SpecificTasksFiles})
    get_filename_component (TName ${filename} NAME_WE)
    add_executable("${TName}" ${filename})
    add_test(NAME "${TName}" COMMAND ${filename})
    target_link_libraries(${TName} SpecificTasks gtest gtest_main)
endforeach()