
#ifndef ABILITIES_H
#define ABILITIES_H

class SpecialAbilities
{
private:
    int changeDefense;
    int changeOffense;
    int changeRangeStart;
    int changeRangeEnds;
    int changeNumAttacks;
    int currNumofTurns;
    int maxNumofTurns;
    int currCoolDownTurns;
    int maxCoolDownTurns;
    bool activated;
    int changeInSpeed;
    bool statsReset;

public:

    SpecialAbilities(int changeDefense, int changeOffense, int changeRangeStart,
                     int changeRangeEnds, int changeNumAttacks,int changeInSpeed, int maxNumofTurns, int maxCoolDownTurns);
    ~SpecialAbilities();


    int getChangeInDefence();
    int getChangeInOffense();
    int getChangeInRangeStarts();
    int getChangeInRangeEnds();
    int getChangeInNumAttacks();
    bool checkDefenseType();
    bool checkOffenseType();
    void activateAbility();
    void resetAbility();

    void coolDown();

    void reset();
    bool isActivated();
    int getChangeInSpeed();
    void resetStats();
    void startCoolDown();

    int coolDownTurns();
    int effectTurns();
    bool isStatsReset();

};

#endif
