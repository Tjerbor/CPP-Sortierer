//*******************************************************************
#include "EmbSysLib.h"
#include "Module/Rtos/Rtos.h"
#include "ReportHandler.h"
#include "config.h"
#include ".\Bargraf.h"
#include <stdio.h>
#include<chrono>
#include<thread>

//*******************************************************************
class myTimerTask : public TaskManager::Task
{
public:
	//---------------------------------------------------------------
	myTimerTask( TaskManager &taskManager )
	{
		cnt = 0;
		taskManager.add( this );
	}

	//---------------------------------------------------------------
	virtual void update( void )
	{
		cnt++;
	}
	void delay(uint32_t millis)
	{
		uint32_t cntinitial = cnt;
		uint32_t diff = (uint32_t) millis / 10;
		while(cnt-cntinitial < diff){
		}
	}
	//---------------------------------------------------------------
	DWORD cnt;
};

//*******************************************************************
class myRtosTask : public Rtos::Task
{
public:
	//---------------------------------------------------------------
	myRtosTask( Rtos &rtos )
	: Rtos::Task( rtos, 500/* stack size*/ )
	{
		cnt = 0;
	}

private:
	//---------------------------------------------------------------
	virtual void update( void )
	{
		while(1)
		{
			cnt++;
			pause();  // pause the task until next time slot
		}
	}

public:
	//---------------------------------------------------------------
	DWORD cnt;

}; //class myTask

//*******************************************************************
Rtos    rtos (    2,   // max num of tasks
		1000 ); // time slice in us

//*******************************************************************
int main(void)
{
	disp.printf(0,0,__DATE__ " " __TIME__);
	terminal.printf( __DATE__ " " __TIME__ "\r\n" );

	int  num = 0;

	myTimerTask timerTask( taskManager );

	myRtosTask  rtosTask ( rtos );

	rtosTask.start();
	Bargraf b('-');
	//Signal_Farbe.enable();

	while(1)
	{
		/*
    if( char *str = terminal.getString() )
    {
      terminal.printf( "\r\n=>%s\r\n", str );
    }
		 */

		switch( enc.getEvent() )
		{
		case DigitalEncoder::LEFT:     num -= 1; break;
		case DigitalEncoder::RIGHT:    num += 1; break;
		case DigitalEncoder::CTRL_DWN: num  = 0; break;
		default:                                 break;
		}

		if( btnA.getEvent() == Digital::ACTIVATED )
		{
			led0.toggle();
			//Motor_Band.toggle();
			/*Ventil_Stapel.toggle();
        Ventil_Ausw.toggle();
        Ventil_Verarb.toggle();
        Motor_Pumpe.toggle();
			 */
			/*Motor_Pumpe.set(1);
			timerTask.delay(500);
			Ventil_Stapel.set(1);
			timerTask.delay(250);
			Motor_Pumpe.set(0);
			Ventil_Stapel.set(0);

			Motor_Pumpe.set(1);
			Motor_Band.set(1);
			timerTask.delay(2000);
			Ventil_Ausw.set(1);
			timerTask.delay(1000);
			Motor_Band.set(0);
			Ventil_Ausw.set(0);
			Motor_Pumpe.set(0);
			 */
			Motor_Band.toggle();
			Motor_Pumpe.toggle();
		}
		if(PC0.getEvent() == Digital::ACTIVATED)
		{
			Motor_Pumpe.set(1);
			timerTask.delay(10000);
			Motor_Pumpe.set(0);
		}
		if(PC1.getEvent() == Digital::ACTIVATED)
		{
			Ventil_Verarb.set(1);
			timerTask.delay(350);
			Ventil_Verarb.set(0);
		}
		if(PC6.getEvent() == Digital::ACTIVATED)
		{
			Ventil_Ausw.set(1);
			timerTask.delay(350);
			Ventil_Ausw.set(0);
		}
		if(PC7.getEvent() == Digital::ACTIVATED)
		{
			Ventil_Stapel.set(1);
			timerTask.delay(350);
			Ventil_Stapel.set(0);
		}

		//System::delayMilliSec(1000);

		//b.draw(num);
		disp.printf( 1, 0, "clr:%-5d", Signal_Farbe.getRaw() );
		disp.printf( 1, 10, "drk:%-5d", Signal_Druck.getRaw() );
		disp.printf( 2, 0, "light:%-5d ", Light_Stapel.get() );
		disp.printf( 2, 10, "band:%-5d ", Inkremental_Band.get() );
		disp.printf( 3, 0, "timer:%-5d ", timerTask.cnt );
		disp.refresh();
		//disp.printf(1,0,"Bargrafs:%-5d",b.getAmount());
		//disp.refresh();
		/*
    disp.printf( 1, 0, "timer:%-5d ", timerTask.cnt );
    disp.printf( 2, 0, "rtos: %-5d ", rtosTask.cnt  );
    disp.printf( 3, 0, "num:  %-5d ", num           );
    disp.refresh();
		 */
	}
}
//EOF
