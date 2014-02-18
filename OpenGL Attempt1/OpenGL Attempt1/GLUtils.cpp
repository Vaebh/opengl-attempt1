#include "GLUtils.h"

#include <iostream>
#include <fstream>

using std::cout;
using std::endl;

void ShaderCompilationCheck(GLuint shader, string shaderType)
{
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if(status == GL_TRUE)
		cout << shaderType + " shader compilation SUCCESS" << endl;
	else if(status == GL_FALSE)
		cout << shaderType + " shader compilation FAILED" << endl;
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

void Setup2D(GLuint& shaderProgram)
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
GLuint CreateShaderProgram(const GLchar * vertexShaderSource, const GLchar * fragShaderSource)
{
	// Loading Vertex Shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	ShaderCompilationCheck(vertexShader, "Vertex");

	// Loading Fragment Shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragShaderSource, NULL);
	glCompileShader(fragmentShader);
	ShaderCompilationCheck(fragmentShader, "Fragment");

	// Actually create the shader program
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// Telling the program which buffer the fragment shader is writing to
	glBindFragDataLocation(shaderProgram, 0, "outColor");
	glLinkProgram(shaderProgram);

	return shaderProgram;
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

const GLchar* LoadShader(string path)
{
	string shaderSrc = "";
	std::ifstream myFile;

	myFile.open(path);
	if(myFile.is_open() && !myFile.bad())
	{
		shaderSrc = shaderSrc.assign(std::istreambuf_iterator<char>(myFile), std::istreambuf_iterator<char>());

		const GLchar* shader = shaderSrc.c_str();
		return shader;
	}

	return "";
}




//-------------------------------------------------------------------------------------
// Old stuff
//-------------------------------------------------------------------------------------
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

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

static void mouseCallback(GLFWwindow * window, int button, int action, int mods)
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