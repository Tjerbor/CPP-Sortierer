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
        motor.toggle();
        num = 20;
    }

    b.draw(num);
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
