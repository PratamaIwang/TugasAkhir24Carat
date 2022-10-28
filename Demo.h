#pragma once
#include "RenderEngine.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <SOIL/SOIL.h>
#include <vector>

class Demo :
	public RenderEngine
{
public:
	Demo();
	~Demo();
private:
	GLuint shaderProgram, VBO, VAO, EBO, texture, VBO2, VAO2, EBO2, texture2;
		
	float angle = 0;
	float pindahX = 0;
	float pindahZ = 0;
	std::vector< float > xArr;
	std::vector< float > zArr;
	int index = 0;
	int totalPoin = 1000;
	virtual void Init();
	virtual void DeInit();
	virtual void Update(double deltaTime);
	virtual void Render();
	virtual void ProcessInput(GLFWwindow *window);
	void BuildColoredCube();
	void BuildColoredPlane();
	void DrawColoredCube();
	void DrawColoredPlane();
	void DrawBezier();

	// Kasur
	GLuint texture3, texture4, texture5, VBO3, VAO3, EBO3, VBO4, VAO4, EBO4, VBO5, VAO5, EBO5;
	void BuildWoods();
	void BuildBlanket();
	void BuildPillow();
	void DrawWoods(double posX, double posY, double posZ, double scX, double scY, double scZ);
	void DrawBlanket();
	void DrawPillow();
};

