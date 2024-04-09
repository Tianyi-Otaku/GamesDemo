#include"OpenGL.h"
#include"Log.h"

float vertices[] = {
	//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
		0.5f, 0.5f, 0.0f,		 1.0f,0.0f,0.0f,	1.0f,1.0f,			// 右上角
		0.5f, -0.5f, 0.0f,		0.0f,1.0f,0.0f,		1.0f,0.0f,		   	// 右下角
		-0.5f, -0.5f, 0.0f,		0.0f,0.0f,1.0f,		0.0f,0.0f,			// 左下角
		-0.5f, 0.5f, 0.0f,		1.0f,1.0f,1.0f,		0.0f,1.0f			// 左上角
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
	if(window == NULL)
	{
		logs.error("Failed to create GLFW window");
		glfwTerminate();
		return NULL;
	}
	glfwMakeContextCurrent(window);
	//GLAD初始化
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		logs.error("Failed to initialize GLAD");
		//std::cout << "Failed to initialize GLAD" << std::endl;
	//后配置
	return window;
}
OpenGL::~OpenGL() {
	glfwTerminate();
}

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
		logs.error("错误：打开文件失败:" + dataPath);
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
	//1.创建
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//2.输入数据
	glShaderSource(vertexShader,1,&vertexShaderSource, NULL);
	//3.编译
	glCompileShader(vertexShader);
	//检错
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
	//检错
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

	//检错
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