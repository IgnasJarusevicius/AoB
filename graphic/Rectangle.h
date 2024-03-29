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
    virtual void Render() const override;
    static unsigned int texture;
};

class RectangleOutline : public Rectangle
{
public:
    RectangleOutline(float x, float y, float w, float h, float z = 0.0f);
    RectangleOutline(const RectangleOutline&) = delete;
    RectangleOutline(RectangleOutline&&) = default;
protected:
    void Render() const override;
};
