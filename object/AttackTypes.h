#pragma once
#include <string>
#include "data_types.h"

struct EffectInfo;

class StatsEffect
{
public:
    StatsEffect(const EffectInfo&);
    virtual ~StatsEffect() = default;
    bool UpdateLife(float dt);
    void ResetLife();
    void Apply(UnitStats& s) const;
    const std::string& Name() const;  
    bool operator==(const StatsEffect& other);
    bool operator!=(const StatsEffect& other);
private:
    float life;
    const EffectInfo& info;
};

struct AttackDamage
{
    AttackDamage(const AttackDamage&) = delete;
    ~AttackDamage();
    float base;
    float rand;
    DamageType type;   
    StatsEffect* effect;
};

class AttackType
{
public:
    AttackType(std::string n, const UnitStats& s, int ap);
    virtual ~AttackType() = default;
    virtual AttackDamage GetDamage() const = 0;
    virtual int GetAp() const;
    const std::string& Name() const;    
protected:
    const UnitStats& stats;
    const std::string name;
    const int ap_cost;
};

class NormalAttack : public AttackType
{
public:
    NormalAttack(const UnitStats& s);
    AttackDamage GetDamage() const override;
};

class PreciseShot : public AttackType
{
public:
    PreciseShot(const UnitStats& s);
    AttackDamage GetDamage() const override;
};

class CripplingShot : public AttackType
{
public:
    CripplingShot(const UnitStats& s);
    AttackDamage GetDamage() const override;
};