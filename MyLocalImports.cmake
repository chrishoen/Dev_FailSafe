#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_lib_import_CalcLib _target)

   target_link_libraries(${_target} CalcLib)

endfunction()

function(my_inc_import_CalcLib _target)

   target_include_directories(${_target} PRIVATE $<TARGET_PROPERTY:CalcLib,INTERFACE_INCLUDE_DIRECTORIES>)

endfunction()

