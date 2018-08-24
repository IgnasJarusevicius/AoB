#ifndef STATS_H
#define STATS_H

class Stats
{
public: 
    static int score;
    static int multi;
    static int level; 
    static int unlocked;
    static int stats[2];
    static int xp[2];
    static int xp2[2];
    static void Init();
    static void Damage(int dmg, bool rng);
    static void Die();
    static void EndTurn();
    static void Add (int i,int val);
    static void Draw(float,float); 
    static void Unlock();        
};
#endif
