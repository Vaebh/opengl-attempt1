#include <iostream>
#include <time.h>
#include <GL\glew.h>
#include <GLFW\glfw3.h>

using namespace std;

float moveHorz, moveVert = 0;

double mouseX, mouseY = 0;

int width, height;

float ratio;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

	if(key == GLFW_KEY_D && action == GLFW_REPEAT || action == GLFW_PRESS)
		moveHorz += 0.01f;
	if(key == GLFW_KEY_A && action == GLFW_REPEAT || action == GLFW_PRESS)
		moveHorz -= 0.01f;
	if(key == GLFW_KEY_W && action == GLFW_REPEAT || action == GLFW_PRESS)
		moveVert += 0.01f;
	if(key == GLFW_KEY_S && action == GLFW_REPEAT || action == GLFW_PRESS)
		moveVert -= 0.01f;
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

int main(void)
{
	if (!glfwInit())
		return 1;
    
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(640, 480, "Red Square Adventures", NULL, NULL);
  
	if (!window)
	{
		glfwTerminate();
			return 1;
	}
  
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();
   
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);

	printf("%u\n", vertexBuffer);

	float vertices[] = 
	{
		-0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f // Vertex 1 (X, Y) red, top Left
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f // Vertex 2 (X, Y) green, top right
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f  // Vertex 3 (X, Y) blue, bottom right
		-0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // Vertex 4 (X, Y) white, bottom left
	};

	GLuint vbo;
	glGenBuffers(1, &vbo); // Generate 1 buffer

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

	GLuint tex;
	glGenTextures(1, &tex);

	glBindTexture(GL_TEXTURE_2D, tex);
   
  int width, height;
  unsigned char* image =
  SOIL_load_image("sample.png", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,GL_UNSIGNED_BYTE, image);
  SOIL_free_image_data(image);
  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Vertex Shader
	const GLchar * vertexSource = "#version 150\n"
    "in vec2 texcoord;"
		"in vec2 position;"
		"in vec3 color;"
		"out vec3 Color;"
    "out vec2 Texcoord;"
		"void main()"
		"{"
    "Texcoord = texcoord;"
		"Color = color;"
		"gl_Position = vec4(position, 0.0, 1.0);"
		"}";

	cout << vertexSource << endl;

	// Fragment Shader
	const GLchar * fragmentSource = "#version 150\n"
		"in vec3 Color;"
    "in vec2 Texcoord;"
		"out vec4 outColor;"
    "uniform sampler2D tex;"
		"void main()"
		"{"
		"    outColor = texture(tex, Texcoord) * vec4(Color, 1.0);"
		"}";

	// Loading Vertex Shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);

	glCompileShader(vertexShader);

	// Checking if Vertex Shader compiled or not
	char buffer[512];
	glGetShaderInfoLog(vertexShader, 512, NULL, buffer);

	GLint status;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
	if(status == GL_TRUE)
		cout << "Vertex shader compilation SUCCESS" << endl;
	else if(status == GL_FALSE)
		cout << "Vertex shader compilation FAILED" << endl;

	// Loading Fragment Shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);

	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
	if(status == GL_TRUE)
		cout << "Fragment shader compilation SUCCESS" << endl;
	else if(status == GL_FALSE)
		cout << "Fragment shader compilation FAILED" << endl;

	// Actually create the shader program
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	// Telling the program which buffer the fragment shader is writing to
	glBindFragDataLocation(shaderProgram, 0, "outColor");

	// Link the program (?)
	glLinkProgram(shaderProgram);

	// Set our shader to be the active shader
	glUseProgram(shaderProgram);

	/*GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	cout << posAttrib << endl;
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(posAttrib);*/

	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
  cout << "PositionAttrib: " << posAttrib << endl;
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE,
						   7*sizeof(float), 0);

	GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
	cout << "ColorAttrib: " << colAttrib << endl;
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE,
						   7*sizeof(float), (void*)(2*sizeof(float)));
                     
  GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
	cout << "TexAttrib: " << texAttrib << endl;
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE,
						   7*sizeof(float), (void*)(5*sizeof(float)));

	// Setting input callbacks
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouseCallback);

	// Setting the screen to be black and swapping the buffers
	glClearColor(0, 0, 0, 1);
	glfwSwapBuffers(window);

	// Loop until the window should close
	while (!glfwWindowShouldClose(window))
	{
		//GLint uniColor = glGetUniformLocation(shaderProgram, "triangleColor");
		//glUniform3f(uniColor, 1.0f, 0.0f, 0.0f);

		//float time = (float)clock() / (float)CLOCKS_PER_SEC;
		//glUniform3f(uniColor, (sin(time * 4.0f) + 1.0f) / 2.0f, 0.0f, 0.0f);

		//glDrawArrays(GL_TRIANGLES, 0, 3);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);

		// Check for new events
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();

	return 0;
}