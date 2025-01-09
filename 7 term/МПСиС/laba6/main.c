#include <msp430.h>
#include <msp430f5529.h>
#include "HAL_Dogs102x6.h"
#include "HAL_Cma3000.h"
#include "ff.h"
#include "structure.h"
#include "CTS_Layer.h"
#include <stdlib.h>

// Данные и позиции для рисования дополнительной информации
#define FILE_NAME "buffer.bin"

int buff_size_2 = 96;
int buff_size = 48;
int num_y_cont = 900, num_y = 0;
int passed = 0;
int index = 0;
int full_loop = 0;
int write = 0;
//int file_draw = 0;
uint16_t buffer[48];
uint16_t temp_buffer[48];


int MAPPING_VALUES[] = { 1142, 571, 286, 143, 71, 36, 18 };
uint8_t BITx[] = { BIT6, BIT5, BIT4, BIT3, BIT2, BIT1, BIT0 };

int parseProjectionByte(uint8_t projectionByte) {
    int i = 0;
    int projectionValue = 0;

    int isNegative = projectionByte & BIT7;

    for (; i < 7; i++) {
        if (isNegative) {
            projectionValue += (BITx[i] & projectionByte) ? 0 : MAPPING_VALUES[i];
        }
        else {
            projectionValue += (BITx[i] & projectionByte) ? MAPPING_VALUES[i] : 0;
        }
    }

    projectionValue *= isNegative ? -1 : 1;

    return projectionValue;
}

void Cma3000_readAccel_y(void)
{
    Cma3000_yAccel = Cma3000_readRegister(DOUTY);
    __delay_cycles(50 * 25);
}

void SetupButtons()
{
    P2REN |= BIT2;
    P2OUT |= BIT2;
    P1REN |= BIT7;
    P1OUT |= BIT7;
}

uint16_t main(void){

    WDTCTL = WDTPW + WDTHOLD;

    FATFS fs;
    FIL file;
    UINT bw = 0;

    Dogs102x6_init();
    Dogs102x6_backlightInit();
    Dogs102x6_setBacklight(255);
    Dogs102x6_clearScreen();

    Cma3000_init();

    SetupButtons();

    TA2CCTL0 = CCIE;
    TA2CCR0 = 2;
    TA2CTL = TASSEL__ACLK + MC__UP + ID__8 + TACLR + TAIE;
    TA1CTL &= ~TAIFG;

    FRESULT res = f_mount(0, &fs);
    if (res == FR_NO_FILESYSTEM)
    {
        f_mkfs(0, 0, 512);
    }

    // Работа DMA по прерыванию TA2CCR0 CCIFG(из даташита)
    DMACTL0 = DMA0TSEL_0;
    // Одиночная пересылка, включение DMA, разрешение прерываний
    // нет инкремента dst, src, размер данных 16 бит.
    DMA0CTL = DMADT_0+DMAEN+DMAIE;
    // Размер = 1
    DMA0SZ = 1;

    // Источник - значение оси Y.
    __data16_write_addr((unsigned short) &DMA0SA,(unsigned long) &num_y);
    // Назначение - в элемент массива.
    __data16_write_addr((unsigned short) &DMA0DA,(unsigned long) &buffer[index]);

    uint8_t file_draw = 0;
    char* temp[128];

    while(1){
        Cma3000_readAccel_y();
        num_y = parseProjectionByte(Cma3000_yAccel);
        //__data16_write_addr((unsigned short) &DMA0SA,(unsigned long) &num_y);

        if(file_draw == 1){
            f_open(&file, FILE_NAME, FA_READ);
            f_read(&file, temp_buffer, buff_size_2, &bw);
            f_close(&file);

            int length = index;

            if(full_loop == 1){
                length = buff_size;
            }

            int i = 0;
            int j = 0;
            int r = 0;
            int c = 0;
            Dogs102x6_clearScreen();

            for(i = 0; i < length; i++){
                Dogs102x6_pixelDraw(i, (uint8_t)(temp_buffer[i]/100), DOGS102x6_DRAW_NORMAL);

            }
            /*for(i = 0; i < length; i+=3){
                for(j = 0; j < 3; j++){

                    ltoa((LONG)temp_buffer[i + j], temp, 10);

                    Dogs102x6_stringDraw(r, c, temp, DOGS102x6_DRAW_NORMAL);

                    c+=36;
                }
                r++; c = 0;
            }*/
            file_draw = 0;
        }


        if ((P2IN & BIT2) == 0)
        {
            file_draw = 1;
        }
        else
        {
            file_draw = 0;
        }

        if ((P1IN & BIT7) == 0)
        {
            //passed_2 = 1;
            Dogs102x6_clearScreen();
        }

        if(passed == 1 && write == 1){
             f_open(&file, FILE_NAME, FA_WRITE | FA_CREATE_ALWAYS);
             f_write(&file, buffer, buff_size_2, &bw);
             f_close(&file);
             write = 0;
        }
        else if(num_y > num_y_cont && passed == 0 && write == 0){
             passed = 1;
             write = 1;
        }
        else if(num_y < num_y_cont && passed == 1){
             passed = 0;
             write = 0;
        }

        index++;
        if (index == buff_size)
        {
           full_loop = 1;
           index = 0;
        }

      // Обновляем адрес назначения DMA
        _data16_write_addr((unsigned short) &DMA0DA,(unsigned long) &buffer[index]);
        // Запуск DMA
        DMA0CTL |= DMAEN;
        DMA0CTL |= DMAREQ;

        while(!(DMA0CTL & DMAIFG));

        DMA0CTL &= ~DMAEN;

    }
}
