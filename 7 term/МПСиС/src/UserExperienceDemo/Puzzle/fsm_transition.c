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
//  fsm_transition.c
//
//  Describtion:
//    A simple state machine for the MSP430
//    You can add your own code in here!!!
//
//  Generated with Excel Table
//  Date:  08/26/2008        Time:  15:00:57
//
//****************************************************************************//

#include <MSP430.h>
#include <stdint.h>
#include <stdlib.h>
#include "HAL_Dogs102x6.h"

#include "fsm_transition.h"
#include "fsm.h"

//****************************************************************************//
// Global variables
//****************************************************************************//

#define X_FIELD_SIZE 1 * DOGS102x6_X_SIZE / 3
#define Y_FIELD_SIZE 1 * DOGS102x6_Y_SIZE / 3

#define X_FIELD_CENTER X_FIELD_SIZE / 2
#define Y_FIELD_CENTER X_FIELD_SIZE / 2

const GAME_POS GamePos[FIELD_SIZE] =
{
    1 * X_FIELD_SIZE - X_FIELD_CENTER, 1 * Y_FIELD_SIZE - Y_FIELD_CENTER, 2 * X_FIELD_SIZE -
    X_FIELD_CENTER, 1 * Y_FIELD_SIZE - Y_FIELD_CENTER, 3 * X_FIELD_SIZE - X_FIELD_CENTER, 1 *
    Y_FIELD_SIZE - Y_FIELD_CENTER,
    1 * X_FIELD_SIZE - X_FIELD_CENTER, 2 * Y_FIELD_SIZE - Y_FIELD_CENTER, 2 * X_FIELD_SIZE -
    X_FIELD_CENTER, 2 * Y_FIELD_SIZE - Y_FIELD_CENTER, 3 * X_FIELD_SIZE - X_FIELD_CENTER, 2 *
    Y_FIELD_SIZE - Y_FIELD_CENTER,
    1 * X_FIELD_SIZE - X_FIELD_CENTER, 3 * Y_FIELD_SIZE - Y_FIELD_CENTER, 2 * X_FIELD_SIZE -
    X_FIELD_CENTER, 3 * Y_FIELD_SIZE - Y_FIELD_CENTER, 3 * X_FIELD_SIZE - X_FIELD_CENTER, 3 *
    Y_FIELD_SIZE - Y_FIELD_CENTER,
};

uint8_t GameData[FIELD_SIZE];


//****************************************************************************//
//  UpdateField
//
//  DESCRIPTION:
//    Update field and check for winning the game
//
//  PROTOTYPE:
//    void UpdateField (void)
//
//  PARAMETERS:
//    None
//
//  RETURN VALUE:
//    None
//
//****************************************************************************//
void UpdateField(void)
{
    uint8_t i;
    uint8_t num = ' ';

    // Draw field
    Dogs102x6_clearScreen();
    // Border
    Dogs102x6_horizontalLineDraw(0, DOGS102x6_X_SIZE,                0, DOGS102x6_DRAW_NORMAL);
    Dogs102x6_horizontalLineDraw(0, DOGS102x6_X_SIZE, DOGS102x6_Y_SIZE, DOGS102x6_DRAW_NORMAL);
    Dogs102x6_verticalLineDraw(0, DOGS102x6_Y_SIZE,                0, DOGS102x6_DRAW_NORMAL);
    Dogs102x6_verticalLineDraw(0, DOGS102x6_Y_SIZE, DOGS102x6_X_SIZE, DOGS102x6_DRAW_NORMAL);

    Dogs102x6_horizontalLineDraw(0, DOGS102x6_X_SIZE, 1 * DOGS102x6_Y_SIZE / 3,
                                 DOGS102x6_DRAW_NORMAL);                                                //
                                                                                                        // horizontal
                                                                                                        // lines
    Dogs102x6_horizontalLineDraw(0, DOGS102x6_X_SIZE, 2 * DOGS102x6_Y_SIZE / 3,
                                 DOGS102x6_DRAW_NORMAL);
    Dogs102x6_verticalLineDraw(0, DOGS102x6_Y_SIZE, 1 * DOGS102x6_X_SIZE / 3, DOGS102x6_DRAW_NORMAL);   //
                                                                                                        // vertical
                                                                                                        // lines
    Dogs102x6_verticalLineDraw(0, DOGS102x6_Y_SIZE, 2 * DOGS102x6_X_SIZE / 3, DOGS102x6_DRAW_NORMAL);

    // Update field
    for (i = 0; i < FIELD_SIZE; i++)
    {
        num = GameData[i] + NR_OFFSET;
        if (num == '0') num = ' ';

        Dogs102x6_charDrawXY(GamePos[i].PosX, GamePos[i].PosY, num, DOGS102x6_DRAW_NORMAL);
    }

}

//****************************************************************************//
// Transition function "InitGame"
//****************************************************************************//
void FSM_InitGame(void)
{
    // Write text on LCD
    Dogs102x6_clearScreen();

    Dogs102x6_stringDraw(0, 0, "Puzzle Objective:", DOGS102x6_DRAW_NORMAL);
    Dogs102x6_stringDraw(1, 0, "- Tilt to move #s", DOGS102x6_DRAW_NORMAL);
    Dogs102x6_stringDraw(2, 0, "- Sum of rows &  ", DOGS102x6_DRAW_NORMAL);
    Dogs102x6_stringDraw(3, 0, "  cols must = 12 ", DOGS102x6_DRAW_NORMAL);
    Dogs102x6_stringDraw(4, 0, "- To re-cal Accel", DOGS102x6_DRAW_NORMAL);
    Dogs102x6_stringDraw(5, 0, "  go to SETTINGS ", DOGS102x6_DRAW_NORMAL);
    //Dogs102x6_stringDraw(6, 0, "", DOGS102x6_DRAW_INVERT);
    Dogs102x6_stringDraw(7, 0, "Press S1 to Begin", DOGS102x6_DRAW_INVERT);
    // Init and start TimerA
    TB0CTL = TBSSEL_2 + MC_2;
}

//****************************************************************************//
// Transition function "StartGame"
//****************************************************************************//
void FSM_StartGame(void)
{
    uint8_t i;
    uint8_t RandValue;

    // Initialize random generator and stop TimerA
    srand(TB0R);
    TB0CTL = 0x00;

    // Clear game data
    for (i = 0; i < FIELD_SIZE; i++) GameData[i] = 0;

    // Generate random game data
    for (i = 1; i < FIELD_SIZE; i++)
    {
        do
            RandValue = rand() & 0x07;
        while (GameData[RandValue]);

        GameData[RandValue] = i;
    }
    // for test
    //for (i = 0; i <= 7; i++) GameData [i] = DefVal [i];

    // Update field
    UpdateField();
}

//****************************************************************************//
// Transition function "PushLeft"
//****************************************************************************//
void FSM_PushLeft(void)
{
    GameData[ActState - 1] = GameData[ActState - 0];
    GameData[ActState - 0] = 0;

    // Update field
    UpdateField();
}

//****************************************************************************//
// Transition function "PushRight"
//****************************************************************************//
void FSM_PushRight(void)
{
    GameData[ActState - 1] = GameData[ActState - 2];
    GameData[ActState - 2] = 0;

    // Update field
    UpdateField();
}

//****************************************************************************//
// Transition function "PushUp"
//****************************************************************************//
void FSM_PushUp(void)
{
    GameData[ActState - 1] = GameData[ActState + 2];
    GameData[ActState + 2] = 0;

    // Update field
    UpdateField();
}

//****************************************************************************//
// Transition function "PushDown"
//****************************************************************************//
void FSM_PushDown(void)
{
    GameData[ActState - 1] = GameData[ActState - 4];
    GameData[ActState - 4] = 0;

    // Update field
    UpdateField();
}

//****************************************************************************//
// Transition function "StopGame"
//****************************************************************************//
void FSM_StopGame(void)
{
    // Write text on LCD
    Dogs102x6_clearScreen();
    Dogs102x6_stringDrawXY(DOGS102x6_X_SIZE / 2, DOGS102x6_Y_SIZE / 2, "WIN", DOGS102x6_DRAW_NORMAL);

}

//****************************************************************************//
