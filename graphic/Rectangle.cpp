#include "Rectangle.h"
#include <glm/gtc/matrix_transform.hpp>

struct Point3D
{
    Point3D(float xx, float yy, float zz = 0.0f):x(xx),y(yy),z(zz),u(0.0f),v(0.0f){};
    float x;
    float y;
    float z;
    float u;
    float v;
};

unsigned int Rectangle::texture = 0;

Rectangle::Rectangle(float xx, float yy, float width, float height, float zz)
{
    LoadResources();
    Point3D vertices[] = {
        Point3D(width,height,zz),
        Point3D(width,0.0f,zz),
        Point3D(0.0f,0.0f,zz),
        Point3D(0.0f,height,zz),
        Point3D(width,height,zz),
        Point3D(0.0f,0.0f,zz)};

    SetPosition(xx, yy);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Point3D), (void*)0);         // position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Point3D), (void*)(3 * sizeof(float)));         // texture coord attribute
    glEnableVertexAttribArray(1);
}

void Rectangle::LoadResources()
{
    if (texture)
        return;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    uint32_t data = 0xFFFFFFFF;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &data);
}

void Rectangle::Render() const
{
    glBindTexture(GL_TEXTURE_2D, texture);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

RectangleOutline::RectangleOutline(float x, float y, float w, float h, float z):
    Rectangle(x,  y, w, h, z)
{

}

void RectangleOutline::Render() const
{
    glBindTexture(GL_TEXTURE_2D, texture);
    glDrawArrays(GL_LINE_STRIP, 0, 5);
}




