#include "Picture.h"
#include <glm/gtc/matrix_transform.hpp>

struct Vertex
{
    Vertex(float xx, float yy, float uu, float vv):x(xx),y(yy),z(0.0f),u(uu),v(vv){};
    float x;
    float y;
    float z;
    float u;
    float v;
};

Picture::Picture(float xx, float yy, float zz, unsigned tex, float coordx0, float coordx1, float coordy0, float coordy1)
{
    texture = tex;
    glBindTexture(GL_TEXTURE_2D, texture);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
    width *= coordx1-coordx0;
    height *= coordy1 -coordy0;
    Vertex vertices[] = {
        Vertex(width,height,coordx1,coordy0),
        Vertex(width,0.0f,coordx1,coordy1),
        Vertex(0.0f,height,coordx0,coordy0),
        Vertex(0.0f,0.0f,coordx0,coordy1)};

    SetPosition(xx, yy, zz);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);         // position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));         // texture coord attribute
    glEnableVertexAttribArray(1);
}


void Picture::SetPosition(float xx, float yy, float zz)
{
    GraphicObject::SetPosition(xx-width/2, yy-height/2, zz);
}

void Picture::SetTexture(unsigned int tex)
{
    texture = tex;
}

void Picture::Render()
{
    glBindTexture(GL_TEXTURE_2D, texture);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}




