//*******************************************************************
/*!
\file   config.h
\author Thomas Breuer
\date   23.09.2022
\brief  Board specific configuration
*/

//*******************************************************************
/*
Board:    Virtual
*/

//*******************************************************************
using namespace EmbSysLib::Hw;
using namespace EmbSysLib::Dev;
using namespace EmbSysLib::Ctrl;
using namespace EmbSysLib::Mod;

//-------------------------------------------------------------------
// Timer
//-------------------------------------------------------------------
Timer_Mcu   timer( 1000L/*us*/ );
TaskManager taskManager( timer );

//-------------------------------------------------------------------
// Port + Digital
//-------------------------------------------------------------------
Port_Virtual  port( "localhost:1000" );

Digital  led0    ( port,16, Digital::Out, 0 ); // LED 0
Digital  btnA    ( port, 5, Digital::In,  0 ); // button "A"
Digital  btnLeft ( port, 0, Digital::In,  0 ); // Button "<<"
Digital  btnCtrl ( port, 1, Digital::In,  0 ); // Button "o"
Digital  btnRight( port, 2, Digital::In,  0 ); // Button ">>"

DigitalEncoderJoystick    enc( &btnLeft, &btnRight, &btnCtrl, taskManager, 150 );

//-------------------------------------------------------------------
// UART
//-------------------------------------------------------------------
Uart_Stdio uart( true );
Terminal   terminal( uart, 255,255,"#", "!\r\n" );

//-------------------------------------------------------------------
// Display
//-------------------------------------------------------------------
DisplayChar_Virtual  dispHw( 10, 40, "localhost:1000" );
ScreenChar           disp( dispHw );
