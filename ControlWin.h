#ifndef CONTROLWIN_H
#define CONTROLWIN_H

#include "ControlPoint.h"
#include "Player.h"

class ControlWin{

    private:
        ControlWin* cp[3];
        Player * player;
        int count;
        int point;

    public:
        ControlWin(Player* player);
        ~ControlWin();
        void update();
        void reset();
        bool hasWon();
        
};

#endif // CONTROLWIN_H
