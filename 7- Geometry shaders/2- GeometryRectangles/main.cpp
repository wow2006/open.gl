#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Shader macro
#define GLSL(src) "#version 150 core\n" #src

// Vertex shader
const GLchar* vertexShaderSrc = GLSL(
	in vec2 pos;

void main() {
	gl_Position = vec4(pos, 0.0, 1.0);
}
);

// Geometry shader
const GLchar* geometryShaderSrc = GLSL(
	layout(points) in;
layout(triangle_strip, max_vertices = 5) out;

void main() {
	gl_Position = gl_in[0].gl_Position + vec4(-0.1, 0.1, 0.0, 0.0);
	EmitVertex();

	gl_Position = gl_in[0].gl_Position + vec4(0.1, 0.1, 0.0, 0.0);
	EmitVertex();

	gl_Position = gl_in[0].gl_Position + vec4(0.1, -0.1, 0.0, 0.0);
	EmitVertex();

	gl_Position = gl_in[0].gl_Position + vec4(-0.1, -0.1, 0.0, 0.0);
	EmitVertex();

	gl_Position = gl_in[0].gl_Position + vec4(-0.1, 0.1, 0.0, 0.0);
	EmitVertex();

	EndPrimitive();
}
);

// Fragment shader
const GLchar* fragmentShaderSrc = GLSL(
	out vec4 outColor;
void main() {
	outColor = vec4(1.0, 0.0, 0.0, 1.0);
}
);

// Shader creation helper
GLuint createShader(GLenum type, const GLchar* src) {
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);
	return shader;
}

int
main(){
	// Initialize GLFW3
	glfwInit();
	// Set Version to OpenGL 4.5 Core Profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	// Set window to Fixed
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	// Create widnow
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr); // Windowed
	// Set context to current window
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	glewInit();

	// Compile and activate shaders
	GLuint vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderSrc);
	GLuint geometryShader = createShader(GL_GEOMETRY_SHADER, geometryShaderSrc);
	GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderSrc);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, geometryShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	// Create VBO with point coordinates
	GLuint vbo;
	glGenBuffers(1, &vbo);

	GLfloat points[] = {
		-0.45f, 0.45f,
		0.45f, 0.45f,
		0.45f, -0.45f,
		-0.45f, -0.45f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	// Create VAO
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Specify layout of point data
	GLint posAttrib = glGetAttribLocation(shaderProgram, "pos");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

	// Start Drawing Loop
	while (!glfwWindowShouldClose(window))
	{
		// Render frame
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_POINTS, 0, 4);
		// swap buffer
		glfwSwapBuffers(window);
		// Get Events
		glfwPollEvents();
		// check for excape key
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);
	}
	return 0;
}
