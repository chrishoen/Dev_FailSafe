cmake_minimum_required (VERSION 3.8)

project (FailSafe CXX)
my_find_src_files (src_files FailSafe)
add_executable (FailSafe ${src_files})
my_add_compile_options (FailSafe)
my_add_pch (FailSafe)

my_inc_import_DspLib(FailSafe)
my_inc_import_RisLib(FailSafe)

my_lib_import_DspLib(FailSafe)
my_lib_import_RisLib(FailSafe)

