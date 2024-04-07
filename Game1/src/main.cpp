#include<OpenGL.h>
#include<GLFW/glfw3.h>
#include<glad/glad.h>
int main(void) {
	OpenGL opengl;
	GLFWwindow* window = opengl.getWindow();

	Shader shader;
	//顶点着色器
	unsigned int vertexShader = shader.VertexShader();
	//片段着色器
	unsigned int fragmentShader = shader.FragmentShader();
	//着色器程序
	unsigned int shaderProgram = shader.ShaderProgram(vertexShader, fragmentShader);
	//顶点数据
	unsigned int vao = opengl.vertexMap();

	while (!glfwWindowShouldClose(window)) {
		//绘图
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