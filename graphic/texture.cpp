#include <iostream>
#include <vector>
#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const char* fname, bool alpha)
{
    glGenTextures(1, &m_textureObj);

	int width, height, nrComponents;
    std::vector<uint32_t> data_rgba;
    const unsigned numChan = alpha ? 4 : 3;
	unsigned char *data = stbi_load(fname, &width, &height, &nrComponents, numChan);
	if (data)
	{
        const GLenum format = alpha ? GL_RGBA : GL_RGB;
        glBindTexture(GL_TEXTURE_2D, m_textureObj);

        if (alpha && nrComponents==3)
        {
            data_rgba.resize(width*height, 0);
            uint32_t* pIntData = ((uint32_t*)data);
            uint32_t back_color = *pIntData;
            for (unsigned i = 0; i < data_rgba.size(); pIntData++)
                data_rgba[i++] = *pIntData == back_color ? 0 : *pIntData;
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data_rgba.data());
        }
        else
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << fname << std::endl;
		stbi_image_free(data);
	}
}

Texture::operator GLuint() const
{
    return m_textureObj;
}


void Texture::Bind(GLenum TextureUnit)
{
    glActiveTexture(TextureUnit);
    glBindTexture(GL_TEXTURE_2D, m_textureObj);
}
