#ifndef DAMAGE_H
#define DAMAGE_H
#include "bobject.h"
#include "TextObj.h"

class TextReport : public GameObject
{
protected:
    TextReport(float, float, std::string, float life, float speed); 
    ~TextReport() = default;
    void Step(float dt) override;  
    void Enable(bool en) override {};
    TextObj text;
private:
    float life;  
    float speed;
    float x;
    float y;
}; 

class Damage_Report: public TextReport
{
public:
    Damage_Report(float, float, std::string); 
}; 

class AP_Report: public TextReport
{
public:
    AP_Report(float, float, std::string); 
}; 

class Effect_Report: public TextReport
{
public:
    Effect_Report(float, float, std::string); 
}; 

#endif
