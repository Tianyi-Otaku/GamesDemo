#include"OpenGL.h"
#include"Log.h"

float vertices[] = {
	//     ---- λ�� ----       ---- ��ɫ ----     - �������� -
		0.5f, 0.5f, 0.0f,		 1.0f,0.0f,0.0f,	1.0f,1.0f,			// ���Ͻ�
		0.5f, -0.5f, 0.0f,		0.0f,1.0f,0.0f,		1.0f,0.0f,		   	// ���½�
		-0.5f, -0.5f, 0.0f,		0.0f,0.0f,1.0f,		0.0f,0.0f,			// ���½�
		-0.5f, 0.5f, 0.0f,		1.0f,1.0f,1.0f,		0.0f,1.0f			// ���Ͻ�
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
	if(window == NULL)
	{
		logs.error("Failed to create GLFW window");
		glfwTerminate();
		return NULL;
	}
	glfwMakeContextCurrent(window);
	//GLAD��ʼ��
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		logs.error("Failed to initialize GLAD");
		//std::cout << "Failed to initialize GLAD" << std::endl;
	//������
	return window;
}
OpenGL::~OpenGL() {
	glfwTerminate();
}

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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * (sizeof(float)), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * (sizeof(float)), (void*)(3 * (sizeof(float))));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * (sizeof(float)), (void*)(6 * (sizeof(float))));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	return VAO;
}

std::string Shader::ShaderSource(std::string dataPath) {
	std::ifstream fin;
	fin.open(dataPath);
	if (fin.is_open() == false) {
		logs.error("���󣺴��ļ�ʧ��:" + dataPath);
		return nullptr;
	}
	else {
		std::string data;
		char tmp[1024];
		while (fin.getline(tmp,1024)) {
			data += tmp;
			data += '\n';
		}
		return data;
	}
}
unsigned int Shader::VertexShader(std::string shaderSourcePath) {
	std::string data = ShaderSource(shaderSourcePath);
	const char* vertexShaderSource = data.c_str();
	unsigned int vertexShader;
	//1.����
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//2.��������
	glShaderSource(vertexShader,1,&vertexShaderSource, NULL);
	//3.����
	glCompileShader(vertexShader);
	//���
	int  success;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		logs.error("ERROR::SHADER::VERTEX::COMPILATION_FAILED");
	}
	return vertexShader;
}
unsigned int Shader::FragmentShader(std::string shaderSourcePath) {
	std::string data = ShaderSource(shaderSourcePath);
	const char* fragmentShaderSource = data.c_str();
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	//���
	int  success;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		logs.error("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED");
	}
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

	//���
	int  success;
	glGetProgramiv(shaderProgram, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		logs.error("ERROR::PROGRAM::FAILED");
	}
	return shaderProgram;
}