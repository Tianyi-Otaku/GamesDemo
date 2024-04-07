#include"OpenGL.h"

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

float vertices[] = {
	0.5f, 0.5f, 0.0f,   // ���Ͻ�
	0.5f, -0.5f, 0.0f,  // ���½�
	-0.5f, -0.5f, 0.0f, // ���½�
	-0.5f, 0.5f, 0.0f   // ���Ͻ�
};


unsigned int indices[] = {
	// ע��������0��ʼ! 
	// ����������(0,1,2,3)���Ƕ�������vertices���±꣬
	// �����������±��������ϳɾ���
	0, 1, 3, // ��һ��������
	1, 2, 3  // �ڶ���������
};

//��ʼ��
OpenGL::OpenGL() {
	glfwInit();
}	

GLFWwindow* OpenGL::getWindow() {
	//��ʼ��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//��������
	GLFWwindow * window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	glfwMakeContextCurrent(window);
	//GLAD��ʼ��
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	std::cout << "Failed to initialize GLAD" << std::endl;
	//������
	return window;
}

OpenGL::~OpenGL() {
	glfwTerminate();
}

//
unsigned int OpenGL::vertexMap() {
	unsigned int VAO;//�����������Vertex Array Object��VAO
	unsigned int VBO;//���㻺�����Vertex Buffer Object��VBO
	unsigned int EBO;//Ԫ�ػ������Element Buffer Object��EBO       �� ����������� Index Buffer Object��IBO
	//1.����
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	//2.��
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	//3.�趨��������ָ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * (sizeof(float)), (void*)0);
	glEnableVertexAttribArray(0);
	return VAO;
}


unsigned int Shader::VertexShader() {
	unsigned int vertexShader;
	//1.����
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//2.��������
	glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
	//3.����
	glCompileShader(vertexShader);
	return vertexShader;
}

unsigned int Shader::FragmentShader() {
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	return fragmentShader;
}

unsigned int Shader::ShaderProgram(unsigned int &vertexShader,unsigned int &fragmentShader) {
	//1.����
	unsigned int shaderProgram = glCreateProgram();
	//2.��ӳ���
	glAttachShader(shaderProgram,vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	//3.����
	glLinkProgram(shaderProgram);
	//4.��ǰʹ��
	glUseProgram(shaderProgram);
	//5.ɾ��
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return shaderProgram;
}