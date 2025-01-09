library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity test_jk is
--  Port ( );
end test_jk;

architecture Behavioral of test_jk is
    component jk is
         Port ( 
              NOT_R : in STD_LOGIC;
              NOT_S : in STD_LOGIC;
              J : in STD_LOGIC;
              K : in STD_LOGIC;
              CLK : in STD_LOGIC;
              Q : out STD_LOGIC;    
              NOT_Q : out STD_LOGIC);
    end component;    
    signal NOT_R : STD_LOGIC;
    signal NOT_S : STD_LOGIC;
    signal J : STD_LOGIC;
    signal K : STD_LOGIC;
    signal CLK : STD_LOGIC;
    signal Q : STD_LOGIC;
    signal NOT_Q : STD_LOGIC;
begin
    JK_TEST: jk port map (
        NOT_S => NOT_S,
        NOT_R => NOT_R,
        J => J,
        K => K,
        CLK => CLK,
        Q => Q,
        NOT_Q => NOT_Q
    );
    
        stimulis: process
    begin
       J <= '0';
       K <= '0';
       NOT_R <= '1';
       NOT_S <= '1'; 
       wait for 40 ns;
       
       J <= '1';
       K <= '0';
       wait for 20 ns;
       
       J <= '0';
       K <= '1';
       wait for 20 ns;
              
       J <= '1';
       K <= '1';
       wait for 20 ns;
       
       J <= '1';
       K <= '0';
       NOT_R <= '0';
       wait for 20 ns;
       
       NOT_R <= '1';
       J <= '1';
       wait for 20 ns;
       
       NOT_S <= '0';
       J <= '0';
       K <= '1';
       wait for 20 ns;      
       end process;
clocking: process
       begin
           CLK <= '0';
           wait for 10 ns;
           CLK <= '1';
           wait for 10 ns;    
       end process;
end Behavioral;
