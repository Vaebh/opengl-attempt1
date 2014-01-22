#include <iostream>
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
		float thing = (height / (float)width);
		mouseX = ((mouseX * 2.666f) / 640) - 1.33f;
		mouseY = ((mouseY * 2.f) / 480) - 1.f;
		cout << "Scaled XPos: " << mouseX << " Scaled YPos: " << mouseY << endl;
		DrawSquare(mouseX, -mouseY, 0.5f, window);
	}
}

static void mousePosCallback(GLFWwindow * window, double x, double y)
{

}



int main(void)
{
	if (!glfwInit())
		return 1;
    
	GLFWwindow* window = glfwCreateWindow(640, 480, "Red Square Adventures", NULL, NULL);
  
	if (!window)
	{
		glfwTerminate();
			return 1;
	}
  
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouseCallback);

	glClearColor(0, 0, 0, 1);
	glfwSwapBuffers(window);
	
	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float) height;
  
	while (!glfwWindowShouldClose(window))
	{
		/*float ratio;
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float) height;
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);

		glMatrixMode(GL_MODELVIEW);

		glLoadIdentity();*/

		//DrawSquare(0, 0, 0.5f, window);

		//glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
		/*glBegin(GL_QUADS);
		glColor3f(1.f, 0.f, 0.f);
		glVertex3f(-0.5f + moveHorz, -0.5f + moveVert, 0.f);
		glColor3f(0.f, 1.f, 0.f);
		glVertex3f(0.5f + moveHorz, -0.5f + moveVert, 0.f);
		glColor3f(0.f, 0.f, 1.f);
		glVertex3f(0.5f + moveHorz, 0.5f + moveVert, 0.f);
		glColor3f(1.f, 1.f, 1.f);
		glVertex3f(-0.5f + moveHorz, 0.5f + moveVert, 0.f);
		/*glBegin(GL_TRIANGLES);
		glColor3f(1.f, 0.f, 0.f);
		glVertex3f(-0.6f, -0.4f, 0.f);
		glColor3f(0.f, 1.f, 0.f);
		glVertex3f(0.6f, -0.4f, 0.f);
		glColor3f(0.f, 0.f, 1.f);
		glVertex3f(0.f, 0.6f, 0.f);
		glEnd();*/
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();

	return 0;
}