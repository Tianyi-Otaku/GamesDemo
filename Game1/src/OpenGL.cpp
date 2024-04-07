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
	0.5f, 0.5f, 0.0f,   // 右上角
	0.5f, -0.5f, 0.0f,  // 右下角
	-0.5f, -0.5f, 0.0f, // 左下角
	-0.5f, 0.5f, 0.0f   // 左上角
};


unsigned int indices[] = {
	// 注意索引从0开始! 
	// 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
	// 这样可以由下标代表顶点组合成矩形
	0, 1, 3, // 第一个三角形
	1, 2, 3  // 第二个三角形
};

//初始化
OpenGL::OpenGL() {
	glfwInit();
}	

GLFWwindow* OpenGL::getWindow() {
	//初始化
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//创建窗口
	GLFWwindow * window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	glfwMakeContextCurrent(window);
	//GLAD初始化
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	std::cout << "Failed to initialize GLAD" << std::endl;
	//后配置
	return window;
}

OpenGL::~OpenGL() {
	glfwTerminate();
}

//
unsigned int OpenGL::vertexMap() {
	unsigned int VAO;//顶点数组对象：Vertex Array Object，VAO
	unsigned int VBO;//顶点缓冲对象：Vertex Buffer Object，VBO
	unsigned int EBO;//元素缓冲对象：Element Buffer Object，EBO       或 索引缓冲对象 Index Buffer Object，IBO
	//1.生成
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	//2.绑定
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	//3.设定顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * (sizeof(float)), (void*)0);
	glEnableVertexAttribArray(0);
	return VAO;
}


unsigned int Shader::VertexShader() {
	unsigned int vertexShader;
	//1.创建
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//2.输入数据
	glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
	//3.编译
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
	//1.创建
	unsigned int shaderProgram = glCreateProgram();
	//2.添加程序
	glAttachShader(shaderProgram,vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	//3.链接
	glLinkProgram(shaderProgram);
	//4.当前使用
	glUseProgram(shaderProgram);
	//5.删除
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return shaderProgram;
}