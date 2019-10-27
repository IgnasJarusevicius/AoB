#pragma once
#include "GraphicObject.h"
#include "graphic/gres.h"
#include <glm/glm.hpp>

class Picture : public GraphicObject
{
public: 
    Picture(float xx, float yy, float zz, Tile t);
    Picture(float xx, float yy, float zz, float w, float h, Tile t);
    void SetTile(Tile tile);
protected:
    void Render() const override;
    int width;
    int height;
private:  
    Tile tile;
    const bool fixed_size;
};
