#include "main.h"

#include "skybox.h"
#include "LibertyStatue.h"
#include "FlatSurface.h"

#include "LoadNormalShader.h"
#include "LoadMultipleShader.h"

double XMousePos, YMouseOos;
GLFWwindow* window;

double PreviousX = 0.0f;
double PreviousY = 0.0f;
double XPos, YPos;

/*float ScaleX = 1.0f;
float ScaleY = 1.0f;
float TransformX = 0.0f;
float TransformY = -0.2f;

float RotateZ = 0.0f;
float RotateX = 0.0f;
float RotateY = 0.0f;
*/
float prevTime = 0.0f;
float deltaTime = 0.0f;

bool setOrtho = false;
bool setPers = true;
int  pauseCycle = 0;

float xSpeed = 1.0f;
float xFactor = 0.0f;

float LastX = 1366.0f / 2.0f;
float LastY = 768.0f / 2.0f;

float yaw = -90.0f;
float pitch = 0.0f;

bool firstMouse = true;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.5f, 4.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp));
glm::vec3 cameraUpView = glm::normalize(glm::cross(cameraFront, cameraRight));

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse) {
		LastX = xpos;
		LastY = ypos;
		firstMouse = false;
	}

	float xOffSet = xpos - LastX;
	float yOffset = LastY - ypos;
	LastX = xpos;
	LastY = ypos;

	float sensitivity = 0.1f;
	xOffSet *= sensitivity;
	yOffset *= sensitivity;

	yaw += xOffSet;
	pitch += yOffset;

	if (pitch > 89.0f) {
		pitch = 89.0f;
	}
	if (pitch < -89.0f) {
		pitch = -89.0f;
	}

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);
}

void processInput(GLFWwindow* window) {

	float cameraSpeed = 2.0f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		cameraPos += cameraSpeed * cameraFront;
		std::cout << "W" << std::endl;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		cameraPos -= cameraRight * cameraSpeed;
		std::cout << "A" << std::endl;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		cameraPos -= cameraSpeed * cameraFront;
		std::cout << "S" << std::endl;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		cameraPos += cameraRight * cameraSpeed;
		std::cout << "D" << std::endl;
	}
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
		std::cout << "time paused" << std::endl;
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		if (setPers) {
			setOrtho = true;
			setPers = false;
		}
		else if (setOrtho) {
			setPers = true;
			setOrtho = false;
		}
	}
}


int main() {
	stbi_set_flip_vertically_on_load(true);

#pragma region Initialization

	//window = initialize();
	//initialize glfw
	if (glfwInit() != GLFW_TRUE) {
		fprintf(stderr, "Failed to initialized! \n");
		return -1;
	}

	width = 1366;
	height = 768;

	// set opengl version to 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// create window 
	GLFWwindow* window;
	window = glfwCreateWindow(width, height, "Apolinar & Santonia", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to load window! \n");
		return -1;
	}
	glfwMakeContextCurrent(window);

	//initialize glew
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}


#pragma endregion


#pragma region Mesh Loading

	InitializeLibertyStatue();

	std::vector<std::string> faces{
		"right.png",
		"left.png",
		"bottom.png",
		"top.png",
		"front.png",
		"back.png",
	};
	SkyboxData skybox = LoadSkybox("Assets/skybox", faces);
#pragma endregion

#pragma region Shader Loading

	//Load Skybox
	GLuint skyboxShaderProgram = LoadShaders("Shader/skybox_vertex.shader", "Shader/skybox_fragment.shader");

	LoadData();
	//LoadDataForMultipleTexture();
	/*GLuint shaderProgram = LoadShaders("Shader/vertex.shader", "Shader/fragment.shader");
	glUseProgram(shaderProgram);

	GLuint colorLoc = glGetUniformLocation(shaderProgram, "u_color");
	glUniform3f(colorLoc, 1.0f, 1.0f, 0.0f);

	// initialize MVP
	GLuint modelTransformLoc = glGetUniformLocation(shaderProgram, "u_model");
	GLuint viewLoc = glGetUniformLocation(shaderProgram, "u_view");
	GLuint projectionLoc = glGetUniformLocation(shaderProgram, "u_projection");

	// initialize transform
	GLuint transformLoc = glGetUniformLocation(shaderProgram, "u_transform");
	glm::mat4 trans = glm::mat4(1.0f); // identity
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

	// define projection matrix
	//glm::mat4 projection = glm::mat4(1.0f);
	*/
#pragma endregion

	// set bg color to green
	glClearColor(0.4f, 0.4f, 0.6f, 0.0f);

	// var for rotations
	float rotFactor = 0.0f;
	float currentTime = glfwGetTime();
	float prevTime = 0.0f;
	float deltaTime = 0.0f;
	float FOV = 50.0f;

	glm::mat4 projection = glm::mat4(1.0f);
	glm::mat4 orientation = glm::mat4(1.0f);
	glm::mat4 position = glm::mat4(1.0f);

	//depth testing
	glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_ALWAYS); // set the depth test function

	//face culling
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK); // set which face to cull
	//glFrontFace(GL_CCW); // set the front face orientation

	while (!glfwWindowShouldClose(window)) {
		float ratio;
		int width, height;

		/*glfwGetCursorPos(window, &XPos, &YPos);
		//glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::mat4(1.0f);*/
		
		//Input
		processInput(window);
		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		trans = glm::mat4(1.0f);
		float currentTime = glfwGetTime();

		prevTime = currentTime;

		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float)height;
		GLsizei viewportSize = 0.0f;
		if (ratio > 1.0f) {
			viewportSize = width;
		}
		else {
			viewportSize = height;
		}

		glViewport(0, 0, viewportSize, viewportSize);

#pragma region Camera
		glm::mat4 view = glm::lookAt(
			cameraPos,
			cameraPos + cameraFront,
			cameraUp
		);

		glUniform3f(cameraPosLoc, cameraPos.x, cameraPos.y, cameraPos.z);
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

#pragma endregion

#pragma region Projection
		// Perspective Projection
		//projection = glm::perspective(glm::radians(90.0f), ratio, 0.1f, 10.0f),

		// Set projection matrix in shader
		//glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
		
#pragma region View
		/*glm::mat4 view = glm::lookAt(
			glm::vec3(0.0f, 0.3f, -1.0f),
			//glm::vec3(0.5f, 0.0f, -1.0f),
			glm::vec3(trans[3][0], trans[3][1], trans[3][2]),
			glm::vec3(0.0f, 1.0f, 0.0f)
		);
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));*/
#pragma endregion

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//toggle to render wit GL_FILL or GL_LINE
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

#pragma region Draw

		DrawSkyBox(skybox, skyboxShaderProgram, view, projection);

		BindLibertyStatueArray();
		glUseProgram(NormalshaderProgram);

		projection = glm::perspective(glm::radians(FOV), ratio, 0.1f, 10.0f);
		//glm::angleAxis(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

		if (setOrtho) {
			projection = glm::ortho(0.0f, (GLfloat)width, 0.0f, (GLfloat)height * 2, 0.1f, 10.0f);
		}
		else if (setPers) {
			projection = glm::perspective(glm::radians(FOV), ratio, 0.1f, 15.0f);
		}

		projection = glm::perspective(glm::radians(FOV), ratio, 0.1f, 15.0f);
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

		//draw bunny
		//glBindVertexArray(backpack.vaoId);

		// transforms
		trans = glm::mat4(1.0f); // identity

		glm::mat4 normalTrans = glm::transpose(glm::inverse(trans));

		glUniformMatrix4fv(normalTransformLoc, 1, GL_FALSE, glm::value_ptr(normalTrans));
		glUniformMatrix4fv(modeltransformLoc, 1, GL_FALSE, glm::value_ptr(trans));

		//send to shader
		//glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(normalTrans));
		//glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

		//glDrawElements(GL_TRIANGLES, bunnyObjData.numFaces, GL_UNSIGNED_INT, (void*)0);

		/*glBindVertexArray(backpack.vaoId);
		glDrawElements(GL_TRIANGLES, backpack.numFaces, GL_UNSIGNED_INT, (void*)0);

		glActiveTexture(GL_TEXTURE0);
		GLuint backpackTexture = backpack.textures[backpack.materials[0].diffuse_texname];
		glBindTexture(GL_TEXTURE_2D, backpackTexture);

		//drawbackpack
		glDrawElements(GL_TRIANGLES, backpack.numFaces, GL_UNSIGNED_INT, (void*)0);

		//unbindtexture after rendering
		glBindTexture(GL_TEXTURE_2D, 0);
		*/
		DrawLibertyStatue();

		//BindFlatSurfaceArray();
		//DrawFlatSurface();
		//--- stop drawing here ---

		glfwSwapBuffers(window);
#pragma endregion
		//listen for glfw input events
		glfwPollEvents();
	}
	return 0;
}


