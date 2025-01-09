library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity Parallel is
    Port (
    a0, a1, a2: in std_logic;
    ne1, ne2, e3: in std_logic;
    y0, y1, y2, y3, y4, y5, y6, y7: out std_logic
    );
end Parallel;

architecture Behavioral of Parallel is
    signal temp: std_logic_vector(0 to 7);
begin
    temp(0) <= not a0;
    temp(1) <= a0;
    temp(2) <= not a1;
    temp(3) <= a1;
    temp(4) <= not a2;
    temp(5) <= a2;
    temp(6) <= not e3;
    temp(7) <= (not ne1) and (not ne2) and (not temp(6));
    
    y0 <= temp(0) and temp(2) and temp(4) and temp(7);
    y1 <= temp(1) and temp(2) and temp(4) and temp(7);
    y2 <= temp(0) and temp(4) and temp(3) and temp(7);
    y3 <= temp(1) and temp(4) and temp(3) and temp(7);
    y4 <= temp(0) and temp(2) and temp(5) and temp(7);
    y5 <= temp(1) and temp(2) and temp(5) and temp(7);
    y6 <= temp(0) and temp(5) and temp(3) and temp(7);
    y7 <= temp(1) and temp(5) and temp(3) and temp(7);

end Behavioral;
