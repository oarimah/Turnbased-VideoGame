#include "Unit.h"
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
    bool reset;
public:
    SpecialAbilities(int changeDefense, int changeOffense, int changeRangeStart,
            int changeRangeEnds, int changeNumAttacks,int changeInSpeed, int maxNumofTurns, int maxCoolDownTurns);
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
    bool isReset();
	int coolDownTurns();
	int effectTurns():
};

