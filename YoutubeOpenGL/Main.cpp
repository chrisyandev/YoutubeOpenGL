#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

const char* vertexShaderSource = "#version 330 core\n" // vertex shader source
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n" // fragment shader source
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

int main()
{
	glfwInit(); // initialize GLFW

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // tell GLFW what version of OpenGL we're using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // OpenGL 3.3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // using the CORE profile so that we only have modern functions

	GLfloat vertices[] = // coordinates of vertices
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // lower left
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // lower right
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // upper middle
	};

	GLFWwindow* window = glfwCreateWindow(800, 800, "YoutubeOpenGL", NULL, NULL); // create a window of 800 by 800 pixels with a title
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); // introduce the window into the current context

	gladLoadGL(); // load GLAD so it configures OpenGL

	glViewport(0, 0, 800, 800); // specify the viewport with bottom left and top right coordinates

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); // create vertex shader object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // reference the source
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // create fragment shader object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); // reference the source
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram(); // create shader program object
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram); // wrap up after attaching shaders

	glDeleteShader(vertexShader); // no longer needed so delete these
	glDeleteShader(fragmentShader);

	GLuint VAO, VBO; // containers for Vertex Array and Vertex Buffer Objects

	glGenVertexArrays(1, &VAO); // generate array with 1 element
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO); // set the current Vertex Array Object

	glBindBuffer(GL_ARRAY_BUFFER, VBO); // set the current Vertex Buffer Object
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // store vertices inside buffer

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // define how OpenGL should read the VBO
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // makes sure we don't accidentally modify VBO or VAO
	glBindVertexArray(0);

	glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // background color
	glClear(GL_COLOR_BUFFER_BIT); // clean the back buffer and assign new color to it
	glfwSwapBuffers(window); // swap back buffer with front buffer

	while (!glfwWindowShouldClose(window)) // main loop
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram); // set the Shader Program we want to use
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3); // draw the triangle using GL_TRIANGLES primitive
		glfwSwapBuffers(window); // makes sure image is updated each frame

		glfwPollEvents(); // takes care of all GLFW events
	}

	glDeleteVertexArrays(1, &VAO); // delete all objects we created
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(window); // delete window
	glfwTerminate(); // terminate GLFW
	return 0; // program ends
}