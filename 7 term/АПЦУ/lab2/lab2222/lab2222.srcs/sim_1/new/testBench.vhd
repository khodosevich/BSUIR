
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;


entity testBench is
end testBench;

architecture Behavioral of testBench is
component counter
Port(
NOT_LOAD : in std_logic;
NOT_UD : in std_logic;
NOT_ENT : in std_logic;
NOT_ENP : in std_logic;
CLK : in std_logic;
A : in std_logic;
B : in std_logic;
C : in std_logic;
D : in std_logic;
NOT_RCO : out std_logic;
Qa : out std_logic;
Qb : out std_logic;
Qc : out std_logic;
Qd : out std_logic
);
end component;
signal A: std_logic :='0';
signal B: std_logic :='0';
signal C: std_logic :='1';
signal D: std_logic :='1';

signal Qa: std_logic:='0';
signal Qb: std_logic:='0';
signal Qc: std_logic:='0';
signal Qd: std_logic:='0';
signal NOT_RCO: std_logic;

signal NOT_LOAD: std_logic:= '0';
signal NOT_ENP: std_logic:= '0';
signal NOT_ENT: std_logic:= '0';
signal NOT_UD: std_logic:= '1';
signal CLK :std_logic:= '0';

begin
uut: counter port map(
CLK=> CLK,
NOT_UD =>NOT_UD,
NOT_ENT =>NOT_ENT,
NOT_ENP =>NOT_ENP,
NOT_LOAD =>NOT_LOAD,
NOT_RCO =>NOT_RCO,
Qd =>Qd,
Qa =>Qa,
Qb =>Qb,
Qc =>Qc,
A =>A,
B =>B,
C =>C,
D =>D
);

CLK <= not CLK after 20 ns;
NOT_LOAD<='1' after 40 ns;
NOT_UD <= '0' after 260 ns;
NOT_ENP<= '1' after 240 ns, '0' after 320 ns;
NOT_ENT<= '1' after 240 ns, '0' after 320 ns;


end Behavioral;
