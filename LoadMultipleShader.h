#pragma once
#include "main.h"
GLuint MultipleshaderProgram;
GLuint MultiplecolorLoc;
GLuint MultiplemodeltransformLoc;
GLuint MultipleviewLoc;
GLuint MultipleprojectionLoc;
GLuint MultiplenormalTransformLoc;
GLuint MultiplecameraPosLoc;
GLuint MultipleambientColorLoc;
glm::mat4 Multipletrans;
glm::mat4 Multipleprojection;
GLuint MultiplelightPoscLoc;
GLuint MultiplelightDirLoc;
GLuint MultiplediffuseTexLoc;
GLuint MultiplenightTexLoc;

void LoadDataForMultipleTexture() {
	MultipleshaderProgram = LoadShaders("Shader/Phong_vertex.shader", "Shader/night_fragment.shader");

	glUseProgram(MultipleshaderProgram);
	colorLoc = glGetUniformLocation(MultipleshaderProgram, "uniformColor");
	glUniform3f(colorLoc, 1.0f, 1.0f, 1.0f);

	MultiplemodeltransformLoc = glGetUniformLocation(MultipleshaderProgram, "u_model");
	MultipleviewLoc = glGetUniformLocation(MultipleshaderProgram, "u_view");
	MultipleprojectionLoc = glGetUniformLocation(MultipleshaderProgram, "u_projection");

	MultiplenormalTransformLoc = glGetUniformLocation(MultipleshaderProgram, "u_normal");
	MultiplecameraPosLoc = glGetUniformLocation(MultipleshaderProgram, "u_camera_pos");
	MultipleambientColorLoc = glGetUniformLocation(MultipleshaderProgram, "u_ambient_color");
	glUniform3f(MultipleambientColorLoc, 0.1f, 0.1f, 0.1f);

	Multipletrans = glm::mat4(1.0f);
	glUniformMatrix4fv(MultiplemodeltransformLoc, 1, GL_FALSE, glm::value_ptr(Multipletrans));


	Multipleprojection = glm::mat4(1.0f);
	//glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	MultiplelightPoscLoc = glGetUniformLocation(MultipleshaderProgram, "u_light_post");
	MultiplelightDirLoc = glGetUniformLocation(MultipleshaderProgram, "u_light_dir");
	MultiplediffuseTexLoc = glGetUniformLocation(MultipleshaderProgram, "texture_diffuse");
	MultiplenightTexLoc = glGetUniformLocation(MultipleshaderProgram, "night_diffuse");




	glUniform1i(MultiplediffuseTexLoc, 0);
	glUniform1i(MultiplenightTexLoc, 1);


	glUniform3f(MultiplelightPoscLoc, 0.0f, 0.0f, 10.0f);
	glUniform3f(MultiplelightDirLoc, 0.0f, 0.0f, -1.0f);
}