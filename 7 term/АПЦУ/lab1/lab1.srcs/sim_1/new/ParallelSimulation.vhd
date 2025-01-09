library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity ParallelSimulation is

end ParallelSimulation;

Architecture Behavioral of ParallelSimulation is
    component Parallel
        Port (
            a0, a1, a2: in std_logic;
            ne1, ne2, e3: in std_logic;
            y0, y1, y2, y3, y4, y5, y6, y7: out std_logic
        );
    end component;
    signal a0, a1, a2: std_logic;
    signal ne1, ne2, e3: std_logic;
    signal y0, y1, y2, y3, y4, y5, y6, y7: std_logic;
begin
    UUT : Parallel port map(
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
            
            --1
            ne1 <= 'X';
            e3 <= '0';
            wait for 10ns;
            
            --2
            ne2 <= '1';
            e3 <= 'X';
            wait for 10ns;
            
            --3
            a0 <= '0';
            a1 <= '0';
            a2 <= '0';
            ne1 <= '0';
            ne2 <= '0';
            e3 <= '1';
            wait for 10ns;

            --4
            a0 <= '1';
            wait for 10ns;
            
            --5
            a0 <= '0';
            a1 <= '1';
            wait for 10ns;
            
            --6
            a0 <= '1';
            wait for 10ns;
            
            --7
            a0 <= '0';
            a1 <= '0';
            a2 <= '1';
            wait for 10ns;
            
            --8
            a0 <= '1';
            wait for 10ns;
            
            --9
            a0 <= '0';
            a1 <= '1';
            wait for 10ns;
            
            --10
            a0 <= '1';
            wait for 10ns;
        end process;
            
end Behavioral;
