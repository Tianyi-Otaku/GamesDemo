#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
class OpenGL{



public:
	OpenGL();
	GLFWwindow* getWindow();
	
	unsigned int vertexMap();

	void texture(unsigned int& n, std::string dataPath, unsigned int type);

	~OpenGL();
};

//äÖÈ¾Æ÷
class Shader {
public:
	//Shader();
	std::string ShaderSource(std::string dataPath);
	unsigned int VertexShader(std::string shaderSourcePath);
	unsigned int FragmentShader(std::string shaderSourcePath);
	unsigned int ShaderProgram(unsigned int& vertexShader, unsigned int& fragmentShader);
};
