#include "GLUtils.h"

#include <iostream>
#include <fstream>

using std::cout;
using std::endl;

/*GLFWwindow* InitialiseWindow()
{
        if (!glfwInit())
                return NULL;
    
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        GLFWwindow* window = glfwCreateWindow(640, 480, "Red Square Adventures", NULL, NULL);
  
        if (!window)
        {
                glfwTerminate();
                        return NULL;
        }
  
        glfwMakeContextCurrent(window);

        glewExperimental = GL_TRUE;
        glewInit();

        return window;
}*/

bool ShaderCompilationCheck(GLuint shader, std::string shaderType)
{
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if(status == GL_TRUE)
	{
		cout << shaderType + " shader compilation SUCCESS" << endl;
		return true;
	}
	else if(status == GL_FALSE)
	{
		cout << shaderType + " shader compilation FAILED" << endl;
		return false;
	}
}

void Setup3D(GLuint& shaderProgram)
{
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	cout << "PositionAttrib: " << posAttrib << endl;
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), 0);

	GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
	cout << "ColorAttrib: " << colAttrib << endl;
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
                     
	GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
	cout << "TexAttrib: " << texAttrib << endl;
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
}

void Setup2D(const GLuint& shaderProgram)
{
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	cout << "PositionAttrib: " << posAttrib << endl;
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), 0);
                     
	GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
	cout << "TexAttrib: " << texAttrib << endl;
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)(2*sizeof(float)));
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

	// Actually create the shader program
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragShader);

	// Telling the program which buffer the fragment shader is writing to
	glBindFragDataLocation(shaderProgram, 0, "outColor");
	glLinkProgram(shaderProgram);

	return shaderProgram;
}

std::string LoadShader(std::string path)
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

GLuint CreateShaderFromFile(std::string path, GLenum shaderType)
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

//-------------------------------------------------------------------------------------
// LoadImage
//
// @param path - The path to the image relative to the code directory
//
// @return - The index for the image
//-------------------------------------------------------------------------------------
GLuint LoadImage(const GLchar * path)
{
	GLuint texture;
	glGenTextures(1, &texture);

	int width, height;
	unsigned char* image;

	glBindTexture(GL_TEXTURE_2D, texture);
	image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return texture;
}


//-------------------------------------------------------------------------------------
// Old stuff
//-------------------------------------------------------------------------------------
/*void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}*/

void DrawSquare(double centerX, double centerY, float length, GLFWwindow * window)
{
	float ratio;
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float) height;

    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

	glBegin(GL_QUADS);
	glColor3f(1.f, 0.f, 0.f);
	glVertex3f(centerX - length, centerY - length, 0.f);
	glColor3f(0.f, 1.f, 0.f);
	glVertex3f(centerX + length, centerY - length, 0.f);
	glColor3f(0.f, 0.f, 1.f);
	glVertex3f(centerX + length, centerY + length, 0.f);
	glColor3f(1.f, 1.f, 1.f);
	glVertex3f(centerX - length, centerY + length, 0.f);
    glEnd();

	glfwSwapBuffers(window);
}

void mouseCallback(GLFWwindow * window, int button, int action, int mods)
{
	if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);
		cout << "XPos: " << mouseX << " YPos: " << mouseY << endl;

		int width, height;
		glfwGetFramebufferSize(window, &width, &height);

		float screenRatioW = (width / (float)height);
		float screenRatioH = (height / (float)width) * screenRatioW;

		mouseX = ((mouseX * (screenRatioW * 2)) / width) - screenRatioW;
		mouseY = ((mouseY * (screenRatioH * 2)) / height) - screenRatioH;

		cout << "Scaled XPos: " << mouseX << " Scaled YPos: " << mouseY << endl;
	}
}