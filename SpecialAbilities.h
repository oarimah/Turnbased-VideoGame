#include "Unit.h"
#include <string.h>


class SpecialAbilities
{
private:
    std::string changeDefense;
    std::string changeOffense;
    int changeRangeStart;
    int changeRangeEnds;
    int changeNumAttacks;
    int currNumofTurns;
    int maxNumofTurns;
    int currCoolDownTurns;
    int maxCoolDownTurns;
    bool activated;
public:
    SpecialAbilities(std::string changeDefense, std::string changeOffense, int changeRangeStart, int changeRangeEnds, int changeNumAttacks,int maxNumofTurns, int maxCoolDownTurns);
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
    void coolDown(int n);
    void reset();
};
