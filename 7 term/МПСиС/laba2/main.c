#include <msp430.h>

volatile int button_pressed = 0;  // ���� ������� ������
volatile int led_off_step = 0;    // ��� ���������� �����������
volatile int delay_counter = 0;    // ������� ��� ���������� ��������

void setup_watchdog_timer() {
    // ��������� ������� WDT ��� ��������� ���������� ������ 100 ��
    WDTCTL = WDTPW | WDTTMSEL | WDTCNTCL | WDT_MDLY_32; // ������ WDT � ���������� 100 ��
    SFRIE1 |= WDTIE; // ��������� ���������� �� WDT
}

void stop_watchdog_timer() {
    SFRIE1 &= ~WDTIE;  // ��������� ���������� WDT
    WDTCTL = WDTPW | WDTHOLD;  // ������������� WDT
}

void main(void) {
    WDTCTL = WDTPW | WDTHOLD; // ��������� ���������� ������

    // ��������� ������ ��� �����������
    P1DIR |= BIT0;  // ������������� �1.0 ��� ����� (LED1)
    P8DIR |= BIT1;  // ������������� �8.1 ��� ����� (LED2)
    P8DIR |= BIT2;  // ������������� �8.2 ��� ����� (LED3)

    // ��������� ������
    P2DIR &= ~BIT2; // ������������� �2.2 ��� ���� (S2)
    P2REN |= BIT2;  // �������� ������������� �������� ��� �2.2
    P2OUT |= BIT2;  // ����������� �2.2 � Vcc
    P2IE |= BIT2;   // ��������� ���������� �� ������
    P2IES |= BIT2;  // ���������� �� ���������� ������ (�������)
    P2IFG &= ~BIT2; // ���������� ���� ����������

    __enable_interrupt(); // ��������� ���������� ����������

    // ��������� ��������� �����������
    P1OUT &= ~BIT0;
    P8OUT &= ~BIT1;
    P8OUT &= ~BIT2;

    while (1) {
        // �������� ���� ������, ��� ��� ��� ������ ���� � �����������
        __low_power_mode_3(); // �������� ����� ����������������
    }
}

// ���������� �� ������� ��� ���������� ������
#pragma vector=PORT2_VECTOR
__interrupt void PORT2_ISR(void) {
    if (!(P2IN & BIT2)) {  // ������ ������ (��������� �����)
        button_pressed = 1;      // ������������� ���� ������� ������
        led_off_step = 0;        // ���������� ��� ������� �����������
        delay_counter = 0;       // ���������� ������� ��������
        // �������� ��� ����������
        P1OUT |= BIT0;           // �������� LED1
        P8OUT |= BIT1;           // �������� LED2
        P8OUT |= BIT2;           // �������� LED3
        stop_watchdog_timer();   // ������������� WDT, ���� ��� �������
        P2IES &= ~BIT2;          // ������ �� ���������� �� ������������� ������ (����������)
    } else {                     // ������ �������� (������������ �����)
        button_pressed = 0;      // ���������� ���� ������� ������
        led_off_step = 0;        // ���������� ��� ������� �����������
        delay_counter = 0;       // ���������� ������� ��������
        setup_watchdog_timer();  // ��������� WDT ��� ����������������� ������� �����������
        P2IES |= BIT2;           // ������ �� ���������� �� ���������� ������ (�������)
    }

    P2IFG &= ~BIT2; // ���������� ���� ����������
}

// ���������� �� ������� WDT
#pragma vector=WDT_VECTOR
__interrupt void WDT_ISR(void) {
    if (!button_pressed) {  // ���� ������ ��������
        delay_counter++;    // ����������� ������� ��������

        if (delay_counter >= 10) {  // ������ 10 ��� �� 100 �� = 1 �������
            switch (led_off_step) {
            case 0:
                P1OUT &= ~BIT0; // ��������� LED1
                led_off_step++;
                break;
            case 1:
                P8OUT &= ~BIT1; // ��������� LED2
                led_off_step++;
                break;
            case 2:
                P8OUT &= ~BIT2; // ��������� LED3
                led_off_step++;
                stop_watchdog_timer();  // ������������� WDT ����� ����������
                break;
            default:
                stop_watchdog_timer();  // ������������� WDT, ���� ��� ��������� 2
                break;
            }
            delay_counter = 0; // ���������� ������� ����� ������� ���� �������
        }
    }
}

