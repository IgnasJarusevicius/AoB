#pragma once
#include <map>
#include <vector>
#include <glm/glm.hpp>
#include "GraphicObject.h"

struct Character;

struct Vertex
{
    Vertex(float xx, float yy, float uu, float vv):x(xx),y(yy),z(0.0f),u(uu),v(vv){};
    float x;
    float y;
    float z;
    float u;
    float v;
};

class TextObj : public GraphicObject
{
public: 
    TextObj(float xx, float yy, std::string text);
    TextObj(const TextObj&) = delete;
    TextObj(TextObj&& obj);
    ~TextObj();   
    void SetText(std::string text);
    void AddText(std::string text, float x_offset, float y_offset);
private:
    void Render() const override;
    static void LoadResources();
    void AddSymbol(char symbol, float initial_x);  
    float offset_x;
    float offset_y;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    unsigned int ebo; //element buffer object
    
    static std::map<char, const Character*> charMap;  
    static int width;
    static int height;
    static unsigned int texture;
};
