/*********************************************************************
*          Portions COPYRIGHT 2015 STMicroelectronics                *
*          Portions SEGGER Microcontroller GmbH & Co. KG             *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2015  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.28 - Graphical user interface for embedded applications **
All  Intellectual Property rights  in the Software belongs to  SEGGER.
emWin is protected by  international copyright laws.  Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with the following terms:

The  software has  been licensed  to STMicroelectronics International
N.V. a Dutch company with a Swiss branch and its headquarters in Plan-
les-Ouates, Geneva, 39 Chemin du Champ des Filles, Switzerland for the
purposes of creating libraries for ARM Cortex-M-based 32-bit microcon_
troller products commercialized by Licensee only, sublicensed and dis_
tributed under the terms and conditions of the End User License Agree_
ment supplied by STMicroelectronics International N.V.
Full source code is available at: www.segger.com

We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : LCDConf_FlexColor_Template.c
Purpose     : Display controller configuration (single layer)
---------------------------END-OF-HEADER------------------------------
*/

/**
  ******************************************************************************
  * @attention
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

#include "GUI.h"
#include "GUIDRV_FlexColor.h"

/*********************************************************************
*
*       Layer configuration (to be modified)
*
**********************************************************************
*/

//
// Physical display size
//
#define XSIZE_PHYS  480 // To be adapted to x-screen size
#define YSIZE_PHYS  272 // To be adapted to y-screen size

/*********************************************************************
*
*       Configuration checking
*
**********************************************************************
*/
#ifndef   VXSIZE_PHYS
  #define VXSIZE_PHYS XSIZE_PHYS
#endif
#ifndef   VYSIZE_PHYS
  #define VYSIZE_PHYS YSIZE_PHYS
#endif
#ifndef   XSIZE_PHYS
  #error Physical X size of display is not defined!
#endif
#ifndef   YSIZE_PHYS
  #error Physical Y size of display is not defined!
#endif
#ifndef   GUICC_565
  #error Color conversion not defined!
#endif
#ifndef   GUIDRV_FLEXCOLOR
  #error No display driver defined!
#endif

/*********************************************************************
*
*       Local functions
*
**********************************************************************
*/
/********************************************************************
*
*       LcdWriteReg
*
* Function description:
*   Sets display register
*/
static void LcdWriteReg(U16 Data) {
  // ... TBD by user
}

/********************************************************************
*
*       LcdWriteData
*
* Function description:
*   Writes a value to a display register
*/
static void LcdWriteData(U16 Data) {
  // ... TBD by user
}

/********************************************************************
*
*       LcdWriteDataMultiple
*
* Function description:
*   Writes multiple values to a display register.
*/
static void LcdWriteDataMultiple(U16 * pData, int NumItems) {
  while (NumItems--) {
    // ... TBD by user
  }
}

/********************************************************************
*
*       LcdReadDataMultiple
*
* Function description:
*   Reads multiple values from a display register.
*/
static void LcdReadDataMultiple(U16 * pData, int NumItems) {
  while (NumItems--) {
    // ... TBD by user
  }
}

/*********************************************************************
*
*       Public functions
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_X_Config
*
* Function description:
*   Called during the initialization process in order to set up the
*   display driver configuration.
*
*/
void LCD_X_Config(void) {
  GUI_DEVICE * pDevice;
  CONFIG_FLEXCOLOR Config = {0};
  GUI_PORT_API PortAPI = {0};
  //
  // Set display driver and color conversion
  //
  pDevice = GUI_DEVICE_CreateAndLink(GUIDRV_FLEXCOLOR, GUICC_666, 0, 0);
  //
  // Display driver configuration, required for Lin-driver
  //
  LCD_SetSizeEx (0, XSIZE_PHYS , YSIZE_PHYS);
  LCD_SetVSizeEx(0, VXSIZE_PHYS, VYSIZE_PHYS);
  //
  // Orientation
  //
  Config.Orientation = 0;//GUI_SWAP_XY | GUI_MIRROR_Y;
  GUIDRV_FlexColor_Config(pDevice, &Config);
  //
  // Set controller and operation mode
  //
  PortAPI.pfWrite16_A0  = LcdWriteReg;
  PortAPI.pfWrite16_A1  = LcdWriteData;
  PortAPI.pfWriteM16_A1 = LcdWriteDataMultiple;
  PortAPI.pfReadM16_A1  = LcdReadDataMultiple;
  GUIDRV_FlexColor_SetFunc(pDevice, &PortAPI, GUIDRV_FLEXCOLOR_F66720, GUIDRV_FLEXCOLOR_M16C0B8);
}

/*********************************************************************
*
*       LCD_X_DisplayDriver
*
* Function description:
*   This function is called by the display driver for several purposes.
*   To support the according task the routine needs to be adapted to
*   the display controller. Please note that the commands marked with
*   'optional' are not cogently required and should only be adapted if
*   the display controller supports these features.
*
* Parameter:
*   LayerIndex - Index of layer to be configured
*   Cmd        - Please refer to the details in the switch statement below
*   pData      - Pointer to a LCD_X_DATA structure
*
* Return Value:
*   < -1 - Error
*     -1 - Command not handled
*      0 - Ok
*/
int LCD_X_DisplayDriver(unsigned LayerIndex, unsigned Cmd, void * pData) {
  int r;
  (void) LayerIndex;
  (void) pData;
  
  switch (Cmd) {
  case LCD_X_INITCONTROLLER: {
    //
    // Called during the initialization process in order to set up the
    // display controller and put it into operation. If the display
    // controller is not initialized by any external routine this needs
    // to be adapted by the customer...
    //
    // ...
    
    LcdWriteReg(0x01);  //Software Reset
    LcdWriteReg(0x01);
    LcdWriteReg(0x01);
    LcdWriteReg(0xe0);  //START PLL
    LcdWriteData(0x01);
    LcdWriteReg(0xe0);  //LOCK PLL
    LcdWriteData(0x03);
    
    LcdWriteReg(0xb0);	//SET LCD MODE  SET TFT 18Bits MODE
    LcdWriteData(0x08);	//SET TFT MODE & hsync+Vsync+DEN MODE
    LcdWriteData(0x80);	//SET TFT MODE & hsync+Vsync+DEN MODE
    LcdWriteData(0x01);	//SET horizontal size=480-1 HightByte
    LcdWriteData(0xdf); //SET horizontal size=480-1 LowByte
    LcdWriteData(0x01);	//SET vertical size=272-1 HightByte
    LcdWriteData(0x0f);	//SET vertical size=272-1 LowByte
    LcdWriteData(0x00);	//SET even/odd line RGB seq.=RGB
    
    LcdWriteReg(0xf0); //SET pixel data I/F format=8bit
    LcdWriteData(0x00);
    LcdWriteReg(0x3a);  // SET R G B format = 6 6 6
    LcdWriteData(0x60);
    
    LcdWriteReg(0xe2);  //SET PLL freq=113.33MHz ;
    LcdWriteData(0x22);
    LcdWriteData(0x03);
    LcdWriteData(0x04);
    
    LcdWriteReg(0xe6);  //SET PCLK freq=9MHz  ; pixel clock frequency
    LcdWriteData(0x01);
    LcdWriteData(0x45);
    LcdWriteData(0x47);	//
    
    LcdWriteReg(0xb4);	//SET HBP, 
    LcdWriteData(0x02);	//SET HSYNC Tatol 525
    LcdWriteData(0x0d);
    LcdWriteData(0x00);	//SET HBP 43
    LcdWriteData(0x2b);
    LcdWriteData(0x28);	//SET VBP 41=40+1
    LcdWriteData(0x00);	//SET Hsync pulse start position
    LcdWriteData(0x00);
    LcdWriteData(0x00);	//SET Hsync pulse subpixel start position
    
    LcdWriteReg(0xb6); 	//SET VBP, 
    LcdWriteData(0x01);	//SET Vsync total 286=285+1
    LcdWriteData(0x1d);
    LcdWriteData(0x00);	//SET VBP=12
    LcdWriteData(0x0c);
    LcdWriteData(0x09);	//SET Vsync pulse 10=9+1
    LcdWriteData(0x00);	//SET Vsync pulse start position
    LcdWriteData(0x00);
    
    LcdWriteReg(0x2a);	//SET column address
    LcdWriteData(0x00);	//SET start column address=0
    LcdWriteData(0x00);
    LcdWriteData(0x01);	//SET end column address=479
    LcdWriteData(0xdf);
    
    LcdWriteReg(0x2b);	//SET page address
    LcdWriteData(0x00);	//SET start page address=0
    LcdWriteData(0x00);
    LcdWriteData(0x01);	//SET end page address=271
    LcdWriteData(0x0f);
    
    LcdWriteReg(0x29);		//SET display on
    LcdWriteReg(0x2c);
    return 0;
  }
  case LCD_X_SETVRAMADDR: {
       //
       // Required for setting the address of the video RAM for drivers
       // with memory mapped video RAM which is passed in the 'pVRAM' element of p
       //
       //LCD_X_SETVRAMADDR_INFO * p;
       //p = (LCD_X_SETVRAMADDR_INFO *)pData;
       //...
       return 0;
     }
  case LCD_X_SETORG: {
      //
      // Required for setting the display origin which is passed in the 'xPos' and 'yPos' element of p
      //
      //LCD_X_SETORG_INFO * p;
      //p = (LCD_X_SETORG_INFO *)pData;
      //...
      return 0;
  }
  case LCD_X_SHOWBUFFER: {
      //
      // Required if multiple buffers are used. The 'Index' element of p contains the buffer index.
      //
      //LCD_X_SHOWBUFFER_INFO * p;
      //p = (LCD_X_SHOWBUFFER_INFO *)pData;
      //...
      return 0;
  }
  case LCD_X_SETLUTENTRY: {
      //
      // Required for setting a lookup table entry which is passed in the 'Pos' and 'Color' element of p
      //
      //LCD_X_SETLUTENTRY_INFO * p;
      //p = (LCD_X_SETLUTENTRY_INFO *)pData;
      //...
      return 0;
  }
  case LCD_X_ON: {
      //
      // Required if the display controller should support switching on and off
      //
      LcdWriteReg(0x29);		//SET display on
      return 0;
  }
  case LCD_X_OFF: {
      //
      // Required if the display controller should support switching on and off
      //
      LcdWriteReg(0x28);		//SET display off
      return 0;
  }
  default:
    r = -1;
  }
  return r;
}

/*************************** End of file ****************************/

