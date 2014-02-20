#include "Shader.h"

Shader::Shader()
{
  
}

Shader::Shader(const std::string vertexShaderSrc, const std::string fragShaderSrc)
{
        CreateShaderProgram(vertexShaderSrc, fragShaderSrc);
}

Shader::~Shader()
{
        if(mVertexShader)
        {
                glDetachShader(mShaderProgram, mVertexShader);
                glDeleteShader(mVertexShader);
        }
        if(mFragmentShader)
        {
                glDetachShader(mShaderProgram, mFragmentShader);
                glDeleteShader(mFragmentShader);
        }
        if(mShaderProgram)
        {
                glDeleteProgram(mShaderProgram);
        }
}

//-------------------------------------------------------------------------------------
// CreateShaderProgram
//
// @param vertexShaderSource - The vertex shader we want to use
// @param fragShaderSource - The fragment shader we want to use
//
// @return - The index for the shader program we've just created
//-------------------------------------------------------------------------------------
GLuint CreateShaderProgram(std::string vertexShaderSrc, std::string fragShaderSrc)
{
        GLuint vertexShader = CreateShaderFromFile(vertexShaderSrc, GL_VERTEX_SHADER);
        GLuint fragShader = CreateShaderFromFile(fragShaderSrc, GL_FRAGMENT_SHADER);

        if(!ShaderCompilationCheck(vertexShader, "Vertex") || !ShaderCompilationCheck(fragShader, "Fragment"))
        {
                return 0;
        }
        
        mVertexShader = vertexShader;
        mFragmentShader = fragShader;

        // Actually create the shader program
        GLuint shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragShader);

        // Telling the program which buffer the fragment shader is writing to
        glBindFragDataLocation(shaderProgram, 0, "outColor");
        glLinkProgram(shaderProgram);
        
        mShaderProgram = shaderProgram;

        return shaderProgram;
}

bool Shader::ShaderCompilationCheck(GLuint vertexShader, GLuint fragmentShader, std::string shaderName)
{
        GLint vertexStatus, fragmentStatus;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexStatus);
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentStatus);
        
        if(vertexStatus == GL_TRUE && fragmentStatus == GL_TRUE)
        {
                cout << shaderName + " shader compilation SUCCESS" << endl;
                return true;
        }
        else
        {
                if(vertexStatus == GL_FALSE)
                {
                        cout << "Vertex shader compilation FAILED" << endl;
                }
                if(fragmentStatus == GL_FALSE)
                {
                        cout << "Fragment shader compilation FAILED" << endl;
                }
                
                return false;
        }
}

GLuint Shader::CreateShaderFromFile(std::string path, GLenum shaderType)
{
        // Get the shader
        std::string shaderSrcString = LoadShader(path);

        if(shaderSrcString.empty())
        {
                return 0;
        }

        const GLchar* shaderSrc = shaderSrcString.c_str();

        // Loading Vertex Shader
        GLuint shader = glCreateShader(shaderType);
        glShaderSource(shader, 1, &shaderSrc, NULL);
        glCompileShader(shader);

        return shader;
}

std::string Shader::LoadShader(std::string path)
{
        std::string shaderSrc = "";
        std::ifstream myFile;

        myFile.open(path);
        if(myFile.is_open() && !myFile.bad())
        {
                return shaderSrc.assign(std::istreambuf_iterator<char>(myFile), std::istreambuf_iterator<char>());
        }

        return "";
}