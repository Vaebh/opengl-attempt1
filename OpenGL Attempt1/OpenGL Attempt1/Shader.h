class Shader : public
{
public:

        Shader();
        Shader(const std::string& vertexShaderSrc, const std::string& fragShaderSrc);
        ~Shader();
        
        GLuint GetProgramID();
        
private:
        
        GLuint CreateShaderProgram(const std::string& vertexShaderSrc, const std::string& fragShaderSrc)
        GLuint Shader::CreateShaderFromFile(const std::string& path, const GLenum& shaderType);
        std::string Shader::LoadShaderFromFile(const std::string& path) const;
        
        ShaderCompilationCheck(const GLuint& vertexShader, const GLuint& fragmentShader) const;
        
private:
        
        GLuint mShaderProgram;
        GLuint mVertexShader;
        GLuint mFragmentShader;

};