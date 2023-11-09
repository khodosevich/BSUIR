## Copyright (C) 1991-2009 Altera Corporation
## Your use of Altera Corporation's design tools, logic functions 
## and other software and tools, and its AMPP partner logic 
## functions, and any output files from any of the foregoing 
## (including device programming or simulation files), and any 
## associated documentation or information are expressly subject 
## to the terms and conditions of the Altera Program License 
## Subscription Agreement, Altera MegaCore Function License 
## Agreement, or other applicable license agreement, including, 
## without limitation, that your use is for the sole purpose of 
## programming logic devices manufactured by Altera and sold by 
## Altera or its authorized distributors.  Please refer to the 
## applicable agreement for further details.

## VENDOR "Altera"
## PROGRAM "Quartus II"
## VERSION "Version 9.1 Build 222 10/21/2009 SJ Web Edition"

## DATE "11/09/2023 21:00:13"

## 
## Device: Altera EP1C3T100C6 Package TQFP100
## 

## 
## This Tcl script should be used for PrimeTime (Verilog) only
## 

## This file can be sourced in primetime

set report_default_significant_digits 3
set hierarchy_separator .

set quartus_root "c:/altera/91/quartus/"
set search_path [list . [format "%s%s" $quartus_root "eda/synopsys/primetime/lib"]  ]

set link_path [list *  cyclone_asynch_io_lib.db cyclone_asynch_lcell_lib.db  cyclone_core_mem_lib.db cyclone_lcell_register_lib.db  cyclone_memory_register_lib.db  cyclone_pll_lib.db  alt_vtl.db]

read_verilog  cyclone_all_pt.v 

##########################
## DESIGN ENTRY SECTION ##
##########################

read_verilog  lab4.vo
current_design lab4
link
## Set variable timing_propagate_single_condition_min_slew to false only for versions 2004.06 and earlier
regexp {([1-9][0-9][0-9][0-9]\.[0-9][0-9])} $sh_product_version dummy version
if { [string compare "2004.06" $version ] != -1 } {
   set timing_propagate_single_condition_min_slew false
}
set_operating_conditions -analysis_type single
read_sdf lab4_v.sdo

################################
## TIMING CONSTRAINTS SECTION ##
################################


## Start clock definition ##
# WARNING:  The required clock period is not set. The default value (100 ns) is used. 
create_clock -period 100.000 -waveform {0.000 50.000} [get_ports { clk } ] -name clk  
# WARNING:  The required clock period is not set. The default value (100 ns) is used. 
create_clock -period 100.000 -waveform {0.000 50.000} [get_ports { read } ] -name read  
# WARNING:  The required clock period is not set. The default value (100 ns) is used. 
create_clock -period 100.000 -waveform {0.000 50.000} [get_ports { write } ] -name write  

set_propagated_clock [all_clocks]
set_clock_groups -asynchronous \
-group {clk} \
-group {read} \
-group {write}
## End clock definition ##

## Start create collections ##
## End create collections ##

## Start global settings ##
## End global settings ##

## Start collection commands definition ##

## End collection commands definition ##

## Start individual pin commands definition ##
## End individual pin commands definition ##

## Start Output pin capacitance definition ##
set_load -pin_load 10 [get_ports { ROM_data[0] } ]
set_load -pin_load 10 [get_ports { ROM_data[1] } ]
set_load -pin_load 10 [get_ports { ROM_data[2] } ]
set_load -pin_load 10 [get_ports { ROM_data[3] } ]
set_load -pin_load 10 [get_ports { ROM_data[4] } ]
set_load -pin_load 10 [get_ports { ROM_data[5] } ]
set_load -pin_load 10 [get_ports { ROM_data[6] } ]
set_load -pin_load 10 [get_ports { ROM_data[7] } ]
set_load -pin_load 10 [get_ports { buffer_data[0] } ]
set_load -pin_load 10 [get_ports { buffer_data[1] } ]
set_load -pin_load 10 [get_ports { buffer_data[2] } ]
set_load -pin_load 10 [get_ports { buffer_data[3] } ]
set_load -pin_load 10 [get_ports { buffer_data[4] } ]
set_load -pin_load 10 [get_ports { buffer_data[5] } ]
set_load -pin_load 10 [get_ports { buffer_data[6] } ]
set_load -pin_load 10 [get_ports { buffer_data[7] } ]
set_load -pin_load 10 [get_ports { data[0] } ]
set_load -pin_load 10 [get_ports { data[1] } ]
set_load -pin_load 10 [get_ports { data[2] } ]
set_load -pin_load 10 [get_ports { data[3] } ]
set_load -pin_load 10 [get_ports { data[4] } ]
set_load -pin_load 10 [get_ports { data[5] } ]
set_load -pin_load 10 [get_ports { data[6] } ]
set_load -pin_load 10 [get_ports { data[7] } ]
## End Output pin capacitance definition ##

## Start clock uncertainty definition ##
## End clock uncertainty definition ##

## Start Multicycle and Cut Path definition ##
## End Multicycle and Cut Path definition ##

## Destroy Collections ##

update_timing
