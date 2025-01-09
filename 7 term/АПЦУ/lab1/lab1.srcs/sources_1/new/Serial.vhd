library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity Serial is
    Port (
        a0, a1, a2: in std_logic;
        ne1, ne2, e3: in std_logic;
        y0, y1, y2, y3, y4, y5, y6, y7: out std_logic
    );
end Serial;

architecture Behavioral of Serial is

begin
    process(a0, a1, a2, ne1, ne2, e3)
    begin
        if(ne1 = '1') then y0 <= '0'; y1 <= '0'; y2 <= '0'; y3 <= '0'; y4 <= '0'; y5 <= '0'; y6 <= '0'; y7 <= '0';
        elsif(ne2 = '1') then y0 <= '0'; y1 <= '0'; y2 <= '0'; y3 <= '0'; y4 <= '0'; y5 <= '0'; y6 <= '0'; y7 <= '0';
        elsif(e3 = '0') then y0 <= '0'; y1 <= '0'; y2 <= '0'; y3 <= '0'; y4 <= '0'; y5 <= '0'; y6 <= '0'; y7 <= '0';
        elsif(a0 = '0' and a1 = '0' and a2 = '0') then y0 <= '1'; y1 <= '0'; y2 <= '0'; y3 <= '0'; y4 <= '0'; y5 <= '0'; y6 <= '0'; y7 <= '0';
        elsif(a0 = '1' and a1 = '0' and a2 = '0') then y0 <= '0'; y1 <= '1'; y2 <= '0'; y3 <= '0'; y4 <= '0'; y5 <= '0'; y6 <= '0'; y7 <= '0';
        elsif(a0 = '0' and a1 = '1' and a2 = '0') then y0 <= '0'; y1 <= '0'; y2 <= '1'; y3 <= '0'; y4 <= '0'; y5 <= '0'; y6 <= '0'; y7 <= '0';
        elsif(a0 = '1' and a1 = '1' and a2 = '0') then y0 <= '0'; y1 <= '0'; y2 <= '0'; y3 <= '1'; y4 <= '0'; y5 <= '0'; y6 <= '0'; y7 <= '0';
        elsif(a0 = '0' and a1 = '0' and a2 = '1') then y0 <= '0'; y1 <= '0'; y2 <= '0'; y3 <= '0'; y4 <= '1'; y5 <= '0'; y6 <= '0'; y7 <= '0';
        elsif(a0 = '1' and a1 = '0' and a2 = '1') then y0 <= '0'; y1 <= '0'; y2 <= '0'; y3 <= '0'; y4 <= '0'; y5 <= '1'; y6 <= '0'; y7 <= '0';
        elsif(a0 = '0' and a1 = '1' and a2 = '1') then y0 <= '0'; y1 <= '0'; y2 <= '0'; y3 <= '0'; y4 <= '0'; y5 <= '0'; y6 <= '1'; y7 <= '0';
        elsif(a0 = '1' and a1 = '1' and a2 = '1') then y0 <= '0'; y1 <= '0'; y2 <= '0'; y3 <= '0'; y4 <= '0'; y5 <= '0'; y6 <= '0'; y7 <= '1';
        end if;
    end process;
end Behavioral;
