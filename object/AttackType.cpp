#include "AttackTypes.h"
#include <functional>

struct EffectInfo
{
    float life;
    std::string name;
    std::function<void(UnitStats& s)> apply;
};

namespace
{

inline void CrippleEffectApply(UnitStats& s)
{
    s.dmg_base = 0.8f*s.dmg_base;
    s.dmg_rand = 0.8f*s.dmg_rand;
    s.ap_regen = 0.8f*s.ap_regen;
}

EffectInfo CrippleEffect = {3.0f, "Crippled", CrippleEffectApply};

}


StatsEffect::StatsEffect(const EffectInfo& effect) :
    info(effect),
    life(effect.life)
{
}

bool StatsEffect::UpdateLife(float dt)
{
    life -= dt;
    return life <= 0.0f ? false : true;
}

void StatsEffect::ResetLife()
{
    life = info.life;
}

const std::string& StatsEffect::Name() const
{
    return info.name;
}

bool StatsEffect::operator==(const StatsEffect& other)
{
    return (&info == &other.info);
}

bool StatsEffect::operator!=(const StatsEffect& other)
{
    return (&info != &other.info);
}

void StatsEffect::Apply(UnitStats& s) const
{
    info.apply(s);
}

AttackDamage::~AttackDamage()
{
    if (effect)
        delete effect;
}

AttackType::AttackType(std::string n, const UnitStats& s, int ap) :
    stats(s),
    name(n),
    ap_cost(ap)
{
}

int AttackType::GetAp() const
{
    return ap_cost;
}

const std::string& AttackType::Name() const
{
    return name;
}


NormalAttack::NormalAttack(const UnitStats& s) :
    AttackType("Normal Attack", s, s.ap/2+1)
{
}

AttackDamage NormalAttack::GetDamage() const
{
    return {stats.dmg_base, stats.dmg_rand, stats.dmg_type};
}

PreciseShot::PreciseShot(const UnitStats& s) :
    AttackType("Precise shot", s, (2*s.ap+5)/3)
{
}

AttackDamage PreciseShot::GetDamage() const
{
    return  {
        1.35f*stats.dmg_base+0.3f*stats.dmg_rand,
        0.65f*stats.dmg_rand,
        stats.dmg_type,
        nullptr
    };
}


CripplingShot::CripplingShot(const UnitStats& s) :
    AttackType("Crippling shot", s, s.ap/2+3)
{
}

AttackDamage CripplingShot::GetDamage() const
{
    return {
        0.7f*stats.dmg_base,
        0.7f*stats.dmg_rand,
        stats.dmg_type,
        new StatsEffect(CrippleEffect)};
}


