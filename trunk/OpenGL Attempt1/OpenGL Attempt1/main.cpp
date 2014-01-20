#include <GLFW/glfw3.h>

using namespace std;

int main()
{
  glfwSetErrorCallback(error_callback);

	if (!glfwInit())
    exit(EXIT_FAILURE);
    
  GLFWwindow* window = glfwCreateWindow(640, 480, "Red Square Adventures", NULL, NULL);
  
  if (!window)
  {
      glfwTerminate();
      exit(EXIT_FAILURE);
  }
  
  glfwMakeContextCurrent(window);
  
  while (!glfwWindowShouldClose(window))
  {
      // Keep running
  }
  
  glfwDestroyWindow(window);
  
  glfwTerminate();

	return 0;
}

void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}