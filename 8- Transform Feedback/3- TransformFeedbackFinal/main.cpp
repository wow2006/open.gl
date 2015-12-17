#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>

// Shader macro
#define GLSL(src) "#version 150 core\n" #src

// Vertex shader
const GLchar* vertexShaderSrc = GLSL(
	in float inValue;
out float geoValue;

void main() {
	geoValue = sqrt(inValue);
}
);

// Geometry shader
const GLchar* geoShaderSrc = GLSL(
	layout(points) in;
layout(triangle_strip, max_vertices = 3) out;

in float[] geoValue;
out float outValue;

void main() {
	for (int i = 0; i < 3; i++) {
		outValue = geoValue[0] + i;
		EmitVertex();
	}

	EndPrimitive();
}
);

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

	// Compile shaders
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSrc, nullptr);
	glCompileShader(vertexShader);

	GLuint geoShader = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(geoShader, 1, &geoShaderSrc, nullptr);
	glCompileShader(geoShader);

	// Create program and specify transform feedback variables
	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, geoShader);

	const GLchar* feedbackVaryings[] = { "outValue" };
	glTransformFeedbackVaryings(program, 1, feedbackVaryings, GL_INTERLEAVED_ATTRIBS);

	glLinkProgram(program);
	glUseProgram(program);

	// Create VAO
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create input VBO and vertex format
	GLfloat data[] = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f };

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

	GLint inputAttrib = glGetAttribLocation(program, "inValue");
	glEnableVertexAttribArray(inputAttrib);
	glVertexAttribPointer(inputAttrib, 1, GL_FLOAT, GL_FALSE, 0, 0);

	// Create transform feedback buffer
	GLuint tbo;
	glGenBuffers(1, &tbo);
	glBindBuffer(GL_ARRAY_BUFFER, tbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data) * 3, nullptr, GL_STATIC_READ);

	// Create query object to collect info
	GLuint query;
	glGenQueries(1, &query);

	// Perform feedback transform
	glEnable(GL_RASTERIZER_DISCARD);

	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, tbo);

	glBeginQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN, query);
	glBeginTransformFeedback(GL_TRIANGLES);
	glDrawArrays(GL_POINTS, 0, 5);
	glEndTransformFeedback();
	glEndQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN);

	glDisable(GL_RASTERIZER_DISCARD);

	glFlush();

	// Fetch and print results
	GLuint primitives;
	glGetQueryObjectuiv(query, GL_QUERY_RESULT, &primitives);

	GLfloat feedback[15];
	glGetBufferSubData(GL_TRANSFORM_FEEDBACK_BUFFER, 0, sizeof(feedback), feedback);

	printf("%u primitives written!\n\n", primitives);

	for (int i = 0; i < 15; i++) {
		printf("%f\n", feedback[i]);
	}

	return 0;
}
