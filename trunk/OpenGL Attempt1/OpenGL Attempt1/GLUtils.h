#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

using std::string;

//GLFWwindow* InitialiseWindow(int width = 640, int height = 480);

void ShaderCompilationCheck(GLuint shader, string shaderType);

// Sets up the 3D and 2D shader variables
void Setup3D(GLuint& shaderProgram);
void Setup2D(GLuint& shaderProgram);

// Creates a shader program from the supplied vertex and fragment shaders
// Includes compilation check
GLuint CreateShaderProgram(const GLchar * vertexShaderSource, const GLchar * fragShaderSource);

const GLchar* LoadShader(string path);

// Loads an image using the SOIL library
GLuint LoadImage(const GLchar * path);

// Draws a square in direct mode (glBegin and glEnd)
void DrawSquare(double centerX, double centerY, float length, GLFWwindow * window);

// Prints out mouse coordinates
static void mouseCallback(GLFWwindow * window, int button, int action, int mods);

// Keyboard controls, exit with Esc
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);