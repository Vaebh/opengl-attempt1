#include <iostream>
#include <string>
#include <time.h>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

float moveHorz, moveVert = 0;

double mouseX, mouseY = 0;

int width, height;

float ratio;

// Vertex Shader
const GLchar * vertexSource = "#version 150\n"
"in vec2 texcoord;"
"in vec3 position;"
"in vec3 color;"

"out vec3 Color;"
"out vec2 Texcoord;"

"uniform mat4 move;"
"uniform mat4 view;"
"uniform mat4 proj;"

"void main()"
"{"
	"Texcoord = texcoord;"
	"Color = color;"
	"gl_Position = proj * view * move * vec4(position, 1.0);"
"}";

// Fragment Shader
const GLchar * fragmentSource = "#version 150\n"
"in vec3 Color;"
"in vec2 Texcoord;"

"out vec4 outColor;"

"uniform sampler2D texKitten;"
"uniform sampler2D texPuppy;"

"uniform vec4 tintColor;"

"void main()"
"{"
	"vec4 colKitten = texture(texKitten, Texcoord);"
	"vec4 colPuppy = texture(texPuppy, vec2(Texcoord.x, 1- Texcoord.y));"
	"outColor = tintColor * vec4(Color, 1.0) * mix(colPuppy, colKitten, 0.4);"
"}";

// Fragment Shader
// Upside down water cat shader
/*const GLchar * fragmentSource = "#version 150\n"
"in vec3 Color;"
"in vec2 Texcoord;"

"out vec4 outColor;"

"uniform sampler2D texKitten;"
"uniform sampler2D texPuppy;"
"uniform float time;"

"void main()"
"{"
	
    "vec4 colPuppy = texture(texPuppy, Texcoord);"
	"if(Texcoord.y < 0.5)"
	"{outColor = texture(texKitten, Texcoord);}"
	"else"
	"{outColor = texture(texKitten, vec2(Texcoord.x + sin(Texcoord.y * 60.0 + time * 2.0) / 30.0, 1.0 - Texcoord.y));}"
"}";*/

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

	if(key == GLFW_KEY_D && action == GLFW_REPEAT || action == GLFW_PRESS)
		moveHorz -= 10.1f;
	if(key == GLFW_KEY_A && action == GLFW_REPEAT || action == GLFW_PRESS)
		moveHorz += 10.1f;
	if(key == GLFW_KEY_W && action == GLFW_REPEAT || action == GLFW_PRESS)
		moveVert -= 0.1f;
	if(key == GLFW_KEY_S && action == GLFW_REPEAT || action == GLFW_PRESS)
		moveVert += 0.1f;
}

void DrawSquare(double centerX, double centerY, float length, GLFWwindow * window)
{
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

	glBegin(GL_QUADS);
	glColor3f(1.f, 0.f, 0.f);
	glVertex3f(centerX - length + moveHorz, centerY - length + moveVert, 0.f);
	glColor3f(0.f, 1.f, 0.f);
	glVertex3f(centerX + length + moveHorz, centerY - length + moveVert, 0.f);
	glColor3f(0.f, 0.f, 1.f);
	glVertex3f(centerX + length + moveHorz, centerY + length + moveVert, 0.f);
	glColor3f(1.f, 1.f, 1.f);
	glVertex3f(centerX - length + moveHorz, centerY + length + moveVert, 0.f);
    glEnd();

	glfwSwapBuffers(window);
}

static void mouseCallback(GLFWwindow * window, int button, int action, int mods)
{
	if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		// convert mouse coords to range 0 to 1
		glfwGetCursorPos(window, &mouseX, &mouseY);
		cout << "XPos: " << mouseX << " YPos: " << mouseY << endl;

		float screenRatioW = (width / (float)height);
		float screenRatioH = (height / (float)width) * screenRatioW;

		mouseX = ((mouseX * (screenRatioW * 2)) / width) - screenRatioW;
		mouseY = ((mouseY * (screenRatioH * 2)) / height) - screenRatioH;

		cout << "Scaled XPos: " << mouseX << " Scaled YPos: " << mouseY << endl;

		DrawSquare(mouseX, -mouseY, 0.5f, window);
	}
}

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

void ShaderCompilationCheck(GLuint shader, string shaderType)
{
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if(status == GL_TRUE)
		cout << shaderType + " shader compilation SUCCESS" << endl;
	else if(status == GL_FALSE)
		cout << shaderType + " shader compilation FAILED" << endl;
}

int main(void)
{
	// Initialise the window
	GLFWwindow* window = InitialiseWindow();

	if(!window)
		return 1;

	// Creates and binds the Vertex Array Object, which stores all the links between my vertex buffer objects
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glEnable(GL_DEPTH_TEST);

	GLfloat vertices[] = {
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

	// Create and bind the vertex buffer
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
   
	// Create an element array
	GLuint ebo;
	glGenBuffers(1, &ebo);
  
	GLuint elements[] = 
	{
		0, 1, 2,
		2, 3, 0
	};
  
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	// Loading Vertex Shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	ShaderCompilationCheck(vertexShader, "Vertex");

	// Loading Fragment Shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	ShaderCompilationCheck(fragmentShader, "Fragment");

	// Actually create the shader program
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// Telling the program which buffer the fragment shader is writing to
	glBindFragDataLocation(shaderProgram, 0, "outColor");
	glLinkProgram(shaderProgram);
	// Set our shader to be the active shader
	glUseProgram(shaderProgram);

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

	GLuint textures[2];
	glGenTextures(2, textures);
	int width, height;
	unsigned char* image;

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	image = SOIL_load_image("sample.png", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glUniform1i(glGetUniformLocation(shaderProgram, "texKitten"), 0);
	GLint uniKitten = glGetUniformLocation(shaderProgram, "texKitten");

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	image = SOIL_load_image("sample2.png", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glUniform1i(glGetUniformLocation(shaderProgram, "texPuppy"), 1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//GLint uniTime = glGetUniformLocation(shaderProgram, "time");

	glm::mat4 model;
	GLint uniModel = glGetUniformLocation(shaderProgram, "move");
	//trans = glm::rotate(trans, 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));

	// Setting input callbacks
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouseCallback);

	double currentFrame = 0;
	double oldFrame = 0;
	double deltaTime = 0;

	glm::mat4 proj = glm::perspective(45.0f, 640.f / 480.f, 1.0f, 10.0f);
	GLint uniProj = glGetUniformLocation(shaderProgram, "proj");
	glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

	// Loop until the window should close
	while (!glfwWindowShouldClose(window))
	{
		// Clear the screen to black
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		currentFrame = glfwGetTime();
		deltaTime = currentFrame - oldFrame;
		oldFrame = currentFrame;
		
		GLfloat time = ((GLfloat)clock() / (GLfloat)CLOCKS_PER_SEC);
		//time -= oldTime;
		//oldTime = time;
		//GLfloat time = (GLfloat)clock() / (GLfloat)CLOCKS_PER_SEC * 180.0f;
		//glUniform1f(uniTime, time);
		//glUniform1f(uniTime, 1.f);
		//trans = glm::rotate(trans, time, glm::vec3(0.0f, 0.0f, 1.0f));
		//glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));

		// Calculate transformation
        //glm::mat4 trans;
		model = glm::mat4();
        model = glm::rotate(model, ((GLfloat)clock() / (GLfloat)CLOCKS_PER_SEC * 180.f), glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::scale(model, glm::vec3(sin(time * 10.f) / 2.f + 1, sin(time * 10.f) / 2.f + 1, sin(time * 10.f) / 2.f + 1));
        glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));

		//glm::vec3 rotateVec = glm::vec3(1.2f + moveVert, 1.2f + moveVert, 1.2f + moveVert);
		glm::mat4 rotateMat;
		rotateMat = glm::rotate(rotateMat, moveHorz, glm::vec3(0.0f, 0.0f, 1.0f));

		glm::mat4 view = glm::lookAt(
		//glm::vec3(abs(sin(1.2f * time + moveVert - 1)), abs(sin(1.2f * time + moveVert - 1)), abs(sin(1.2f * time + moveVert - 1))),
		glm::vec3(2.2f, 2.2f, 2.2f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f)
		);
		GLint uniView = glGetUniformLocation(shaderProgram, "view");
		glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view * rotateMat));

		GLint uniTintColor = glGetUniformLocation(shaderProgram, "tintColor");
		glUniform4f(uniTintColor, 1.f, 1.f, 1.f, 1.f);

		//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glEnable(GL_STENCIL_TEST);

			glStencilFunc(GL_ALWAYS, 1, 0xFF); // Always set the stencil to 1
			glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
			glStencilMask(0xFF);
			glDepthMask(GL_FALSE);
			glClear(GL_STENCIL_BUFFER_BIT);

			glDrawArrays(GL_TRIANGLES, 36, 6);

			glDepthMask(GL_TRUE);
			glStencilFunc(GL_EQUAL, 1, 0xFF);
			glStencilMask(0x00);

			model = glm::scale(glm::translate(model, glm::vec3(0, 0, -1)), glm::vec3(1, 1, -1));
			glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));

			glUniform4f(uniTintColor, 0.6f, 0.6f, 0.6f, 1.f);

			glDrawArrays(GL_TRIANGLES, 0, 36);

		glDisable(GL_STENCIL_TEST);

		/*glEnable(GL_STENCIL_TEST);

    // Draw floor
    glStencilFunc(GL_ALWAYS, 1, 0xFF); // Set any stencil to 1
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glStencilMask(0xFF); // Write to stencil buffer
    glDepthMask(GL_FALSE); // Don't write to depth buffer
    glClear(GL_STENCIL_BUFFER_BIT); // Clear stencil buffer (0 by default)

    glDrawArrays(GL_TRIANGLES, 36, 6);

    // Draw cube reflection
    glStencilFunc(GL_EQUAL, 1, 0xFF); // Pass test if stencil value is 1
    glStencilMask(0x00); // Don't write anything to stencil buffer
    glDepthMask(GL_TRUE); // Write to depth buffer

    model = glm::scale(
        glm::translate(model, glm::vec3(0, 0, -1)),
        glm::vec3(1, 1, -1)
    );
    glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 0, 36);

glDisable(GL_STENCIL_TEST);*/

		glfwSwapBuffers(window);

		// Check for new events
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}