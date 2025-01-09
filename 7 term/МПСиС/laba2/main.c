#include <msp430.h>

volatile int button_pressed = 0;  // Флаг нажатия кнопки
volatile int led_off_step = 0;    // Шаг выключения светодиодов
volatile int delay_counter = 0;    // Счетчик для увеличения задержки

void setup_watchdog_timer() {
    // Настройка таймера WDT для генерации прерываний каждые 100 мс
    WDTCTL = WDTPW | WDTTMSEL | WDTCNTCL | WDT_MDLY_32; // Таймер WDT с интервалом 100 мс
    SFRIE1 |= WDTIE; // Разрешаем прерывания от WDT
}

void stop_watchdog_timer() {
    SFRIE1 &= ~WDTIE;  // Отключаем прерывание WDT
    WDTCTL = WDTPW | WDTHOLD;  // Останавливаем WDT
}

void main(void) {
    WDTCTL = WDTPW | WDTHOLD; // Отключаем сторожевой таймер

    // Настройка портов для светодиодов
    P1DIR |= BIT0;  // Устанавливаем Р1.0 как выход (LED1)
    P8DIR |= BIT1;  // Устанавливаем Р8.1 как выход (LED2)
    P8DIR |= BIT2;  // Устанавливаем Р8.2 как выход (LED3)

    // Настройка кнопки
    P2DIR &= ~BIT2; // Устанавливаем Р2.2 как вход (S2)
    P2REN |= BIT2;  // Включаем подтягивающий резистор для Р2.2
    P2OUT |= BIT2;  // Подтягиваем Р2.2 к Vcc
    P2IE |= BIT2;   // Разрешаем прерывание по кнопке
    P2IES |= BIT2;  // Прерывание по спадающему фронту (нажатие)
    P2IFG &= ~BIT2; // Сбрасываем флаг прерывания

    __enable_interrupt(); // Разрешаем глобальные прерывания

    // Начальное состояние светодиодов
    P1OUT &= ~BIT0;
    P8OUT &= ~BIT1;
    P8OUT &= ~BIT2;

    while (1) {
        // Основной цикл пустой, так как вся работа идет в прерываниях
        __low_power_mode_3(); // Включаем режим энергосбережения
    }
}

// Прерывание по нажатию или отпусканию кнопки
#pragma vector=PORT2_VECTOR
__interrupt void PORT2_ISR(void) {
    if (!(P2IN & BIT2)) {  // Кнопка нажата (спадающий фронт)
        button_pressed = 1;      // Устанавливаем флаг нажатия кнопки
        led_off_step = 0;        // Сбрасываем шаг гашения светодиодов
        delay_counter = 0;       // Сбрасываем счетчик задержки
        // Включаем все светодиоды
        P1OUT |= BIT0;           // Включаем LED1
        P8OUT |= BIT1;           // Включаем LED2
        P8OUT |= BIT2;           // Включаем LED3
        stop_watchdog_timer();   // Останавливаем WDT, если был запущен
        P2IES &= ~BIT2;          // Меняем на прерывание по возрастающему фронту (отпускание)
    } else {                     // Кнопка отпущена (возрастающий фронт)
        button_pressed = 0;      // Сбрасываем флаг нажатия кнопки
        led_off_step = 0;        // Сбрасываем шаг гашения светодиодов
        delay_counter = 0;       // Сбрасываем счетчик задержки
        setup_watchdog_timer();  // Запускаем WDT для последовательного гашения светодиодов
        P2IES |= BIT2;           // Меняем на прерывание по спадающему фронту (нажатие)
    }

    P2IFG &= ~BIT2; // Сбрасываем флаг прерывания
}

// Прерывание от таймера WDT
#pragma vector=WDT_VECTOR
__interrupt void WDT_ISR(void) {
    if (!button_pressed) {  // Если кнопка отпущена
        delay_counter++;    // Увеличиваем счетчик задержки

        if (delay_counter >= 10) {  // Каждые 10 раз по 100 мс = 1 секунда
            switch (led_off_step) {
            case 0:
                P1OUT &= ~BIT0; // Выключаем LED1
                led_off_step++;
                break;
            case 1:
                P8OUT &= ~BIT1; // Выключаем LED2
                led_off_step++;
                break;
            case 2:
                P8OUT &= ~BIT2; // Выключаем LED3
                led_off_step++;
                stop_watchdog_timer();  // Останавливаем WDT после завершения
                break;
            default:
                stop_watchdog_timer();  // Останавливаем WDT, если шаг превышает 2
                break;
            }
            delay_counter = 0; // Сбрасываем счетчик после каждого шага гашения
        }
    }
}

