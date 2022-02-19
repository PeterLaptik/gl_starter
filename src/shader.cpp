#include "shader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <iostream>


const int MSG_BUF = 512;
const char *ERR_PREFIX = "Shader reader message: ";
const char *ERR_FILE_READING = "Error on shader file reading!";
const char *ERR_VERTEX_COMPILING = "Vertex shader compilation error!";
const char *ERR_FRAGMENT_COMPILING = "Fragment shader compilation error!";
const char *ERR_SHADER_LINKING = "Shader linking error!";


Shader::Shader(const std::string &vertex_path, const std::string &fragment_path)
    : m_shaders_ok(true), m_error_msg("")
{
    // Read shader programs
    std::string code_vertex;
    std::string code_fragment;

    std::ifstream vertex_file;
    std::ifstream fragment_file;

    std::stringstream vertex_stream;
    std::stringstream fragment_stream;

    vertex_file.open(vertex_path.c_str());
    fragment_file.open(fragment_path.c_str());
    m_shaders_ok = !vertex_file.fail() && !fragment_file.fail();
    if(!m_shaders_ok)
    {
        m_error_msg = ERR_FILE_READING;
        std::cout<<ERR_PREFIX<<ERR_FILE_READING<<std::endl;
    }


    vertex_stream<<vertex_file.rdbuf();
    fragment_stream<<fragment_file.rdbuf();

    vertex_file.close();
    fragment_file.close();

    std::string str_vertex = vertex_stream.str();
    std::string str_fragment = fragment_stream.str();

    const char *vertex_code = str_vertex.c_str();
    const char *fragment_code = str_fragment.c_str();

    // Compile shader programs
    int result;
    char log[MSG_BUF];

    unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertex_code, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);

    if(!result)
    {
        glGetShaderInfoLog(vertex, MSG_BUF, NULL, log);
        std::cout<<ERR_PREFIX<<log<<std::endl;
        m_shaders_ok = false;
        if(m_error_msg=="")
            m_error_msg = ERR_VERTEX_COMPILING;
    }

    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragment_code, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);

    if(!result)
    {
        glGetShaderInfoLog(vertex, MSG_BUF, NULL, log);
        std::cout<<ERR_PREFIX<<log<<std::endl;
        m_shaders_ok = false;
        if(m_error_msg=="")
            m_error_msg = ERR_FRAGMENT_COMPILING;
    }

    m_id = glCreateProgram();
    glAttachShader(m_id, vertex);
    glAttachShader(m_id, fragment);
    glLinkProgram(m_id);

    glGetProgramiv(m_id, GL_LINK_STATUS, &result);
    if(!result)
    {
        glGetProgramInfoLog(m_id, MSG_BUF, NULL, log);
        std::cout<<ERR_PREFIX<<log<<std::endl;
        m_shaders_ok = false;
        if(m_error_msg=="")
            m_error_msg = ERR_SHADER_LINKING;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader()
{ }


void Shader::Use()
{
    glUseProgram(m_id);
}

void Shader::SetUniformBool(const std::string &name, bool value)
{
    int u_location = glGetUniformLocation(m_id, name.c_str());
    glUniform1i(u_location, (int)value);
}

void Shader::SetUniformInt(const std::string &name, int value)
{
    int u_location = glGetUniformLocation(m_id, name.c_str());
    glUniform1i(u_location, value);
}

void Shader::SetUniformFloat(const std::string &name, float value)
{
    int u_location = glGetUniformLocation(m_id, name.c_str());
    glUniform1f(u_location, value);
}

void Shader::SetUniformV3(const std::string &name, float value1, float value2, float value3)
{
    int u_location = glGetUniformLocation(m_id, name.c_str());
    glUniform3f(u_location, value1, value2, value3);
}

void Shader::SetUniformV4(const std::string &name, float value1, float value2,
                          float value3, float value4)
{
    int u_location = glGetUniformLocation(m_id, name.c_str());
    glUniform4f(u_location, value1, value2, value3, value4);
}

unsigned int Shader::GetProgramId(void) const
{
    return m_id;
}

bool Shader::AreShadersOk() const
{
    return m_shaders_ok;
}

std::string Shader::GetErrorMessage() const
{
    return m_error_msg;
}
