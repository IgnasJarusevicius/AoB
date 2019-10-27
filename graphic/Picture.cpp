#include "Picture.h"
#include "graphic/gres.h"
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

Picture::Picture(float xx, float yy, float zz, float w, float h, Tile t) :
    width(w),
    height(h),
    tile(t),
    fixed_size(true)
{
    Vertex vertices[] = {
        Vertex(width, height, tile.u1, tile.v0),
        Vertex(width, 0.0f, tile.u1, tile.v1),
        Vertex(0.0f, height, tile.u0, tile.v0),
        Vertex(0.0f, 0.0f, tile.u0, tile.v1)};

    SetPosition(xx, yy, zz);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);         // position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));         // texture coord attribute
    glEnableVertexAttribArray(1);
}

Picture::Picture(float xx, float yy, float zz, Tile t) :
    width(t.width),
    height(t.height),
    tile(t),
    fixed_size(false)
{
    Vertex vertices[] = {
        Vertex(width, height, tile.u1, tile.v0),
        Vertex(width, 0.0f, tile.u1, tile.v1),
        Vertex(0.0f, height, tile.u0, tile.v0),
        Vertex(0.0f, 0.0f, tile.u0, tile.v1)};

    SetPosition(xx, yy, zz);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);         // position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));         // texture coord attribute
    glEnableVertexAttribArray(1);
}

void Picture::SetTile(Tile t)
{
    tile = t;
    int w = fixed_size ? width : t.width;
    int h = fixed_size ? height : t.height;
    Vertex vertices[] = {
        Vertex(w, h, tile.u1, tile.v0),
        Vertex(w, 0.0f, tile.u1, tile.v1),
        Vertex(0.0f, h, tile.u0, tile.v0),
        Vertex(0.0f, 0.0f, tile.u0, tile.v1)};
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void Picture::Render() const
{
    glBindTexture(GL_TEXTURE_2D, tile.tex);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}




