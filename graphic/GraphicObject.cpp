#include "GraphicObject.h"
#include "Shader.h"
#include <glm/gtc/matrix_transform.hpp>

static const char *vertexShaderSource =
"#version 330 core\n\
layout (location = 0) in vec3 aPos;\n\
layout (location = 1) in vec2 aTexCoord;\n\
uniform mat4 gWVP;\n\
out vec2 TexCoord;\n\
void main(){\n\
	gl_Position = gWVP * vec4(aPos, 1.0);\n\
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);\n\
    }\0";

static const char *fragmentShaderSource =
"#version 330 core\n\
out vec4 FragColor;\n\
in vec2 TexCoord;\n\
uniform sampler2D texture1;\n\
uniform vec4 color = vec4(1.0, 1.0, 1.0, 1.0);\n\
void main(){\
vec4 tmpColor = texture(texture1, TexCoord);\n\
if(tmpColor.a < 0.1)\n\
    discard;\n\
FragColor = vec4(tmpColor[0]*color[0], tmpColor[1]*color[1], tmpColor[2]*color[2], tmpColor[3]*color[3]);}\0";

std::forward_list<GraphicObject*> GraphicObject::objList;

glm::mat4 GraphicObject::global_projection = glm::ortho(0.0f, 1024.0f, 0.0f, 768.0f, 0.0f, 1024.0f);

GraphicObject::GraphicObject() : enabled(true)
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    color = glm::vec4(1.0f);
    transform = glm::mat4(1.0f);
    objList.push_front(this);
    rotation = 0.0f;
    scalex = scaley = 1.0f;
}

GraphicObject::~GraphicObject()
{
    objList.remove(this);
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}

void GraphicObject::UpdateTransform()
{
    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(x, y, z));
    model = glm::scale(model, glm::vec3(scalex, scaley, 1.0f));
    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = global_projection*model;
}

void GraphicObject::SetColor(glm::vec3 col)
{
    color = glm::vec4(col[0],col[1], col[2], 1.0f);
}

void GraphicObject::SetColor(glm::vec4 col)
{
    color = col;
}

void GraphicObject::Enable(bool en)
{
    enabled = en;
}

void GraphicObject::SetRotation(float rot)
{
    rotation = rot;
    UpdateTransform();
}

void GraphicObject::SetScale(float ratio)
{
    scalex = scaley = ratio;
    UpdateTransform();
}

void GraphicObject::SetScale(float xratio, float yratio)
{
    scalex = xratio;
    scaley = yratio;
    UpdateTransform();
}

void GraphicObject::SetPosition(float xx, float yy, float zz)
{
    x = xx;
    y = yy;
    z = zz;
    UpdateTransform();
}

void GraphicObject::RenderAll()
{
    static Shader shader(vertexShaderSource, fragmentShaderSource);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader.use();
    for (const auto &obj: objList)
        if (obj->enabled)
        {
            glBindVertexArray(obj->vao);
            shader.setVec4("color", obj->color);
            shader.setMat4("gWVP", obj->transform);
            obj->Render();
        }
}

