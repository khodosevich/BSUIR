// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2018.2 (win64) Build 2258646 Thu Jun 14 20:03:12 MDT 2018
// Date        : Mon Oct  7 21:09:56 2024
// Host        : LAPTOP-KNVLJHHK running 64-bit major release  (build 9200)
// Command     : write_verilog -mode timesim -nolib -sdf_anno true -force -file
//               D:/vivado_project/lab444/project_1/project_1.sim/sim_1/synth/timing/xsim/counter_test_tb_time_synth.v
// Design      : lab4
// Purpose     : This verilog netlist is a timing simulation representation of the design and should not be modified or
//               synthesized. Please ensure that this netlist is used with the corresponding SDF file.
// Device      : xc7a200tfbg676-2
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps
`define XIL_TIMING

module Divider_CLK
   (temp_CLK,
    CLK_NO_DIV_BUFG);
  output temp_CLK;
  input CLK_NO_DIV_BUFG;

  wire CLK_NO_DIV_BUFG;
  wire [31:1]data0;
  wire [31:0]i;
  wire i0_carry__0_n_0;
  wire i0_carry__0_n_1;
  wire i0_carry__0_n_2;
  wire i0_carry__0_n_3;
  wire i0_carry__1_n_0;
  wire i0_carry__1_n_1;
  wire i0_carry__1_n_2;
  wire i0_carry__1_n_3;
  wire i0_carry__2_n_0;
  wire i0_carry__2_n_1;
  wire i0_carry__2_n_2;
  wire i0_carry__2_n_3;
  wire i0_carry__3_n_0;
  wire i0_carry__3_n_1;
  wire i0_carry__3_n_2;
  wire i0_carry__3_n_3;
  wire i0_carry__4_n_0;
  wire i0_carry__4_n_1;
  wire i0_carry__4_n_2;
  wire i0_carry__4_n_3;
  wire i0_carry__5_n_0;
  wire i0_carry__5_n_1;
  wire i0_carry__5_n_2;
  wire i0_carry__5_n_3;
  wire i0_carry__6_n_2;
  wire i0_carry__6_n_3;
  wire i0_carry_n_0;
  wire i0_carry_n_1;
  wire i0_carry_n_2;
  wire i0_carry_n_3;
  wire \i[0]_i_2_n_0 ;
  wire \i[0]_i_3_n_0 ;
  wire \i[0]_i_4_n_0 ;
  wire \i[0]_i_5_n_0 ;
  wire \i[0]_i_6_n_0 ;
  wire \i[0]_i_7_n_0 ;
  wire \i[0]_i_8_n_0 ;
  wire \i[0]_i_9_n_0 ;
  wire [0:0]i_0;
  wire temp_CLK;
  wire temp_CLK_1;
  wire temp_CLK_i_1_n_0;
  wire [3:2]NLW_i0_carry__6_CO_UNCONNECTED;
  wire [3:3]NLW_i0_carry__6_O_UNCONNECTED;

  CARRY4 i0_carry
       (.CI(1'b0),
        .CO({i0_carry_n_0,i0_carry_n_1,i0_carry_n_2,i0_carry_n_3}),
        .CYINIT(i[0]),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O(data0[4:1]),
        .S(i[4:1]));
  CARRY4 i0_carry__0
       (.CI(i0_carry_n_0),
        .CO({i0_carry__0_n_0,i0_carry__0_n_1,i0_carry__0_n_2,i0_carry__0_n_3}),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O(data0[8:5]),
        .S(i[8:5]));
  CARRY4 i0_carry__1
       (.CI(i0_carry__0_n_0),
        .CO({i0_carry__1_n_0,i0_carry__1_n_1,i0_carry__1_n_2,i0_carry__1_n_3}),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O(data0[12:9]),
        .S(i[12:9]));
  CARRY4 i0_carry__2
       (.CI(i0_carry__1_n_0),
        .CO({i0_carry__2_n_0,i0_carry__2_n_1,i0_carry__2_n_2,i0_carry__2_n_3}),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O(data0[16:13]),
        .S(i[16:13]));
  CARRY4 i0_carry__3
       (.CI(i0_carry__2_n_0),
        .CO({i0_carry__3_n_0,i0_carry__3_n_1,i0_carry__3_n_2,i0_carry__3_n_3}),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O(data0[20:17]),
        .S(i[20:17]));
  CARRY4 i0_carry__4
       (.CI(i0_carry__3_n_0),
        .CO({i0_carry__4_n_0,i0_carry__4_n_1,i0_carry__4_n_2,i0_carry__4_n_3}),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O(data0[24:21]),
        .S(i[24:21]));
  CARRY4 i0_carry__5
       (.CI(i0_carry__4_n_0),
        .CO({i0_carry__5_n_0,i0_carry__5_n_1,i0_carry__5_n_2,i0_carry__5_n_3}),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O(data0[28:25]),
        .S(i[28:25]));
  CARRY4 i0_carry__6
       (.CI(i0_carry__5_n_0),
        .CO({NLW_i0_carry__6_CO_UNCONNECTED[3:2],i0_carry__6_n_2,i0_carry__6_n_3}),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O({NLW_i0_carry__6_O_UNCONNECTED[3],data0[31:29]}),
        .S({1'b0,i[31:29]}));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT4 #(
    .INIT(16'h00FE)) 
    \i[0]_i_1 
       (.I0(\i[0]_i_2_n_0 ),
        .I1(\i[0]_i_3_n_0 ),
        .I2(\i[0]_i_4_n_0 ),
        .I3(i[0]),
        .O(i_0));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFFFFFE)) 
    \i[0]_i_2 
       (.I0(\i[0]_i_5_n_0 ),
        .I1(\i[0]_i_6_n_0 ),
        .I2(i[31]),
        .I3(i[30]),
        .I4(i[1]),
        .I5(\i[0]_i_7_n_0 ),
        .O(\i[0]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hFFFFFFFE)) 
    \i[0]_i_3 
       (.I0(i[4]),
        .I1(i[5]),
        .I2(i[2]),
        .I3(i[3]),
        .I4(\i[0]_i_8_n_0 ),
        .O(\i[0]_i_3_n_0 ));
  LUT5 #(
    .INIT(32'hFFFFFFFB)) 
    \i[0]_i_4 
       (.I0(i[12]),
        .I1(i[13]),
        .I2(i[10]),
        .I3(i[11]),
        .I4(\i[0]_i_9_n_0 ),
        .O(\i[0]_i_4_n_0 ));
  LUT4 #(
    .INIT(16'hFF7F)) 
    \i[0]_i_5 
       (.I0(i[23]),
        .I1(i[22]),
        .I2(i[24]),
        .I3(i[25]),
        .O(\i[0]_i_5_n_0 ));
  LUT4 #(
    .INIT(16'hDFFF)) 
    \i[0]_i_6 
       (.I0(i[18]),
        .I1(i[19]),
        .I2(i[21]),
        .I3(i[20]),
        .O(\i[0]_i_6_n_0 ));
  LUT4 #(
    .INIT(16'hFFFD)) 
    \i[0]_i_7 
       (.I0(i[26]),
        .I1(i[27]),
        .I2(i[29]),
        .I3(i[28]),
        .O(\i[0]_i_7_n_0 ));
  LUT4 #(
    .INIT(16'hFFEF)) 
    \i[0]_i_8 
       (.I0(i[7]),
        .I1(i[6]),
        .I2(i[8]),
        .I3(i[9]),
        .O(\i[0]_i_8_n_0 ));
  LUT4 #(
    .INIT(16'hFF7F)) 
    \i[0]_i_9 
       (.I0(i[15]),
        .I1(i[14]),
        .I2(i[16]),
        .I3(i[17]),
        .O(\i[0]_i_9_n_0 ));
  LUT4 #(
    .INIT(16'h0001)) 
    \i[31]_i_1 
       (.I0(i[0]),
        .I1(\i[0]_i_4_n_0 ),
        .I2(\i[0]_i_3_n_0 ),
        .I3(\i[0]_i_2_n_0 ),
        .O(temp_CLK_1));
  FDRE #(
    .INIT(1'b0)) 
    \i_reg[0] 
       (.C(CLK_NO_DIV_BUFG),
        .CE(1'b1),
        .D(i_0),
        .Q(i[0]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \i_reg[10] 
       (.C(CLK_NO_DIV_BUFG),
        .CE(1'b1),
        .D(data0[10]),
        .Q(i[10]),
        .R(temp_CLK_1));
  FDRE #(
    .INIT(1'b0)) 
    \i_reg[11] 
       (.C(CLK_NO_DIV_BUFG),
        .CE(1'b1),
        .D(data0[11]),
        .Q(i[11]),
        .R(temp_CLK_1));
  FDRE #(
    .INIT(1'b0)) 
    \i_reg[12] 
       (.C(CLK_NO_DIV_BUFG),
        .CE(1'b1),
        .D(data0[12]),
        .Q(i[12]),
        .R(temp_CLK_1));
  FDRE #(
    .INIT(1'b0)) 
    \i_reg[13] 
       (.C(CLK_NO_DIV_BUFG),
        .CE(1'b1),
        .D(data0[13]),
        .Q(i[13]),
        .R(temp_CLK_1));
  FDRE #(
    .INIT(1'b0)) 
    \i_reg[14] 
       (.C(CLK_NO_DIV_BUFG),
        .CE(1'b1),
        .D(data0[14]),
        .Q(i[14]),
        .R(temp_CLK_1));
  FDRE #(
    .INIT(1'b0)) 
    \i_reg[15] 
       (.C(CLK_NO_DIV_BUFG),
        .CE(1'b1),
        .D(data0[15]),
        .Q(i[15]),
        .R(temp_CLK_1));
  FDRE #(
    .INIT(1'b0)) 
    \i_reg[16] 
       (.C(CLK_NO_DIV_BUFG),
        .CE(1'b1),
        .D(data0[16]),
        .Q(i[16]),
        .R(temp_CLK_1));
  FDRE #(
    .INIT(1'b0)) 
    \i_reg[17] 
       (.C(CLK_NO_DIV_BUFG),
        .CE(1'b1),
        .D(data0[17]),
        .Q(i[17]),
        .R(temp_CLK_1));
  FDRE #(
    .INIT(1'b0)) 
    \i_reg[18] 
       (.C(CLK_NO_DIV_BUFG),
        .CE(1'b1),
        .D(data0[18]),
        .Q(i[18]),
        .R(temp_CLK_1));
  FDRE #(
    .INIT(1'b0)) 
    \i_reg[19] 
       (.C(CLK_NO_DIV_BUFG),
        .CE(1'b1),
        .D(data0[19]),
        .Q(i[19]),
        .R(temp_CLK_1));
  FDRE #(
    .INIT(1'b0)) 
    \i_reg[1] 
       (.C(CLK_NO_DIV_BUFG),
        .CE(1'b1),
        .D(data0[1]),
        .Q(i[1]),
        .R(temp_CLK_1));
  FDRE #(
    .INIT(1'b0)) 
    \i_reg[20] 
       (.C(CLK_NO_DIV_BUFG),
        .CE(1'b1),
        .D(data0[20]),
        .Q(i[20]),
        .R(temp_CLK_1));
  FDRE #(
    .INIT(1'b0)) 
    \i_reg[21] 
       (.C(CLK_NO_DIV_BUFG),
        .CE(1'b1),
        .D(data0[21]),
        .Q(i[21]),
        .R(temp_CLK_1));
  FDRE #(
    .INIT(1'b0)) 
    \i_reg[22] 
       (.C(CLK_NO_DIV_BUFG),
        .CE(1'b1),
        .D(data0[22]),
        .Q(i[22]),
        .R(temp_CLK_1));
  FDRE #(
    .INIT(1'b0)) 
    \i_reg[23] 
       (.C(CLK_NO_DIV_BUFG),
        .CE(1'b1),
        .D(data0[23]),
        .Q(i[23]),
        .R(temp_CLK_1));
  FDRE #(
    .INIT(1'b0)) 
    \i_reg[24] 
       (.C(CLK_NO_DIV_BUFG),
        .CE(1'b1),
        .D(data0[24]),
        .Q(i[24]),
        .R(temp_CLK_1));
  FDRE #(
    .INIT(1'b0)) 
    \i_reg[25] 
       (.C(CLK_NO_DIV_BUFG),
        .CE(1'b1),
        .D(data0[25]),
        .Q(i[25]),
        .R(temp_CLK_1));
  FDRE #(
    .INIT(1'b0)) 
    \i_reg[26] 
       (.C(CLK_NO_DIV_BUFG),
        .CE(1'b1),
        .D(data0[26]),
        .Q(i[26]),
        .R(temp_CLK_1));
  FDRE #(
    .INIT(1'b0)) 
    \i_reg[27] 
       (.C(CLK_NO_DIV_BUFG),
        .CE(1'b1),
        .D(data0[27]),
        .Q(i[27]),
        .R(temp_CLK_1));
  FDRE #(
    .INIT(1'b0)) 
    \i_reg[28] 
       (.C(CLK_NO_DIV_BUFG),
        .CE(1'b1),
        .D(data0[28]),
        .Q(i[28]),
        .R(temp_CLK_1));
  FDRE #(
    .INIT(1'b0)) 
    \i_reg[29] 
       (.C(CLK_NO_DIV_BUFG),
        .CE(1'b1),
        .D(data0[29]),
        .Q(i[29]),
        .R(temp_CLK_1));
  FDRE #(
    .INIT(1'b0)) 
    \i_reg[2] 
       (.C(CLK_NO_DIV_BUFG),
        .CE(1'b1),
        .D(data0[2]),
        .Q(i[2]),
        .R(temp_CLK_1));
  FDRE #(
    .INIT(1'b0)) 
    \i_reg[30] 
       (.C(CLK_NO_DIV_BUFG),
        .CE(1'b1),
        .D(data0[30]),
        .Q(i[30]),
        .R(temp_CLK_1));
  FDRE #(
    .INIT(1'b0)) 
    \i_reg[31] 
       (.C(CLK_NO_DIV_BUFG),
        .CE(1'b1),
        .D(data0[31]),
        .Q(i[31]),
        .R(temp_CLK_1));
  FDRE #(
    .INIT(1'b0)) 
    \i_reg[3] 
       (.C(CLK_NO_DIV_BUFG),
        .CE(1'b1),
        .D(data0[3]),
        .Q(i[3]),
        .R(temp_CLK_1));
  FDRE #(
    .INIT(1'b0)) 
    \i_reg[4] 
       (.C(CLK_NO_DIV_BUFG),
        .CE(1'b1),
        .D(data0[4]),
        .Q(i[4]),
        .R(temp_CLK_1));
  FDRE #(
    .INIT(1'b0)) 
    \i_reg[5] 
       (.C(CLK_NO_DIV_BUFG),
        .CE(1'b1),
        .D(data0[5]),
        .Q(i[5]),
        .R(temp_CLK_1));
  FDRE #(
    .INIT(1'b0)) 
    \i_reg[6] 
       (.C(CLK_NO_DIV_BUFG),
        .CE(1'b1),
        .D(data0[6]),
        .Q(i[6]),
        .R(temp_CLK_1));
  FDRE #(
    .INIT(1'b0)) 
    \i_reg[7] 
       (.C(CLK_NO_DIV_BUFG),
        .CE(1'b1),
        .D(data0[7]),
        .Q(i[7]),
        .R(temp_CLK_1));
  FDRE #(
    .INIT(1'b0)) 
    \i_reg[8] 
       (.C(CLK_NO_DIV_BUFG),
        .CE(1'b1),
        .D(data0[8]),
        .Q(i[8]),
        .R(temp_CLK_1));
  FDRE #(
    .INIT(1'b0)) 
    \i_reg[9] 
       (.C(CLK_NO_DIV_BUFG),
        .CE(1'b1),
        .D(data0[9]),
        .Q(i[9]),
        .R(temp_CLK_1));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT5 #(
    .INIT(32'hFFFE0001)) 
    temp_CLK_i_1
       (.I0(i[0]),
        .I1(\i[0]_i_4_n_0 ),
        .I2(\i[0]_i_3_n_0 ),
        .I3(\i[0]_i_2_n_0 ),
        .I4(temp_CLK),
        .O(temp_CLK_i_1_n_0));
  FDRE #(
    .INIT(1'b0)) 
    temp_CLK_reg
       (.C(CLK_NO_DIV_BUFG),
        .CE(1'b1),
        .D(temp_CLK_i_1_n_0),
        .Q(temp_CLK),
        .R(1'b0));
endmodule

module counter
   (ledsmain_OBUF,
    ledsboard_OBUF,
    temp_CLK,
    pushbuttons_IBUF,
    dipswitch_IBUF);
  output [3:0]ledsmain_OBUF;
  output [0:0]ledsboard_OBUF;
  input temp_CLK;
  input [3:0]pushbuttons_IBUF;
  input [3:0]dipswitch_IBUF;

  wire J22__0;
  wire J32__0;
  wire [3:0]dipswitch_IBUF;
  wire [0:0]ledsboard_OBUF;
  wire [3:0]ledsmain_OBUF;
  wire [3:0]pushbuttons_IBUF;
  wire temp_CLK;

  jk D1
       (.J22__0(J22__0),
        .J32__0(J32__0),
        .current_state_reg_0(ledsmain_OBUF[0]),
        .current_state_reg_1(ledsmain_OBUF[1]),
        .current_state_reg_2(ledsmain_OBUF[2]),
        .dipswitch_IBUF(dipswitch_IBUF[0]),
        .ledsboard_OBUF(ledsboard_OBUF),
        .ledsmain_OBUF(ledsmain_OBUF[3]),
        .pushbuttons_IBUF(pushbuttons_IBUF),
        .temp_CLK(temp_CLK));
  jk_0 D2
       (.J22__0(J22__0),
        .dipswitch_IBUF(dipswitch_IBUF[1]),
        .ledsmain_OBUF(ledsmain_OBUF[1]),
        .pushbuttons_IBUF(pushbuttons_IBUF[0]),
        .temp_CLK(temp_CLK));
  jk_1 D3
       (.J32__0(J32__0),
        .current_state_reg_0(ledsmain_OBUF[2]),
        .dipswitch_IBUF(dipswitch_IBUF[2]),
        .pushbuttons_IBUF(pushbuttons_IBUF[0]),
        .temp_CLK(temp_CLK));
  jk_2 D4
       (.J32__0(J32__0),
        .current_state_reg_0(ledsmain_OBUF[2]),
        .dipswitch_IBUF(dipswitch_IBUF[3]),
        .ledsmain_OBUF(ledsmain_OBUF[3]),
        .pushbuttons_IBUF({pushbuttons_IBUF[3],pushbuttons_IBUF[0]}),
        .temp_CLK(temp_CLK));
endmodule

module jk
   (current_state_reg_0,
    J32__0,
    J22__0,
    ledsboard_OBUF,
    temp_CLK,
    pushbuttons_IBUF,
    dipswitch_IBUF,
    current_state_reg_1,
    current_state_reg_2,
    ledsmain_OBUF);
  output current_state_reg_0;
  output J32__0;
  output J22__0;
  output [0:0]ledsboard_OBUF;
  input temp_CLK;
  input [3:0]pushbuttons_IBUF;
  input [0:0]dipswitch_IBUF;
  input current_state_reg_1;
  input current_state_reg_2;
  input [0:0]ledsmain_OBUF;

  wire J22__0;
  wire J32__0;
  wire current_state_i_1__2_n_0;
  wire current_state_reg_0;
  wire current_state_reg_1;
  wire current_state_reg_2;
  wire [0:0]dipswitch_IBUF;
  wire [0:0]ledsboard_OBUF;
  wire [0:0]ledsmain_OBUF;
  wire [3:0]pushbuttons_IBUF;
  wire temp_CLK;

  LUT5 #(
    .INIT(32'hA9FFA900)) 
    current_state_i_1__2
       (.I0(current_state_reg_0),
        .I1(pushbuttons_IBUF[2]),
        .I2(pushbuttons_IBUF[1]),
        .I3(pushbuttons_IBUF[0]),
        .I4(dipswitch_IBUF),
        .O(current_state_i_1__2_n_0));
  LUT6 #(
    .INIT(64'h0020000000000010)) 
    current_state_i_2
       (.I0(current_state_reg_0),
        .I1(pushbuttons_IBUF[2]),
        .I2(pushbuttons_IBUF[0]),
        .I3(pushbuttons_IBUF[1]),
        .I4(current_state_reg_1),
        .I5(pushbuttons_IBUF[3]),
        .O(J32__0));
  LUT5 #(
    .INIT(32'h04000004)) 
    current_state_i_2__0
       (.I0(pushbuttons_IBUF[1]),
        .I1(pushbuttons_IBUF[0]),
        .I2(pushbuttons_IBUF[2]),
        .I3(current_state_reg_0),
        .I4(pushbuttons_IBUF[3]),
        .O(J22__0));
  FDRE #(
    .INIT(1'b0)) 
    current_state_reg
       (.C(temp_CLK),
        .CE(1'b1),
        .D(current_state_i_1__2_n_0),
        .Q(current_state_reg_0),
        .R(1'b0));
  LUT6 #(
    .INIT(64'hFFFF7FFFFFFFFFFE)) 
    \ledsboard_OBUF[0]_inst_i_1 
       (.I0(pushbuttons_IBUF[3]),
        .I1(current_state_reg_0),
        .I2(current_state_reg_2),
        .I3(current_state_reg_1),
        .I4(pushbuttons_IBUF[2]),
        .I5(ledsmain_OBUF),
        .O(ledsboard_OBUF));
endmodule

(* ORIG_REF_NAME = "jk" *) 
module jk_0
   (ledsmain_OBUF,
    temp_CLK,
    J22__0,
    pushbuttons_IBUF,
    dipswitch_IBUF);
  output [0:0]ledsmain_OBUF;
  input temp_CLK;
  input J22__0;
  input [0:0]pushbuttons_IBUF;
  input [0:0]dipswitch_IBUF;

  wire J22__0;
  wire current_state_i_1_n_0;
  wire [0:0]dipswitch_IBUF;
  wire [0:0]ledsmain_OBUF;
  wire [0:0]pushbuttons_IBUF;
  wire temp_CLK;

  LUT4 #(
    .INIT(16'h6F6C)) 
    current_state_i_1
       (.I0(ledsmain_OBUF),
        .I1(J22__0),
        .I2(pushbuttons_IBUF),
        .I3(dipswitch_IBUF),
        .O(current_state_i_1_n_0));
  FDRE #(
    .INIT(1'b0)) 
    current_state_reg
       (.C(temp_CLK),
        .CE(1'b1),
        .D(current_state_i_1_n_0),
        .Q(ledsmain_OBUF),
        .R(1'b0));
endmodule

(* ORIG_REF_NAME = "jk" *) 
module jk_1
   (current_state_reg_0,
    temp_CLK,
    J32__0,
    pushbuttons_IBUF,
    dipswitch_IBUF);
  output current_state_reg_0;
  input temp_CLK;
  input J32__0;
  input [0:0]pushbuttons_IBUF;
  input [0:0]dipswitch_IBUF;

  wire J32__0;
  wire current_state_i_1__0_n_0;
  wire current_state_reg_0;
  wire [0:0]dipswitch_IBUF;
  wire [0:0]pushbuttons_IBUF;
  wire temp_CLK;

  LUT4 #(
    .INIT(16'h6F6C)) 
    current_state_i_1__0
       (.I0(current_state_reg_0),
        .I1(J32__0),
        .I2(pushbuttons_IBUF),
        .I3(dipswitch_IBUF),
        .O(current_state_i_1__0_n_0));
  FDRE #(
    .INIT(1'b0)) 
    current_state_reg
       (.C(temp_CLK),
        .CE(1'b1),
        .D(current_state_i_1__0_n_0),
        .Q(current_state_reg_0),
        .R(1'b0));
endmodule

(* ORIG_REF_NAME = "jk" *) 
module jk_2
   (ledsmain_OBUF,
    temp_CLK,
    J32__0,
    current_state_reg_0,
    pushbuttons_IBUF,
    dipswitch_IBUF);
  output [0:0]ledsmain_OBUF;
  input temp_CLK;
  input J32__0;
  input [0:0]current_state_reg_0;
  input [1:0]pushbuttons_IBUF;
  input [0:0]dipswitch_IBUF;

  wire J32__0;
  wire current_state_i_1__1_n_0;
  wire [0:0]current_state_reg_0;
  wire [0:0]dipswitch_IBUF;
  wire [0:0]ledsmain_OBUF;
  wire [1:0]pushbuttons_IBUF;
  wire temp_CLK;

  LUT6 #(
    .INIT(64'h6AA6FFFF6AA6C00C)) 
    current_state_i_1__1
       (.I0(ledsmain_OBUF),
        .I1(J32__0),
        .I2(current_state_reg_0),
        .I3(pushbuttons_IBUF[1]),
        .I4(pushbuttons_IBUF[0]),
        .I5(dipswitch_IBUF),
        .O(current_state_i_1__1_n_0));
  FDRE #(
    .INIT(1'b0)) 
    current_state_reg
       (.C(temp_CLK),
        .CE(1'b1),
        .D(current_state_i_1__1_n_0),
        .Q(ledsmain_OBUF),
        .R(1'b0));
endmodule

(* NotValidForBitStream *)
module lab4
   (ledsmain,
    ledsboard,
    pushbuttons,
    dipswitch,
    sysclk_p,
    sysclk_n);
  output [3:0]ledsmain;
  output [3:0]ledsboard;
  input [4:0]pushbuttons;
  input [3:0]dipswitch;
  input sysclk_p;
  input sysclk_n;

  wire CLK_NO_DIV;
  wire CLK_NO_DIV_BUFG;
  wire [3:0]dipswitch;
  wire [3:0]dipswitch_IBUF;
  wire [3:0]ledsboard;
  wire [0:0]ledsboard_OBUF;
  wire [3:0]ledsmain;
  wire [3:0]ledsmain_OBUF;
  wire [4:0]pushbuttons;
  wire [3:0]pushbuttons_IBUF;
  (* DIFF_TERM = 0 *) (* IBUF_LOW_PWR *) wire sysclk_n;
  (* DIFF_TERM = 0 *) (* IBUF_LOW_PWR *) wire sysclk_p;
  wire temp_CLK;

initial begin
 $sdf_annotate("counter_test_tb_time_synth.sdf",,,,"tool_control");
end
  BUFG CLK_NO_DIV_BUFG_inst
       (.I(CLK_NO_DIV),
        .O(CLK_NO_DIV_BUFG));
  (* BOX_TYPE = "PRIMITIVE" *) 
  (* CAPACITANCE = "DONT_CARE" *) 
  (* IBUF_DELAY_VALUE = "0" *) 
  (* IFD_DELAY_VALUE = "AUTO" *) 
  IBUFDS #(
    .IOSTANDARD("DEFAULT")) 
    buffds
       (.I(sysclk_p),
        .IB(sysclk_n),
        .O(CLK_NO_DIV));
  counter couner_uut
       (.dipswitch_IBUF(dipswitch_IBUF),
        .ledsboard_OBUF(ledsboard_OBUF),
        .ledsmain_OBUF(ledsmain_OBUF),
        .pushbuttons_IBUF(pushbuttons_IBUF),
        .temp_CLK(temp_CLK));
  IBUF \dipswitch_IBUF[0]_inst 
       (.I(dipswitch[0]),
        .O(dipswitch_IBUF[0]));
  IBUF \dipswitch_IBUF[1]_inst 
       (.I(dipswitch[1]),
        .O(dipswitch_IBUF[1]));
  IBUF \dipswitch_IBUF[2]_inst 
       (.I(dipswitch[2]),
        .O(dipswitch_IBUF[2]));
  IBUF \dipswitch_IBUF[3]_inst 
       (.I(dipswitch[3]),
        .O(dipswitch_IBUF[3]));
  Divider_CLK divideri
       (.CLK_NO_DIV_BUFG(CLK_NO_DIV_BUFG),
        .temp_CLK(temp_CLK));
  OBUF \ledsboard_OBUF[0]_inst 
       (.I(ledsboard_OBUF),
        .O(ledsboard[0]));
  OBUFT \ledsboard_OBUF[1]_inst 
       (.I(1'b0),
        .O(ledsboard[1]),
        .T(1'b1));
  OBUFT \ledsboard_OBUF[2]_inst 
       (.I(1'b0),
        .O(ledsboard[2]),
        .T(1'b1));
  OBUFT \ledsboard_OBUF[3]_inst 
       (.I(1'b0),
        .O(ledsboard[3]),
        .T(1'b1));
  OBUF \ledsmain_OBUF[0]_inst 
       (.I(ledsmain_OBUF[0]),
        .O(ledsmain[0]));
  OBUF \ledsmain_OBUF[1]_inst 
       (.I(ledsmain_OBUF[1]),
        .O(ledsmain[1]));
  OBUF \ledsmain_OBUF[2]_inst 
       (.I(ledsmain_OBUF[2]),
        .O(ledsmain[2]));
  OBUF \ledsmain_OBUF[3]_inst 
       (.I(ledsmain_OBUF[3]),
        .O(ledsmain[3]));
  IBUF \pushbuttons_IBUF[0]_inst 
       (.I(pushbuttons[0]),
        .O(pushbuttons_IBUF[0]));
  IBUF \pushbuttons_IBUF[1]_inst 
       (.I(pushbuttons[1]),
        .O(pushbuttons_IBUF[1]));
  IBUF \pushbuttons_IBUF[2]_inst 
       (.I(pushbuttons[2]),
        .O(pushbuttons_IBUF[2]));
  IBUF \pushbuttons_IBUF[3]_inst 
       (.I(pushbuttons[3]),
        .O(pushbuttons_IBUF[3]));
endmodule
`ifndef GLBL
`define GLBL
`timescale  1 ps / 1 ps

module glbl ();

    parameter ROC_WIDTH = 100000;
    parameter TOC_WIDTH = 0;

//--------   STARTUP Globals --------------
    wire GSR;
    wire GTS;
    wire GWE;
    wire PRLD;
    tri1 p_up_tmp;
    tri (weak1, strong0) PLL_LOCKG = p_up_tmp;

    wire PROGB_GLBL;
    wire CCLKO_GLBL;
    wire FCSBO_GLBL;
    wire [3:0] DO_GLBL;
    wire [3:0] DI_GLBL;
   
    reg GSR_int;
    reg GTS_int;
    reg PRLD_int;

//--------   JTAG Globals --------------
    wire JTAG_TDO_GLBL;
    wire JTAG_TCK_GLBL;
    wire JTAG_TDI_GLBL;
    wire JTAG_TMS_GLBL;
    wire JTAG_TRST_GLBL;

    reg JTAG_CAPTURE_GLBL;
    reg JTAG_RESET_GLBL;
    reg JTAG_SHIFT_GLBL;
    reg JTAG_UPDATE_GLBL;
    reg JTAG_RUNTEST_GLBL;

    reg JTAG_SEL1_GLBL = 0;
    reg JTAG_SEL2_GLBL = 0 ;
    reg JTAG_SEL3_GLBL = 0;
    reg JTAG_SEL4_GLBL = 0;

    reg JTAG_USER_TDO1_GLBL = 1'bz;
    reg JTAG_USER_TDO2_GLBL = 1'bz;
    reg JTAG_USER_TDO3_GLBL = 1'bz;
    reg JTAG_USER_TDO4_GLBL = 1'bz;

    assign (strong1, weak0) GSR = GSR_int;
    assign (strong1, weak0) GTS = GTS_int;
    assign (weak1, weak0) PRLD = PRLD_int;

    initial begin
	GSR_int = 1'b1;
	PRLD_int = 1'b1;
	#(ROC_WIDTH)
	GSR_int = 1'b0;
	PRLD_int = 1'b0;
    end

    initial begin
	GTS_int = 1'b1;
	#(TOC_WIDTH)
	GTS_int = 1'b0;
    end

endmodule
`endif
