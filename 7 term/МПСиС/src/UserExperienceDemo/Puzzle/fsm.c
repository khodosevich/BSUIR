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
//  fsm.c
//
//  Describtion:
//    A simple state machine for the MSP430
//    Do not change code in here!!!
//
//  Generated with Excel Table
//  Date:  08/26/2008        Time:  15:00:56
//
//****************************************************************************//

#include <stdint.h>
#include <stdio.h>

#include "fsm.h"

//****************************************************************************//
// Global variables
//****************************************************************************//
uint8_t ActState;

const FSM_STATE_TABLE StateTable[NR_STATES][NR_EVENTS] =
{
    NULL, INIT_GAME, NULL, INIT_GAME, NULL, INIT_GAME, NULL, INIT_GAME, FSM_StartGame, EMPTY_FIELD9,
    FSM_StopGame, INIT_GAME,
    FSM_PushLeft, EMPTY_FIELD2, NULL, EMPTY_FIELD1, FSM_PushUp, EMPTY_FIELD4, NULL, EMPTY_FIELD1,
    FSM_InitGame, INIT_GAME, NULL, EMPTY_FIELD1,
    FSM_PushLeft, EMPTY_FIELD3, FSM_PushRight, EMPTY_FIELD1, FSM_PushUp, EMPTY_FIELD5, NULL,
    EMPTY_FIELD2, FSM_InitGame, INIT_GAME, NULL, EMPTY_FIELD2,
    NULL, EMPTY_FIELD3, FSM_PushRight, EMPTY_FIELD2, FSM_PushUp, EMPTY_FIELD6, NULL, EMPTY_FIELD3,
    FSM_InitGame, INIT_GAME, NULL, EMPTY_FIELD3,
    FSM_PushLeft, EMPTY_FIELD5, NULL, EMPTY_FIELD4, FSM_PushUp, EMPTY_FIELD7, FSM_PushDown,
    EMPTY_FIELD1, FSM_InitGame, INIT_GAME, NULL, EMPTY_FIELD4,
    FSM_PushLeft, EMPTY_FIELD6, FSM_PushRight, EMPTY_FIELD4, FSM_PushUp, EMPTY_FIELD8, FSM_PushDown,
    EMPTY_FIELD2, FSM_InitGame, INIT_GAME, NULL, EMPTY_FIELD5,
    NULL, EMPTY_FIELD6, FSM_PushRight, EMPTY_FIELD5, FSM_PushUp, EMPTY_FIELD9, FSM_PushDown,
    EMPTY_FIELD3, FSM_InitGame, INIT_GAME, NULL, EMPTY_FIELD6,
    FSM_PushLeft, EMPTY_FIELD8, NULL, EMPTY_FIELD7, NULL, EMPTY_FIELD7, FSM_PushDown, EMPTY_FIELD4,
    FSM_InitGame, INIT_GAME, NULL, EMPTY_FIELD7,
    FSM_PushLeft, EMPTY_FIELD9, FSM_PushRight, EMPTY_FIELD7, NULL, EMPTY_FIELD8, FSM_PushDown,
    EMPTY_FIELD5, FSM_InitGame, INIT_GAME, NULL, EMPTY_FIELD8,
    NULL, EMPTY_FIELD9, FSM_PushRight, EMPTY_FIELD8, NULL, EMPTY_FIELD9, FSM_PushDown, EMPTY_FIELD6,
    FSM_InitGame, INIT_GAME, FSM_StopGame, STOP_GAME,
    NULL, STOP_GAME, NULL, STOP_GAME, NULL, STOP_GAME, NULL, STOP_GAME, FSM_InitGame, INIT_GAME,
    NULL, STOP_GAME
};


//****************************************************************************//
// Initialize state machine
//****************************************************************************//
void FSM_Init(void)
{
    ActState = INIT_GAME;
}

//****************************************************************************//
// Event function "Left"
//****************************************************************************//
void FSM_Left(void)
{
    if (StateTable[ActState][LEFT].ptrFunct != NULL)
        StateTable[ActState][LEFT].ptrFunct();

    ActState = StateTable[ActState][LEFT].NextState;
}

//****************************************************************************//
// Event function "Right"
//****************************************************************************//
void FSM_Right(void)
{
    if (StateTable[ActState][RIGHT].ptrFunct != NULL)
        StateTable[ActState][RIGHT].ptrFunct();

    ActState = StateTable[ActState][RIGHT].NextState;
}

//****************************************************************************//
// Event function "Up"
//****************************************************************************//
void FSM_Up(void)
{
    if (StateTable[ActState][UP].ptrFunct != NULL)
        StateTable[ActState][UP].ptrFunct();

    ActState = StateTable[ActState][UP].NextState;
}

//****************************************************************************//
// Event function "Down"
//****************************************************************************//
void FSM_Down(void)
{
    if (StateTable[ActState][DOWN].ptrFunct != NULL)
        StateTable[ActState][DOWN].ptrFunct();

    ActState = StateTable[ActState][DOWN].NextState;
}

//****************************************************************************//
// Event function "Button"
//****************************************************************************//
void FSM_Button(void)
{
    if (StateTable[ActState][BUTTON].ptrFunct != NULL)
        StateTable[ActState][BUTTON].ptrFunct();

    ActState = StateTable[ActState][BUTTON].NextState;
}

//****************************************************************************//
// Event function "Win"
//****************************************************************************//
void FSM_Win(void)
{
    if (StateTable[ActState][WIN].ptrFunct != NULL)
        StateTable[ActState][WIN].ptrFunct();

    ActState = StateTable[ActState][WIN].NextState;
}

//****************************************************************************//
