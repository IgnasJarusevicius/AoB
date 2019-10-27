#pragma once
#include <complex>
#include "bobject.h"
#include "audio.h"
#include "ProgressBar.h"
#include "data_types.h"
#include "AttackTypes.h"
//------------------------------------------------------------------------------


class Character: public Unit
{
public: 
    Character(const UnitResources &stats, int p);
    virtual ~Character();
    std::pair<int, int> Move(int grid_x, int grid_y);
    virtual Grid::GridData<int>* Select();
    void Step(float dt = 0.0f) override;  
    virtual bool Attack(Character* target);
    virtual bool IsMoving() const;
    UnitInfo GetUnitInfo() const;
    int Damage(AttackDamage&& dmg);
    void EndTurn(float step, bool active = false);
    float GetSize() const override;
    void Enable(bool en = false) override;
    const std::vector<AttackType*>& GetAttackTypes() const;
    void SelectAttack(int index);
protected:
    enum State
    {
        STAND = 0,
        MOVE,
        ATTACK,
        DIE,
        DEAD
    };
    const UnitStats& base_stats;
    UnitStats stats;
    void UpdateMoveRange();
    virtual void ExecuteAttack();
    int direction;
    const int sounds[3];
    Character* target;
    std::vector<std::complex<float> > path;
    int speed;
    State state;
    Sprite* (*spriteset)[8]; 
    Grid::GridData<int> moveZone;  
    AttackType* attack;
    std::vector<AttackType*> att_types;
private:  
    void ApplyEffects(float dt = 0.0f);
    std::vector<StatsEffect*> effects;
    void Animation_End();
    void SetDirection(std::complex<float> dest);     
    void Check(int grid_x, int grid_y, int ind);
    void GetPath(int grid_x, int grid_y);
    ProgressBar hp_bar;
    const float speed_x[8];
    const float speed_y[8];
    float z;
}; 

