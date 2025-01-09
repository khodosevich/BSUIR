library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity counter_test_tb is
--  Port ( );
end counter_test_tb;

architecture Behavioral of counter_test_tb is



component counter
port(
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


component counter_test
port(
    NOT_LOAD : in std_logic;
    NOT_UD : in std_logic;
    NOT_ENT : in std_logic;
    NOT_ENP : in std_logic;
    CLK : in std_logic;
    A : in std_logic;
    B : in std_logic;
    C : in std_logic;
    D : in std_logic;
--NOT_RCO : out std_logic;
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

signal Qa: std_logic;
signal Qb: std_logic;
signal Qc: std_logic;
signal Qd: std_logic;
signal NOT_RCO: std_logic;

signal NOT_LOAD: std_logic:= '0';
signal NOT_ENP: std_logic:= '0';
signal NOT_ENT: std_logic:= '0';
signal NOT_UD: std_logic:= '1';
signal CLK :std_logic:= '0';


--signal NOT_RCO_test : std_logic;
signal Qa_test : std_logic;
signal Qb_test : std_logic;
signal Qc_test : std_logic;
signal Qd_test : std_logic;


begin


counter_uut: counter
port map(
    NOT_LOAD =>NOT_LOAD,
    NOT_UD =>NOT_UD,
    NOT_ENT =>NOT_ENT,
    NOT_ENP =>NOT_ENP,
    CLK =>CLK,------------------------
    A =>A,
    B =>B,
    C =>C,
    D =>D,
    NOT_RCO=>NOT_RCO ,
    Qa =>Qa,
    Qb =>Qb,
    Qc =>Qc,
    Qd =>Qd
);

counter_uut_test: counter_test 
port map(
    NOT_LOAD =>NOT_LOAD,
    NOT_UD =>NOT_UD,
    NOT_ENT =>NOT_ENT,
    NOT_ENP =>NOT_ENP,
    CLK =>CLK,-------------
    A =>A,
    B =>B,
    C =>C,
    D =>D,
--NOT_RCO=>NOT_RCO_test ,
    Qa =>Qa_test,
    Qb =>Qb_test,
    Qc =>Qc_test,
    Qd =>Qd_test
);

CLK <= not CLK after 20 ns;
NOT_LOAD<='1' after 40 ns;
NOT_UD <= '0' after 260 ns;
NOT_ENP<= '1' after 240 ns, '0' after 320 ns;
NOT_ENT<= '1' after 240 ns, '0' after 320 ns;

process(CLK)
    begin
        if rising_edge(CLK) then
            -- Здесь можно добавить условия проверки
            assert (Qa = Qa_test) report "Qa mismatch!" severity error;
            assert (Qb = Qb_test) report "Qb mismatch!" severity error;
            assert (Qc = Qc_test) report "Qc mismatch!" severity error;
            assert (Qd = Qd_test) report "Qd mismatch!" severity error;
            --assert (NOT_RCO = NOT_RCO_test) report "NOT_RCO mismatch!" severity error;
        end if;
    end process;

end Behavioral;
