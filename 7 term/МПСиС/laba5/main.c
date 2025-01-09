#include <msp430.h>
#include <math.h>
#include <stdint.h>

// Определения для команд управления ЖК-дисплеем и данных акселерометра
#define SET_COLUMN_ADDRESS_LSB 0x00
#define SET_COLUMN_ADDRESS_MSB 0x10
#define SET_PAGE_ADDRESS 0xB0

#define SET_SEG_DIRECTION 0xA0
#define SET_COM_DIRECTION 0xC0

#define SET_POWER_CONTROL 0x2F
#define SET_SCROLL_LINE 0x40
#define SET_VLCD_RESISTOR_RATIO 0x27
#define SET_ELECTRONIC_VOLUME_MSB 0x81

#define SET_ELECTRONIC_VOLUME_LSB 0x0F
#define SET_ALL_PIXEL_ON 0xA4
#define SET_INVERSE_DISPLAY 0xA6
#define SET_DISPLAY_ENABLE 0xAF
#define SET_LCD_BIAS_RATIO 0xA2
#define SET_ADV_PROGRAM_CONTROL0_MSB 0xFA
#define SET_ADV_PROGRAM_CONTROL0_LSB 0x90

#define NONE 0
#define READ_X_AXIS_DATA 0x18
#define READ_Y_AXIS_DATA 0x19
#define READ_Z_AXIS_DATA 0x20

// Определения регистров акселерометра
#define REVID 0x01
#define CTRL 0x02
#define MODE_400 0x04 // Measurement mode 400 Hz ODR
#define DOUTX 0x06
#define DOUTY 0x07
#define DOUTZ 0x08
#define G_RANGE_2 0x80 // 2g range
#define I2C_DIS 0x10 // I2C disabled

#define CD BIT6
#define CS BIT4

#define PAGES 12
#define COLUMNS 9

// Инициализирует ориентацию сегмента ЖК-дисплея для зеркального отображения
void Dogs102x6_setMirrorSegDisplay();
// Инициализирует ориентацию столбцов ЖК-дисплея для зеркального отображения
void Dogs102x6_setMirrorColDisplay();
int MirrorColMode=0;
int MirrorSegMode=0;

int MAPPING_VALUES[] = { 4571, 2286, 1141, 571, 286, 143, 71 };
uint8_t BITx[] = { BIT6, BIT5, BIT4, BIT3, BIT2, BIT1, BIT0 };

uint8_t MODE_COMMANDS[2][1] = { {SET_SEG_DIRECTION}, {SET_SEG_DIRECTION | 1}
};

uint8_t Dogs102x6_initMacro[] = {
     SET_SCROLL_LINE,
     SET_SEG_DIRECTION,
     SET_COM_DIRECTION,
     SET_ALL_PIXEL_ON,
     SET_INVERSE_DISPLAY,
     SET_LCD_BIAS_RATIO,
     SET_POWER_CONTROL,
     SET_VLCD_RESISTOR_RATIO,
     SET_ELECTRONIC_VOLUME_MSB,
     SET_ELECTRONIC_VOLUME_LSB,
     SET_ADV_PROGRAM_CONTROL0_MSB,
     SET_ADV_PROGRAM_CONTROL0_LSB,
     SET_DISPLAY_ENABLE,
     SET_PAGE_ADDRESS,
     SET_COLUMN_ADDRESS_MSB,
     SET_COLUMN_ADDRESS_LSB
};

int inverted = 0;
int COLUMN_START_ADDRESS = 100;
int PAGE_START_ADDRESS = 7;

// Символы для чисел и знаков, отображаемых на ЖК-дисплее
uint8_t symbols[12][6] = {
     {0xff, 0x81, 0x81, 0x81, 0x81, 0xff}, // UPPER 0 INDEX 0
     {0x08, 0x10, 0x20, 0x40, 0x80, 0xff}, // UPPER 1 INDEX 0
     {0x9f, 0x91, 0x91, 0x91, 0x91, 0xf1}, // UPPER 2 INDEX 0
     {0x91, 0x91, 0x91, 0x91, 0x91, 0xff}, // UPPER 3 INDEX 0
     {0xf0, 0x10, 0x10, 0x10, 0x10, 0xff}, // UPPER 4 INDEX 0
     {0xf1, 0x91, 0x91, 0x91, 0x91, 0x9f}, // UPPER 5 INDEX 0
     {0xff, 0x91, 0x91, 0x91, 0x91, 0x9f}, // UPPER 6 INDEX 0
     {0x80, 0x80, 0x80, 0x80, 0x80, 0xff}, // UPPER 7 INDEX 0
     {0xff, 0x91, 0x91, 0x91, 0x91, 0xff}, // UPPER 8 INDEX 0
     {0xf1, 0x91, 0x91, 0x91, 0x91, 0xff}, // UPPER 9 INDEX 0
     {0x00, 0x08, 0x08, 0x3e, 0x08, 0x08}, // UPPER + INDEX 0
     {0x00, 0x08, 0x08, 0x08, 0x08, 0x08}, // UPPER - INDEX 0
};

// Записывает данные в указанный регистр акселерометра
uint8_t CMA3000_writeCommand(uint8_t byte_one, uint8_t byte_two);
// Инициализирует конфигурацию акселерометра
void CMA3000_init(void);
// Вычисляет угол по заданному значению проекции
int calculateAngleFromProjection(double projection);
// Преобразует байт проекции акселерометра в целое число
long int parseProjectionByte(uint8_t projection_byte);
// Считывает регистр с акселерометра и возвращает результат
int8_t Cma3000_readRegister(int8_t Address);

// Вычисляет количество цифр в числе
int getNumberLength(long int number);
// Отображает числовое значение на ЖК-экране
void printNumber(long int angle);

// Очищает весь ЖК-экран
void Dogs102x6_clearScreen(void);
// Устанавливает адрес ЖК-дисплея для записи
void Dogs102x6_setAddress(uint8_t pa, uint8_t ca);
//записывает данные на ЖК-дисплей
void Dogs102x6_writeData(uint8_t* sData, uint8_t i);
//пишет команду для ЖК-дисплея
void Dogs102x6_writeCommand(uint8_t* sCmd, uint8_t i);
//инициализирует подсветку
void Dogs102x6_backlightInit(void);
//инициализирует настройки и конфигурацию ЛСД
void Dogs102x6_init(void);

#define CHECK_CYCLES 2000

// Инициализирует таймер для отсчета времени события и обновления экрана
void timer_init(void)
{
     TA0CCR0 = CHECK_CYCLES;
     TA0CTL |= TASSEL__ACLK;
     TA0CTL |= MC__UP;
     TA0CTL |= ID__1;
     TA1CCR0 = CHECK_CYCLES;
     TA1CTL |= TASSEL__ACLK;
     TA1CTL |= MC__UP;
     TA1CTL |= ID__1;
}

// Инициализирует кнопки и их поведение прерывания
void btn_init(void)
{
     P1DIR &= ~BIT7;
     P1OUT |= BIT7;
     P1REN |= BIT7;
     P1IFG &= ~BIT7;
     P1IES |= BIT7;
     P1IE |= BIT7;
     P2DIR &= ~BIT2;
     P2OUT |= BIT2;
     P2REN |= BIT2;
     P2IFG &= ~BIT2;
     P2IES |= BIT2;
     P2IE |= BIT2;
}

// Устанавливает режим зеркального отображения направления столбцов на ЖК-дисплее
void Dogs102x6_setMirrorColDisplay()
{
     uint8_t cmd[] = {SET_COM_DIRECTION};

     if(MirrorColMode == 1)
     {
         cmd[0] = SET_COM_DIRECTION | 0x08;
     }
     else
     {
         cmd[0] = SET_COM_DIRECTION ;
     }
     Dogs102x6_writeCommand(cmd, 1);
}

// Устанавливает режим зеркального отображения направления сегмента на ЖК-дисплее
void Dogs102x6_setMirrorSegDisplay()
{
     uint8_t cmd[] = {SET_SEG_DIRECTION};

     if(MirrorSegMode == 1)
     {
         cmd[0] = SET_SEG_DIRECTION | 0x01;
     }
     else
     {
         cmd[0] = SET_SEG_DIRECTION ;
     }
     Dogs102x6_writeCommand(cmd, 1);
}

// Переключает режим инверсии для ЖК-дисплея
void inv_lcd(){
     uint8_t cmd[1];

     if(inverted){
         inverted = 0;
         cmd[0] = SET_INVERSE_DISPLAY;
     }
     else{
         inverted = 1;
         cmd[0] = 0xA7;
     }
     Dogs102x6_writeCommand(cmd, 1);
}

// Обработчик прерываний для обработки данных акселерометра
#pragma vector = PORT2_VECTOR
__interrupt void accelerometerInterrupt(void) {
     volatile uint8_t xProjectionByte = Cma3000_readRegister(DOUTX);
     volatile uint8_t yProjectionByte = Cma3000_readRegister(DOUTY);
     volatile uint8_t zProjectionByte = Cma3000_readRegister(DOUTZ);
     volatile long int xAxisProjection = parseProjectionByte(xProjectionByte);
     volatile long int yAxisProjection = parseProjectionByte(yProjectionByte);
     volatile long int zAxisProjection = parseProjectionByte(zProjectionByte);
     // ось x
     int angle = calculateAngleFromProjection((double) xAxisProjection);
     angle *= zAxisProjection <= 0 ? 1 : -1;
     Dogs102x6_clearScreen();
     printNumber(angle);
}

// Обработчик прерываний для кнопки S1 для переключения зеркалирования сегмента
#pragma vector = PORT1_VECTOR
__interrupt void buttonS1(void)
{
     __delay_cycles(7000);
     if ((P1IN & BIT7) == 0) {
         MirrorSegMode^=1;
         MirrorColMode^=1;
         if(MirrorSegMode == 0)COLUMN_START_ADDRESS = 30 ;
         else
             COLUMN_START_ADDRESS = 80 ;
         Dogs102x6_clearScreen();
         Dogs102x6_setMirrorColDisplay();
         Dogs102x6_setMirrorSegDisplay();
     }
     P1IFG = 0;
}

int getNumberLength(long int number) {
     int length = 0;
     number = abs(number);
     if(number == 0)
         return 1;
     while(number) {
         number /= 10;
         length++;
     }
     return length;
}

void Dogs102x6_clearScreen(void){
     uint8_t LcdData[] = { 0x00 };
     uint8_t p, c;
     for (p = 0; p < 8; p++){
         Dogs102x6_setAddress(p, 0);
         for (c = 0; c < 132; c++)
             Dogs102x6_writeData(LcdData, 1);
     }
}

void Dogs102x6_setAddress(uint8_t pa, uint8_t ca){
     uint8_t cmd[1];
     // ca-=1;
     if (pa > 7)
         pa = 7;
     if (ca > 131)
         ca = 131;
     cmd[0] = SET_PAGE_ADDRESS + pa;
     // cmd[0] = SET_PAGE_ADDRESS + ( pa );
     uint8_t H = 0x00;
     uint8_t L = 0x00;
     uint8_t ColumnAddress[] = { SET_COLUMN_ADDRESS_MSB, SET_COLUMN_ADDRESS_LSB};
     L = (ca & 0x0F);
     H = (ca & 0xF0);
     H = (H >> 4);
     ColumnAddress[0] = SET_COLUMN_ADDRESS_LSB + L;
     ColumnAddress[1] = SET_COLUMN_ADDRESS_MSB + H;
     Dogs102x6_writeCommand(cmd, 1);
     Dogs102x6_writeCommand(ColumnAddress, 2);
}

void Dogs102x6_writeData(uint8_t* sData, uint8_t i){
     P7OUT &= ~CS;
     P5OUT |= CD;
     while (i){
         while (!(UCB1IFG & UCTXIFG));
         UCB1TXBUF = *sData;
         sData++;
         i--;
     }
     while (UCB1STAT & UCBUSY);
     UCB1RXBUF;
     P7OUT |= CS;
}

void Dogs102x6_writeCommand(uint8_t* sCmd, uint8_t i){
     P7OUT &= ~CS;
     P5OUT &= ~CD;
     while (i){
         while (!(UCB1IFG & UCTXIFG));
         UCB1TXBUF = *sCmd;
         sCmd++;
         i--;
     }
     while (UCB1STAT & UCBUSY);
     UCB1RXBUF;
     P7OUT |= CS;
}

void Dogs102x6_backlightInit(void){
     P7DIR |= BIT6;
     P7OUT |= BIT6;
     P7SEL &= ~BIT6;
}

void Dogs102x6_init(void){
     P5DIR |= BIT7;
     P5OUT &= BIT7;
     P5OUT |= BIT7;
     P7DIR |= CS;
     P5DIR |= CD;
     P5OUT &= ~CD;
     P4SEL |= BIT1;
     P4DIR |= BIT1;
     P4SEL |= BIT3;
     P4DIR |= BIT3;
     UCB1CTL1 = UCSSEL_2 + UCSWRST;
     UCB1BR0 = 0x02;
     UCB1BR1 = 0;
     UCB1CTL0 = UCCKPH + UCMSB + UCMST + UCMODE_0 + UCSYNC;
     UCB1CTL1 &= ~UCSWRST;
     UCB1IFG &= ~UCRXIFG;
     Dogs102x6_writeCommand(Dogs102x6_initMacro, 13);
}

void CMA3000_init(void) {
     P2DIR &= ~BIT5; // mode: input
     P2OUT |= BIT5;
     P2REN |= BIT5; // enable pull up resistor
     P2IE |= BIT5; // interrupt enable
     P2IES &= ~BIT5; // process on interrupt's front
     P2IFG &= ~BIT5; // clear interrupt flag
     // set up cma3000 (CBS - Chip Select (active - 0))
     P3DIR |= BIT5; // mode: output
     P3OUT |= BIT5; // disable cma3000 SPI data transfer
     // set up ACCEL_SCK (SCK - Serial Clock)
     P2DIR |= BIT7; // mode: output
     P2SEL |= BIT7; // clk is UCA0CLK
     // Setup SPI communication
     P3DIR |= (BIT3 | BIT6); // Set MOSI and PWM pins to output mode
     P3DIR &= ~BIT4; // Set MISO to input mode
     P3SEL |= (BIT3 | BIT4); // Set mode : P3.3 - UCA0SIMO , P3.4 - UCA0SOMI
     P3OUT |= BIT6; // Power cma3000
     UCA0CTL1 = UCSSEL_2 | UCSWRST;
     UCA0BR0 = 0x30;
     UCA0BR1 = 0x0;
     UCA0CTL0 = UCCKPH | UCMSB | UCMST | UCSYNC | UCMODE_0;
     UCA0CTL1 &= ~UCSWRST;
     // dummy read from REVID
     CMA3000_writeCommand(0x04, NONE);
     __delay_cycles(1250);
     // write to CTRL register
     CMA3000_writeCommand(0x0A, BIT4 | BIT2);
     __delay_cycles(25000);
      // Activate measurement mode: 2g/400Hz
      CMA3000_writeCommand(CTRL, G_RANGE_2 | I2C_DIS | MODE_400);
      // Settling time per DS = 10ms
      // __delay_cycles(1000 * TICKSPERUS);
      __delay_cycles(25000);
 }

uint8_t CMA3000_writeCommand(uint8_t firstByte, uint8_t secondByte) {
     volatile char indata;
     P3OUT &= ~BIT5;
     indata = UCA0RXBUF;
     while(!(UCA0IFG & UCTXIFG));
     UCA0TXBUF = firstByte;
     while(!(UCA0IFG & UCRXIFG));
     indata = UCA0RXBUF;
     while(!(UCA0IFG & UCTXIFG));
     UCA0TXBUF = secondByte;
     while(!(UCA0IFG & UCRXIFG));
     indata = UCA0RXBUF;
     while(UCA0STAT & UCBUSY);
     P3OUT |= BIT5;
     return indata;
}

long int parseProjectionByte(uint8_t projectionByte) {
     long int projectionValue = 0;
     int i = 0;
     int isNegative = projectionByte & BIT7;
     for (; i < 7; i++) {
         if (isNegative) {
             projectionValue += (BITx[i] & projectionByte) ? 0 :MAPPING_VALUES[i];
     }
         else {
             projectionValue += (BITx[i] & projectionByte) ? MAPPING_VALUES[i] : 0;
         }
     }
     projectionValue *= isNegative ? -1 : 1;
     return projectionValue;
}

int calculateAngleFromProjection(double projection) {
     projection /= 1000;
     projection = projection > 1 ? 1 : projection < -1 ? -1 : projection;
     double angle = acos(projection);
     angle *= 57.3;
     return (int) angle;
}

int8_t Cma3000_readRegister(int8_t Address)
{
     int8_t Result;
     // Address to be shifted left by 2 and RW bit to be reset
      Address <<= 2;
      // Select acceleration sensor
      P3OUT &= ~BIT5;
      // Read RX buffer just to clear interrupt flag
      Result = UCA0RXBUF;
      // Wait until ready to write
      while (!(UCA0IFG & UCTXIFG)) ;
      // Write address to TX buffer
      UCA0TXBUF = Address;
      // Wait until new data was written into RX buffer
      while (!(UCA0IFG & UCRXIFG)) ;
      // Read RX buffer just to clear interrupt flag
      Result = UCA0RXBUF;
      // Wait until ready to write
      while (!(UCA0IFG & UCTXIFG)) ;
      // Write dummy data to TX buffer
      UCA0TXBUF = 0;
      // Wait until new data was written into RX buffer
      while (!(UCA0IFG & UCRXIFG)) ;
      // Read RX buffer
      Result = UCA0RXBUF;
      // Wait until USCI_A0 state machine is no longer busy
      while (UCA0STAT & UCBUSY) ;
      // Deselect acceleration sensor
      P3OUT |= BIT5;
      // Return new data from RX buffer
      return Result;
 }

void printNumber(long CURRENT_NUMBER) {
     int nDigits = getNumberLength(CURRENT_NUMBER);
     int number = CURRENT_NUMBER;
     int COL_ADR=COLUMN_START_ADDRESS;
     int pa = PAGE_START_ADDRESS;
     if(number < 0) {
         Dogs102x6_setAddress( pa, COL_ADR);
         Dogs102x6_writeData(symbols[11], 6);
     } else {
         Dogs102x6_setAddress( pa, COL_ADR);
         Dogs102x6_writeData(symbols[10], 6);
     }
     int i = 0;
     int divider = pow(10, nDigits - 1);
     number = abs(number);
     for (i = 1; i <= nDigits; i++) {
         int digit = number / divider;
         Dogs102x6_setAddress(pa, COL_ADR + (i * 2) + (i * 6));
         Dogs102x6_writeData(symbols[digit], 6);
         number = number % divider;
         divider /= 10;
     }
}

// Основной цикл инициализации и выполнения программы
int main(void) {
     WDTCTL = WDTPW | WDTHOLD;
     Dogs102x6_init();
     Dogs102x6_backlightInit();
     Dogs102x6_clearScreen();
     timer_init();
     btn_init();
     CMA3000_init();
     MirrorColMode=0;
     Dogs102x6_setMirrorColDisplay();
     MirrorSegMode=0;
     Dogs102x6_setMirrorSegDisplay();
     COLUMN_START_ADDRESS = 30 ;
     Dogs102x6_clearScreen();
     __bis_SR_register(LPM0_bits + GIE);
     return 0;
}
