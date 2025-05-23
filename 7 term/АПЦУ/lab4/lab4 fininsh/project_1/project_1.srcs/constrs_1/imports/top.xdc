# LEDs on AC701 main board
set_property PACKAGE_PIN M26 [get_ports LED_out[0]]
set_property IOSTANDARD LVCMOS33 [get_ports LED_out[0]]
set_property PACKAGE_PIN T24 [get_ports LED_out[1]]
set_property IOSTANDARD LVCMOS33 [get_ports LED_out[1]]
set_property PACKAGE_PIN T25 [get_ports LED_out[2]]
set_property IOSTANDARD LVCMOS33 [get_ports LED_out[2]]
set_property PACKAGE_PIN R26 [get_ports LED_out[3]]
set_property IOSTANDARD LVCMOS33 [get_ports LED_out[3]]

# LEDs on external board
set_property PACKAGE_PIN F25 [get_ports LED_out[4]]
set_property IOSTANDARD LVCMOS25 [get_ports LED_out[4]]
set_property PACKAGE_PIN G25 [get_ports LED_out[5]]
set_property IOSTANDARD LVCMOS25 [get_ports LED_out[5]]
set_property PACKAGE_PIN G26 [get_ports LED_out[6]]
set_property IOSTANDARD LVCMOS25 [get_ports LED_out[6]]
set_property PACKAGE_PIN H26 [get_ports LED_out[7]]
set_property IOSTANDARD LVCMOS25 [get_ports LED_out[7]]

# Pushbuttons
set_property PACKAGE_PIN P6 [get_ports IN_buttons[0]]
set_property IOSTANDARD LVCMOS15 [get_ports IN_buttons[0]]
set_property PACKAGE_PIN R5 [get_ports IN_buttons[1]]
set_property IOSTANDARD SSTL15 [get_ports IN_buttons[1]]
set_property PACKAGE_PIN U6 [get_ports IN_buttons[2]]
set_property IOSTANDARD SSTL15 [get_ports IN_buttons[2]]
set_property PACKAGE_PIN U5 [get_ports IN_buttons[3]]
set_property IOSTANDARD SSTL15 [get_ports IN_buttons[3]]
set_property PACKAGE_PIN T5 [get_ports IN_buttons[4]]
set_property IOSTANDARD SSTL15 [get_ports IN_buttons[4]]

# DIP switches
set_property PACKAGE_PIN R8 [get_ports IN_switches[0]]
set_property IOSTANDARD SSTL15 [get_ports IN_switches[0]]
set_property PACKAGE_PIN P8 [get_ports IN_switches[1]]
set_property IOSTANDARD SSTL15 [get_ports IN_switches[1]]
set_property PACKAGE_PIN R7 [get_ports IN_switches[2]]
set_property IOSTANDARD SSTL15 [get_ports IN_switches[2]]
set_property PACKAGE_PIN R6 [get_ports IN_switches[3]]
set_property IOSTANDARD SSTL15 [get_ports IN_switches[3]]

# System clock 200 MHz
set_property PACKAGE_PIN R3 [get_ports sysclk_p]
set_property IOSTANDARD LVDS_25 [get_ports sysclk_p]
set_property PACKAGE_PIN P3 [get_ports sysclk_n]
set_property IOSTANDARD LVDS_25 [get_ports sysclk_n]


