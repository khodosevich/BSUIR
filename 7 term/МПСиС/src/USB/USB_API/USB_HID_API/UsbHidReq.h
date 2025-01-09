/* --COPYRIGHT--,BSD
 * Copyright (c) 2012, Texas Instruments Incorporated
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
/* 
 * ======== UsbHidReq.h ========
 */
#ifndef _UsbHidReq_H_
#define _UsbHidReq_H_

#ifdef __cplusplus
extern "C"
{
#endif


/**
 * Return Hid descriptor to host over control endpoint
 */
BYTE usbGetHidDescriptor(VOID);
/**
 * Return HID report descriptor to host over control endpoint
 */
BYTE usbGetReportDescriptor(VOID);
/**
 * Receive Set_Report from host over control endpoint
 */
BYTE usbSetReport(VOID);
/**
 * Process Get_Report request from host over control endpoint
 */
BYTE usbGetReport(VOID);
/**
 * Receive Set_Idle from host over control endpoint
 */
BYTE usbSetIdle(VOID);
/**
 * Process Get_Idle request from host over control endpoint
 */
BYTE usbGetIdle(VOID);
/**
 * Receive Set_Protocol from host over control endpoint
 */
BYTE usbSetProtocol(VOID);
/**
 * Process Get_Protocol request from host over control endpoint
 */
BYTE usbGetProtocol(VOID);


#ifdef __cplusplus
}
#endif
#endif  //_UsbHidReq_H_
