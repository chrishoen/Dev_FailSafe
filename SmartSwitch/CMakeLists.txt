cmake_minimum_required (VERSION 3.8)

project (SmartSwitch CXX)
my_find_src_files (src_files SmartSwitch)
add_executable (SmartSwitch ${src_files})
my_add_compile_options (SmartSwitch)
my_add_pch (SmartSwitch)

my_inc_import_DspLib(SmartSwitch)
my_inc_import_RisLib(SmartSwitch)

my_lib_import_DspLib(SmartSwitch)
my_lib_import_RisLib(SmartSwitch)

