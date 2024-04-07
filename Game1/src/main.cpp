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
		
		glBindVertexArray(vao);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);//����������
		glfwPollEvents();//�����¼�
	}
	return 0;
}