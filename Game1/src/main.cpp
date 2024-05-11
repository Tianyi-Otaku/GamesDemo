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
	//������ɫ��
	unsigned int vertexShader = shader.VertexShader(vertexShaderPath);
	//Ƭ����ɫ��
	unsigned int fragmentShader = shader.FragmentShader(fragmentShaderPath);
	//��ɫ������
	unsigned int shaderProgram = shader.ShaderProgram(vertexShader, fragmentShader);
	//��������
	unsigned int vao = opengl.vertexMap();
	//��������
	unsigned int texture1, texture2;
	opengl.texture(texture1, "./resources/textures/wall.jpg", GL_RGB);
	opengl.texture(texture2, "./resources/textures/awesomeface.png", GL_RGBA);
	//�����������
	glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
	glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1);
	//�任
	//glm::mat4 trans(1.0f);
	//trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
	//trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));



	while (!glfwWindowShouldClose(window)) {
		//��ͼ
		//glActiveTexture(GL_TEXTURE0); // �ڰ�����֮ǰ�ȼ�������Ԫ
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

		glfwSwapBuffers(window);//����������
		glfwPollEvents();//�����¼�
	}
	return 0;
}