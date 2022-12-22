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
	GLuint texture3, texture4, texture5, texture6, texture7, texture8, texture9, texture10, VBO3, VAO3, EBO3, VBO4, VAO4, EBO4, VBO5, VAO5, EBO5, VBO6, VAO6, EBO6, VBO7, VAO7, EBO7, VAO8, VBO8, EBO8;
	GLuint depthmapShader, shadowmapShader, depthMapFBO, depthMap;

	float viewCamX, viewCamY, viewCamZ, upCamX, upCamY, upCamZ, posCamX, posCamY, posCamZ, CAMERA_SPEED, fovy;
	void MoveCamera(float speed);
	void StrafeCamera(float speed);
	void RotateCamera(float speed);
	void InitCamera();

	void BuildDepthMap();
	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

	float angle = 0;
	virtual void Init();
	virtual void DeInit();
	virtual void Update(double deltaTime);
	virtual void Render();
	virtual void ProcessInput(GLFWwindow *window);
	void BuildColoredCube();
	void BuildLantai();
	void DrawColoredCube();
	void DrawLantai(GLuint shader);
	void BuildDinding();
	void DrawDinding(GLuint shader);
	void BuildPintu();
	void DrawPintu(double posX, double posY, double posZ, double scX, double scY, double scZ, GLuint shader);
	void BuildKarpet();
	void DrawKarpet(double posX, double posY, double posZ, double scX, double scY, double scZ, GLuint shader);

	// Kasur
	void BuildWoods();
	void BuildBlanket();
	void BuildPillow();
	void DrawWoods(double posX, double posY, double posZ, double scX, double scY, double scZ, GLuint shader);
	void DrawBlanket(double posX, double posY, double posZ, double scX, double scY, double scZ, GLuint shader);
	void DrawPillow(double posX, double posY, double posZ, double scX, double scY, double scZ, GLuint shader);

	//Kipas
	void BuildKipas();
	void DrawKipas(double posX, double posY, double posZ, double scX, double scY, double scZ, GLuint shader, int rot);

	//Lampu
	void BuildLampu();
	void DrawLampu(double posX, double posY, double posZ, double scX, double scY, double scZ, GLuint shader);

	void BuildKepalaLampu();
	void DrawKepalaLampu(double posX, double posY, double posZ, double scX, double scY, double scZ, GLuint shader);

	float drawAll = 0;
};

