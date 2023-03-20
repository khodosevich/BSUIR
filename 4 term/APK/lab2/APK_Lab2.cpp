#include <dos.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

char color = 0x89;	// default color (blue);

void changeColor() // change color randomly
{
	color = colors[rand() % COLORS];
	return;
}

void print()
{
	char temp;  // current bit
	int i, val;
	VIDEO far* screen = (VIDEO far*)MK_FP(0xB800, 0);   // get video card buffer

	//-----------------------------------------MASK---------------------------------------------------
	val = inp(0x21);                                     // get mask MASTER register
	for (i = 0; i < 8; i++)                              // find bits
	{
		temp = val % 2;                                  // get last bit
		val = val >> 1;                                  // move bits on right
		screen->symbol = temp + '0';                     // save bit as a char ('0' or '1')
		screen->attribute = color;                       // set color of print symbol by video card
		screen++;                                        // get to next symbol
	}
	screen++;                                            // space between master and slave

	val = inp(0xA1);                                     // get mask SLAVE register
	for (i = 0; i < 8; i++)								 // find bits
	{
		temp = val % 2;									 // get last bit
		val = val >> 1;									 // move bits on right
		screen->symbol = temp + '0';					 // save bit as a char ('0' or '1')
		screen->attribute = color;						 // set color of print symbol by video card
		screen++;										 // get to next symbol
	}
	screen += 63;									     // next line
	//-----------------------------------------MASK---------------------------------------------------

	//----------------------------------------REQUEST-------------------------------------------------
	outp(0x20, 0x0A);                                    // switch to MASTERS's request register
	val = inp(0x20);                                     // get MASTERS's request register
	for (i = 0; i < 8; i++)								 // find bits
	{
		temp = val % 2;									 // get last bit
		val = val >> 1;									 // move bits on right
		screen->symbol = temp + '0';					 // save bit as a char ('0' or '1')
		screen->attribute = color;						 // set color of print symbol by video card
		screen++;										 // get to next symbol
	}
	screen++;                                            // space

	outp(0xA0, 0x0A);                                    // switch to SLAVE's request register
	val = inp(0xA0);                                     // get SLAVE's request register
	for (i = 0; i < 8; i++)								 // find bits
	{
		temp = val % 2;									 // get last bit
		val = val >> 1;									 // move bits on right
		screen->symbol = temp + '0';					 // save bit as a char ('0' or '1')
		screen->attribute = color;						 // set color of print symbol by video card
		screen++;										 // get to next symbol
	}
	screen += 63;                                        // go to next line
	//----------------------------------------REQUEST-------------------------------------------------

	//----------------------------------------SERVICE-------------------------------------------------
	outp(0x20, 0x0B);                                    // switch to MASTER's service register
	val = inp(0x20);                                     // get MASTER's service register
	for (i = 0; i < 8; i++)                              // find bits
	{
		temp = val % 2;									 // get last bit
		val = val >> 1;									 // move bits on right
		screen->symbol = temp + '0';					 // save bit as a char 
		screen->attribute = color;						 // set color of print 
		screen++;										 // get to next symbol
	}
	screen++;                                            // space

	outp(0xA0, 0x0B);                                    // switch to SLAVE's service register
	val = inp(0xA0);                                     // getting SLAVES's service register
	for (i = 0; i < 8; i++)                              // find bits
	{
		temp = val % 2;								     // get last bit
		val = val >> 1;									 // move bits on right
		screen->symbol = temp + '0';					 // save bit as a char 
		screen->attribute = color;						 // set color of print 
		screen++;										 // get to next symbol
	}
	//----------------------------------------SERVICE-------------------------------------------------
}

//--------------------------------------------IRQ 0-7-------------------------------------------------
void interrupt(*oldint8) (...);							 // IRQ 0  - interrupt of timer (18,2 times per second)
void interrupt(*oldint9) (...);							 // IRQ 1  - interrupt of keypad (press and release key)
void interrupt(*oldint10) (...);						 // IRQ 2  - interrupt for cascade interruptions in AT machines
void interrupt(*oldint11) (...);						 // IRQ 3  - interrupt of async port COM 2
void interrupt(*oldint12) (...);						 // IRQ 4  - interrupt of async port COM 1
void interrupt(*oldint13) (...);						 // IRQ 5  - interrupt of hard disk controller (for XT)
void interrupt(*oldint14) (...);						 // IRQ 6  - interrupt of floppy disk controller (when finish operation with floppy disk)
void interrupt(*oldint15) (...);						 // IRQ 7  - interrupt of printer (when printer is ready to work)
//--------------------------------------------IRQ 0-7-------------------------------------------------

//--------------------------------------------IRQ 8-15------------------------------------------------
void interrupt(*oldint70) (...);						 // IRQ 8  - interrupt of real time clock
void interrupt(*oldint71) (...);						 // IRQ 9  - interrupt of EGA controller
void interrupt(*oldint72) (...);						 // IRQ 10 - reserved interrupt
void interrupt(*oldint73) (...);						 // IRQ 11 - reserved interrupt
void interrupt(*oldint74) (...);						 // IRQ 12 - reserved interrupt
void interrupt(*oldint75) (...);						 // IRQ 13 - interrupt of mathematic soprocessor
void interrupt(*oldint76) (...);						 // IRQ 14 - interrupt of hard disk
void interrupt(*oldint77) (...);						 // IRQ 15 - reserved interrupt
//--------------------------------------------IRQ 8-15------------------------------------------------

//---------------------------------------NEW INTERRUPTIONS--------------------------------------------
void interrupt  newint08(...) { print(); oldint8(); }                     // set function for service interrupt	int8
void interrupt  newint09(...) { print(); oldint9(); }	  // set function for service interrupt	int9
void interrupt  newint0A(...) { print(); oldint10(); }	  // set function for service interrupt	int10
void interrupt  newint0B(...) { print(); oldint11(); }	  // set function for service interrupt	int11
void interrupt  newint0C(...) { print(); oldint12(); }	  // set function for service interrupt	int12
void interrupt  newint0D(...) { print(); oldint13(); }	  // set function for service interrupt	int13
void interrupt  newint0E(...) { print(); oldint14(); }	  // set function for service interrupt	int14
void interrupt  newint0F(...) { print(); oldint15(); }	  // set function for service interrupt	int15

void interrupt  newintC8(...) { print(); oldint70(); }	  // set function for service interrupt	int70
void interrupt  newintC9(...) { print(); oldint71(); }	  // set function for service interrupt	int71
void interrupt  newintCA(...) { print(); oldint72(); }	  // set function for service interrupt	int72
void interrupt  newintCB(...) { print(); oldint73(); }	  // set function for service interrupt	int73
void interrupt  newintCC(...) { print(); oldint74(); }	  // set function for service interrupt	int74
void interrupt  newintCD(...) { print(); oldint75(); }	  // set function for service interrupt	int75
void interrupt  newintCE(...) { print(); oldint76(); }	  // set function for service interrupt	int76
void interrupt  newintCF(...) { print(); oldint77(); }	  // set function for service interrupt	int77
//---------------------------------------NEW INTERRUPTIONS--------------------------------------------

void initialize()
{
	//IRQ 0-7	
	oldint8 = getvect(0x08);		// IRQ  0 - system timer
	oldint9 = getvect(0x09);		// IRQ  1 - keyboard controller
	oldint10 = getvect(0x0A);		// IRQ  2 - cascaded signals from IRQs 8-15 (any devices configured to use IRQ2 will actually be using IRQ9)
	oldint11 = getvect(0x0B);		// IRQ  3 - serial port controller for serial port 2 (shared with  serial port 4, if present)
	oldint12 = getvect(0x0C);		// IRQ  4 - serial port controller for serial port 1 (shared with serial port 3, if present)
	oldint13 = getvect(0x0D);		// IRQ  5 - parallel port 2 and 3 or sound card
	oldint14 = getvect(0x0E);		// IRQ  6 - floppy disk controller
	oldint15 = getvect(0x0F);		// IRQ  7 - parallel port 1. It is used for printers or for any parallel port if a printer is not present

	//IRQ 8-15
	oldint70 = getvect(0x70);		// IRQ  8 - real-time clock (RTC)
	oldint71 = getvect(0x71);		// IRQ  9 - Advanced Configuration and Power Interface (ACPI) system control interrupt
	oldint72 = getvect(0x72);		// IRQ 10 - the interrupt is left open for the use of peripherals (open interrupt/available, SCSI or NIC)
	oldint73 = getvect(0x73);		// IRQ 11 - the interrupt is left open for the use of peripherals (open interrupt/available, SCSI or NIC)
	oldint74 = getvect(0x74);		// IRQ 12 - mouse on PS/2 connector
	oldint75 = getvect(0x75);		// IRQ 13 - CPU co-processor or integrated floating point unit or inter-processor interrupt (use depends on OS)
	oldint76 = getvect(0x76);		// IRQ 14 - primary ATA channel (ATA interface usually serves hard disk drives and CD drives)
	oldint77 = getvect(0x77);		// IRQ 15 - secondary ATA channel

	//------------------------------------NEW HANDLERS--------------------------------------------------
	//set new handlers for IRQ 0-7
	setvect(0x08, newint08);		// set new handler for IRQ 0
	setvect(0x09, newint09);		// set new handler for IRQ 1
	setvect(0x0A, newint0A);		// set new handler for IRQ 2
	setvect(0x0B, newint0B);		// set new handler for IRQ 3
	setvect(0x0C, newint0C);		// set new handler for IRQ 4
	setvect(0x0D, newint0D);		// set new handler for IRQ 5
	setvect(0x0E, newint0E);		// set new handler for IRQ 6
	setvect(0x0F, newint0F);		// set new handler for IRQ 7

	//set new handlers for IRQ 8-15
	setvect(0x98, newintC8);		// set new handlers for IRQ 8
	setvect(0x99, newintC9);		// set new handlers for IRQ 9
	setvect(0x9A, newintCA);		// set new handlers for IRQ 10
	setvect(0x9B, newintCB);		// set new handlers for IRQ 11
	setvect(0x9C, newintCC);		// set new handlers for IRQ 12
	setvect(0x9D, newintCD);		// set new handlers for IRQ 13
	setvect(0x9E, newintCE);		// set new handlers for IRQ 14
	setvect(0x9F, newintCF);		// set new handlers for IRQ 15
	//------------------------------------NEW HANDLERS--------------------------------------------------

	_disable(); // CLI

	// interrupt initializtion for Master
	outp(0x20, 0x11);				// ICW1 - initialize MASTER
	outp(0x21, 0x08);				// ICW2 - base vector for MASTER (C0H)
	outp(0x21, 0x04);				// ICW3 - the port bit of SLAVE (in binary format)
	outp(0x21, 0x01);				// ICW4 - default

	// interrupt initialization for Slave
	outp(0xA0, 0x11);  				// ICW1 - initialize SLAVE
	outp(0xA1, 0x98);				// ICW2 - base vector for SLAVE (08H)
	outp(0xA1, 0x02);   			// ICW3 - the port number of connected port on MASTER
	outp(0xA1, 0x01);   			// ICW4 - default

	_enable(); // STI
}

int main()
{
	unsigned far* p;                               // declare pointer that can link to other segment
	initialize();                                  // execute initialization
	system("cls");                                 // clear console

	printf("                   -  MASK\n");        // the mask of Master and Slave
	printf("                   -  REQUEST\n");     // the request of Master and Slave
	printf("                   -  SERVICE\n");     // the service of Master and Slave
	printf(" MASTER   SLAVE\n");

	// resident 
	FP_SEG(p) = _psp;                              // get segment
	FP_OFF(p) = 0x2c;                              // get data segment offset with environment variables
	_dos_freemem(*p);                              // free for DOS

	_dos_keep(0, (_DS - _CS) + (_SP / 16) + 1);    // left program resident, 1st param - ending code,
	// 2nd param - volume of memory, that must be reserved for program after ending
	return 0;
}