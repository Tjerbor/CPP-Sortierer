#ifndef BARGRAF_H
#define BARGRAF_H
#include "EmbSysLib.h"

class Bargraf
{
    private:
        const char barChar;
        static int amount;
    public:
        Bargraf(char c);
        virtual ~Bargraf();
        void draw(int length);
        int getAmount()
        {
            return amount;
        };
        char getBarChar()
        {
            return barChar;
        }
};

#endif // BARGRAF_H
