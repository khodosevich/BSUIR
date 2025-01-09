library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
use std.textio.all;
use ieee.std_logic_textio.all;

entity Serial_sim2 is
end Serial_sim2;

architecture Behavioral of Serial_sim2 is

    component Serial
        Port (
            a0, a1, a2: in std_logic;
            ne1, ne2, e3: in std_logic;
            y0, y1, y2, y3, y4, y5, y6, y7: out std_logic
        );
    end component;

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
    signal ref_y0, ref_y1, ref_y2, ref_y3, ref_y4, ref_y5, ref_y6, ref_y7: std_logic;
    
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

    REF : Parallel port map(
        a0 => a0,
        a1 => a1,
        a2 => a2,
        ne1 => ne1,
        ne2 => ne2,
        e3 => e3,
        y0 => ref_y0,
        y1 => ref_y1,
        y2 => ref_y2,
        y3 => ref_y3,
        y4 => ref_y4,
        y5 => ref_y5,
        y6 => ref_y6,
        y7 => ref_y7
    );

    stimulus: process
        variable read_input : line;

        variable a0_txt, a1_txt, a2_txt : std_logic;
        variable ne1_txt, ne2_txt, e3_txt : std_logic;


    begin
        file_open(input_buf, "C:\BSUIR\7semestr\apcu\lab3\generate\test2.txt", read_mode);

        while not endfile(input_buf) loop
            readline(input_buf, read_input);

            read(read_input, a0_txt);
            read(read_input, a1_txt);
            read(read_input, a2_txt);
            read(read_input, ne1_txt);
            read(read_input, ne2_txt);
            read(read_input, e3_txt);

            a0 <= a0_txt;
            a1 <= a1_txt;
            a2 <= a2_txt;
            ne1 <= ne1_txt;
            ne2 <= ne2_txt;
            e3 <= e3_txt;

            wait for 10 ns;

        if y0 /= ref_y0 then
            report "Ошибка: y0 не соответствует ожидаемому значению" severity ERROR;
            report "Значение y0 должно быть : " & std_logic'image(ref_y0);
        end if;
         
        if y1 /= ref_y1 then
            report "Ошибка: y1 не соответствует ожидаемому значению" severity ERROR;
            report "Значение y1 должно быть : " & std_logic'image(ref_y1);
        end if;
                                            
        if y2 /= ref_y2 then
            report "Ошибка: y2 не соответствует ожидаемому значению" severity ERROR;
            report "Значение y2 должно быть : " & std_logic'image(ref_y2);
        end if;
                                                              
        if y3 /= ref_y3 then
            report "Ошибка: y3 не соответствует ожидаемому значению" severity ERROR;
            report "Значение y3 должно быть : " & std_logic'image(ref_y3);
        end if; 
        
        if y4 /= ref_y4 then
            report "Ошибка: y4 не соответствует ожидаемому значению" severity ERROR;
            report "Значение y4 должно быть : " & std_logic'image(ref_y4);
        end if;
         
        if y5 /= ref_y5 then
            report "Ошибка: y5 не соответствует ожидаемому значению" severity ERROR;
            report "Значение y5 должно быть : " & std_logic'image(ref_y5);
        end if;
                                            
        if y6 /= ref_y6 then
            report "Ошибка: y6 не соответствует ожидаемому значению" severity ERROR;
            report "Значение y6 должно быть : " & std_logic'image(ref_y6);
        end if;
                                                              
        if y7 /= ref_y7 then
            report "Ошибка: y7 не соответствует ожидаемому значению" severity ERROR;
            report "Значение y7 должно быть : " & std_logic'image(ref_y7);
        end if;
        
        end loop;

        file_close(input_buf);
        wait;
    end process;
end Behavioral;
