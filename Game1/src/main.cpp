#include<OpenGL.h>
#include<GLFW/glfw3.h>
#include<glad/glad.h>
int main(void) {
	OpenGL opengl;
	GLFWwindow* window = opengl.getWindow();

	Shader shader;
	//������ɫ��
	unsigned int vertexShader = shader.VertexShader();
	//Ƭ����ɫ��
	unsigned int fragmentShader = shader.FragmentShader();
	//��ɫ������
	unsigned int shaderProgram = shader.ShaderProgram(vertexShader, fragmentShader);
	//��������
	unsigned int vao = opengl.vertexMap();

	while (!glfwWindowShouldClose(window)) {
		//��ͼ
		glBindVertexArray(vao);
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