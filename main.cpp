#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
//use define later

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"layout (location = 2) in vec2 aTex;\n"
"out vec3 color;\n"
"out vec2 texCord;\n"
"uniform float scale;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x*(1.0+scale), aPos.y*(1.0+scale), aPos.z*(1.0+scale), 1.0);\n"
"   color = aColor;\n"
"   texCord = aTex;\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 color;\n"
"in vec2 texCord;\n"
"uniform sampler2D tex0;\n"
"void main()\n"
"{\n"
"   FragColor = texture(tex0, texCord);\n"
"}\n\0";
int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLfloat verticies[] =
	{
		-0.5f,	-0.5f,	0.0f,	1.0f, 0.0f, 0.0f,	0.0f, 0.0f, //0 lower left corner
		0.5f,	-0.5f,	0.0f,	0.0f, 1.0f, 0.0f,	1.0f, 0.0f,//1 lower right corner
		0.25f,	0.5f ,	0.0f,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f,//2 upper corner 
		-0.25f	,0.5f,	0.0f,	1.0f, 1.0f, 1.0f,	0.0f ,1.0f
	};

	GLint indices[] =
	{
		0,2,1, //lower left triangle
		0,3,2, // upper triangle
	};

	GLFWwindow* window = glfwCreateWindow(800, 800, "Client", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "ERROR WINDOW";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0, 0, 800, 800);

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();
	
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//usually an array but we only sending one traingle
	GLuint VAO, VBO, EBO; 
	 
	//buffer going from cpu to GPU
	//VBO is like an ID, it's not storing glarraybuffer into VAO
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO); 
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	//where to start in vertex, how much data in vertex (so we have 3 points), datatype, flase cuz floats, amount of data of each vertex, offset where pointer starts

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//safely unbinds GL_ARRAY_BUFFER and vertex array from their ID VAO and VBO so they aren't modified 
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	GLuint uniId = glGetUniformLocation(shaderProgram, "scale");

	//so GL_ARRAY_BUFFER is modified but we cant change it further 

	//stream modify a multiple times and used once
	//tbh idk
	//static means modified once and used multple times
	//a trangle that will always stay there
	//dynamic means modified multiple and used multipel times
	//moving square


	//this is the back buffer
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f); //set it 
	glClear(GL_COLOR_BUFFER_BIT); //clear buffer of back color information
	//this moves the back buffer to the front buffer to render
	glfwSwapBuffers(window);


	int widthImg, heightImg, numColCh; 
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load("Shark_Texture.png", &widthImg, &heightImg, &numColCh, 0);

	GLuint texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	//float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	//glTexParameterfv(GL_TEXTURE_2D , GL_TEXTURE_BORDER_COLOR, flatColor);


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
	glGenerateMipmap(GL_TEXTURE_2D);

	GLuint tex0Uni = glGetUniformLocation(shaderProgram, "tex0");
	glUniform1i(tex0Uni, 0);
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f); //set it 
		glClear(GL_COLOR_BUFFER_BIT); //clear buffer of back color information
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glUniform1f(uniId, 0.5);
		glBindTexture(GL_TEXTURE_2D,texture);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);
	glDeleteTextures(1, &texture);
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0; 
}