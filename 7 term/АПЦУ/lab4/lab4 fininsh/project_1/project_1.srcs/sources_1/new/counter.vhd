library IEEE;
use IEEE.STD_LOGIC_1164.ALL;


entity counter is
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
end counter;

architecture Behavioral of counter is
component jk is
port (
    NOT_R : in STD_LOGIC := '1';
    NOT_S : in STD_LOGIC := '1';
    J : in STD_LOGIC;
    K : in STD_LOGIC;
    CLK : in STD_LOGIC;
    Q : out STD_LOGIC;    
    NOT_Q : out STD_LOGIC);
end component;

signal LOAD : std_logic;
signal ENP : std_logic;
signal ENT : std_logic;
signal UD : std_logic;

signal t1 : std_logic;
signal t3:  std_logic;
signal t4:  std_logic;
signal t5 :  std_logic;
signal t6:  std_logic;
signal J1 :  std_logic;
signal J2 :  std_logic;
signal J3:  std_logic;
signal J4 :  std_logic;

signal NOT_J1 : std_logic;
signal NOT_J2 : std_logic;
signal NOT_J3 : std_logic;
signal NOT_J4 : std_logic;

signal Da : std_logic;
signal Db : std_logic;
signal Dc : std_logic;
signal Dd : std_logic;

signal NOT_Da : std_logic;
signal NOT_Db : std_logic;
signal NOT_Dc : std_logic;
signal NOT_Dd : std_logic;

begin

LOAD<= not NOT_LOAD;
ENP<= not NOT_ENP;
ENT<= not NOT_ENT;
UD<= not NOT_UD;

t1<= ENP and ENT and NOT_LOAD;

NOT_RCO<=(t3 and t4 and t5 and t6 and ENT and UD) NOR (t3 and t4 and t5 and t6 and ENT and NOT_UD);

t3<=(NOT_UD and NOT_Da) NOR (UD and Da);
t4<=(NOT_UD and NOT_Db) NOR (UD and Db);
t5<=(NOT_UD and NOT_Dc) NOR (UD and Dc);
t6<=(NOT_UD and NOT_Dd) NOR (UD and Dd);
J1<= ((NOT_LOAD and Da) XOR t1) NOR (LOAD and A);
J2<= ((NOT_LOAD and Db) XOR (t1 and t3)) NOR (LOAD and B);
J3<= ((NOT_LOAD and Dc) XOR (t1 and t3 and t4)) NOR (LOAD and C);
J4<= ((NOT_LOAD and Dd) XOR (t1 and t3 and t4 and t5)) NOR (LOAD and D);
NOT_J1<= not J1;
NOT_J2<= not J2;
NOT_J3<= not J3;
NOT_J4<= not J4;

D1: jk port map(
J=> NOT_J1,
K=> J1 ,
CLK=> CLK,
Q => Da,
NOT_Q=>NOT_Da
);

D2: jk port map(
J=> NOT_J2,
K=> J2 ,
CLK=> CLK,
Q => Db,
NOT_Q=>NOT_Db
);

D3: jk port map(
J=> NOT_J3,
K=> J3 ,
CLK=> CLK,
Q => Dc,
NOT_Q=>NOT_Dc
);

D4: jk port map(
J=> NOT_J4,
K=> J4 ,
CLK=> CLK,
Q => Dd,
NOT_Q=>NOT_Dd
);

Qa<=not NOT_Da;
Qb<=not NOT_Db;
Qc<=not NOT_Dc;
Qd<=not NOT_Dd;

end Behavioral;
