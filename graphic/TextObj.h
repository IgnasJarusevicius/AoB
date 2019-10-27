#pragma once
#include <map>
#include <vector>
#include <glm/glm.hpp>
#include "GraphicObject.h"

struct Character;
struct Vertex;

class TextObj : public GraphicObject
{
public: 
    TextObj(float xx, float yy, std::string text);
    ~TextObj();   
    void SetText(std::string text);
    void AddText(std::string text, float x_offset, float y_offset);
private:
    void Render() override;
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
