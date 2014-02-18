#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "GLUtils.h"
#include <time.h>

using namespace std;

float moveHorz, moveVert = 0;

double mouseX, mouseY = 0;

int width, height;

float ratio;

// 3D Vertex Shader
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

// 3D Fragment Shader
const GLchar * fragmentSource = "#version 150\n"
"in vec3 Color;"
"in vec2 Texcoord;"

"out vec4 outColor;"

"uniform sampler2D texKitten;"
"uniform sampler2D texPuppy;"
"uniform vec3 tintColor;"

"void main()"
"{"
	"vec4 colKitten = texture(texKitten, Texcoord);"
	"vec4 colPuppy = texture(texPuppy, vec2(Texcoord.x, 1- Texcoord.y));"
	"outColor = vec4(tintColor, 1) * vec4(Color, 1.0) * mix(colPuppy, colKitten, 0.4);"
"}";

// 2D Vertex Shader
const GLchar * vertex2DSource = "#version 150\n"
"in vec2 texcoord;"
"in vec2 position;"

"out vec2 Texcoord;"

"void main()"
"{"
	"Texcoord = texcoord;"
	"gl_Position = vec4(position, 0, 1.0);"
"}";

// 2D Fragment Shader
const GLchar * fragment2DSource = "#version 150\n"
"in vec2 Texcoord;"

"out vec4 outColor;"

"uniform sampler2D texFrameBuffer;"

"void main()"
"{"
	"const float blurSizeH = 1.0 / 300.0;"
	"const float blurSizeV = 1.0 / 200.0;"
	"vec4 sum = vec4(0.0,0.0,0.0,0.0);"
    "for (int x = -4; x <= 4; x++)"
	"{"
        "for (int y = -4; y <= 4; y++)"
		"{"
            "sum += texture(texFrameBuffer, vec2(Texcoord.x + x * blurSizeH, Texcoord.y + y * blurSizeV)) / 81.0;"
		"}"
	"}"
    "outColor = sum;"
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
	glfwInit();

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

	// Loading 3D Shader
	GLuint shader3D = CreateShaderProgram(vertexSource, fragmentSource);
	glUseProgram(shader3D);
	GLuint shader2D = CreateShaderProgram(vertex2DSource, fragment2DSource);

	// Specify the layout of the vertex data
    glBindVertexArray(vaoCube);
    glBindBuffer(GL_ARRAY_BUFFER, vboCube);
	Setup3D(shader3D);

	glBindVertexArray(vaoQuad);
    glBindBuffer(GL_ARRAY_BUFFER, vboQuad);
    Setup2D(shader2D);

	//glUniform1i(glGetUniformLocation(shader2D, "texFrameBuffer"), 0);

	const GLchar * shaderSrc = LoadShader("test.txt");

	GLuint texKitten = LoadImage("sample.png");
	GLuint texPuppy = LoadImage("sample2.png");

	glUseProgram(shader3D);
    glUniform1i(glGetUniformLocation(shader3D, "texKitten"), 0);
    glUniform1i(glGetUniformLocation(shader3D, "texPuppy"), 1);

	GLint uniModel = glGetUniformLocation(shader3D, "move");

    // Set up projection
    glm::mat4 view = glm::lookAt(
        glm::vec3(2.5f, 2.5f, 2.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 1.0f)
    );
    GLint uniView = glGetUniformLocation(shader3D, "view");
    glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

    glm::mat4 proj = glm::perspective(45.0f, 640.0f / 480.0f, 1.0f, 10.0f);
    GLint uniProj = glGetUniformLocation(shader3D, "proj");
    glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

    GLint uniColor = glGetUniformLocation(shader3D, "tintColor");

	glUseProgram(shader2D);
    glUniform1i(glGetUniformLocation(shader2D, "texFramebuffer"), 0);

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
		glUseProgram(shader3D);

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
        glUseProgram(shader2D);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texColorBuffer);

        glDrawArrays(GL_TRIANGLES, 0, 6);

		glfwSwapBuffers(window);

		// Check for new events
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

int main(void)
{
	return NewMain();
	//return OldMain();

	return 0;
}