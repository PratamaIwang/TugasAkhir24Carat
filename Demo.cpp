#include "Demo.h"
#include <vector>

Demo::Demo() {

}
Demo::~Demo() {
}

void Demo::Init() {
	// build and compile our shader program
	// ------------------------------------
	shadowmapShader = BuildShader("shadowMapping.vert", "shadowMapping.frag", nullptr);
	depthmapShader = BuildShader("depthMap.vert", "depthMap.frag", nullptr);

	BuildLantai();

	//BuildDinding();
	//BuildPintu();
	//BuildBlanket();
	//BuildPillow();
	//BuildWoods();
	//BuildKarpet();
	//BuildKipas();
	//BuildLampu();
	//BuildKepalaLampu();

	InitCamera();
	BuildDepthMap();
}
void Demo::DeInit() {
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO2);
	glDeleteBuffers(1, &VBO2);
	glDeleteBuffers(1, &EBO2);
	glDeleteVertexArrays(1, &VAO3);
	glDeleteBuffers(1, &VBO3);
	glDeleteBuffers(1, &EBO3);
	glDeleteVertexArrays(1, &VAO4);
	glDeleteBuffers(1, &VBO4);
	glDeleteBuffers(1, &EBO4);
	glDeleteVertexArrays(1, &VAO5);
	glDeleteBuffers(1, &VBO5);
	glDeleteBuffers(1, &EBO5);
}

void Demo::ProcessInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	// zoom camera
	// -----------
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		if (fovy < 90) {
			fovy += 0.0001f;
		}
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		if (fovy > 0) {
			fovy -= 0.0001f;
		}
	}

	// update camera movement 
	// -------------
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		MoveCamera(CAMERA_SPEED);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		MoveCamera(-CAMERA_SPEED);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		StrafeCamera(-CAMERA_SPEED);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		StrafeCamera(CAMERA_SPEED);
	}

	// update camera rotation
	// ----------------------
	double mouseX, mouseY;
	double midX = screenWidth / 2;
	double midY = screenHeight / 2;
	float angleY = 0.0f;
	float angleZ = 0.0f;

	// Get mouse position
	glfwGetCursorPos(window, &mouseX, &mouseY);
	if ((mouseX == midX) && (mouseY == midY)) {
		return;
	}

	// Set mouse position
	glfwSetCursorPos(window, midX, midY);

	// Get the direction from the mouse cursor, set a resonable maneuvering speed
	angleY = (float)((midX - mouseX)) / 1000;
	angleZ = (float)((midY - mouseY)) / 1000;

	// The higher the value is the faster the camera looks around.
	viewCamY += angleZ * 2;

	// limit the rotation around the x-axis
	if ((viewCamY - posCamY) > 8) {
		viewCamY = posCamY + 8;
	}
	if ((viewCamY - posCamY) < -8) {
		viewCamY = posCamY - 8;
	}
	RotateCamera(-angleY);



}

void Demo::Update(double deltaTime) {
	angle += (float)((deltaTime * 1.5f) / 500);
}

void Demo::Render() {
	glEnable(GL_DEPTH_TEST);

	glm::mat4 lightProjection, lightView;
	glm::mat4 lightSpaceMatrix;
	float near_plane = 1.0f, far_plane = 7.5f;
	lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
	lightView = glm::lookAt(glm::vec3(17.0f, 6.0f, -3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0, 1.0, 0.0));
	lightSpaceMatrix = lightProjection * lightView;

	// render scene from light's point of view
	UseShader(this->depthmapShader);
	glUniformMatrix4fv(glGetUniformLocation(this->depthmapShader, "lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));
	glViewport(0, 0, this->SHADOW_WIDTH, this->SHADOW_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);

	// Kasur
	DrawWoods(14.8, 1, -15, 10, 0.5, 6, this->depthmapShader);
	DrawWoods(9.6, 1, -15, 0.5, 3, 6.2, this->depthmapShader);
	DrawWoods(20, 1, -15, 0.5, 3, 6.2, this->depthmapShader);
	DrawBlanket(12.8, 1.5, -15, 6, 0.5, 6, this->depthmapShader);
	DrawPillow(17.6, 1.5, -15, 4, 0.5, 6, this->depthmapShader);

	// Meja
	DrawWoods(18, 0.5, -10, 4, 4, 0.5, this->depthmapShader);
	DrawWoods(18, 2.6, -7.1, 4, 0.25, 7, this->depthmapShader);
	DrawWoods(18, 0.5, -4, 4, 4, 0.5, this->depthmapShader);

	// Kursi
	DrawWoods(13, 0.5, -7.5, 0.25, 4, 2, this->depthmapShader);
	DrawWoods(14, 1.3, -7.5, 2, 0.25, 2, this->depthmapShader);
	DrawWoods(15, 0.5, -7.5, 0.25, 1.5, 2, this->depthmapShader);

	// Kipas
	DrawKipas(0, 20, -5, 1, 2, 1, this->depthmapShader, 0);
	DrawKipas(0, 19, -5, 10, 0.2, 1, this->depthmapShader, 1);
	DrawKipas(0, 19, -5, 1, 0.2, 10, this->depthmapShader, 1);

	// Lampu
	DrawLampu(18, 0.5, -1, 0.2, 10, 0.2, this->depthmapShader);
	DrawLampu(18, 0, -1, 2, 0.2, 2, this->depthmapShader);
	DrawKepalaLampu(18, 6, -1, 2, 2, 2, this->depthmapShader);


	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glViewport(0, 0, this->screenWidth, this->screenHeight);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Pass perspective projection matrix
	UseShader(this->shadowmapShader);
	glm::mat4 projection = glm::perspective(fovy, (GLfloat)this->screenWidth / (GLfloat)this->screenHeight, 0.1f, 100.0f);
	GLint projLoc = glGetUniformLocation(this->shadowmapShader, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	// LookAt camera (position, target/direction, up)
	glm::mat4 view = glm::lookAt(glm::vec3(posCamX, posCamY, posCamZ), glm::vec3(viewCamX, viewCamY, viewCamZ), glm::vec3(upCamX, upCamY, upCamZ));
	GLint viewLoc = glGetUniformLocation(this->shadowmapShader, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	// Setting Light Attributes
	glUniformMatrix4fv(glGetUniformLocation(this->shadowmapShader, "lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));
	glUniform3f(glGetUniformLocation(this->shadowmapShader, "viewPos"), posCamX, posCamY, posCamZ);
	glUniform3f(glGetUniformLocation(this->shadowmapShader, "lightPos"), -2.0f, 4.0f, -1.0f);

	// Configure Shaders
	glUniform1i(glGetUniformLocation(this->shadowmapShader, "diffuseTexture"), 0);
	glUniform1i(glGetUniformLocation(this->shadowmapShader, "shadowMap"), 1);

	DrawLantai(this->shadowmapShader);
	
	// Dinding & Pintu
	DrawPintu(-15, 4, -20, 5, 10, 0.1, this->shadowmapShader);
	DrawDinding(this->shadowmapShader);

	// Karpet
	DrawKarpet(12.5, -0.4, -4.4, 15, 0.2, 15, this->shadowmapShader);

	// Kasur
	DrawWoods(14.8, 1, -15, 10, 0.5, 6, this->shadowmapShader);
	DrawWoods(9.6, 1, -15, 0.5, 3, 6.2, this->shadowmapShader);
	DrawWoods(20, 1, -15, 0.5, 3, 6.2, this->shadowmapShader);
	DrawBlanket(12.8, 1.5, -15, 6, 0.5, 6, this->shadowmapShader);
	DrawPillow(17.6, 1.5, -15, 4, 0.5, 6, this->shadowmapShader);

	// Meja
	DrawWoods(18, 0.5, -10, 4, 4, 0.5, this->shadowmapShader);
	DrawWoods(18, 2.6, -7.1, 4, 0.25, 7, this->shadowmapShader);
	DrawWoods(18, 0.5, -4, 4, 4, 0.5, this->shadowmapShader);

	// Kursi
	DrawWoods(13, 0.5, -7.5, 0.25, 4, 2, this->shadowmapShader);
	DrawWoods(14, 1.3, -7.5, 2, 0.25, 2, this->shadowmapShader);
	DrawWoods(15, 0.5, -7.5, 0.25, 1.5, 2, this->shadowmapShader);
	
	// Kipas
	DrawKipas(0, 20, -5, 1, 2, 1, this->shadowmapShader, 0);
	DrawKipas(0, 19, -5, 10, 0.2, 1, this->shadowmapShader, 1);
	DrawKipas(0, 19, -5, 1, 0.2, 10, this->shadowmapShader, 1);

	// Lampu
	DrawLampu(18, 0.5, -1, 0.2, 10, 0.2, this->shadowmapShader);
	DrawLampu(18, 0, -1, 2, 0.2, 2, this->shadowmapShader);
	DrawKepalaLampu(18, 6, -1, 2, 2, 2, this->shadowmapShader);

	glDisable(GL_DEPTH_TEST);
}

void Demo::BuildPintu() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("pintu3.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords

		// front
		-0.5, -0.5, 0.5, 0, 0, 0.0f,  0.0f,  1.0f,  // 0
		0.5, -0.5, 0.5, 1, 0, 0.0f,  0.0f,  1.0f,  // 1
		0.5,  0.5, 0.5, 1, 1, 0.0f,  0.0f,  1.0f,  // 2
		-0.5,  0.5, 0.5, 0, 1, 0.0f,  0.0f,  1.0f, // 3

		// right
		0.5,  0.5,  0.5, 0, 0, 1.0f,  0.0f,  0.0f, // 4
		0.5,  0.5, -0.5, 1, 0, 1.0f,  0.0f,  0.0f, // 5
		0.5, -0.5, -0.5, 1, 1, 1.0f,  0.0f,  0.0f,  // 6
		0.5, -0.5,  0.5, 0, 1, 1.0f,  0.0f,  0.0f, // 7

		// back
		-0.5, -0.5, -0.5, 0, 0, 0.0f,  0.0f,  -1.0f, // 8 
		0.5,  -0.5, -0.5, 1, 0, 0.0f,  0.0f,  -1.0f, // 9
		0.5,   0.5, -0.5, 1, 1, 0.0f,  0.0f,  -1.0f, // 10
		-0.5,  0.5, -0.5, 0, 1, 0.0f,  0.0f,  -1.0f, // 11

		// left
		-0.5, -0.5, -0.5, 0, 0, -1.0f,  0.0f,  0.0f, // 12
		-0.5, -0.5,  0.5, 1, 0, -1.0f,  0.0f,  0.0f, // 13
		-0.5,  0.5,  0.5, 1, 1, -1.0f,  0.0f,  0.0f, // 14
		-0.5,  0.5, -0.5, 0, 1, -1.0f,  0.0f,  0.0f, // 15

		// upper
		 0.5, 0.5,  0.5, 0, 0, 0.0f,  1.0f,  0.0f,  // 16
		-0.5, 0.5,  0.5, 1, 0, 0.0f,  1.0f,  0.0f, // 17
		-0.5, 0.5, -0.5, 1, 1, 0.0f,  1.0f,  0.0f, // 18
		 0.5, 0.5, -0.5, 0, 1, 0.0f,  1.0f,  0.0f,  // 19

		// bottom
		-0.5, -0.5, -0.5, 0, 0, 0.0f,  -1.0f,  0.0f, // 20
		 0.5, -0.5, -0.5, 1, 0, 0.0f,  -1.0f,  0.0f, // 21
		 0.5, -0.5,  0.5, 1, 1, 0.0f,  -1.0f,  0.0f, // 22
		-0.5, -0.5,  0.5, 0, 1, 0.0f,  -1.0f,  0.0f, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO3);
	glGenBuffers(1, &VBO3);
	glGenBuffers(1, &EBO3);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO3);

	glBindBuffer(GL_ARRAY_BUFFER, VBO3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO3);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define normal pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	
	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void Demo::DrawPintu(double posX, double posY, double posZ, double scX, double scY, double scZ, GLuint shader)
{
	UseShader(shader);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glBindVertexArray(VAO3);

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(posX, posY, posZ));
	model = glm::scale(model, glm::vec3(scX, scY, scZ));

	GLint modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildDinding()
{
	// Load and create a texture 
	glGenTextures(1, &texture6);
	glBindTexture(GL_TEXTURE_2D, texture6);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image("dinding2.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Build geometry
	GLfloat vertices[] = {
		// format position, tex coords
		// back
		-20.0, -0.5, -20.0,  0,  0, 0.0f,  0.0f,  -1.0f, //0
		-20.0, 20.5, -20.0, 1,  0, 0.0f,  0.0f,  -1.0f, //1
		 20.0, 20.5, -20.0, 1, 1, 0.0f,  0.0f,  -1.0f, //2
		 20.0, -0.5, -20.0,  0, 1, 0.0f,  0.0f,  -1.0f, //3

		 // left
		-20.0, -0.5,  20.0, 0, 0, -1.0f,  0.0f,  0.0f, //4
		-20.0, 20.5,  20.0, 1, 0, -1.0f,  0.0f,  0.0f, //5
		-20.0, 20.5, -20.0, 1, 1, -1.0f,  0.0f,  0.0f, //6
		-20.0, -0.5, -20.0, 0, 1, -1.0f,  0.0f,  0.0f, //7

		//right
		20.0, -0.5, -20.0, 0, 0, 1.0f,  0.0f,  0.0f, //8
		20.0, 20.5, -20.0, 1, 0, 1.0f,  0.0f,  0.0f, //9
		20.0, 20.5,  20.0, 1, 1, 1.0f,  0.0f,  0.0f, //10
		20.0, -0.5,  20.0, 0, 1, 1.0f,  0.0f,  0.0f, //11

		//top
		-20.0, 20.5,  20.0, 0, 0, 0.0f,  1.0f,  0.0f, //12
		-20.0, 20.5, -20.0, 1, 0, 0.0f,  1.0f,  0.0f, //13
		 20.0, 20.5, -20.0, 1, 1, 0.0f,  1.0f,  0.0f, //14
		 20.0, 20.5,  20.0, 0, 1, 0.0f,  1.0f,  0.0f, //15
	};

	GLuint indices[] = { 0,  2,  1,  0,  3,  2,  4,  6,  5,  4,  7,  6,  8,  10,  9,  8,  11,  10,  12,  14,  13,  12,  15,  14,};

	glGenVertexArrays(1, &VAO2);
	glGenBuffers(1, &VBO2);
	glGenBuffers(1, &EBO2);

	glBindVertexArray(VAO2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);

	// TexCoord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define normal pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);


	glBindVertexArray(0); // Unbind VAO
}
void Demo::DrawDinding(GLuint shader)
{
	UseShader(shader);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture6);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);

	glBindVertexArray(VAO2); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	GLint modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildLantai()
{
	// Load and create a texture 
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image("ubin3.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Build geometry
	GLfloat vertices[] = {
		// format position, tex coords
		// bottom
		-20.0, -0.5, -20.0,  0,  0, 0.0f,  1.0f,  0.0f,
		 20.0, -0.5, -20.0, 20,  0, 0.0f,  1.0f,  0.0f,
		 20.0, -0.5,  20.0, 20, 20, 0.0f,  1.0f,  0.0f,
		-20.0, -0.5,  20.0,  0, 20, 0.0f,  1.0f,  0.0f,
	};

	GLuint indices[] = { 0,  2,  1,  0,  3,  2,};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// TexCoord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define normal pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);


	glBindVertexArray(0); // Unbind VAO
}
void Demo::DrawLantai(GLuint shader)
{
	UseShader(shader);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);

	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	GLint modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildWoods() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture3);
	glBindTexture(GL_TEXTURE_2D, texture3);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("wooden.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords

		// front
		-0.5, -0.5, 0.5, 0, 0, 0.0f,  0.0f,  1.0f, // 0
		 0.5, -0.5, 0.5, 1, 0, 0.0f,  0.0f,  1.0f,  // 1
		 0.5,  0.5, 0.5, 1, 1, 0.0f,  0.0f,  1.0f,  // 2
		-0.5,  0.5, 0.5, 0, 1, 0.0f,  0.0f,  1.0f, // 3

		// right
		0.5,  0.5,  0.5, 0, 0, 1.0f,  0.0f,  0.0f, // 4
		0.5,  0.5, -0.5, 1, 0, 1.0f,  0.0f,  0.0f, // 5
		0.5, -0.5, -0.5, 1, 1, 1.0f,  0.0f,  0.0f, // 6
		0.5, -0.5,  0.5, 0, 1, 1.0f,  0.0f,  0.0f, // 7

		// back
		-0.5, -0.5, -0.5, 0, 0, 0.0f,  0.0f,  -1.0f, // 8 
		0.5,  -0.5, -0.5, 1, 0, 0.0f,  0.0f,  -1.0f, // 9
		0.5,   0.5, -0.5, 1, 1, 0.0f,  0.0f,  -1.0f, // 10
		-0.5,  0.5, -0.5, 0, 1, 0.0f,  0.0f,  -1.0f, // 11

		// left
		-0.5, -0.5, -0.5, 0, 0, -1.0f,  0.0f,  0.0f, // 12
		-0.5, -0.5,  0.5, 1, 0, -1.0f,  0.0f,  0.0f, // 13
		-0.5,  0.5,  0.5, 1, 1, -1.0f,  0.0f,  0.0f, // 14
		-0.5,  0.5, -0.5, 0, 1, -1.0f,  0.0f,  0.0f, // 15

		// upper
		 0.5, 0.5,  0.5, 0, 0, 0.0f,  1.0f,  0.0f,  // 16
		-0.5, 0.5,  0.5, 1, 0, 0.0f,  1.0f,  0.0f, // 17
		-0.5, 0.5, -0.5, 1, 1, 0.0f,  1.0f,  0.0f, // 18
		 0.5, 0.5, -0.5, 0, 1, 0.0f,  1.0f,  0.0f,  // 19

		// bottom
		-0.5, -0.5, -0.5, 0, 0, 0.0f,  -1.0f,  0.0f, // 20
		 0.5, -0.5, -0.5, 1, 0, 0.0f,  -1.0f,  0.0f, // 21
		 0.5, -0.5,  0.5, 1, 1, 0.0f,  -1.0f,  0.0f, // 22
		-0.5, -0.5,  0.5, 0, 1, 0.0f,  -1.0f,  0.0f, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO3);
	glGenBuffers(1, &VBO3);
	glGenBuffers(1, &EBO3);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO3);

	glBindBuffer(GL_ARRAY_BUFFER, VBO3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO3);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define normal pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);


	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
void Demo::DrawWoods(double posX, double posY, double posZ, double scX, double scY, double scZ, GLuint shader)
{
	UseShader(shader);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture3);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glBindVertexArray(VAO3);

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(posX, posY, posZ));
	model = glm::scale(model, glm::vec3(scX, scY, scZ));

	GLint modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildBlanket() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture4);
	glBindTexture(GL_TEXTURE_2D, texture4);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("blanket.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords

		// front
		-0.5, -0.5, 0.5, 0, 0, 0.0f,  0.0f,  1.0f, // 0
		 0.5, -0.5, 0.5, 1, 0, 0.0f,  0.0f,  1.0f,  // 1
		 0.5,  0.5, 0.5, 1, 1, 0.0f,  0.0f,  1.0f,  // 2
		-0.5,  0.5, 0.5, 0, 1, 0.0f,  0.0f,  1.0f, // 3

		// right
		0.5,  0.5,  0.5, 0, 0, 1.0f,  0.0f,  0.0f, // 4
		0.5,  0.5, -0.5, 1, 0, 1.0f,  0.0f,  0.0f, // 5
		0.5, -0.5, -0.5, 1, 1, 1.0f,  0.0f,  0.0f, // 6
		0.5, -0.5,  0.5, 0, 1, 1.0f,  0.0f,  0.0f, // 7

		// back
		-0.5, -0.5, -0.5, 0, 0, 0.0f,  0.0f,  -1.0f, // 8 
		0.5,  -0.5, -0.5, 1, 0, 0.0f,  0.0f,  -1.0f, // 9
		0.5,   0.5, -0.5, 1, 1, 0.0f,  0.0f,  -1.0f, // 10
		-0.5,  0.5, -0.5, 0, 1, 0.0f,  0.0f,  -1.0f, // 11

		// left
		-0.5, -0.5, -0.5, 0, 0, -1.0f,  0.0f,  0.0f, // 12
		-0.5, -0.5,  0.5, 1, 0, -1.0f,  0.0f,  0.0f, // 13
		-0.5,  0.5,  0.5, 1, 1, -1.0f,  0.0f,  0.0f, // 14
		-0.5,  0.5, -0.5, 0, 1, -1.0f,  0.0f,  0.0f, // 15

		// upper
		 0.5, 0.5,  0.5, 0, 0, 0.0f,  1.0f,  0.0f,  // 16
		-0.5, 0.5,  0.5, 1, 0, 0.0f,  1.0f,  0.0f, // 17
		-0.5, 0.5, -0.5, 1, 1, 0.0f,  1.0f,  0.0f, // 18
		 0.5, 0.5, -0.5, 0, 1, 0.0f,  1.0f,  0.0f,  // 19

		// bottom
		-0.5, -0.5, -0.5, 0, 0, 0.0f,  -1.0f,  0.0f,// 20
		 0.5, -0.5, -0.5, 1, 0, 0.0f,  -1.0f,  0.0f, // 21
		 0.5, -0.5,  0.5, 1, 1, 0.0f,  -1.0f,  0.0f, // 22
		-0.5, -0.5,  0.5, 0, 1, 0.0f,  -1.0f,  0.0f,// 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO4);
	glGenBuffers(1, &VBO4);
	glGenBuffers(1, &EBO4);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO4);

	glBindBuffer(GL_ARRAY_BUFFER, VBO4);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO4);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define normal pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);


	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
void Demo::DrawBlanket(double posX, double posY, double posZ, double scX, double scY, double scZ, GLuint shader)
{
	UseShader(shader);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture4);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glBindVertexArray(VAO4);

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(posX, posY, posZ));
	model = glm::scale(model, glm::vec3(scX, scY, scZ));

	GLint modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildPillow() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture5);
	glBindTexture(GL_TEXTURE_2D, texture5);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("pillow.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords

		// front
		-0.5, -0.5, 0.5, 0, 0, 0.0f,  0.0f,  1.0f, // 0
		 0.5, -0.5, 0.5, 1, 0, 0.0f,  0.0f,  1.0f, // 1
		 0.5,  0.5, 0.5, 1, 1, 0.0f,  0.0f,  1.0f, // 2
		-0.5,  0.5, 0.5, 0, 1, 0.0f,  0.0f,  1.0f, // 3

		// right
		0.5,  0.5,  0.5, 0, 0, 1.0f,  0.0f,  0.0f, // 4
		0.5,  0.5, -0.5, 1, 0, 1.0f,  0.0f,  0.0f, // 5
		0.5, -0.5, -0.5, 1, 1, 1.0f,  0.0f,  0.0f, // 6
		0.5, -0.5,  0.5, 0, 1, 1.0f,  0.0f,  0.0f, // 7

		// back
		-0.5, -0.5, -0.5, 0, 0, 0.0f,  0.0f,  -1.0f, // 8 
		0.5,  -0.5, -0.5, 1, 0, 0.0f,  0.0f,  -1.0f, // 9
		0.5,   0.5, -0.5, 1, 1, 0.0f,  0.0f,  -1.0f, // 10
		-0.5,  0.5, -0.5, 0, 1, 0.0f,  0.0f,  -1.0f, // 11

		// left
		-0.5, -0.5, -0.5, 0, 0, -1.0f,  0.0f,  0.0f, // 12
		-0.5, -0.5,  0.5, 1, 0, -1.0f,  0.0f,  0.0f, // 13
		-0.5,  0.5,  0.5, 1, 1, -1.0f,  0.0f,  0.0f, // 14
		-0.5,  0.5, -0.5, 0, 1, -1.0f,  0.0f,  0.0f, // 15

		// upper
		 0.5, 0.5,  0.5, 0, 0, 0.0f,  1.0f,  0.0f,  // 16
		-0.5, 0.5,  0.5, 1, 0, 0.0f,  1.0f,  0.0f, // 17
		-0.5, 0.5, -0.5, 1, 1, 0.0f,  1.0f,  0.0f, // 18
		 0.5, 0.5, -0.5, 0, 1, 0.0f,  1.0f,  0.0f,  // 19

		// bottom
		-0.5, -0.5, -0.5, 0, 0, 0.0f,  -1.0f,  0.0f, // 20
		 0.5, -0.5, -0.5, 1, 0, 0.0f,  -1.0f,  0.0f, // 21
		 0.5, -0.5,  0.5, 1, 1, 0.0f,  -1.0f,  0.0f, // 22
		-0.5, -0.5,  0.5, 0, 1, 0.0f,  -1.0f,  0.0f, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO5);
	glGenBuffers(1, &VBO5);
	glGenBuffers(1, &EBO5);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO5);

	glBindBuffer(GL_ARRAY_BUFFER, VBO5);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO5);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define normal pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
void Demo::DrawPillow(double posX, double posY, double posZ, double scX, double scY, double scZ, GLuint shader)
{
	UseShader(shader);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture5);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glBindVertexArray(VAO5);

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(posX, posY, posZ));
	model = glm::scale(model, glm::vec3(scX, scY, scZ));

	GLint modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildKarpet() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture7);
	glBindTexture(GL_TEXTURE_2D, texture7);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("karpet.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords

		// front
		-0.5, -0.5, 0.5, 0, 0, 0.0f,  0.0f,  1.0f,  // 0
		 0.5, -0.5, 0.5, 1, 0, 0.0f,  0.0f,  1.0f,  // 1
		 0.5,  0.5, 0.5, 1, 1, 0.0f,  0.0f,  1.0f,  // 2
		-0.5,  0.5, 0.5, 0, 1, 0.0f,  0.0f,  1.0f,  // 3

		// right
		0.5,  0.5,  0.5, 0, 0, 1.0f,  0.0f,  0.0f, // 4
		0.5,  0.5, -0.5, 1, 0, 1.0f,  0.0f,  0.0f, // 5
		0.5, -0.5, -0.5, 1, 1, 1.0f,  0.0f,  0.0f, // 6
		0.5, -0.5,  0.5, 0, 1, 1.0f,  0.0f,  0.0f, // 7

		// back
		-0.5, -0.5, -0.5, 0, 0, 0.0f,  0.0f,  -1.0f, // 8 
		0.5,  -0.5, -0.5, 1, 0, 0.0f,  0.0f,  -1.0f, // 9
		0.5,   0.5, -0.5, 1, 1, 0.0f,  0.0f,  -1.0f, // 10
		-0.5,  0.5, -0.5, 0, 1, 0.0f,  0.0f,  -1.0f, // 11

		// left
		-0.5, -0.5, -0.5, 0, 0, -1.0f,  0.0f,  0.0f, // 12
		-0.5, -0.5,  0.5, 1, 0, -1.0f,  0.0f,  0.0f, // 13
		-0.5,  0.5,  0.5, 1, 1, -1.0f,  0.0f,  0.0f, // 14
		-0.5,  0.5, -0.5, 0, 1, -1.0f,  0.0f,  0.0f, // 15

		// upper
		 0.5, 0.5,  0.5, 0, 0, 0.0f,  1.0f,  0.0f,   // 16
		-0.5, 0.5,  0.5, 1, 0, 0.0f,  1.0f,  0.0f,  // 17
		-0.5, 0.5, -0.5, 1, 1, 0.0f,  1.0f,  0.0f,  // 18
		 0.5, 0.5, -0.5, 0, 1, 0.0f,  1.0f,  0.0f,   // 19

		// bottom
		-0.5, -0.5, -0.5, 0, 0, 0.0f,  -1.0f,  0.0f, // 20
		 0.5, -0.5, -0.5, 1, 0, 0.0f,  -1.0f,  0.0f, // 21
		 0.5, -0.5,  0.5, 1, 1, 0.0f,  -1.0f,  0.0f, // 22
		-0.5, -0.5,  0.5, 0, 1, 0.0f,  -1.0f,  0.0f, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO6);
	glGenBuffers(1, &VBO6);
	glGenBuffers(1, &EBO6);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO6);

	glBindBuffer(GL_ARRAY_BUFFER, VBO6);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO6);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define normal pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);


	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void Demo::DrawKarpet(double posX, double posY, double posZ, double scX, double scY, double scZ, GLuint shader) {
	UseShader(shader);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture7);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);

	glBindVertexArray(VAO6);

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(posX, posY, posZ));
	model = glm::scale(model, glm::vec3(scX, scY, scZ));

	GLint modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildKipas() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture8);
	glBindTexture(GL_TEXTURE_2D, texture8);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("kipas.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords

		// front
		-0.5, -0.5, 0.5, 0, 0, 0.0f,  0.0f,  1.0f,  // 0
		 0.5, -0.5, 0.5, 1, 0, 0.0f,  0.0f,  1.0f,  // 1
		 0.5,  0.5, 0.5, 1, 1, 0.0f,  0.0f,  1.0f,  // 2
		-0.5,  0.5, 0.5, 0, 1, 0.0f,  0.0f,  1.0f,  // 3

		// right
		0.5,  0.5,  0.5, 0, 0, 1.0f,  0.0f,  0.0f, // 4
		0.5,  0.5, -0.5, 1, 0, 1.0f,  0.0f,  0.0f, // 5
		0.5, -0.5, -0.5, 1, 1, 1.0f,  0.0f,  0.0f, // 6
		0.5, -0.5,  0.5, 0, 1, 1.0f,  0.0f,  0.0f, // 7

		// back
		-0.5, -0.5, -0.5, 0, 0, 0.0f,  0.0f,  -1.0f, // 8 
		0.5,  -0.5, -0.5, 1, 0, 0.0f,  0.0f,  -1.0f, // 9
		0.5,   0.5, -0.5, 1, 1, 0.0f,  0.0f,  -1.0f, // 10
		-0.5,  0.5, -0.5, 0, 1, 0.0f,  0.0f,  -1.0f, // 11

		// left
		-0.5, -0.5, -0.5, 0, 0, -1.0f,  0.0f,  0.0f, // 12
		-0.5, -0.5,  0.5, 1, 0, -1.0f,  0.0f,  0.0f, // 13
		-0.5,  0.5,  0.5, 1, 1, -1.0f,  0.0f,  0.0f, // 14
		-0.5,  0.5, -0.5, 0, 1, -1.0f,  0.0f,  0.0f, // 15

		// upper
		 0.5, 0.5,  0.5, 0, 0, 0.0f,  1.0f,  0.0f,   // 16
		-0.5, 0.5,  0.5, 1, 0, 0.0f,  1.0f,  0.0f,  // 17
		-0.5, 0.5, -0.5, 1, 1, 0.0f,  1.0f,  0.0f,  // 18
		 0.5, 0.5, -0.5, 0, 1, 0.0f,  1.0f,  0.0f,   // 19

		 // bottom
		 -0.5, -0.5, -0.5, 0, 0, 0.0f,  -1.0f,  0.0f, // 20
		  0.5, -0.5, -0.5, 1, 0, 0.0f,  -1.0f,  0.0f, // 21
		  0.5, -0.5,  0.5, 1, 1, 0.0f,  -1.0f,  0.0f, // 22
		 -0.5, -0.5,  0.5, 0, 1, 0.0f,  -1.0f,  0.0f, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO7);
	glGenBuffers(1, &VBO7);
	glGenBuffers(1, &EBO7);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO7);

	glBindBuffer(GL_ARRAY_BUFFER, VBO7);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO7);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define normal pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);


	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void Demo::DrawKipas(double posX, double posY, double posZ, double scX, double scY, double scZ, GLuint shader, int rot) {
	UseShader(shader);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture8);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);

	glBindVertexArray(VAO7);

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(posX, posY, posZ));
	
	if (rot == 1) {
		model = glm::rotate(model, angle, glm::vec3(0, 1, 0));
	}
	else if (rot == 2) {
		model = glm::rotate(model, angle, glm::vec3(0, 0, 1));
	}
	
	model = glm::scale(model, glm::vec3(scX, scY, scZ));

	GLint modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildLampu() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture9);
	glBindTexture(GL_TEXTURE_2D, texture9);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("lampu.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords

		// front
		-0.5, -0.5, 0.5, 0, 0, 0.0f,  0.0f,  1.0f,  // 0
		 0.5, -0.5, 0.5, 1, 0, 0.0f,  0.0f,  1.0f,  // 1
		 0.5,  0.5, 0.5, 1, 1, 0.0f,  0.0f,  1.0f,  // 2
		-0.5,  0.5, 0.5, 0, 1, 0.0f,  0.0f,  1.0f,  // 3

		// right
		0.5,  0.5,  0.5, 0, 0, 1.0f,  0.0f,  0.0f, // 4
		0.5,  0.5, -0.5, 1, 0, 1.0f,  0.0f,  0.0f, // 5
		0.5, -0.5, -0.5, 1, 1, 1.0f,  0.0f,  0.0f, // 6
		0.5, -0.5,  0.5, 0, 1, 1.0f,  0.0f,  0.0f, // 7

		// back
		-0.5, -0.5, -0.5, 0, 0, 0.0f,  0.0f,  -1.0f, // 8 
		0.5,  -0.5, -0.5, 1, 0, 0.0f,  0.0f,  -1.0f, // 9
		0.5,   0.5, -0.5, 1, 1, 0.0f,  0.0f,  -1.0f, // 10
		-0.5,  0.5, -0.5, 0, 1, 0.0f,  0.0f,  -1.0f, // 11

		// left
		-0.5, -0.5, -0.5, 0, 0, -1.0f,  0.0f,  0.0f, // 12
		-0.5, -0.5,  0.5, 1, 0, -1.0f,  0.0f,  0.0f, // 13
		-0.5,  0.5,  0.5, 1, 1, -1.0f,  0.0f,  0.0f, // 14
		-0.5,  0.5, -0.5, 0, 1, -1.0f,  0.0f,  0.0f, // 15

		// upper
		 0.5, 0.5,  0.5, 0, 0, 0.0f,  1.0f,  0.0f,   // 16
		-0.5, 0.5,  0.5, 1, 0, 0.0f,  1.0f,  0.0f,  // 17
		-0.5, 0.5, -0.5, 1, 1, 0.0f,  1.0f,  0.0f,  // 18
		 0.5, 0.5, -0.5, 0, 1, 0.0f,  1.0f,  0.0f,   // 19

		 // bottom
		 -0.5, -0.5, -0.5, 0, 0, 0.0f,  -1.0f,  0.0f, // 20
		  0.5, -0.5, -0.5, 1, 0, 0.0f,  -1.0f,  0.0f, // 21
		  0.5, -0.5,  0.5, 1, 1, 0.0f,  -1.0f,  0.0f, // 22
		 -0.5, -0.5,  0.5, 0, 1, 0.0f,  -1.0f,  0.0f, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO8);
	glGenBuffers(1, &VBO8);
	glGenBuffers(1, &EBO8);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO8);

	glBindBuffer(GL_ARRAY_BUFFER, VBO8);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO8);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define normal pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);


	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void Demo::DrawLampu(double posX, double posY, double posZ, double scX, double scY, double scZ, GLuint shader) {
	UseShader(shader);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture9);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);

	glBindVertexArray(VAO8);

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(posX, posY, posZ));
	model = glm::scale(model, glm::vec3(scX, scY, scZ));

	GLint modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildKepalaLampu() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture10);
	glBindTexture(GL_TEXTURE_2D, texture10);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("kepalalampu.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords

		// front
		-0.5, -0.5, 0.5, 0, 0, 0.0f,  0.0f,  1.0f,  // 0
		 0.5, -0.5, 0.5, 1, 0, 0.0f,  0.0f,  1.0f,  // 1
		 0.5,  0.5, 0.5, 1, 1, 0.0f,  0.0f,  1.0f,  // 2
		-0.5,  0.5, 0.5, 0, 1, 0.0f,  0.0f,  1.0f,  // 3

		// right
		0.5,  0.5,  0.5, 0, 0, 1.0f,  0.0f,  0.0f, // 4
		0.5,  0.5, -0.5, 1, 0, 1.0f,  0.0f,  0.0f, // 5
		0.5, -0.5, -0.5, 1, 1, 1.0f,  0.0f,  0.0f, // 6
		0.5, -0.5,  0.5, 0, 1, 1.0f,  0.0f,  0.0f, // 7

		// back
		-0.5, -0.5, -0.5, 0, 0, 0.0f,  0.0f,  -1.0f, // 8 
		0.5,  -0.5, -0.5, 1, 0, 0.0f,  0.0f,  -1.0f, // 9
		0.5,   0.5, -0.5, 1, 1, 0.0f,  0.0f,  -1.0f, // 10
		-0.5,  0.5, -0.5, 0, 1, 0.0f,  0.0f,  -1.0f, // 11

		// left
		-0.5, -0.5, -0.5, 0, 0, -1.0f,  0.0f,  0.0f, // 12
		-0.5, -0.5,  0.5, 1, 0, -1.0f,  0.0f,  0.0f, // 13
		-0.5,  0.5,  0.5, 1, 1, -1.0f,  0.0f,  0.0f, // 14
		-0.5,  0.5, -0.5, 0, 1, -1.0f,  0.0f,  0.0f, // 15

		// upper
		 0.5, 0.5,  0.5, 0, 0, 0.0f,  1.0f,  0.0f,   // 16
		-0.5, 0.5,  0.5, 1, 0, 0.0f,  1.0f,  0.0f,  // 17
		-0.5, 0.5, -0.5, 1, 1, 0.0f,  1.0f,  0.0f,  // 18
		 0.5, 0.5, -0.5, 0, 1, 0.0f,  1.0f,  0.0f,   // 19

		 // bottom
		 -0.5, -0.5, -0.5, 0, 0, 0.0f,  -1.0f,  0.0f, // 20
		  0.5, -0.5, -0.5, 1, 0, 0.0f,  -1.0f,  0.0f, // 21
		  0.5, -0.5,  0.5, 1, 1, 0.0f,  -1.0f,  0.0f, // 22
		 -0.5, -0.5,  0.5, 0, 1, 0.0f,  -1.0f,  0.0f, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO8);
	glGenBuffers(1, &VBO8);
	glGenBuffers(1, &EBO8);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO8);

	glBindBuffer(GL_ARRAY_BUFFER, VBO8);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO8);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define normal pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);


	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void Demo::DrawKepalaLampu(double posX, double posY, double posZ, double scX, double scY, double scZ, GLuint shader) {
	UseShader(shader);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture10);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);

	glBindVertexArray(VAO8);

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(posX, posY, posZ));
	model = glm::scale(model, glm::vec3(scX, scY, scZ));

	GLint modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::InitCamera()
{
	posCamX = 0.0f;
	posCamY = 5.0f;
	posCamZ = 8.0f;
	viewCamX = 0.0f;
	viewCamY = 1.0f;
	viewCamZ = 0.0f;
	upCamX = 0.0f;
	upCamY = 1.0f;
	upCamZ = 0.0f;
	CAMERA_SPEED = 0.01f;
	fovy = 45.0f;
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
void Demo::MoveCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	// forward positive cameraspeed and backward negative -cameraspeed.
	posCamX = posCamX + x * speed;
	posCamZ = posCamZ + z * speed;
	viewCamX = viewCamX + x * speed;
	viewCamZ = viewCamZ + z * speed;
}
void Demo::StrafeCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	float orthoX = -z;
	float orthoZ = x;

	// left positive cameraspeed and right negative -cameraspeed.
	posCamX = posCamX + orthoX * speed;
	posCamZ = posCamZ + orthoZ * speed;
	viewCamX = viewCamX + orthoX * speed;
	viewCamZ = viewCamZ + orthoZ * speed;
}
void Demo::RotateCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	viewCamZ = (float)(posCamZ + glm::sin(speed) * x + glm::cos(speed) * z);
	viewCamX = (float)(posCamX + glm::cos(speed) * x - glm::sin(speed) * z);
}

void Demo::BuildDepthMap() {
	// configure depth map FBO
	// -----------------------
	glGenFramebuffers(1, &depthMapFBO);
	// create depth texture
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, this->SHADOW_WIDTH, this->SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	// attach depth texture as FBO's depth buffer
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

int main(int argc, char** argv) {
	RenderEngine& app = Demo();
	app.Start("Tugas Akhir 24Carat", 1920, 1080, true, true);
}