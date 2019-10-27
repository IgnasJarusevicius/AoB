#ifndef RANGED_H
#define RANGED_H
#include "character.h"
//------------------------------------------------------------------------------

class UnitStats;

class Ranged : public Character {
public:
    Ranged(const UnitResources &stats, int p);
    ~Ranged() = default;
    Grid::GridData<int>* Select() override;
    bool Attack(Character* obj) override;
    bool IsMoving() const override;
private:
    int CollisionLine(std::complex<float> pos1, std::complex<float> pos2) const;
    
    class Arrow : public GameObject
    {
    public:
        Arrow(Ranged* owner);
        void Step(float dt) override;
    private:
        Ranged* shooter;
        std::complex<float> position;
        Picture image;
        Character* const target;
        const std::complex<float> destination;
        const std::complex<float> direction;
        ~Arrow() = default;

    };  
    Arrow* arrow;
    void ExecuteAttack() override;
};
//------------------------------------------------------------------------------
#endif
