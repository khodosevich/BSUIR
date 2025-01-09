library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;


entity counter_test is
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
end counter_test;

architecture Behavioral of counter_test is

begin

    process(CLK)
    variable count : std_logic_vector(3 downto 0) := "0000";
    begin

    if rising_edge(CLK) then
                if NOT_ENP = '0' and NOT_ENT = '0' then  -- Счетчик работает
                    if NOT_LOAD = '0' then  -- Загрузка начального значения
                        count := D & C & B & A;  -- Считываем значения A, B, C, D
                    else
                        if NOT_UD = '1' then  -- Счет вверх
                            count := count + 1;
                        else  -- Счет вниз
                            count := count - 1;
                        end if;
                    end if;
                end if;
            end if;
            Qa <= count(0);
                    Qb <= count(1);
                    Qc <= count(2);
                    Qd <= count(3);
                    --if (count = "1111" or count = "0000") then
                                    --NOT_RCO <= '0';
                                --else
                                    --NOT_RCO <= '1';
                                --end if;
        end process;
    
end Behavioral;
