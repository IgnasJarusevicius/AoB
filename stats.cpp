#include "stats.h"

int Stats::score;
int Stats::multi;
int Stats::level;
int Stats::unlocked;
int Stats::stats[2];
int Stats::xp[2];
int Stats::xp2[2];

void Stats::Init()
{
    score = 0;
    multi = 3;
    level = 1;
    unlocked = 0x0007;
    stats[0] = 1;
    xp[0] = 0;
    xp2[0] = 250;
    stats[1] = 1;
    xp[1] = 0;
    xp2[1] = 250;

}

void Stats::Damage(int dmg, bool rng)
{
    score += multi*dmg;
    if (rng)
        Add(1, dmg);
    else
        Add(0, dmg);
}

void Stats::EndTurn()
{
    multi -= multi > 1 ? 1 : 0;
}

void Stats::Die()
{
    multi += multi < 10 ? 1 : 0;
}

void Stats::Add(int i, int val)
{
    if (stats[i] == 5)
        return;

    xp[i] += val;
    if (xp[i] >= xp2[i])
    {
        if (stats[i] != 4)
        {
            xp[i] -= xp2[i];
            xp2[i] = 200 * stats[i] * stats[i];
        }
        else
            xp[i] = xp2[i];
        stats[i] += 1;
        Unlock();
    }
}

void Stats::Unlock()
{
    if (stats[0] >= 3)
        unlocked |= 0x0008;
    if (stats[0] >= 2 && stats[1] >= 2)
        unlocked |= 0x0010;
    if (stats[1] >= 3)
        unlocked |= 0x0020;
    if (stats[0] >= 4)
        unlocked |= 0x0040;
    if (stats[0] >= 3 && stats[1] >= 2)
        unlocked |= 0x0080;
    if (stats[1] >= 4)
        unlocked |= 0x0100;
    if (stats[0] >= 5)
        unlocked |= 0x0200;
    if (stats[0] == 4 && stats[1] >= 3)
        unlocked |= 0x0400;
}






