library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity Divider_CLK is
    Port ( CLK_IN : in STD_LOGIC;
           CLK_OUT : out STD_LOGIC);
end Divider_CLK;

architecture Behavioral of Divider_CLK is
    signal temp_CLK : std_logic := '0';
    
    constant divide_value: integer := 200000000 / 2; -- Делитель частоты
begin
    process (CLK_IN)
       variable i  : integer := 0;
    begin
        if CLK_IN'event and CLK_IN = '1' then
            if (i = divide_value) then
                i := 0;
                temp_CLK <= not temp_CLK;
            else 
                i := i + 1;
            end if;
        end if;
    end process;
    
    CLK_OUT <= temp_CLK;       
end Behavioral;
