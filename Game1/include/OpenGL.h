#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class OpenGL{



public:
	OpenGL();
	GLFWwindow* getWindow();
	
	unsigned int vertexMap();

	~OpenGL();
};

//äÖÈ¾Æ÷
class Shader {
public:
	//Shader();
	unsigned int VertexShader();
	unsigned int FragmentShader();
	unsigned int ShaderProgram(unsigned int& vertexShader, unsigned int& fragmentShader);
};
