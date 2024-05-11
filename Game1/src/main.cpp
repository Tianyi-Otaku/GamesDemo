#include<OpenGL.h>
#include<GLFW/glfw3.h>
#include<glad/glad.h>
#include<Log.h>

#define STB_IMAGE_IMPLEMENTATION
#include<stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
	unsigned int texture1, texture2;
	opengl.texture(texture1, "./resources/textures/wall.jpg", GL_RGB);
	opengl.texture(texture2, "./resources/textures/awesomeface.png", GL_RGBA);
	//激活！！！！！
	glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
	glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1);
	//变换
	//glm::mat4 trans(1.0f);
	//trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
	//trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));



	while (!glfwWindowShouldClose(window)) {
		//绘图
		//glActiveTexture(GL_TEXTURE0); // 在绑定纹理之前先激活纹理单元
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glBindVertexArray(vao);
		
		glm::mat4 trans(1.0f);
		trans = glm::translate(trans, glm::vec3(0.0f, 0.0f, 0.0f));
		trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.5f, 0.5f, 0.0f));
		unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));


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