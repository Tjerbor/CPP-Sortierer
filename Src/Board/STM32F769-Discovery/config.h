//*******************************************************************
/*!
\file   config.h
\author Thomas Breuer
\date   23.02.2023
\brief  Board specific configuration
*/

//*******************************************************************
/*
Board:    STM32F769-Discovery
*/

//*******************************************************************
#include "Hardware/Peripheral/Display/DisplayGraphic_OTM8009A.cpp"

//*******************************************************************
using namespace EmbSysLib::Hw;
using namespace EmbSysLib::Dev;
using namespace EmbSysLib::Ctrl;
using namespace EmbSysLib::Mod;

//*******************************************************************
PinConfig::MAP PinConfig::table[] =
{
  // UART
  USART1_TX_PA9,
  USART1_RX_PA10,
  
  // FMC
  FMC_D0_PD14,  
  FMC_D1_PD15,  
  FMC_D2_PD0, 
  FMC_D3_PD1,
  FMC_D4_PE7,
  FMC_D5_PE8, 
  FMC_D6_PE9, 
  FMC_D7_PE10, 
  FMC_D8_PE11, 
  FMC_D9_PE12, 
  FMC_D10_PE13, 
  FMC_D11_PE14, 
  FMC_D12_PE15,
  FMC_D13_PD8,  
  FMC_D14_PD9,
  FMC_D15_PD10,  
  FMC_D16_PH8,
  FMC_D17_PH9,
  FMC_D18_PH10,
  FMC_D19_PH11,
  FMC_D20_PH12,
  FMC_D21_PH13,
  FMC_D22_PH14,
  FMC_D23_PH15,
  FMC_D24_PI0,
  FMC_D25_PI1,
  FMC_D26_PI2,
  FMC_D27_PI3,
  FMC_D28_PI6,
  FMC_D29_PI7,
  FMC_D30_PI9,
  FMC_D31_PI10,

  FMC_A0_PF0,
  FMC_A1_PF1,
  FMC_A2_PF2,
  FMC_A3_PF3,
  FMC_A4_PF4,
  FMC_A5_PF5,
  FMC_A6_PF12,
  FMC_A7_PF13,
  FMC_A8_PF14,
  FMC_A9_PF15,
  FMC_A10_PG0,
  FMC_A11_PG1,
  FMC_A12_PG2,
  FMC_A13_PG3,
  FMC_A14_PG4,
  FMC_A15_PG5,

  FMC_SDCLK_PG8,
  FMC_SDNCAS_PG15,
  FMC_SDCKE0_PH2,
  FMC_SDNE0_PH3,
  FMC_SDNWE_PH5,
  FMC_SDNRAS_PF11,
  FMC_NBL0_PE0,
  FMC_NBL1_PE1, 
  FMC_NBL2_PI4,
  FMC_NBL3_PI5,

  END_OF_TABLE
};

//-------------------------------------------------------------------
// Timer
//-------------------------------------------------------------------
Timer_Mcu   timer( Timer_Mcu::TIM_14, 10000L/*us*/ );
TaskManager taskManager( timer );

//-------------------------------------------------------------------
// Port + Digital
//-------------------------------------------------------------------
Port_Mcu   portA( Port_Mcu::PA );
Port_Mcu   portB( Port_Mcu::PB );
Port_Mcu   portD( Port_Mcu::PD );
Port_Mcu   portF( Port_Mcu::PF );
Port_Mcu   portJ( Port_Mcu::PJ );

Digital    led0    ( portJ,13, Digital::Out,  0 ); // LD1 (red)
Digital    btnA    ( portA, 0, Digital::In,   0 ); // B1 (user button)
Digital    btnLeft ( portF, 8, Digital::InPU, 1 );
Digital    btnCtrl ( portF, 9, Digital::InPU, 1 );
Digital    btnRight( portA, 6, Digital::InPU, 1 );

DigitalEncoderJoystick    enc( &btnLeft, &btnRight, &btnCtrl, taskManager, 150 );

//-------------------------------------------------------------------
// UART
//-------------------------------------------------------------------
Uart_Mcu  uart( Uart_Mcu::USART_1, 9600, 0, 100, 100 );
Terminal  terminal( uart, 255,255,"#", "!\r\n" );

//-------------------------------------------------------------------
// Display
//-------------------------------------------------------------------
Memory_Flash image         ( 10 ); // Size: 256k
Font         fontFont_16x24( MemoryImage( image, "Font_16x24" ).getPtr() );

Port::Pin     lcdResetPin( portJ, 15 );
Fmc_Mcu       fmc        ( Fmc_Mcu::SDRAM_Bank1 );  
Dsi_Mcu       hwDSI      ( fmc.startAddr() );
                        
DisplayGraphic_OTM8009Aram dispGraphicHw( hwDSI,lcdResetPin, DisplayGraphic_OTM8009A::LANDSCAPE_90, fontFont_16x24, 2 );
ScreenChar                 disp         ( dispGraphicHw );
