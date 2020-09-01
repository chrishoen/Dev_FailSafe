cmake_minimum_required (VERSION 3.8)
#change1
set (CMAKE_USER_MAKE_RULES_OVERRIDE "${CMAKE_CURRENT_LIST_DIR}/MyOverrides.cmake")
include(MyPrecompiledHeader.cmake)
include(MyCodeMacros.cmake)
include(MyGlobalImports.cmake)
include(MyLocalImports.cmake)

project ("Dev_FailSafe")
my_init_global_import_variables()

add_subdirectory ("FailSafe")
return()

add_subdirectory ("FailSafe")
add_subdirectory ("Test")
return()

