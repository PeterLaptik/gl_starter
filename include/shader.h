#ifndef SHADER_H
#define SHADER_H

#include<string>

class Shader
{
    public:
        Shader(const std::string &vertex_path, const std::string &fragment_path);
        virtual ~Shader();

        void Use(void);

        void SetUniformBool(const std::string &name, bool value);
        void SetUniformInt(const std::string &name, int value);
        void SetUniformFloat(const std::string &name, float value);
        void SetUniformV3(const std::string &name, float value1, float value2, float value3);
        void SetUniformV4(const std::string &name, float value1, float value2,
                          float value3, float value4);

        unsigned int GetProgramId(void) const;
        bool AreShadersOk(void) const;
        std::string GetErrorMessage(void) const;


    public:
        // Shader program ID
        unsigned int m_id;
        // Are shader initialized correctly
        bool m_shaders_ok;
        // First error message (if shader was not initialized)
        std::string m_error_msg;
};

#endif // SHADER_H
