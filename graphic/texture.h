#ifndef TEXTURE_H
#define	TEXTURE_H

#include "glad/glad.h"

class Texture
{
public:
    Texture(const char* fname, bool alpha = true);
    void Bind(GLenum TextureUnit);
    operator GLuint() const;

private:
    GLuint m_textureObj;
};


#endif	/* TEXTURE_H */

