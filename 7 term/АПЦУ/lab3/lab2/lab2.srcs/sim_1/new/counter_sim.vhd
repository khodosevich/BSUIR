library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
use std.textio.all;
use ieee.std_logic_textio.all;

entity counter_sim is
end counter_sim;

architecture Behavioral of counter_sim is
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
signal A: std_logic;
signal B: std_logic;
signal C: std_logic;
signal D: std_logic;

signal Qa: std_logic;
signal Qb: std_logic;
signal Qc: std_logic;
signal Qd: std_logic;
signal NOT_RCO: std_logic;

signal NOT_LOAD: std_logic;
signal NOT_ENP: std_logic;
signal NOT_ENT: std_logic;
signal NOT_UD: std_logic;
signal CLK :std_logic;

signal ERR: std_logic := '0';

file input_buf : text;

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

stimulus: process
       
       variable read_input : line;
       
       variable CLK_txt : std_logic;
       variable NOT_UD_txt : std_logic;
       variable NOT_ENT_txt : std_logic;
       variable NOT_ENP_txt : std_logic;
       variable NOT_LOAD_txt : std_logic;
       variable NOT_RCO_txt : std_logic;
       variable A_txt : std_logic;
       variable B_txt : std_logic;
       variable C_txt : std_logic;
       variable D_txt : std_logic;
       
       variable Qa_txt : std_logic;
       variable Qb_txt : std_logic;
       variable Qc_txt : std_logic;
       variable Qd_txt : std_logic;
       
       variable space_txt : character;
              
        begin

        file_open(input_buf, "C:\BSUIR\7semestr\apcu\lab3\generate\test3.txt", read_mode);
    
        while not endfile(input_buf) loop
        readline(input_buf, read_input);
        
        read(read_input, NOT_LOAD_txt);
        --read(read_input, space_txt);
        read(read_input, NOT_UD_txt);
        --read(read_input, space_txt);
        read(read_input, NOT_ENT_txt);
        --read(read_input, space_txt);
        read(read_input, NOT_ENP_txt);
        --read(read_input, space_txt);
        read(read_input, CLK_txt);
        --read(read_input, space_txt);
        read(read_input, A_txt);
        --read(read_input, space_txt);
        read(read_input, B_txt);
        --read(read_input, space_txt);
        read(read_input, C_txt);
        --read(read_input, space_txt);
        read(read_input, D_txt);
        --read(read_input, space_txt);
        read(read_input, Qa_txt);
        --read(read_input, space_txt);
        read(read_input, Qb_txt);
        --read(read_input, space_txt);
        read(read_input, Qc_txt);
        --read(read_input, space_txt);
        read(read_input, Qd_txt);
        --read(read_input, space_txt);
        read(read_input, NOT_RCO_txt);
        
        NOT_LOAD<=NOT_LOAD_txt;
        NOT_UD<=NOT_UD_txt;
        NOT_ENT<=NOT_ENT_txt;
        NOT_ENP<=NOT_ENP_txt;
        A<=A_txt;
        B<=B_txt;
        C<=C_txt;
        D<=D_txt;
        
        wait for 5 ns;
        CLK<=CLK_txt;
        wait for 2 ns;
              
        if Qa = Qa_txt and Qb = Qb_txt and Qc = Qc_txt and Qd = Qd_txt and NOT_RCO = NOT_RCO_txt then
            ERR <= '0';
        else
            ERR <= '1';
        end if;
        --wait for 1 ns;

       
       if Qa /= Qa_txt or Qb /= Qb_txt or Qc /= Qc_txt or Qd /= Qd_txt or NOT_RCO /= NOT_RCO_txt then
            report "Входные значения:" severity note;
            report "NOT_LOAD_txt: " & std_logic'image(NOT_LOAD_txt) & 
                 ", NOT_UD_txt: " & std_logic'image(NOT_UD_txt) & 
                 ", NOT_ENT_txt: " & std_logic'image(NOT_ENT_txt) & 
                 ", NOT_ENP_txt: " & std_logic'image(NOT_ENT_txt) & 
                 ", CLK_txt: " & std_logic'image(CLK_txt) & 
                 ", A_txt: " & std_logic'image(A_txt) & 
                 ", B_txt: " & std_logic'image(B_txt) & 
                 ", C_txt: " & std_logic'image(C_txt) & 
                 ", D_txt: " & std_logic'image(D_txt) severity note;
            report "Выходные значения:" severity note;
            report "Qa: " & std_logic'image(Qa) & 
                 ", Qb: " & std_logic'image(Qb) & 
                 ", Qc: " & std_logic'image(Qc) & 
                 ", Qd: " & std_logic'image(Qd) & 
                 ", NOT_RCO: " & std_logic'image(NOT_RCO) severity note;
               
            report "Ожидаемые значения:" severity note;
            report "Qa_txt: " & std_logic'image(Qa_txt) & 
                 ", Qb_txt: " & std_logic'image(Qb_txt) & 
                 ", Qc_txt: " & std_logic'image(Qc_txt) & 
                 ", Qd_txt: " & std_logic'image(Qd_txt) & 
                 ", NOT_RCO_txt: " & std_logic'image(NOT_RCO_txt) severity note;
       end if;
       
        if Qa /= Qa_txt then
            report "Ошибка: Qa не соответствует ожидаемому значению" severity ERROR;
            report "Значение Qa должно быть : " & std_logic'image(Qa_txt);
            
        end if;
         
        if Qb /= Qb_txt then
            report "Ошибка: Qb не соответствует ожидаемому значению" severity ERROR;
            report "Значение Qb должно быть : " & std_logic'image(Qb_txt);
        end if;
                                            
        if Qc /= Qc_txt then
            report "Ошибка: Qc не соответствует ожидаемому значению" severity ERROR;
            report "Значение Qc должно быть : " & std_logic'image(Qc_txt);
        end if;
                                                              
        if Qd /= Qd_txt then
            report "Ошибка: Qd не соответствует ожидаемому значению" severity ERROR;
            report "Значение Qd должно быть : " & std_logic'image(Qd_txt);
        end if; 
        
        if NOT_RCO /= NOT_RCO_txt then
            report "Ошибка: NOT_RCO не соответствует ожидаемому значению" severity ERROR;
            report "Значение NOT_RCO должно быть : " & std_logic'image(NOT_RCO_txt);
        end if;
               
        end loop;    
        file_close(input_buf);
        wait;
        end process;
            
end Behavioral;
