#include<OpenGL.h>
#include<GLFW/glfw3.h>
#include<glad/glad.h>
#include<Log.h>
#define STB_IMAGE_IMPLEMENTATION
#include<stb_image.h>
int main(void) {
	const std::string vertexShaderPath = "./resources/code/shader.vs";
	const std::string fragmentShaderPath = "./resources/code/shader.fs";

	OpenGL opengl;
	GLFWwindow* window = opengl.getWindow();
	Shader shader;
	//顶点着色器
	unsigned int vertexShader = shader.VertexShader(vertexShaderPath);
	//片段着色器
	unsigned int fragmentShader = shader.FragmentShader(fragmentShaderPath);
	//着色器程序
	unsigned int shaderProgram = shader.ShaderProgram(vertexShader, fragmentShader);
	//顶点数据
	unsigned int vao = opengl.vertexMap();
	//纹理数据

	//1. 数据
	int width, height, nrChannels;
	unsigned char* data = stbi_load("./resources/textures/wall.jpg", &width, &height, &nrChannels, 0);
	//2. 纹理采样
	unsigned int texture1, texture2;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	//3.设置属性
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//4.加载纹理
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	//5.释放数据
	stbi_image_free(data);
	//0----------------------------
	stbi_set_flip_vertically_on_load(true);
	data = stbi_load("./resources/textures/awesomeface.png", &width, &height, &nrChannels, 0);
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	//3.设置属性
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//4.加载纹理
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	//5.释放数据
	stbi_image_free(data);
	//激活！！！！！
	glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
	glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1);
	while (!glfwWindowShouldClose(window)) {
		//绘图
		//glActiveTexture(GL_TEXTURE0); // 在绑定纹理之前先激活纹理单元
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glBindVertexArray(vao);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		//Uniform
		//int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		//glUseProgram(shaderProgram);

		glfwSwapBuffers(window);//交换缓冲区
		glfwPollEvents();//处理事件
	}
	return 0;
}