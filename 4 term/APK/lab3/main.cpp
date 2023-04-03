#include <stdio.h>
#include <conio.h>
#include <dos.h>

#define c4 261u
#define d4 293u
#define e4 329u
#define f4 349u
#define g4 392u
#define a4 440u
#define b4 493u
#define a3 220u
#define b3 247u
#define gb4 415u
#define c5 523u

void stateWords(void)
{
    unsigned channel, state;

    // Порт 40h (канал 0, прерывание системных часов)
    // Порт 41h (канал 1, регенерация памяти)
    // Порт 42h (канал 2, звук из динамика)

    int ports[] = { 0x40, 0x41, 0x42 };

    // 11 - RBC (всегда 11)
    // 1 -  забываем про CE
    // 0 - считывание канала состояния
    // 001, 010, 100 - канал
    // 0 - всегда 0
    //                11 1 0 001 0, 11 1 0 010 0, 11 1 0 100 0
    int  controlWord[] = { 226, 228, 232 };

    // Почти такой же, как регистр управления (в setFrequency)
    // 6 - проверка, готов ли таймер к считыванию
    // 7 - ВЫХОД: проверка состояния линии
    char stateWord[] = "76000000";


    printf("Status word: \n");
    for (channel = 0; channel < 3; channel++)
    {
        // Выбираем канал (команды CLC) в регистре команд
        outp(0x43, controlWord[channel]);
        // Читаем состояние
        state = inp(ports[channel]);

        //преобразовываем состояние в двоичный файл
        for (int i = 7; i >= 0; i--)
        {
            stateWord[i] = (char)((state % 2) + '0');
            state /= 2;
        }
        printf("Channel %d: %s\n", channel, stateWord);
    }
}

void setFrequency(unsigned divider)
{
    unsigned long kd = 1193180 / divider;

    // 10 11 011 0:
    // 10 - канал
    // 11 - чтение/запись младшего, затем старшего байта
    // 011 - меандр
    // 0 - ячейка
    outp(0x43, 0xB6);
    //Наименьший байт делителя частоты
    outp(0x42, kd % 256);
    kd /= 256;
    //Самый старший байт делителя частоты
    outp(0x42, kd);
}

void playMusic(void)
{
    int i;
    unsigned notes[61][3] = {
            {a4, 150u, 150u},
            {e4, 150u, 150u},
            {a4, 150u, 150u},
            {e4, 150u, 150u},
            {a4, 150u, 150u},
            {gb4, 150u, 150u},
            {gb4, 150u, 300u},
            {gb4, 150u, 150u},
            {e4, 150u, 150u},
            {gb4, 150u, 150u},
            {e4, 150u, 150u},
            {gb4, 150u, 150u},
            {a4, 150u, 150u},
            {a4, 150u, 300u},
            {a4, 150u, 150u},
            {e4, 150u, 150u},
            {a4, 150u, 150u},
            {e4, 150u, 150u},
            {a4, 150u, 150u},
            {gb4, 150u, 150u},
            {gb4, 150u, 300u},
            {gb4, 150u, 150u},
            {e4, 150u, 150u},
            {gb4, 150u, 150u},
            {e4, 150u, 150u},
            {gb4, 150u, 150u},
            {e4, 300u, 300u},
            {a4, 150u, 150u},
            {b4, 150u, 150u},
            {b4, 85u, 150u},
            {b4, 85u, 150u},
            {b4, 150u, 150u},
            {b4, 150u, 150u},
            {c5, 150u, 150u},
            {c5, 85u, 150u},
            {c5, 85u, 150u},
            {c5, 150u, 150u},
            {c5, 150u, 150u},
            {c5, 150u, 150u},
            {c5, 150u, 150u},
            {b4, 150u, 150u},
            {a4, 150u, 150u},
            {gb4, 150u, 150u},
            {a4, 150u, 150u},
            {a4, 150u, 300u},
            {a4, 150u, 150u},
            {b4, 150u, 150u},
            {b4, 85u, 150u},
            {b4, 85u, 150u},
            {b4, 150u, 150u},
            {b4, 150u, 150u},
            {c5, 150u, 150u},
            {c5, 85u, 150u},
            {c5, 85u, 150u},
            {c5, 150u, 150u},
            {c5, 150u, 150u},
            {c5, 150u, 150u},
            {b4, 150u, 150u},
            {a4, 150u, 150u},
            {gb4, 150u, 150u},
            {a4, 300u, 150u},
    };

    printf("kuznechik play for you\n");
    for (i = 0; i < 61; i++)
    {
        setFrequency(notes[i][0]);
        // Включение динамик, используя первые 2 бита:
        // 0 - включение/выключение канала 2 в системном таймере
        // 1 - включение/выключение динамического
        outp(0x61, inp(0x61) | 0x03);
        delay(notes[i][1]);
        //выключение динамика
        outp(0x61, inp(0x61) & 0xFC);
        delay(notes[i][2]);
    }
}

int showMenu(void)
{
    int option;

    printf("\nMenu\n");
    printf("1. Kuznechik\n");
    printf("2. Play a default sound\n");
    printf("3. Division factor\n");
    printf("4. Status word\n");
    printf("5. Exiting the program\n");

    do
    {
        printf("Choose option: ");
        fflush(stdin);
    } while (!scanf("%d", &option));

    return option;
}

void div(void)
{
    // порт 40h (канал 0, прерывание системных часов)
    // порт 41h (канал 1, регенерация памяти)
    // порт 42h (канал 2, звук из динамика)
    int channel;
    int ports[] = { 0x40, 0x41, 0x42 };
    int controlWord[] = { 0x0, 0x40, 0x80 }; // Команды  CLC: для считывания текущего состояния регистра счетчика канала
    unsigned byte, lowByte, highByte, maxByte;

    printf("\nDivision factor: \n");

    for (channel = 0; channel < 3; channel++)
    {
        byte = 0;
        maxByte = 0;

        for (unsigned long i = 0; i < 65536; i++)
        {
            outp(0x43, controlWord[channel]);     // выбор канала
            lowByte = inp(ports[channel]);        // считывание наименьшего бита
            highByte = inp(ports[channel]);       // считывание старшего бита
            byte = highByte * 256 + lowByte;   // генерируем бит

            if (byte > maxByte)
                maxByte = byte;
        }

        printf("\nChannel %d: %4X\n", channel, maxByte);
    }
}

void sound(void)
{
    int byte;
    int arrayOfHz[9] = { 392, 329, 329, 392, 329, 329, 392, 349, 329 };
    int arrayOfMS[9] = { 400, 400, 400, 400, 400, 400, 400, 400, 400 };
    int countOfDelay[9] = { 100, 100, 100, 100, 100, 100, 100, 100, 100 };
    long unsigned base = 1193180; // IRQ 18,2 раза в секунду


    for (int i = 0; i < 9; i++)
    {
        // настройка 2-го канала:
        // порт 42h (системный таймер, канал 2, звук из динамика)
        // порт 43h (командный регистр)
        outp(0x43, 0xB6);                   // 0xB6 - настройка 2 канала по порту 43h
        byte = base / arrayOfHz[i];
        outp(0x42, byte % 256);             //наименьший байт делителя частоты
        outp(0x42, byte /= 256);            //самый старший байт делителя частоты

        outp(0x61, inp(0x61) | 3);          //включение
        delay(arrayOfMS[i]);                 //ожидание
        outp(0x61, inp(0x61) & 0xFC);       //выключение
        delay(countOfDelay[i]);         //ожидание
    }
}

int main(void)
{
    clrscr();
    while (1)
    {
        switch (showMenu())
        {
            case 1:
                clrscr();
                playMusic();
                break;
            case 2:
                clrscr();
                sound();
                break;
            case 3:
                clrscr();
                div();
                break;
            case 4:
                clrscr();
                stateWords();
                break;
            case 5:
                clrscr();
                return 1;
            default:
                clrscr();
                printf("Error option\n");
                break;
        }
    }
}