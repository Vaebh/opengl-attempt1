class Shader : public
{
public:
Shader();
~Shader();

GLuint mShaderProgram;
GLuint mVertexShader;
GLuint mFragmentShader;

private:
CreateShaderFromFile
ShaderCompilationCheck(const GLuint vertexShader, const GLuint fragmentShader) const;

};