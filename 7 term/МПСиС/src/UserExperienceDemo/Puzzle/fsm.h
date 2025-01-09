/* --COPYRIGHT--,BSD
 * Copyright (c) 2010, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
//****************************************************************************//
//  MSP430 state machine
//  fsm.h
//
//  Describtion:
//    A simple state machine for the MSP430
//
//  Generated with Excel Table
//  Date:  08/26/2008        Time:  15:00:57
//
//****************************************************************************//

#ifndef FSM_H
#define FSM_H

//****************************************************************************//
// State table typedef
//****************************************************************************//
typedef struct
{
    void (*ptrFunct)(void);
    uint8_t NextState;
} FSM_STATE_TABLE;

extern uint8_t ActState;


//****************************************************************************//
// Some useful macros
//****************************************************************************//
#define NR_EVENTS 6
#define LEFT  0
#define RIGHT  1
#define UP  2
#define DOWN  3
#define BUTTON  4
#define WIN  5

#define NR_STATES 11
#define INIT_GAME  0
#define EMPTY_FIELD1  1
#define EMPTY_FIELD2  2
#define EMPTY_FIELD3  3
#define EMPTY_FIELD4  4
#define EMPTY_FIELD5  5
#define EMPTY_FIELD6  6
#define EMPTY_FIELD7  7
#define EMPTY_FIELD8  8
#define EMPTY_FIELD9  9
#define STOP_GAME  10


//****************************************************************************//
// Function prototypes
//****************************************************************************//
// Initialize state machine
void FSM_Init(void);

// Event function "Left"
void FSM_Left(void);

// Event function "Right"
void FSM_Right(void);

// Event function "Up"
void FSM_Up(void);

// Event function "Down"
void FSM_Down(void);

// Event function "Button"
void FSM_Button(void);

// Event function "Win"
void FSM_Win(void);

// Transition function "StartGame"
void FSM_StartGame(void);

// Transition function "StopGame"
void FSM_StopGame(void);

// Transition function "PushLeft"
void FSM_PushLeft(void);

// Transition function "PushUp"
void FSM_PushUp(void);

// Transition function "InitGame"
void FSM_InitGame(void);

// Transition function "PushRight"
void FSM_PushRight(void);

// Transition function "PushDown"
void FSM_PushDown(void);


//****************************************************************************//

#endif /* FSM_H */

//****************************************************************************//
