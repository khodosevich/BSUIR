library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity SerialSimulation is

end SerialSimulation;

Architecture Behavioral of SerialSimulation is
    component Serial
        Port (
            a0, a1, a2: in std_logic;
            ne1, ne2, e3: in std_logic;
            y0, y1, y2, y3, y4, y5, y6, y7: out std_logic
        );
    end component;
    signal a0, a1, a2: std_logic;
    signal ne1, ne2, e3: std_logic;
    signal y0, y1, y2, y3, y4, y5, y6, y7: std_logic;
    
    signal a0_2, a1_2, a2_2: std_logic;
    signal ne1_2, ne2_2, e3_2: std_logic;
    signal y0_2, y1_2, y2_2, y3_2, y4_2, y5_2, y6_2, y7_2: std_logic;
begin
    UUT : Serial port map(
        a0 => a0,
        a1 => a1,
        a2 => a2,
        ne1 => ne1,
        ne2 => ne2,
        e3 => e3,
        y0 => y0,
        y1 => y1,
        y2 => y2,
        y3 => y3,
        y4 => y4,
        y5 => y5,
        y6 => y6,
        y7 => y7
    );
    
    UUT2 : Serial port map(
        a0 => a0_2,
        a1 => a1_2,
        a2 => a2_2,
        ne1 => ne1_2,
        ne2 => ne2_2,
        e3 => e3_2,
        y0 => y0_2,
        y1 => y1_2,
        y2 => y2_2,
        y3 => y3_2,
        y4 => y4_2,
        y5 => y5_2,
        y6 => y6_2,
        y7 => y7_2
    );
    stimulus: process
        begin
            --0
            a0 <= 'X';
            a1 <= 'X';
            a2 <= 'X';
            ne1 <= '1';
            ne2 <= 'X';
            e3 <= 'X';
            wait for 10ns;
            
            a0_2 <= 'X';
            a1_2 <= 'X';
            a2_2 <= 'X';
            ne1_2 <= '1';
            ne2_2 <= 'X';
            e3_2 <= 'X';
            wait for 10ns;
            
            --1
            ne1 <= 'X';
            e3 <= '0';
            wait for 10ns;
            
            ne1_2 <= 'X';
            e3_2 <= '0';
            wait for 10ns;
            
            --2
            ne2 <= '1';
            e3 <= 'X';
            wait for 10ns;
            
            ne2_2 <= '1';
            e3_2 <= 'X';
            wait for 10ns;
            
            --3
            a0 <= '0';
            a1 <= '0';
            a2 <= '0';
            ne1 <= '0';
            ne2 <= '0';
            e3 <= '1';
            wait for 10ns;
            
            a0_2 <= '0';
            a1_2 <= '0';
            a2_2 <= '0';
            ne1_2 <= '0';
            ne2_2 <= '0';
            e3_2 <= '1';
            wait for 10ns;

            --4
            a0 <= '1';
            wait for 10ns;
            
            a0_2 <= '1';
            wait for 10ns;
            
            --5
            a0 <= '0';
            a1 <= '1';
            wait for 10ns;
            
            a0_2 <= '0';
            a1_2 <= '1';
            wait for 10ns;
            
            --6
            a0 <= '1';
            wait for 10ns;
            
            a0_2 <= '1';
            wait for 10ns;
            
            --7
            a0 <= '0';
            a1 <= '0';
            a2 <= '1';
            wait for 10ns;
            
            a0_2 <= '0';
            a1_2 <= '0';
            a2_2 <= '1';
            wait for 10ns;

            
            --8
            a0 <= '1';
            wait for 10ns;
            
                        a0_2 <= '1';
            wait for 10ns;
            
            --9
            a0 <= '0';
            a1 <= '1';
            wait for 10ns;
            
                        a0_2 <= '0';
            a1_2 <= '1';
            wait for 10ns;
            
            --10
            a0 <= '1';
            wait for 10ns;
            
                        a0_2 <= '1';
            wait for 10ns;
        end process;
            
end Behavioral;
