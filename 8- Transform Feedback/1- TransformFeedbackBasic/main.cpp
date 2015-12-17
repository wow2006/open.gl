#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>

// Shader macro
#define GLSL(src) "#version 150 core\n" #src

// Vertex shader
const GLchar* vertexShaderSrc = GLSL(
    in float inValue;
    out float outValue;

    void main() {
        outValue = sqrt(inValue);
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

  // Compile shader
  GLuint shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(shader, 1, &vertexShaderSrc, nullptr);
  glCompileShader(shader);

  // Create program and specify transform feedback variables
  GLuint program = glCreateProgram();
  glAttachShader(program, shader);

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
  glBufferData(GL_ARRAY_BUFFER, sizeof(data), nullptr, GL_STATIC_READ);

  // Perform feedback transform
  glEnable(GL_RASTERIZER_DISCARD);

  glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, tbo);

  glBeginTransformFeedback(GL_POINTS);
      glDrawArrays(GL_POINTS, 0, 5);
  glEndTransformFeedback();

  glDisable(GL_RASTERIZER_DISCARD);

  glFlush();

  // Fetch and print results
  GLfloat feedback[5];
  glGetBufferSubData(GL_TRANSFORM_FEEDBACK_BUFFER, 0, sizeof(feedback), feedback);

  printf("%f %f %f %f %f\n", feedback[0], feedback[1], feedback[2], feedback[3], feedback[4]);

  return 0;
}
