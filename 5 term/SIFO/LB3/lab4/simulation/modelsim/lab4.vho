-- Copyright (C) 1991-2009 Altera Corporation
-- Your use of Altera Corporation's design tools, logic functions 
-- and other software and tools, and its AMPP partner logic 
-- functions, and any output files from any of the foregoing 
-- (including device programming or simulation files), and any 
-- associated documentation or information are expressly subject 
-- to the terms and conditions of the Altera Program License 
-- Subscription Agreement, Altera MegaCore Function License 
-- Agreement, or other applicable license agreement, including, 
-- without limitation, that your use is for the sole purpose of 
-- programming logic devices manufactured by Altera and sold by 
-- Altera or its authorized distributors.  Please refer to the 
-- applicable agreement for further details.

-- VENDOR "Altera"
-- PROGRAM "Quartus II"
-- VERSION "Version 9.1 Build 222 10/21/2009 SJ Web Edition"

-- DATE "11/09/2023 21:00:13"

-- 
-- Device: Altera EP1C3T100C6 Package TQFP100
-- 

-- 
-- This VHDL file should be used for ModelSim-Altera (VHDL) only
-- 

LIBRARY CYCLONE;
LIBRARY IEEE;
USE CYCLONE.CYCLONE_COMPONENTS.ALL;
USE IEEE.STD_LOGIC_1164.ALL;

ENTITY 	lab4 IS
    PORT (
	buffer_data : OUT std_logic_vector(7 DOWNTO 0);
	read : IN std_logic;
	clk : IN std_logic;
	write : IN std_logic;
	address : IN std_logic_vector(4 DOWNTO 0);
	\gnd\ : IN std_logic;
	data : OUT std_logic_vector(7 DOWNTO 0);
	ROM_data : OUT std_logic_vector(7 DOWNTO 0)
	);
END lab4;

-- Design Ports Information
-- data[7]	=>  Location: PIN_23,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
-- data[6]	=>  Location: PIN_41,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
-- data[5]	=>  Location: PIN_100,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
-- data[4]	=>  Location: PIN_77,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
-- data[3]	=>  Location: PIN_48,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
-- data[2]	=>  Location: PIN_89,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
-- data[1]	=>  Location: PIN_85,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
-- data[0]	=>  Location: PIN_78,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
-- buffer_data[7]	=>  Location: PIN_90,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
-- buffer_data[6]	=>  Location: PIN_92,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
-- buffer_data[5]	=>  Location: PIN_88,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
-- buffer_data[4]	=>  Location: PIN_86,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
-- buffer_data[3]	=>  Location: PIN_79,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
-- buffer_data[2]	=>  Location: PIN_84,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
-- buffer_data[1]	=>  Location: PIN_91,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
-- buffer_data[0]	=>  Location: PIN_99,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
-- ROM_data[7]	=>  Location: PIN_76,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
-- ROM_data[6]	=>  Location: PIN_37,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
-- ROM_data[5]	=>  Location: PIN_71,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
-- ROM_data[4]	=>  Location: PIN_69,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
-- ROM_data[3]	=>  Location: PIN_73,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
-- ROM_data[2]	=>  Location: PIN_72,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
-- ROM_data[1]	=>  Location: PIN_38,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
-- ROM_data[0]	=>  Location: PIN_53,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
-- gnd	=>  Location: PIN_1,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
-- read	=>  Location: PIN_5,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
-- write	=>  Location: PIN_3,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
-- clk	=>  Location: PIN_10,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
-- address[0]	=>  Location: PIN_4,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
-- address[1]	=>  Location: PIN_22,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
-- address[2]	=>  Location: PIN_24,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
-- address[3]	=>  Location: PIN_87,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
-- address[4]	=>  Location: PIN_21,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default

ARCHITECTURE structure OF lab4 IS
SIGNAL gnd : std_logic := '0';
SIGNAL vcc : std_logic := '1';
SIGNAL unknown : std_logic := 'X';
SIGNAL devoe : std_logic := '1';
SIGNAL devclrn : std_logic := '1';
SIGNAL devpor : std_logic := '1';
SIGNAL ww_devoe : std_logic;
SIGNAL ww_devclrn : std_logic;
SIGNAL ww_devpor : std_logic;
SIGNAL ww_buffer_data : std_logic_vector(7 DOWNTO 0);
SIGNAL ww_read : std_logic;
SIGNAL ww_clk : std_logic;
SIGNAL ww_write : std_logic;
SIGNAL ww_address : std_logic_vector(4 DOWNTO 0);
SIGNAL \ww_gnd\ : std_logic;
SIGNAL ww_data : std_logic_vector(7 DOWNTO 0);
SIGNAL ww_ROM_data : std_logic_vector(7 DOWNTO 0);
SIGNAL \inst|inst|altsyncram_component|auto_generated|ram_block1a7_PORTAADDR_bus\ : std_logic_vector(4 DOWNTO 0);
SIGNAL \inst|inst|altsyncram_component|auto_generated|ram_block1a7_PORTADATAOUT_bus\ : std_logic_vector(7 DOWNTO 0);
SIGNAL \inst1|inst|sram|ram_block|auto_generated|ram_block1a7_PORTADATAIN_bus\ : std_logic_vector(7 DOWNTO 0);
SIGNAL \inst1|inst|sram|ram_block|auto_generated|ram_block1a7_PORTAADDR_bus\ : std_logic_vector(4 DOWNTO 0);
SIGNAL \inst1|inst|sram|ram_block|auto_generated|ram_block1a7_PORTADATAOUT_bus\ : std_logic_vector(7 DOWNTO 0);
SIGNAL \inst1|inst|_~0_combout\ : std_logic;
SIGNAL \inst7|inst~combout\ : std_logic;
SIGNAL \clk~combout\ : std_logic;
SIGNAL \write~combout\ : std_logic;
SIGNAL \read~combout\ : std_logic;
SIGNAL \gnd~combout\ : std_logic;
SIGNAL \inst1|inst|datatri[7]~9_combout\ : std_logic;
SIGNAL \inst1|inst|datatri[7]~10_combout\ : std_logic;
SIGNAL \inst1|inst|datatri[0]~23_combout\ : std_logic;
SIGNAL \inst1|inst|datatri[0]~24_combout\ : std_logic;
SIGNAL \inst1|inst|datatri[1]~21_combout\ : std_logic;
SIGNAL \inst1|inst|datatri[1]~22_combout\ : std_logic;
SIGNAL \inst1|inst|datatri[2]~19_combout\ : std_logic;
SIGNAL \inst1|inst|datatri[2]~20_combout\ : std_logic;
SIGNAL \inst1|inst|datatri[3]~17_combout\ : std_logic;
SIGNAL \inst1|inst|datatri[3]~18_combout\ : std_logic;
SIGNAL \inst1|inst|datatri[4]~15_combout\ : std_logic;
SIGNAL \inst1|inst|datatri[4]~16_combout\ : std_logic;
SIGNAL \inst1|inst|datatri[5]~13_combout\ : std_logic;
SIGNAL \inst1|inst|datatri[5]~14_combout\ : std_logic;
SIGNAL \inst1|inst|datatri[6]~11_combout\ : std_logic;
SIGNAL \inst1|inst|datatri[6]~12_combout\ : std_logic;
SIGNAL \inst1|inst|datatri[7]~8_combout\ : std_logic;
SIGNAL \inst1|inst|datatri[7]~25_combout\ : std_logic;
SIGNAL \inst1|inst|datatri[6]~26_combout\ : std_logic;
SIGNAL \inst1|inst|datatri[5]~27_combout\ : std_logic;
SIGNAL \inst1|inst|datatri[4]~28_combout\ : std_logic;
SIGNAL \inst1|inst|datatri[3]~29_combout\ : std_logic;
SIGNAL \inst1|inst|datatri[2]~30_combout\ : std_logic;
SIGNAL \inst1|inst|datatri[1]~31_combout\ : std_logic;
SIGNAL \inst1|inst|datatri[0]~32_combout\ : std_logic;
SIGNAL \inst1|inst|sram|ram_block|auto_generated|q_a\ : std_logic_vector(7 DOWNTO 0);
SIGNAL \inst|inst|altsyncram_component|auto_generated|q_a\ : std_logic_vector(7 DOWNTO 0);
SIGNAL \inst7|inst1|lpm_ff_component|dffs\ : std_logic_vector(7 DOWNTO 0);
SIGNAL \address~combout\ : std_logic_vector(4 DOWNTO 0);
SIGNAL \ALT_INV_clk~combout\ : std_logic;

BEGIN

buffer_data <= ww_buffer_data;
ww_read <= read;
ww_clk <= clk;
ww_write <= write;
ww_address <= address;
\ww_gnd\ <= \gnd\;
data <= ww_data;
ROM_data <= ww_ROM_data;
ww_devoe <= devoe;
ww_devclrn <= devclrn;
ww_devpor <= devpor;

\inst|inst|altsyncram_component|auto_generated|ram_block1a7_PORTAADDR_bus\ <= (\address~combout\(4) & \address~combout\(3) & \address~combout\(2) & \address~combout\(1) & \address~combout\(0));

\inst|inst|altsyncram_component|auto_generated|q_a\(7) <= \inst|inst|altsyncram_component|auto_generated|ram_block1a7_PORTADATAOUT_bus\(0);
\inst|inst|altsyncram_component|auto_generated|q_a\(6) <= \inst|inst|altsyncram_component|auto_generated|ram_block1a7_PORTADATAOUT_bus\(1);
\inst|inst|altsyncram_component|auto_generated|q_a\(5) <= \inst|inst|altsyncram_component|auto_generated|ram_block1a7_PORTADATAOUT_bus\(2);
\inst|inst|altsyncram_component|auto_generated|q_a\(4) <= \inst|inst|altsyncram_component|auto_generated|ram_block1a7_PORTADATAOUT_bus\(3);
\inst|inst|altsyncram_component|auto_generated|q_a\(3) <= \inst|inst|altsyncram_component|auto_generated|ram_block1a7_PORTADATAOUT_bus\(4);
\inst|inst|altsyncram_component|auto_generated|q_a\(2) <= \inst|inst|altsyncram_component|auto_generated|ram_block1a7_PORTADATAOUT_bus\(5);
\inst|inst|altsyncram_component|auto_generated|q_a\(1) <= \inst|inst|altsyncram_component|auto_generated|ram_block1a7_PORTADATAOUT_bus\(6);
\inst|inst|altsyncram_component|auto_generated|q_a\(0) <= \inst|inst|altsyncram_component|auto_generated|ram_block1a7_PORTADATAOUT_bus\(7);

\inst1|inst|sram|ram_block|auto_generated|ram_block1a7_PORTADATAIN_bus\ <= (\inst1|inst|datatri[0]~24_combout\ & \inst1|inst|datatri[1]~22_combout\ & \inst1|inst|datatri[2]~20_combout\ & \inst1|inst|datatri[3]~18_combout\ & 
\inst1|inst|datatri[4]~16_combout\ & \inst1|inst|datatri[5]~14_combout\ & \inst1|inst|datatri[6]~12_combout\ & \inst1|inst|datatri[7]~10_combout\);

\inst1|inst|sram|ram_block|auto_generated|ram_block1a7_PORTAADDR_bus\ <= (\address~combout\(4) & \address~combout\(3) & \address~combout\(2) & \address~combout\(1) & \address~combout\(0));

\inst1|inst|sram|ram_block|auto_generated|q_a\(7) <= \inst1|inst|sram|ram_block|auto_generated|ram_block1a7_PORTADATAOUT_bus\(0);
\inst1|inst|sram|ram_block|auto_generated|q_a\(6) <= \inst1|inst|sram|ram_block|auto_generated|ram_block1a7_PORTADATAOUT_bus\(1);
\inst1|inst|sram|ram_block|auto_generated|q_a\(5) <= \inst1|inst|sram|ram_block|auto_generated|ram_block1a7_PORTADATAOUT_bus\(2);
\inst1|inst|sram|ram_block|auto_generated|q_a\(4) <= \inst1|inst|sram|ram_block|auto_generated|ram_block1a7_PORTADATAOUT_bus\(3);
\inst1|inst|sram|ram_block|auto_generated|q_a\(3) <= \inst1|inst|sram|ram_block|auto_generated|ram_block1a7_PORTADATAOUT_bus\(4);
\inst1|inst|sram|ram_block|auto_generated|q_a\(2) <= \inst1|inst|sram|ram_block|auto_generated|ram_block1a7_PORTADATAOUT_bus\(5);
\inst1|inst|sram|ram_block|auto_generated|q_a\(1) <= \inst1|inst|sram|ram_block|auto_generated|ram_block1a7_PORTADATAOUT_bus\(6);
\inst1|inst|sram|ram_block|auto_generated|q_a\(0) <= \inst1|inst|sram|ram_block|auto_generated|ram_block1a7_PORTADATAOUT_bus\(7);
\ALT_INV_clk~combout\ <= NOT \clk~combout\;

-- Location: LC_X6_Y10_N6
\inst1|inst|_~0\ : cyclone_lcell
-- Equation(s):
-- \inst1|inst|_~0_combout\ = (\write~combout\ & (((!\gnd~combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "00aa",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \write~combout\,
	datad => \gnd~combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \inst1|inst|_~0_combout\);

-- Location: LC_X9_Y12_N2
\inst7|inst\ : cyclone_lcell
-- Equation(s):
-- \inst7|inst~combout\ = LCELL(((\clk~combout\ & ((\write~combout\) # (\read~combout\)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f0c0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \write~combout\,
	datac => \clk~combout\,
	datad => \read~combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \inst7|inst~combout\);

-- Location: PIN_10,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
\clk~I\ : cyclone_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "input",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => GND,
	padio => ww_clk,
	combout => \clk~combout\);

-- Location: PIN_3,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
\write~I\ : cyclone_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "input",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => GND,
	padio => ww_write,
	combout => \write~combout\);

-- Location: PIN_5,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
\read~I\ : cyclone_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "input",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => GND,
	padio => ww_read,
	combout => \read~combout\);

-- Location: PIN_1,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
\gnd~I\ : cyclone_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "input",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => GND,
	padio => \ww_gnd\,
	combout => \gnd~combout\);

-- Location: LC_X5_Y11_N8
\inst1|inst|datatri[7]~9\ : cyclone_lcell
-- Equation(s):
-- \inst1|inst|datatri[7]~9_combout\ = ((\write~combout\) # ((\read~combout\) # (\gnd~combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "fffc",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \write~combout\,
	datac => \read~combout\,
	datad => \gnd~combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \inst1|inst|datatri[7]~9_combout\);

-- Location: LC_X5_Y11_N9
\inst7|inst1|lpm_ff_component|dffs[7]\ : cyclone_lcell
-- Equation(s):
-- \inst7|inst1|lpm_ff_component|dffs\(7) = DFFEAS((((\inst1|inst|datatri[7]~10_combout\) # (!\read~combout\))), GLOBAL(\inst7|inst~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "ff0f",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \inst7|inst~combout\,
	datac => \read~combout\,
	datad => \inst1|inst|datatri[7]~10_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \inst7|inst1|lpm_ff_component|dffs\(7));

-- Location: LC_X5_Y11_N0
\inst1|inst|datatri[7]~10\ : cyclone_lcell
-- Equation(s):
-- \inst1|inst|datatri[7]~10_combout\ = ((\inst1|inst|datatri[7]~8_combout\ & ((\inst7|inst1|lpm_ff_component|dffs\(7)) # (!\write~combout\)))) # (!\inst1|inst|datatri[7]~9_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f755",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \inst1|inst|datatri[7]~9_combout\,
	datab => \write~combout\,
	datac => \inst7|inst1|lpm_ff_component|dffs\(7),
	datad => \inst1|inst|datatri[7]~8_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \inst1|inst|datatri[7]~10_combout\);

-- Location: PIN_4,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
\address[0]~I\ : cyclone_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "input",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => GND,
	padio => ww_address(0),
	combout => \address~combout\(0));

-- Location: PIN_22,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
\address[1]~I\ : cyclone_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "input",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => GND,
	padio => ww_address(1),
	combout => \address~combout\(1));

-- Location: PIN_24,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
\address[2]~I\ : cyclone_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "input",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => GND,
	padio => ww_address(2),
	combout => \address~combout\(2));

-- Location: PIN_87,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
\address[3]~I\ : cyclone_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "input",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => GND,
	padio => ww_address(3),
	combout => \address~combout\(3));

-- Location: PIN_21,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
\address[4]~I\ : cyclone_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "input",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => GND,
	padio => ww_address(4),
	combout => \address~combout\(4));

-- Location: M4K_X13_Y10
\inst1|inst|sram|ram_block|auto_generated|ram_block1a7\ : cyclone_ram_block
-- pragma translate_off
GENERIC MAP (
	mem_init0 => X"0000000000000000000000000000000000000000000000000000000000000000",
	data_interleave_offset_in_bits => 1,
	data_interleave_width_in_bits => 1,
	init_file => "./lab4ramhex.hex",
	init_file_layout => "port_a",
	logical_ram_name => "RAM:inst1|lpm_ram_io:inst|altram:sram|altsyncram:ram_block|altsyncram_0o91:auto_generated|ALTSYNCRAM",
	operation_mode => "single_port",
	port_a_address_clear => "none",
	port_a_address_width => 5,
	port_a_byte_enable_clear => "none",
	port_a_byte_enable_clock => "none",
	port_a_data_in_clear => "none",
	port_a_data_out_clear => "none",
	port_a_data_out_clock => "clock1",
	port_a_data_width => 8,
	port_a_first_address => 0,
	port_a_first_bit_number => 0,
	port_a_last_address => 31,
	port_a_logical_ram_depth => 32,
	port_a_logical_ram_width => 8,
	port_a_write_enable_clear => "none",
	port_b_address_width => 5,
	port_b_data_width => 8,
	ram_block_type => "M4K")
-- pragma translate_on
PORT MAP (
	portawe => \inst1|inst|_~0_combout\,
	clk0 => \clk~combout\,
	clk1 => \ALT_INV_clk~combout\,
	portadatain => \inst1|inst|sram|ram_block|auto_generated|ram_block1a7_PORTADATAIN_bus\,
	portaaddr => \inst1|inst|sram|ram_block|auto_generated|ram_block1a7_PORTAADDR_bus\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	portadataout => \inst1|inst|sram|ram_block|auto_generated|ram_block1a7_PORTADATAOUT_bus\);

-- Location: M4K_X13_Y11
\inst|inst|altsyncram_component|auto_generated|ram_block1a7\ : cyclone_ram_block
-- pragma translate_off
GENERIC MAP (
	mem_init0 => X"04F878B838D8589818E868A828C8488808F070B030D0509010E060A020C04080",
	data_interleave_offset_in_bits => 1,
	data_interleave_width_in_bits => 1,
	init_file => "lab4romhex.hex",
	init_file_layout => "port_a",
	logical_ram_name => "ROM:inst|lpm_rom0:inst|altsyncram:altsyncram_component|altsyncram_c341:auto_generated|ALTSYNCRAM",
	operation_mode => "rom",
	port_a_address_clear => "none",
	port_a_address_width => 5,
	port_a_byte_enable_clear => "none",
	port_a_byte_enable_clock => "none",
	port_a_data_in_clear => "none",
	port_a_data_out_clear => "none",
	port_a_data_out_clock => "none",
	port_a_data_width => 8,
	port_a_first_address => 0,
	port_a_first_bit_number => 0,
	port_a_last_address => 31,
	port_a_logical_ram_depth => 32,
	port_a_logical_ram_width => 8,
	port_a_write_enable_clear => "none",
	port_a_write_enable_clock => "none",
	port_b_address_width => 5,
	port_b_data_width => 8,
	ram_block_type => "M4K")
-- pragma translate_on
PORT MAP (
	clk0 => \ALT_INV_clk~combout\,
	portaaddr => \inst|inst|altsyncram_component|auto_generated|ram_block1a7_PORTAADDR_bus\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	portadataout => \inst|inst|altsyncram_component|auto_generated|ram_block1a7_PORTADATAOUT_bus\);

-- Location: LC_X5_Y11_N6
\inst7|inst1|lpm_ff_component|dffs[0]\ : cyclone_lcell
-- Equation(s):
-- \inst7|inst1|lpm_ff_component|dffs\(0) = DFFEAS((((\inst1|inst|datatri[0]~24_combout\) # (!\read~combout\))), GLOBAL(\inst7|inst~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "ff0f",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \inst7|inst~combout\,
	datac => \read~combout\,
	datad => \inst1|inst|datatri[0]~24_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \inst7|inst1|lpm_ff_component|dffs\(0));

-- Location: LC_X5_Y11_N4
\inst1|inst|datatri[0]~23\ : cyclone_lcell
-- Equation(s):
-- \inst1|inst|datatri[0]~23_combout\ = (\read~combout\ & (\inst|inst|altsyncram_component|auto_generated|q_a\(0) & ((\inst7|inst1|lpm_ff_component|dffs\(0)) # (!\write~combout\)))) # (!\read~combout\ & (((\inst7|inst1|lpm_ff_component|dffs\(0))) # 
-- (!\write~combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f531",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \read~combout\,
	datab => \write~combout\,
	datac => \inst|inst|altsyncram_component|auto_generated|q_a\(0),
	datad => \inst7|inst1|lpm_ff_component|dffs\(0),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \inst1|inst|datatri[0]~23_combout\);

-- Location: LC_X5_Y11_N5
\inst1|inst|datatri[0]~24\ : cyclone_lcell
-- Equation(s):
-- \inst1|inst|datatri[0]~24_combout\ = ((\inst1|inst|datatri[0]~23_combout\ & ((\inst1|inst|sram|ram_block|auto_generated|q_a\(0)) # (!\gnd~combout\)))) # (!\inst1|inst|datatri[7]~9_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "bf0f",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \inst1|inst|sram|ram_block|auto_generated|q_a\(0),
	datab => \gnd~combout\,
	datac => \inst1|inst|datatri[7]~9_combout\,
	datad => \inst1|inst|datatri[0]~23_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \inst1|inst|datatri[0]~24_combout\);

-- Location: LC_X9_Y12_N5
\inst7|inst1|lpm_ff_component|dffs[1]\ : cyclone_lcell
-- Equation(s):
-- \inst7|inst1|lpm_ff_component|dffs\(1) = DFFEAS((((\inst1|inst|datatri[1]~22_combout\) # (!\read~combout\))), GLOBAL(\inst7|inst~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f0ff",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \inst7|inst~combout\,
	datac => \inst1|inst|datatri[1]~22_combout\,
	datad => \read~combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \inst7|inst1|lpm_ff_component|dffs\(1));

-- Location: LC_X12_Y10_N8
\inst1|inst|datatri[1]~21\ : cyclone_lcell
-- Equation(s):
-- \inst1|inst|datatri[1]~21_combout\ = (\read~combout\ & (\inst|inst|altsyncram_component|auto_generated|q_a\(1) & ((\inst7|inst1|lpm_ff_component|dffs\(1)) # (!\write~combout\)))) # (!\read~combout\ & (((\inst7|inst1|lpm_ff_component|dffs\(1))) # 
-- (!\write~combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f351",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \read~combout\,
	datab => \write~combout\,
	datac => \inst7|inst1|lpm_ff_component|dffs\(1),
	datad => \inst|inst|altsyncram_component|auto_generated|q_a\(1),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \inst1|inst|datatri[1]~21_combout\);

-- Location: LC_X12_Y10_N9
\inst1|inst|datatri[1]~22\ : cyclone_lcell
-- Equation(s):
-- \inst1|inst|datatri[1]~22_combout\ = ((\inst1|inst|datatri[1]~21_combout\ & ((\inst1|inst|sram|ram_block|auto_generated|q_a\(1)) # (!\gnd~combout\)))) # (!\inst1|inst|datatri[7]~9_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "df55",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \inst1|inst|datatri[7]~9_combout\,
	datab => \inst1|inst|sram|ram_block|auto_generated|q_a\(1),
	datac => \gnd~combout\,
	datad => \inst1|inst|datatri[1]~21_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \inst1|inst|datatri[1]~22_combout\);

-- Location: LC_X12_Y10_N1
\inst7|inst1|lpm_ff_component|dffs[2]\ : cyclone_lcell
-- Equation(s):
-- \inst7|inst1|lpm_ff_component|dffs\(2) = DFFEAS((((\inst1|inst|datatri[2]~20_combout\))) # (!\read~combout\), GLOBAL(\inst7|inst~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "ff55",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \inst7|inst~combout\,
	dataa => \read~combout\,
	datad => \inst1|inst|datatri[2]~20_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \inst7|inst1|lpm_ff_component|dffs\(2));

-- Location: LC_X12_Y10_N5
\inst1|inst|datatri[2]~19\ : cyclone_lcell
-- Equation(s):
-- \inst1|inst|datatri[2]~19_combout\ = (\read~combout\ & (\inst|inst|altsyncram_component|auto_generated|q_a\(2) & ((\inst7|inst1|lpm_ff_component|dffs\(2)) # (!\write~combout\)))) # (!\read~combout\ & (((\inst7|inst1|lpm_ff_component|dffs\(2))) # 
-- (!\write~combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f531",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \read~combout\,
	datab => \write~combout\,
	datac => \inst|inst|altsyncram_component|auto_generated|q_a\(2),
	datad => \inst7|inst1|lpm_ff_component|dffs\(2),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \inst1|inst|datatri[2]~19_combout\);

-- Location: LC_X12_Y10_N6
\inst1|inst|datatri[2]~20\ : cyclone_lcell
-- Equation(s):
-- \inst1|inst|datatri[2]~20_combout\ = ((\inst1|inst|datatri[2]~19_combout\ & ((\inst1|inst|sram|ram_block|auto_generated|q_a\(2)) # (!\gnd~combout\)))) # (!\inst1|inst|datatri[7]~9_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "bf33",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \inst1|inst|sram|ram_block|auto_generated|q_a\(2),
	datab => \inst1|inst|datatri[7]~9_combout\,
	datac => \gnd~combout\,
	datad => \inst1|inst|datatri[2]~19_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \inst1|inst|datatri[2]~20_combout\);

-- Location: LC_X12_Y10_N3
\inst7|inst1|lpm_ff_component|dffs[3]\ : cyclone_lcell
-- Equation(s):
-- \inst7|inst1|lpm_ff_component|dffs\(3) = DFFEAS((((\inst1|inst|datatri[3]~18_combout\))) # (!\read~combout\), GLOBAL(\inst7|inst~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "ff55",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \inst7|inst~combout\,
	dataa => \read~combout\,
	datad => \inst1|inst|datatri[3]~18_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \inst7|inst1|lpm_ff_component|dffs\(3));

-- Location: LC_X12_Y10_N0
\inst1|inst|datatri[3]~17\ : cyclone_lcell
-- Equation(s):
-- \inst1|inst|datatri[3]~17_combout\ = (\read~combout\ & (\inst|inst|altsyncram_component|auto_generated|q_a\(3) & ((\inst7|inst1|lpm_ff_component|dffs\(3)) # (!\write~combout\)))) # (!\read~combout\ & (((\inst7|inst1|lpm_ff_component|dffs\(3))) # 
-- (!\write~combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f531",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \read~combout\,
	datab => \write~combout\,
	datac => \inst|inst|altsyncram_component|auto_generated|q_a\(3),
	datad => \inst7|inst1|lpm_ff_component|dffs\(3),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \inst1|inst|datatri[3]~17_combout\);

-- Location: LC_X12_Y10_N2
\inst1|inst|datatri[3]~18\ : cyclone_lcell
-- Equation(s):
-- \inst1|inst|datatri[3]~18_combout\ = ((\inst1|inst|datatri[3]~17_combout\ & ((\inst1|inst|sram|ram_block|auto_generated|q_a\(3)) # (!\gnd~combout\)))) # (!\inst1|inst|datatri[7]~9_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "df55",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \inst1|inst|datatri[7]~9_combout\,
	datab => \inst1|inst|sram|ram_block|auto_generated|q_a\(3),
	datac => \gnd~combout\,
	datad => \inst1|inst|datatri[3]~17_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \inst1|inst|datatri[3]~18_combout\);

-- Location: LC_X9_Y12_N4
\inst7|inst1|lpm_ff_component|dffs[4]\ : cyclone_lcell
-- Equation(s):
-- \inst7|inst1|lpm_ff_component|dffs\(4) = DFFEAS((((\inst1|inst|datatri[4]~16_combout\))) # (!\read~combout\), GLOBAL(\inst7|inst~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "ff55",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \inst7|inst~combout\,
	dataa => \read~combout\,
	datad => \inst1|inst|datatri[4]~16_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \inst7|inst1|lpm_ff_component|dffs\(4));

-- Location: LC_X6_Y10_N4
\inst1|inst|datatri[4]~15\ : cyclone_lcell
-- Equation(s):
-- \inst1|inst|datatri[4]~15_combout\ = (\write~combout\ & (\inst7|inst1|lpm_ff_component|dffs\(4) & ((\inst|inst|altsyncram_component|auto_generated|q_a\(4)) # (!\read~combout\)))) # (!\write~combout\ & 
-- (((\inst|inst|altsyncram_component|auto_generated|q_a\(4))) # (!\read~combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f531",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \write~combout\,
	datab => \read~combout\,
	datac => \inst7|inst1|lpm_ff_component|dffs\(4),
	datad => \inst|inst|altsyncram_component|auto_generated|q_a\(4),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \inst1|inst|datatri[4]~15_combout\);

-- Location: LC_X6_Y10_N5
\inst1|inst|datatri[4]~16\ : cyclone_lcell
-- Equation(s):
-- \inst1|inst|datatri[4]~16_combout\ = ((\inst1|inst|datatri[4]~15_combout\ & ((\inst1|inst|sram|ram_block|auto_generated|q_a\(4)) # (!\gnd~combout\)))) # (!\inst1|inst|datatri[7]~9_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f733",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \gnd~combout\,
	datab => \inst1|inst|datatri[7]~9_combout\,
	datac => \inst1|inst|sram|ram_block|auto_generated|q_a\(4),
	datad => \inst1|inst|datatri[4]~15_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \inst1|inst|datatri[4]~16_combout\);

-- Location: LC_X6_Y10_N2
\inst7|inst1|lpm_ff_component|dffs[5]\ : cyclone_lcell
-- Equation(s):
-- \inst7|inst1|lpm_ff_component|dffs\(5) = DFFEAS((((\inst1|inst|datatri[5]~14_combout\)) # (!\read~combout\)), GLOBAL(\inst7|inst~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "ff33",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \inst7|inst~combout\,
	datab => \read~combout\,
	datad => \inst1|inst|datatri[5]~14_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \inst7|inst1|lpm_ff_component|dffs\(5));

-- Location: LC_X6_Y10_N0
\inst1|inst|datatri[5]~13\ : cyclone_lcell
-- Equation(s):
-- \inst1|inst|datatri[5]~13_combout\ = (\write~combout\ & (\inst7|inst1|lpm_ff_component|dffs\(5) & ((\inst|inst|altsyncram_component|auto_generated|q_a\(5)) # (!\read~combout\)))) # (!\write~combout\ & 
-- (((\inst|inst|altsyncram_component|auto_generated|q_a\(5))) # (!\read~combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f531",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \write~combout\,
	datab => \read~combout\,
	datac => \inst7|inst1|lpm_ff_component|dffs\(5),
	datad => \inst|inst|altsyncram_component|auto_generated|q_a\(5),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \inst1|inst|datatri[5]~13_combout\);

-- Location: LC_X6_Y10_N1
\inst1|inst|datatri[5]~14\ : cyclone_lcell
-- Equation(s):
-- \inst1|inst|datatri[5]~14_combout\ = ((\inst1|inst|datatri[5]~13_combout\ & ((\inst1|inst|sram|ram_block|auto_generated|q_a\(5)) # (!\gnd~combout\)))) # (!\inst1|inst|datatri[7]~9_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f733",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \gnd~combout\,
	datab => \inst1|inst|datatri[7]~9_combout\,
	datac => \inst1|inst|sram|ram_block|auto_generated|q_a\(5),
	datad => \inst1|inst|datatri[5]~13_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \inst1|inst|datatri[5]~14_combout\);

-- Location: LC_X6_Y10_N9
\inst7|inst1|lpm_ff_component|dffs[6]\ : cyclone_lcell
-- Equation(s):
-- \inst7|inst1|lpm_ff_component|dffs\(6) = DFFEAS((((\inst1|inst|datatri[6]~12_combout\)) # (!\read~combout\)), GLOBAL(\inst7|inst~combout\), VCC, , , , , , )

-- pragma translate_off
GENERIC MAP (
	lut_mask => "ff33",
	operation_mode => "normal",
	output_mode => "reg_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	clk => \inst7|inst~combout\,
	datab => \read~combout\,
	datad => \inst1|inst|datatri[6]~12_combout\,
	aclr => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \inst7|inst1|lpm_ff_component|dffs\(6));

-- Location: LC_X5_Y11_N1
\inst1|inst|datatri[6]~11\ : cyclone_lcell
-- Equation(s):
-- \inst1|inst|datatri[6]~11_combout\ = (\read~combout\ & (\inst|inst|altsyncram_component|auto_generated|q_a\(6) & ((\inst7|inst1|lpm_ff_component|dffs\(6)) # (!\write~combout\)))) # (!\read~combout\ & (((\inst7|inst1|lpm_ff_component|dffs\(6))) # 
-- (!\write~combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f351",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \read~combout\,
	datab => \write~combout\,
	datac => \inst7|inst1|lpm_ff_component|dffs\(6),
	datad => \inst|inst|altsyncram_component|auto_generated|q_a\(6),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \inst1|inst|datatri[6]~11_combout\);

-- Location: LC_X6_Y10_N8
\inst1|inst|datatri[6]~12\ : cyclone_lcell
-- Equation(s):
-- \inst1|inst|datatri[6]~12_combout\ = ((\inst1|inst|datatri[6]~11_combout\ & ((\inst1|inst|sram|ram_block|auto_generated|q_a\(6)) # (!\gnd~combout\)))) # (!\inst1|inst|datatri[7]~9_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f733",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \gnd~combout\,
	datab => \inst1|inst|datatri[7]~9_combout\,
	datac => \inst1|inst|sram|ram_block|auto_generated|q_a\(6),
	datad => \inst1|inst|datatri[6]~11_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \inst1|inst|datatri[6]~12_combout\);

-- Location: LC_X5_Y11_N3
\inst1|inst|datatri[7]~8\ : cyclone_lcell
-- Equation(s):
-- \inst1|inst|datatri[7]~8_combout\ = (\inst1|inst|sram|ram_block|auto_generated|q_a\(7) & (((\inst|inst|altsyncram_component|auto_generated|q_a\(7)) # (!\read~combout\)))) # (!\inst1|inst|sram|ram_block|auto_generated|q_a\(7) & (!\gnd~combout\ & 
-- ((\inst|inst|altsyncram_component|auto_generated|q_a\(7)) # (!\read~combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "bb0b",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \inst1|inst|sram|ram_block|auto_generated|q_a\(7),
	datab => \gnd~combout\,
	datac => \read~combout\,
	datad => \inst|inst|altsyncram_component|auto_generated|q_a\(7),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \inst1|inst|datatri[7]~8_combout\);

-- Location: LC_X5_Y11_N7
\inst1|inst|datatri[7]~25\ : cyclone_lcell
-- Equation(s):
-- \inst1|inst|datatri[7]~25_combout\ = ((\inst1|inst|datatri[7]~8_combout\ & ((\inst7|inst1|lpm_ff_component|dffs\(7)) # (!\write~combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "c0cc",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \inst1|inst|datatri[7]~8_combout\,
	datac => \inst7|inst1|lpm_ff_component|dffs\(7),
	datad => \write~combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \inst1|inst|datatri[7]~25_combout\);

-- Location: LC_X6_Y10_N3
\inst1|inst|datatri[6]~26\ : cyclone_lcell
-- Equation(s):
-- \inst1|inst|datatri[6]~26_combout\ = (\inst1|inst|datatri[6]~11_combout\ & (((\inst1|inst|sram|ram_block|auto_generated|q_a\(6))) # (!\gnd~combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "d0d0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \gnd~combout\,
	datab => \inst1|inst|sram|ram_block|auto_generated|q_a\(6),
	datac => \inst1|inst|datatri[6]~11_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \inst1|inst|datatri[6]~26_combout\);

-- Location: LC_X6_Y10_N7
\inst1|inst|datatri[5]~27\ : cyclone_lcell
-- Equation(s):
-- \inst1|inst|datatri[5]~27_combout\ = ((\inst1|inst|datatri[5]~13_combout\ & ((\inst1|inst|sram|ram_block|auto_generated|q_a\(5)) # (!\gnd~combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f500",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \gnd~combout\,
	datac => \inst1|inst|sram|ram_block|auto_generated|q_a\(5),
	datad => \inst1|inst|datatri[5]~13_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \inst1|inst|datatri[5]~27_combout\);

-- Location: LC_X7_Y10_N2
\inst1|inst|datatri[4]~28\ : cyclone_lcell
-- Equation(s):
-- \inst1|inst|datatri[4]~28_combout\ = ((\inst1|inst|datatri[4]~15_combout\ & ((\inst1|inst|sram|ram_block|auto_generated|q_a\(4)) # (!\gnd~combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "cc0c",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \inst1|inst|datatri[4]~15_combout\,
	datac => \gnd~combout\,
	datad => \inst1|inst|sram|ram_block|auto_generated|q_a\(4),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \inst1|inst|datatri[4]~28_combout\);

-- Location: LC_X12_Y10_N4
\inst1|inst|datatri[3]~29\ : cyclone_lcell
-- Equation(s):
-- \inst1|inst|datatri[3]~29_combout\ = (\inst1|inst|datatri[3]~17_combout\ & (((\inst1|inst|sram|ram_block|auto_generated|q_a\(3)) # (!\gnd~combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "aa0a",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	dataa => \inst1|inst|datatri[3]~17_combout\,
	datac => \gnd~combout\,
	datad => \inst1|inst|sram|ram_block|auto_generated|q_a\(3),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \inst1|inst|datatri[3]~29_combout\);

-- Location: LC_X12_Y10_N7
\inst1|inst|datatri[2]~30\ : cyclone_lcell
-- Equation(s):
-- \inst1|inst|datatri[2]~30_combout\ = ((\inst1|inst|datatri[2]~19_combout\ & ((\inst1|inst|sram|ram_block|auto_generated|q_a\(2)) # (!\gnd~combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "cc0c",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \inst1|inst|datatri[2]~19_combout\,
	datac => \gnd~combout\,
	datad => \inst1|inst|sram|ram_block|auto_generated|q_a\(2),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \inst1|inst|datatri[2]~30_combout\);

-- Location: LC_X7_Y10_N4
\inst1|inst|datatri[1]~31\ : cyclone_lcell
-- Equation(s):
-- \inst1|inst|datatri[1]~31_combout\ = ((\inst1|inst|datatri[1]~21_combout\ & ((\inst1|inst|sram|ram_block|auto_generated|q_a\(1)) # (!\gnd~combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "cc0c",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \inst1|inst|datatri[1]~21_combout\,
	datac => \gnd~combout\,
	datad => \inst1|inst|sram|ram_block|auto_generated|q_a\(1),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \inst1|inst|datatri[1]~31_combout\);

-- Location: LC_X5_Y11_N2
\inst1|inst|datatri[0]~32\ : cyclone_lcell
-- Equation(s):
-- \inst1|inst|datatri[0]~32_combout\ = ((\inst1|inst|datatri[0]~23_combout\ & ((\inst1|inst|sram|ram_block|auto_generated|q_a\(0)) # (!\gnd~combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f030",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \gnd~combout\,
	datac => \inst1|inst|datatri[0]~23_combout\,
	datad => \inst1|inst|sram|ram_block|auto_generated|q_a\(0),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \inst1|inst|datatri[0]~32_combout\);

-- Location: PIN_23,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
\data[7]~I\ : cyclone_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "output",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	datain => \inst1|inst|datatri[7]~25_combout\,
	oe => \inst1|inst|datatri[7]~9_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	padio => ww_data(7));

-- Location: PIN_41,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
\data[6]~I\ : cyclone_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "output",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	datain => \inst1|inst|datatri[6]~26_combout\,
	oe => \inst1|inst|datatri[7]~9_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	padio => ww_data(6));

-- Location: PIN_100,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
\data[5]~I\ : cyclone_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "output",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	datain => \inst1|inst|datatri[5]~27_combout\,
	oe => \inst1|inst|datatri[7]~9_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	padio => ww_data(5));

-- Location: PIN_77,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
\data[4]~I\ : cyclone_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "output",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	datain => \inst1|inst|datatri[4]~28_combout\,
	oe => \inst1|inst|datatri[7]~9_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	padio => ww_data(4));

-- Location: PIN_48,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
\data[3]~I\ : cyclone_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "output",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	datain => \inst1|inst|datatri[3]~29_combout\,
	oe => \inst1|inst|datatri[7]~9_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	padio => ww_data(3));

-- Location: PIN_89,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
\data[2]~I\ : cyclone_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "output",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	datain => \inst1|inst|datatri[2]~30_combout\,
	oe => \inst1|inst|datatri[7]~9_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	padio => ww_data(2));

-- Location: PIN_85,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
\data[1]~I\ : cyclone_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "output",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	datain => \inst1|inst|datatri[1]~31_combout\,
	oe => \inst1|inst|datatri[7]~9_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	padio => ww_data(1));

-- Location: PIN_78,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
\data[0]~I\ : cyclone_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "output",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	datain => \inst1|inst|datatri[0]~32_combout\,
	oe => \inst1|inst|datatri[7]~9_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	padio => ww_data(0));

-- Location: PIN_90,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
\buffer_data[7]~I\ : cyclone_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "output",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	datain => \inst7|inst1|lpm_ff_component|dffs\(7),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => VCC,
	padio => ww_buffer_data(7));

-- Location: PIN_92,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
\buffer_data[6]~I\ : cyclone_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "output",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	datain => \inst7|inst1|lpm_ff_component|dffs\(6),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => VCC,
	padio => ww_buffer_data(6));

-- Location: PIN_88,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
\buffer_data[5]~I\ : cyclone_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "output",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	datain => \inst7|inst1|lpm_ff_component|dffs\(5),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => VCC,
	padio => ww_buffer_data(5));

-- Location: PIN_86,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
\buffer_data[4]~I\ : cyclone_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "output",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	datain => \inst7|inst1|lpm_ff_component|dffs\(4),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => VCC,
	padio => ww_buffer_data(4));

-- Location: PIN_79,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
\buffer_data[3]~I\ : cyclone_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "output",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	datain => \inst7|inst1|lpm_ff_component|dffs\(3),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => VCC,
	padio => ww_buffer_data(3));

-- Location: PIN_84,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
\buffer_data[2]~I\ : cyclone_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "output",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	datain => \inst7|inst1|lpm_ff_component|dffs\(2),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => VCC,
	padio => ww_buffer_data(2));

-- Location: PIN_91,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
\buffer_data[1]~I\ : cyclone_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "output",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	datain => \inst7|inst1|lpm_ff_component|dffs\(1),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => VCC,
	padio => ww_buffer_data(1));

-- Location: PIN_99,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
\buffer_data[0]~I\ : cyclone_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "output",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	datain => \inst7|inst1|lpm_ff_component|dffs\(0),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => VCC,
	padio => ww_buffer_data(0));

-- Location: PIN_76,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
\ROM_data[7]~I\ : cyclone_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "output",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	datain => \inst|inst|altsyncram_component|auto_generated|q_a\(7),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => VCC,
	padio => ww_ROM_data(7));

-- Location: PIN_37,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
\ROM_data[6]~I\ : cyclone_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "output",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	datain => \inst|inst|altsyncram_component|auto_generated|q_a\(6),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => VCC,
	padio => ww_ROM_data(6));

-- Location: PIN_71,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
\ROM_data[5]~I\ : cyclone_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "output",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	datain => \inst|inst|altsyncram_component|auto_generated|q_a\(5),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => VCC,
	padio => ww_ROM_data(5));

-- Location: PIN_69,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
\ROM_data[4]~I\ : cyclone_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "output",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	datain => \inst|inst|altsyncram_component|auto_generated|q_a\(4),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => VCC,
	padio => ww_ROM_data(4));

-- Location: PIN_73,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
\ROM_data[3]~I\ : cyclone_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "output",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	datain => \inst|inst|altsyncram_component|auto_generated|q_a\(3),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => VCC,
	padio => ww_ROM_data(3));

-- Location: PIN_72,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
\ROM_data[2]~I\ : cyclone_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "output",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	datain => \inst|inst|altsyncram_component|auto_generated|q_a\(2),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => VCC,
	padio => ww_ROM_data(2));

-- Location: PIN_38,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
\ROM_data[1]~I\ : cyclone_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "output",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	datain => \inst|inst|altsyncram_component|auto_generated|q_a\(1),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => VCC,
	padio => ww_ROM_data(1));

-- Location: PIN_53,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
\ROM_data[0]~I\ : cyclone_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "output",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	datain => \inst|inst|altsyncram_component|auto_generated|q_a\(0),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => VCC,
	padio => ww_ROM_data(0));
END structure;


