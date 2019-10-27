#pragma once
#include <glm/glm.hpp>
#include "GraphicObject.h"

class Shader;

class Rectangle : public GraphicObject
{
public: 
    Rectangle(float xx, float yy, float width, float height, float zz = 0.0f);
protected:   
    static void LoadResources();
    virtual void Render() override;
    static unsigned int texture;
};

class RectangleOutline : public Rectangle
{
public:
    RectangleOutline(float x, float y, float w, float h, float z = 0.0f);
protected:
    void Render() override;
};
