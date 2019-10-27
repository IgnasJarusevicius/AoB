#pragma once
#include "GraphicObject.h"
#include <glm/glm.hpp>

class Picture : public GraphicObject
{
public: 
    Picture(float xx, float yy, float zz, unsigned tex, float coordx0 = 0.0f, float coordx1 = 1.0f, float coordy0 = 0.0f, float coordy1 = 1.0f);
    void SetPosition(float xx, float yy, float zz) override;
    void SetTexture(unsigned int tex);
protected:
    void Render() override;
    int width;
    int height;
private:    
    unsigned texture;
};
