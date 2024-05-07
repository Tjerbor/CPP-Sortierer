#include "stdio.h"
#include <iostream>
#include <string>
#include <sstream>
#include "EmbSysLib.h"
#include ".\Bargraf.h"

using namespace EmbSysLib::Dev;
extern ScreenChar disp;

int Bargraf::amount = 0;

Bargraf::Bargraf(char c)
:barChar(c)
{
    amount++;
    disp.printf(0,0,"");
    disp.refresh();
}
Bargraf::~Bargraf()
{
    amount--;
    disp.printf(0,0,"");
    disp.refresh();
}

void Bargraf::draw(int length)
{
    std::string res = "";
    for(int i = 0; i < std::abs(length) && i < 20; i++)
    {
        res += barChar;
    }

    if(length < 0)
    {
        disp.printf(0,0,"%20s", res.c_str());
    }
    else
    {
        disp.printf(0,0,"%-20s", res.c_str());
    }
    disp.refresh();
    //std::printf("%s", res.c_str());

}


