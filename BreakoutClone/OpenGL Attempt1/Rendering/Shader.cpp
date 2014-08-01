#include "../Rendering/Shader.h"
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;

#define DEBUG_PRINTING 0

Shader::Shader()
{
  
}

Shader::Shader(const std::string& vertexShaderSrc, const std::string& fragShaderSrc)
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

GLint Shader::GetAttributeLocation(const char * inAttributeName)
{
  return glGetAttribLocation(GetProgramID(), inAttributeName);
}

//-------------------------------------------------------------------------------------
// CreateShaderProgram
//
// @param vertexShaderSource - The vertex shader we want to use
// @param fragShaderSource - The fragment shader we want to use
//
// @return - The index for the shader program we've just created
//-------------------------------------------------------------------------------------
GLuint Shader::CreateShaderProgram(const std::string& vertexShaderSrc, const std::string& fragShaderSrc)
{
	GLuint vertexShader = CreateShaderFromFile(vertexShaderSrc, GL_VERTEX_SHADER);
	GLuint fragShader = CreateShaderFromFile(fragShaderSrc, GL_FRAGMENT_SHADER);

	if(!ShaderCompilationCheck(vertexShader, fragShader, "NAME"))
	{
		return 0;
	}
        
	mVertexShader = vertexShader;
	mFragmentShader = fragShader;

	// Actually create the shader program
	mShaderProgram = glCreateProgram();
	glAttachShader(mShaderProgram, vertexShader);
	glAttachShader(mShaderProgram, fragShader);

	// Telling the program which buffer the fragment shader is writing to
	glBindFragDataLocation(mShaderProgram, 0, "outColor");
	glLinkProgram(mShaderProgram);
        
	//mShaderProgram = shaderProgram;

	#if DEBUG_PRINTING == 1
	if(glIsProgram(mShaderProgram) == GL_TRUE)
		cout << "isProgram success" << endl;
	else
		cout << "isProgram fail" << endl;
	#endif

	/*glUseProgram(mShaderProgram);

	GLint posAttrib = glGetAttribLocation(mShaderProgram, "position");
	std::cout << "PositionAttrib: " << posAttrib << std::endl;
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), 0);
                     
	GLint texAttrib = glGetAttribLocation(mShaderProgram, "texcoord");
	std::cout << "TexAttrib: " << texAttrib << std::endl;
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)(2*sizeof(float)));*/

	return mShaderProgram;
}

bool Shader::ShaderCompilationCheck(const GLuint vertexShader, const GLuint fragmentShader, const std::string shaderName) const
{
	GLint vertexStatus, fragmentStatus;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexStatus);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentStatus);
        
	if(vertexStatus == GL_TRUE && fragmentStatus == GL_TRUE)
	{
		#if DEBUG_PRINTING == 1
		cout << shaderName + " shader compilation SUCCESS" << endl;
		#endif
		return true;
	}
	else
	{
		if(vertexStatus == GL_FALSE)
		{
			#if DEBUG_PRINTING == 1
			cout << "Vertex shader compilation FAILED" << endl;
			#endif
		}
		if(fragmentStatus == GL_FALSE)
		{
			#if DEBUG_PRINTING == 1
			cout << "Fragment shader compilation FAILED" << endl;
			#endif
		}
                
		return false;
	}
}

GLuint Shader::CreateShaderFromFile(const std::string& path, const GLenum& shaderType)
{
	// Get the shader
	std::string shaderSrcString = LoadShaderFromFile(path);

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

std::string Shader::LoadShaderFromFile(const std::string& path) const
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