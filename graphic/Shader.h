#pragma once
#include "glad/glad.h"
#include <glm/glm.hpp>
#include <iostream>

class Shader
{
public:
    unsigned int m_id;
    Shader(const char* vShaderCode, const char* fShaderCode)
    {
        int success;
        char info[1024];
        unsigned int vertex, fragment;
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertex, sizeof(info), NULL, info);
            std::cout << "Error compiling vertex shader: " << info << std::endl;
        }
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragment, sizeof(info), NULL, info);
            std::cout << "Error compiling fragment shader: " << info << std::endl;
        }
        // shader Program
        m_id = glCreateProgram();
        glAttachShader(m_id, vertex);
        glAttachShader(m_id, fragment);
        glLinkProgram(m_id);
        glGetProgramiv(m_id, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(m_id, sizeof(info), NULL, info);
            std::cout << "Error linking shaders: " << info << std::endl;
        }
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }
    void use() 
    { 
        glUseProgram(m_id); 
    }
    // ------------------------------------------------------------------------  
    void setVec3(const std::string &name, const glm::vec3 &value) const
    { 
        glUniform3fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]); 
    }
    // ------------------------------------------------------------------------  
    void setVec4(const std::string &name, const glm::vec4 &value) const
    { 
        glUniform4fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]); 
    }
    // ------------------------------------------------------------------------
    void setInt(const std::string &name, int value) const
    { 
        glUniform1i(glGetUniformLocation(m_id, name.c_str()), value); 
    }
    // ------------------------------------------------------------------------
    void setFloat(const std::string &name, float value) const
    { 
        glUniform1f(glGetUniformLocation(m_id, name.c_str()), value); 
    }
    // ------------------------------------------------------------------------
    void setMat4(const std::string &name, const glm::mat4 &mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
};
