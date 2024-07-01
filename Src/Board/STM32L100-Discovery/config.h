//*******************************************************************
/*!
\file   config.h
\author Thomas Breuer
\date   23.03.2023
\brief  Board specific configuration
 */

//*******************************************************************
/*
Board:    STM32L100-Discovery
 */

//*******************************************************************
#include "Hardware/Peripheral/Display/DisplayChar_DIP204spi.cpp"

//*******************************************************************
using namespace EmbSysLib::Hw;
using namespace EmbSysLib::Dev;
using namespace EmbSysLib::Ctrl;
using namespace EmbSysLib::Mod;

//*******************************************************************
PinConfig::MAP PinConfig::table[] =
{
		//ADC
		ADC12_IN3_PA3,
		ADC12_IN2_PA2,

		// SPI
		SPI2_MOSI_PB15,
		SPI2_MISO_PB14,
		SPI2_SCK_PB13,
		SPI2_NSS_PB12,

		// UART
		USART1_TX_PA9,
		USART1_RX_PA10,

		END_OF_TABLE
};

//-------------------------------------------------------------------
// Timer
//-------------------------------------------------------------------
Timer_Mcu   timer( Timer_Mcu::TIM_10, 10000L/*us*/ );
TaskManager taskManager( timer );

//-------------------------------------------------------------------
// Port + Digital
//-------------------------------------------------------------------
Port_Mcu   portA( Port_Mcu::PA );
Port_Mcu   portB( Port_Mcu::PB );
Port_Mcu   portC( Port_Mcu::PC );
Port_Mcu   portD( Port_Mcu::PD );


//Sortierer Sensoren + Aktoren
Digital led0(portC, 8, Digital::Out, 0); // LD4 (blue)
Digital btnA(portA, 0, Digital::In, 0); // B1 (user button)
Digital PC0(portC, 0, Digital::InPU, 1);
Digital PC1(portC, 1, Digital::InPU, 1);
Digital PC6(portC, 6, Digital::InPU, 1);
Digital PC7(portC, 7, Digital::InPU, 1);
Digital rotA(portA, 8, Digital::InPU, 1);
Digital rotB(portA, 1, Digital::InPU, 1);
Digital rotCtrl(portA, 15, Digital::InPU, 1);
Digital Motor_Band(portB, 4, Digital::Out, 0);
Digital Ventil_Stapel(portB, 0, Digital::Out, 0);
Digital Ventil_Ausw(portB, 1, Digital::Out, 0);
Digital Ventil_Verarb(portB, 6, Digital::Out, 0);
Digital Motor_Pumpe(portB, 8, Digital::Out, 0);
Digital Light_Stapel(portA, 6, Digital::InPU, 0);
Digital Light_Verarb(portA, 7, Digital::InPU, 0);
Digital Inkremental_Band(portC, 2, Digital::InPU, 0);

//Sortier Sensor
Adc_Mcu adc(timer);
AnalogInAdc Signal_Farbe(adc, 3);
AnalogInAdc Signal_Druck(adc, 2);

DigitalEncoderRotaryknob  enc( &rotA, &rotB, &rotCtrl, taskManager );

//-------------------------------------------------------------------
// UART
//-------------------------------------------------------------------
Uart_Mcu  uart    ( Uart_Mcu::USART_1, 9600, 100, 100 );
Terminal  terminal( uart, 255,255,"#", "!\r\n" );

//-------------------------------------------------------------------
// Display
//-------------------------------------------------------------------
SPImaster_Mcu         spi          ( SPImaster_Mcu::SPI_2, SPImaster_Mcu::CR_1000kHz, SPImaster_Mcu::CPOL_H_CPHA_H );
SPImaster::Device     spiDevDisplay( spi, portB, 12 );
DisplayChar_DIP204spi dispHw       ( spiDevDisplay );
ScreenChar            disp         ( dispHw );

//-------------------------------------------------------------------
// InduRobot
//-------------------------------------------------------------------
Digital  enable( portD, 2, Digital::Out, 1 );

Digital  motor_1_minus( portB, 4, Digital::Out,  0 );
Digital  motor_1_plus ( portB, 5, Digital::Out,  0 );

Digital  endschalter_1( portA, 2, Digital::InPU, 0 );
Digital  increment_1  ( portA, 3, Digital::InPU, 0 );
