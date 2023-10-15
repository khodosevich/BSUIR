#include "stdafx.h"
#include "hexioctrl.h"
#include "pci_codes.h"
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <iomanip> 
#include <string.h>

const int IDENTIFY_DEVICE = 0xEC; //команда идентификации устройства для ATA
const int IDENTIFY_PACKET_DEVICE = 0xA1; //команда идентификации устройства для ATAPI
 
const int dataRegister[2] = {0x1F0, 0x170}; //командный регистр хранения блока данных 1/2 канал
const int DH_register[2] = {0x1F6, 0x176}; //командный регистр хранения номера устройства и головки 1/2 канал
const int StateCommandRegister[2] = {0x1F7, 0x177}; //командный регистр для записи команды либо для чтения состояния 1/2 канал
const int altStateRegister[2] = {0x3F6, 0x376}; //управляющий регистр состояния устройств 1/2 канал
 
unsigned short data[256]; // объявление блока данных, который потом заполняется
 
void WaitDeviceBusy(int channelNum);
bool getDeviceInfo(int devNum, int channelNum);
void showTable();
bool waitReady(int channelNum);
 
 
int main()
{
    ALLOW_IO_OPERATIONS;
    setlocale(LC_ALL, "Russian");
    for( int channel = 0; channel <= 1; channel++ ) // по 1 и 2 каналу
        for( int device = 0; device <= 1; device++ ) // по ведущему и ведомому устройству на каждом канале
        {               
            if(getDeviceInfo(device, channel))  
            {
                printf("\n   Канал %d     Устройство %d\n", channel, device);
                showTable();
            }
        }
        system("pause");
        return 0;
}
 
//функция для проверки 6 бита(готовность к записи команды)
bool waitReady(int channelNum)
{
    for (int i = 0; i < 1000; i++)
    {
        unsigned char state = _inp(altStateRegister[channelNum]); //регистр состояния
        if(state & (1 << 6)) return true; 
    }
    return false;
}
 
//функция для проверки 7 бита(готовность устройства)
void  WaitDeviceBusy(int channelNum)
{
    unsigned char state;
    do state = _inp(altStateRegister[channelNum]); //регистр состояния
    while (state & (1 << 7));
}

//получение информации об устройстве
bool  getDeviceInfo(int devNum, int channelNum)
{   
    const int commands[2] = {IDENTIFY_PACKET_DEVICE, IDENTIFY_DEVICE};
    for (int i = 0; i < 2; i++)
    {
        // Ожидаем обнуления бита BSY(бит готовности)
        WaitDeviceBusy(channelNum);
 
        // Адресуем устройство
        unsigned char regData = (devNum << 4) + (7 << 5); //111X0000
        _outp(DH_register[channelNum], regData);   // номер устройства и головки в DH
 
        // Дожидаемся признака готовности к записи команды, если устройство присутствует
        if(!waitReady(channelNum))  return false;    

        // Записываем код команды в регистр команд
        _outp(StateCommandRegister[channelNum], commands[i]); // в командный регистр
 
        WaitDeviceBusy(channelNum);
                
        // Проверка на ошибку (неподдерживаемая команда)
        unsigned char curState = _inp( StateCommandRegister[channelNum]);
        if(!(curState & (1 << 3)))  // Если DRQ = 0
        {
            if(i == 1) return false;
            continue;
        }
        else break;
    }
 
    // Получение конфигурационного блока
    for( int i = 0; i < 256; i++ )
        data[ i ] = _inpw( dataRegister[channelNum ] );  //из регистра данных
    
    return true;
}
 

void showTable()
{
    printf("\n   Наименование модели устройства: ");
    for(int i = 27; i <= 46; i++)
        printf("%c%c", data[i] >> 8, data[i] & 0x00FF ); 
 
    printf("\n   Серийный номер: ");
    for( int i = 10; i <= 19; i++ )
        printf("%c%c", data[i] >> 8, data[i] & 0x00FF );
 
    printf("\n   Версия прошивки: ");
    for( int i = 23; i <= 26; i++ )
        printf("%c%c", data[i] >> 8, data[i] & 0x00FF );
 
    printf("\n   Тип обмена данными: ");

    if(data[0] & (1 << 15)) printf("ATAPI\n"); //если 15 бит в 0 байте==1, то ATAPI
    else printf("ATA\n");                      //иначе ATA, остальные printf аналогично
 

    if(!(data[0] & (1 << 15))){ 
		printf("   Размер: %.2lf ГБ\n", (long double)(((unsigned long *)data)[30]) * 512 / (1024 * 1024 * 1024));
    }
 
    printf("\n\n - PIO:");
	if(data[64] & 1) printf("  %s", "PIO 3," );
	if(data[64] & 2) printf("  %s", "PIO 4\n" );
 
    printf("\n - Multiword DMA:");
	if(data[63] & 1) printf("  %s", "MWDMA 0," );
	if(data[63] & 2) printf("  %s", "MWDMA 1," );
	if(data[63] & 4) printf("  %s", "MWDMA 2\n" );
 
    printf("\n - Ultra DMA:" );
	if(data[88] & 1) printf("  %s", "UDMA Mode 0," );
	if(data[88] & (1 << 1)) printf("  %s", "UDMA Mode 1," );
	if(data[88] & (1 << 2)) printf("  %s", "UDMA Mode 2," );
	if(data[88] & (1 << 3)) printf("  %s", "UDMA Mode 3," );
	if(data[88] & (1 << 4)) printf("  %s", "UDMA Mode 4," );
	if(data[88] & (1 << 5)) printf("  %s", "UDMA Mode 5\n" );

    printf("\n\n - Версии ATA:" );
	if(data[80] & (1 << 1)) printf("  %s", "ATA 1," );
	if(data[80] & (1 << 2)) printf("  %s", "ATA 2," );
	if(data[80] & (1 << 3)) printf("  %s", "ATA 3," );
	if(data[80] & (1 << 4)) printf("  %s", "ATA 4," );
	if(data[80] & (1 << 5)) printf("  %s", "ATA 5," );
	if(data[80] & (1 << 6)) printf("  %s", "ATA 6," );
	if(data[80] & (1 << 7)) printf("  %s", "ATA 7\n" );
    
    printf("\n_____________________________________________________________________________\n\n");
}
