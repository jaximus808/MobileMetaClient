#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/ext.hpp"
#include"Camera.h"

#include"ShaderClass.h"

//use define later

// Vertex Shader source code

int main()
{

	int width = 800; 
	int height = 800; 
	float rotation = 0.0f;

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLfloat verticies[] =
	{
		//Position				//color					//texture map		//normal map
		-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side
		-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
		 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
		 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side

		-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
		-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
		 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,     -0.8f, 0.5f,  0.0f, // Left Side

		-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
		 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
		 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f, -0.8f, // Non-facing side

		 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
		 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
		 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.8f, 0.5f,  0.0f, // Right side

		 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
		-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
		 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f,  0.8f  // Facing side
	};

	////BOTTOM
	//	-0.125f,	-0.25f,	0.125f,		1.0f, 0.0f, 0.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
	//	-0.125f,	-0.25f,	-0.125f,	0.0f, 1.0f, 0.0f,	5.0f, 0.0f,		0.0f, -1.0f, 0.0f,
	//	0.125f,		-0.25f,	-0.125f,	0.0f, 1.0f, 0.0f,	5.0f, 0.0f,		0.0f, -1.0f, 0.0f,
	//	0.125f,		-0.25f,	0.125f,		0.0f, 1.0f, 0.0f,	5.0f, 0.0f,		0.0f, -1.0f, 0.0f,
	//	
	//	//TOP
	//	-0.125f,	0.25f,	0.125f,		1.0f, 0.0f, 0.0f,	0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
	//	-0.125f,	0.25f,	-0.125f,	0.0f, 1.0f, 0.0f,	5.0f, 0.0f,		0.0f, 1.0f, 0.0f,
	//	0.125f,		0.25f,	-0.125f,	0.125f, 1.0f, 0.0f,	5.0f, 0.0f,		0.0f, 1.0f, 0.0f,
	//	0.125f,		0.25f,	0.125f,		0.125f, 1.0f, 0.0f,	5.0f, 0.0f,		0.0f, 1.0f, 0.0f,

	GLint indices[] =
	{
		0, 1, 2, // Bottom side
		0, 2, 3, // Bottom side
		4, 6, 5, // Left side
		7, 9, 8, // Non-facing side
		10, 12, 11, // Right side
		13, 15, 14 // Facing side
	};

	/*0, 1, 2,
		0, 2, 3,

		0, 1, 5,
		0, 4, 5,

		1, 2, 6,
		1, 5, 6,

		2, 3, 7,
		2, 6, 7,

		3, 0, 4,
		3, 7, 4,

		4, 5, 6,
		4, 6, 7,*/
	GLfloat lightVertices[] =
	{ //     COORDINATES     //
		-0.1f, -0.1f,  0.1f,
		-0.1f, -0.1f, -0.1f,
		 0.1f, -0.1f, -0.1f,
		 0.1f, -0.1f,  0.1f,
		-0.1f,  0.1f,  0.1f,
		-0.1f,  0.1f, -0.1f,
		 0.1f,  0.1f, -0.1f,
		 0.1f,  0.1f,  0.1f
	};

	GLuint lightIndices[] =
	{
		0, 1, 2,
		0, 2, 3,
		0, 4, 7,
		0, 7, 3,
		3, 7, 6,
		3, 6, 2,
		2, 6, 5,
		2, 5, 1,
		1, 5, 4,
		1, 4, 0,
		4, 5, 6,
		4, 6, 7
	};
	

	GLFWwindow* window = glfwCreateWindow(width, height, "Client", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "ERROR WINDOW";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0, 0, width, height);

	Shader shaderProgram("default.vert", "default.frag");

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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(3);

	//safely unbinds GL_ARRAY_BUFFER and vertex array from their ID VAO and VBO so they aren't modified 
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	Shader lightShader("light.vert", "light.frag");
	
	GLuint LVAO, LVBO, LEBO;

	//buffer going from cpu to GPU
	//VBO is like an ID, it's not storing glarraybuffer into VAO
	
	glGenVertexArrays(1, &LVAO);
	glGenBuffers(1, &LVBO);
	glGenBuffers(1, &LEBO);

	glBindVertexArray(LVAO);

	glBindBuffer(GL_ARRAY_BUFFER, LVBO);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(lightVertices), lightVertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, LEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(lightIndices), lightIndices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glm::vec4 lightColor = glm::vec4(0.8f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(-0.5f, 0.5f, 0.0f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 boxPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 boxModel = glm::mat4(1.0f);
	boxModel = glm::translate(boxModel, boxPos);

	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);


	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(boxModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	//so GL_ARRAY_BUFFER is modified but we cant change it further 

	//stream modify a multiple times and used once
	//tbh idk
	//static means modified once and used multple times
	//a trangle that will always stay there
	//dynamic means modified multiple and used multipel times
	//moving square



	int widthImg, heightImg, numColCh; 
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load("red_texture.png", &widthImg, &heightImg, &numColCh, STBI_rgb_alpha);

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

	GLuint tex0Uni = glGetUniformLocation(shaderProgram.ID, "tex0");
	shaderProgram.Activate();
	glUniform1i(tex0Uni, 0);

	float prevTime = 0.0f;
	float currentTime = 0.0f;
	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f), window);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f); //set it 
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); //clear buffer of back color information
		

		currentTime = glfwGetTime();
		camera.updateMatrix(45.0f, 0.1f, 100.0f);
		camera.Inputs((currentTime - prevTime) );
		shaderProgram.Activate();
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);

		
		camera.Matrix(shaderProgram, "camMatrix");
		prevTime = currentTime;

		glBindVertexArray(VAO);
		glBindTexture(GL_TEXTURE_2D,texture);
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);

		lightShader.Activate();
		camera.Matrix(lightShader, "camMatrix");
		glBindVertexArray(LVAO);
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	shaderProgram.Delete();
	glDeleteTextures(1, &texture);
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0; 
}