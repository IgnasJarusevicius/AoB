#pragma once
#include "glad/glad.h"
#include <glm/glm.hpp>
#include <forward_list>

class GraphicObject
{
public:
    static void RenderAll();
    void Enable(bool en = true);
    void SetColor(glm::vec3 color);
    void SetColor(glm::vec4 color);   
    virtual void SetPosition(float xx, float yy, float zz = 0.0f);
    void SetRotation(float rot);
    void SetScale(float ratio);
    void SetScale(float xratio, float yratio);
protected:
    glm::mat4 transform;
    GraphicObject();
    GraphicObject(const GraphicObject&) = delete;
    GraphicObject(GraphicObject&& obj);
    virtual ~GraphicObject();
    virtual void Render() const = 0;   
    bool enabled;
    GLuint vbo; //vertex buffer object
    GLuint vao; //vertex array object
private:
    void UpdateTransform(); 
    float rotation; 
    float x;
    float y;
    float z;
    float scalex;
    float scaley;
    glm::vec4 color;  
    static glm::mat4 global_projection; 
    static std::forward_list<GraphicObject*> objList;
};
