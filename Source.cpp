#include<glew.h>
#include<glfw3.h>

#include<iostream>
#include<cmath>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void escape_input(GLFWwindow* window, int key, int scancode, int action, int mods);

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

int count = 0;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location=0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos,1.0f);\n"
"}\0";

const char* fragmentShader1Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
"	FragColor=ourColor;\n"
"}\0";

const char* fragmentShader2Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
"	FragColor=ourColor;\n"
"}\0";

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Reached Triangle", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create window Object" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glViewport(0, 0, WIDTH, HEIGHT);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, escape_input);

	GLenum check = glewInit();
	if (check != GLEW_OK) {
		std::cout << "Glew did't initialize" << std::endl;
		return -1;
	}

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::COMPILATION_SHADER_FAIL_VERTEX" << infoLog << std::endl;
	}

	unsigned int fragmentShader[2];
	fragmentShader[0] = glCreateShader(GL_FRAGMENT_SHADER);
	fragmentShader[1] = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader[0], 1, &fragmentShader1Source, NULL);
	glCompileShader(fragmentShader[0]);

	glShaderSource(fragmentShader[1], 1, &fragmentShader2Source, NULL);
	glCompileShader(fragmentShader[1]);

	int fragSuccess;
	char fragInfoLog[512];
	glGetShaderiv(fragmentShader[0], GL_COMPILE_STATUS, &fragSuccess);

	if (!fragSuccess) {
		glGetShaderInfoLog(fragmentShader[0], 512, NULL, fragInfoLog);
		std::cout << "ERROR::COMPILATION_SHADER_FAIL_FRAGMENT" << fragInfoLog << std::endl;
	}

	glGetShaderiv(fragmentShader[1], GL_COMPILE_STATUS, &fragSuccess);

	if (!fragSuccess) {
		glGetShaderInfoLog(fragmentShader[1], 512, NULL, fragInfoLog);
		std::cout << "ERROR::COMPILATION_SHADER_FAIL_FRAGMENT" << fragInfoLog << std::endl;
	}

	unsigned int shaderProgram[2];
	shaderProgram[0] = glCreateProgram();
	shaderProgram[1] = glCreateProgram();

	glAttachShader(shaderProgram[0], vertexShader);
	glAttachShader(shaderProgram[0], fragmentShader[0]);
	glLinkProgram(shaderProgram[0]);

	glAttachShader(shaderProgram[1], vertexShader);
	glAttachShader(shaderProgram[1], fragmentShader[1]);
	glLinkProgram(shaderProgram[1]);

	int progSuccess;
	char progInfoLog[512];
	glGetProgramiv(shaderProgram[0], GL_LINK_STATUS, &progSuccess);
	if (!progSuccess) {
		glGetProgramInfoLog(shaderProgram[0], 512, NULL, progInfoLog);
		std::cout << "ERROR::LINKING_PROGRAM_FAILED" << progInfoLog << std::endl;
	}

	glGetProgramiv(shaderProgram[1], GL_LINK_STATUS, &progSuccess);
	if (!progSuccess) {
		glGetProgramInfoLog(shaderProgram[1], 512, NULL, progInfoLog);
		std::cout << "ERROR::LINKING_PROGRAM_FAILED" << progInfoLog << std::endl;
	}

	GLfloat vertices[] = {
		0.15f,  0.15f, 0.0f,
		0.15f, -0.15f, 0.0f,
		-0.15f, -0.15f, 0.0f,
		-0.15f,  0.15f, 0.0f
	};

	GLfloat vertices2[] = {
		0.3f,0.3f,0.0f,
		0.3f,0.15f,0.0f,
		0.15f,0.15f,0.0f,
		0.15f,0.3f,0.0f
	};

	unsigned int indices[] = {
		0,1,3,
		1,2,3
	};

	unsigned int EBO[2];
	glGenBuffers(1, &EBO[0]);

	unsigned int VBO[2];
	glGenBuffers(1, &VBO[0]);

	unsigned int VAO[2];
	glGenVertexArrays(1, &VAO[0]);

	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &EBO[1]);
	glGenVertexArrays(1, &VAO[1]);
	glGenBuffers(1, &VBO[1]);

	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), &vertices2, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);




	glClearColor(1.0f, 1.0f, 1.0f, 0.2f);

	while (!glfwWindowShouldClose(window)) {

		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram[0]);
		glBindVertexArray(VAO[0]);
		glUseProgram(shaderProgram[0]);

		double timeValue = glfwGetTime();
		float greenValue = static_cast<float>(sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram[0], "ourColor");
		glUniform4f(vertexColorLocation, greenValue, greenValue, greenValue, 1.0f);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		glUseProgram(shaderProgram[1]);
		glBindVertexArray(VAO[1]);

		timeValue = glfwGetTime();
		greenValue = static_cast<float>(sin(timeValue) / 2.0f) + 0.5f;
		vertexColorLocation = glGetUniformLocation(shaderProgram[1], "ourColor");
		glUseProgram(shaderProgram[1]);
		glUniform4f(vertexColorLocation, 0.0f, 1.0f, greenValue, 1.0f);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void escape_input(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	else if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		if (count == 0) {
			glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
			count++;
		}
		else {
			glClearColor(1.0f, 1.0f, 1.0f, 0.2f);
			count = 0;
		}
	}
}