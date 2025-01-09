library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
use std.textio.all;
use ieee.std_logic_textio.all;
    
entity Serial_sim is

end Serial_sim;

Architecture Behavioral of Serial_sim is
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
    
    file input_buf : text;

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
    
       stimulus: process
       
       variable read_input : line;
       
       variable a0_txt : std_logic;
       variable a1_txt : std_logic;
       variable a2_txt : std_logic;
       variable ne1_txt : std_logic;
       variable ne2_txt : std_logic;
       variable e3_txt : std_logic;

       
       variable y0_txt : std_logic;
       variable y1_txt : std_logic;
       variable y2_txt : std_logic;
       variable y3_txt : std_logic;
       variable y4_txt : std_logic;
       variable y5_txt : std_logic;
       variable y6_txt : std_logic;
       variable y7_txt : std_logic;
            
        begin

        file_open(input_buf, "C:\BSUIR\7semestr\apcu\lab3\generate\test.txt", read_mode);
    
        while not endfile(input_buf) loop
        readline(input_buf, read_input);
        
        read(read_input, a0_txt);
        read(read_input, a1_txt);
        read(read_input, a2_txt);
        read(read_input, ne1_txt);
        read(read_input, ne2_txt);
        read(read_input, e3_txt);
        read(read_input, y0_txt);
        read(read_input, y1_txt);
        read(read_input, y2_txt);
        read(read_input, y3_txt);
        read(read_input, y4_txt);
        read(read_input, y5_txt);
        read(read_input, y6_txt);
        read(read_input, y7_txt);

        a0<=a0_txt;
        a1<=a1_txt;
        a2<=a2_txt;
        ne1<=ne1_txt;
        ne2<=ne2_txt;
        e3<=e3_txt;
        wait for 5 ns;
        
        if y0 /= y0_txt then
            report "Ошибка: y0 не соответствует ожидаемому значению" severity ERROR;
            report "Значение y0 должно быть : " & std_logic'image(y0_txt);
        end if;
         
        if y1 /= y1_txt then
            report "Ошибка: y1 не соответствует ожидаемому значению" severity ERROR;
            report "Значение y1 должно быть : " & std_logic'image(y1_txt);
        end if;
                                            
        if y2 /= y2_txt then
            report "Ошибка: y2 не соответствует ожидаемому значению" severity ERROR;
            report "Значение y2 должно быть : " & std_logic'image(y2_txt);
        end if;
                                                              
        if y3 /= y3_txt then
            report "Ошибка: y3 не соответствует ожидаемому значению" severity ERROR;
            report "Значение y3 должно быть : " & std_logic'image(y3_txt);
        end if; 
        
        if y4 /= y4_txt then
            report "Ошибка: y4 не соответствует ожидаемому значению" severity ERROR;
            report "Значение y4 должно быть : " & std_logic'image(y4_txt);
        end if;
         
        if y5 /= y5_txt then
            report "Ошибка: y5 не соответствует ожидаемому значению" severity ERROR;
            report "Значение y5 должно быть : " & std_logic'image(y5_txt);
        end if;
                                            
        if y6 /= y6_txt then
            report "Ошибка: y6 не соответствует ожидаемому значению" severity ERROR;
            report "Значение y6 должно быть : " & std_logic'image(y6_txt);
        end if;
                                                              
        if y7 /= y7_txt then
            report "Ошибка: y7 не соответствует ожидаемому значению" severity ERROR;
            report "Значение y7 должно быть : " & std_logic'image(y7_txt);
        end if;
              
        end loop;    
        file_close(input_buf);
        wait;
        end process;
            
end Behavioral;
