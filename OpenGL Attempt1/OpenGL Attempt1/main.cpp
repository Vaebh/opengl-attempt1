#include "GLIncludes.h"
#include "GLUtils.h"
#include "Shader.h"
#include "Sprite.h"
#include "Render.h"
#include "Input.h"
#include <time.h>
#include <iostream>
#include "Scene.h"
#include "AudioSystem.h"

#include <fmod.hpp>
#include <fmod_errors.h>
using namespace std;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

	//if(key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT))
		//kitten->moveX += 0.01f;
	if(key == GLFW_KEY_A)
	{
		cout << "AAAA" << endl;
		//kitten->moveX -= 0.01f;
	}

	if(key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		//kitten->moveY += 0.01f;
		cout << "WWWWW" << endl;
	}
	if(key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		cout << "SSSSS" << endl;
		//kitten->moveY -= 0.01f;
	}
}

GLfloat vertices[] = 
{
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

	0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

	// floor
	-1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	1.0f,  1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	1.0f,  1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	-1.0f,  1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	-1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f
};

// Quad vertices
GLfloat quadVertices[] = 
{
	-1.0f,  1.0f,  0.0f, 1.0f,
	1.0f,  1.0f,  1.0f, 1.0f,
	1.0f, -1.0f,  1.0f, 0.0f,

	1.0f, -1.0f,  1.0f, 0.0f,
	-1.0f, -1.0f,  0.0f, 0.0f,
	-1.0f,  1.0f,  0.0f, 1.0f
};

GLFWwindow* InitialiseWindow()
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
}


int NewMain()
{
	// Initialise the window
	GLFWwindow* window = InitialiseWindow();

	if(!window)
		return 1;

	// Creates and binds the Vertex Array Objects, which store all the links between my vertex buffer objects
	GLuint vaoCube, vaoQuad;
	glGenVertexArrays(1, &vaoCube);
	glGenVertexArrays(1, &vaoQuad);

	// Load vertex data
    GLuint vboCube, vboQuad;
    glGenBuffers(1, &vboCube);
    glGenBuffers(1, &vboQuad);

	glBindBuffer(GL_ARRAY_BUFFER, vboCube);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vboQuad);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

	Shader shader3D = Shader("3DVertexShader.txt", "3DFragShader.txt");
	Shader shader2D = Shader("2DVertexShader.txt", "2DFragShader.txt");

	// Loading 3D Shader
	GLuint shader3DProgram = shader3D.GetProgramID();

	if(glIsProgram(shader3DProgram) == GL_TRUE)
		cout << "isProgram success" << endl;
	else
		cout << "isProgram fail" << endl;

	glUseProgram(shader3DProgram);
	GLuint shader2DProgram = shader2D.GetProgramID();

	// Specify the layout of the vertex data
    glBindVertexArray(vaoCube);
    glBindBuffer(GL_ARRAY_BUFFER, vboCube);
	Setup3D(shader3DProgram);

	glBindVertexArray(vaoQuad);
    glBindBuffer(GL_ARRAY_BUFFER, vboQuad);
    Setup2D(shader2DProgram);

	//glUniform1i(glGetUniformLocation(shader2D, "texFrameBuffer"), 0);

	GLuint texKitten = LoadImage("sample.png");
	GLuint texPuppy = LoadImage("sample2.png");

	glUseProgram(shader3DProgram);
    glUniform1i(glGetUniformLocation(shader3DProgram, "texKitten"), 0);
    glUniform1i(glGetUniformLocation(shader3DProgram, "texPuppy"), 1);

	GLint uniModel = glGetUniformLocation(shader3DProgram, "move");

    // Set up projection
    glm::mat4 view = glm::lookAt(
        glm::vec3(2.5f, 2.5f, 2.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 1.0f)
    );
    GLint uniView = glGetUniformLocation(shader3DProgram, "view");
    glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

    glm::mat4 proj = glm::perspective(45.0f, 640.0f / 480.0f, 1.0f, 10.0f);
    GLint uniProj = glGetUniformLocation(shader3DProgram, "proj");
    glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

    GLint uniColor = glGetUniformLocation(shader3DProgram, "tintColor");

	glUseProgram(shader2DProgram);
    glUniform1i(glGetUniformLocation(shader2DProgram, "texFramebuffer"), 0);

	// Create frame buffer
    GLuint frameBuffer;
    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

    // Create texture to hold color buffer
    GLuint texColorBuffer;
    glGenTextures(1, &texColorBuffer);
    glBindTexture(GL_TEXTURE_2D, texColorBuffer);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 640, 480, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);

    // Create Renderbuffer Object to hold depth and stencil buffers
    GLuint rboDepthStencil;
    glGenRenderbuffers(1, &rboDepthStencil);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepthStencil);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 640, 480);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rboDepthStencil);

	// Setting input callbacks
	//glfwSetKeyCallback(window, key_callback);
	//glfwSetMouseButtonCallback(window, mouseCallback);

	// Loop until the window should close
	while (!glfwWindowShouldClose(window))
	{
		// Bind our framebuffer and draw 3D scene (spinning cube)
        glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
        glBindVertexArray(vaoCube);
		glEnable(GL_DEPTH_TEST);
		glUseProgram(shader3DProgram);

		glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texKitten);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texPuppy);

		// Clear the screen to black
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Calculate transformation
        glm::mat4 model;
        model = glm::rotate(
            model,
            (GLfloat)clock() / (GLfloat)CLOCKS_PER_SEC * 180.0f,
            glm::vec3(0.0f, 0.0f, 1.0f)
        );
        glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));
        
        // Draw cube
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glEnable(GL_STENCIL_TEST);

            // Draw floor
            glStencilFunc(GL_ALWAYS, 1, 0xFF);
            glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
            glStencilMask(0xFF);
            glDepthMask(GL_FALSE);
            glClear(GL_STENCIL_BUFFER_BIT);
                
            glDrawArrays(GL_TRIANGLES, 36, 6);

            // Draw cube reflection
            glStencilFunc(GL_EQUAL, 1, 0xFF);
            glStencilMask(0x00);
            glDepthMask(GL_TRUE);

            model = glm::scale(glm::translate(model, glm::vec3(0, 0, -1)), glm::vec3(1, 1, -1));
            glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));

            glUniform3f(uniColor, 0.3f, 0.3f, 0.3f);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            glUniform3f(uniColor, 1.0f, 1.0f, 1.0f);

        glDisable(GL_STENCIL_TEST);

		// Bind default framebuffer and draw contents of our framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glBindVertexArray(vaoQuad);
        glDisable(GL_DEPTH_TEST);
        glUseProgram(shader2DProgram);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texKitten);

        glDrawArrays(GL_TRIANGLES, 0, 6);

		glfwSwapBuffers(window);

		// Check for new events
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

int NewNewMain()
{
	// Initialise the window
	GLFWwindow* window = InitialiseWindow();

	if(!window)
		return 1;

	Sprite* puppy = NULL;
	Sprite* kitten = NULL;

	Scene* theScene = new Scene();

	kitten = new Sprite("bros.png");
	Input* inputHandler = new Input(window, kitten);
	kitten->SetPosition(Vector3(-0.2, 0, 0));

	puppy = new Sprite("sample2.png");
	//Input* inputHandler = new Input(window, puppy);
	puppy->SetPosition(Vector3(0.8, 0.5, 0));
	puppy->mScale = Vector3(0.5, 0.5, 0);

	theScene->AddToScene(kitten);
	theScene->AddToScene(puppy);

	AudioSystem* audioSystem = new AudioSystem();
	audioSystem->Initialise();

	audioSystem->PlaySound("Tank.mp3");

	//glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouseCallback);

	double olddelta = 0;
	double delta = 0;
	double begin_time = glfwGetTime();

	// Loop until the window should close
	while (!glfwWindowShouldClose(window))
	{
		delta = glfwGetTime() - olddelta;
		olddelta = glfwGetTime();

		theScene->Update(delta);
		//audioSystem->Update(delta);

		//if(kitten)
			//kitten->Update(delta);

		//if(puppy)
			//puppy->Update(delta);

		Render::GetSingleton()->Draw();

		glfwSwapBuffers(window);

		// Check for new events
		glfwPollEvents();
	}

	//delete kitten;
	//kitten = 0;

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

int main(void)
{
	return NewNewMain();
	//return NewMain();
	//return OldMain();

	return 0;
}