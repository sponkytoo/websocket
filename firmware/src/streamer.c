/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    streamer.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It 
    implements the logic of the application's state machine and it may call 
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************
#include "ws_server.h"
#include "streamer.h"
#include "tcpip/src/common/helpers.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.
    
    Application strings and buffers are be defined outside this structure.
 */

STREAMER_DATA streamerData;

extern WS_SERVER_DATA ws_serverData;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
 */

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


/* TODO:  Add any necessary local functions.
 */


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void STREAMER_Initialize ( void )

  Remarks:
    See prototype in streamer.h.
 */

void STREAMER_Initialize(void)
{
    /* Place the App state machine in its initial state. */
    streamerData.state = STREAMER_STATE_INIT;


    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}

/******************************************************************************
  Function:
    void STREAMER_Tasks ( void )

  Remarks:
    See prototype in streamer.h.
 */

void STREAMER_Tasks(void)
{
    /* Check the application's current state. */
    switch (streamerData.state)
    {
        /* Application's initial state. */
    case STREAMER_STATE_INIT:
    {
        bool appInitialized = true;


        if (appInitialized)
        {

            streamerData.state = STREAMER_STATE_SERVICE_TASKS;
        }
        break;
    }

    case STREAMER_STATE_SERVICE_TASKS:
    {
        if (ws_serverData.StreamActive == true)
        {

            char DataString[256];
            char SingleNumberString[32];
            uint16_t Value;
            uint32_t ix;
            static uint16_t count = 0;

            DataString[0] = 0;
            for (ix = 0; ix < 4; ix++)
            {
                Value = (uint16_t) count; //SYS_RANDOM_PseudoGet();
                count += 4000;
                uitoa(Value, (uint8_t *) SingleNumberString);
                strcat(DataString, SingleNumberString);
                strcat(DataString, " ");
            }
            DataString[strlen(DataString) - 1] = 0;

            wsSendDataCallback((const uint8_t*) DataString, strlen(DataString));
        }
        vTaskDelay(ws_serverData.delay);
        break;
    }

        /* TODO: implement your application state machine.*/


        /* The default state should never be executed. */
    default:
    {
        /* TODO: Handle error in application's state machine. */
        break;
    }
    }
}



/*******************************************************************************
 End of File
 */