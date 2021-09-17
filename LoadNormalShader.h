#pragma once
#include "main.h"

GLuint NormalshaderProgram;
GLuint colorLoc;
GLuint modeltransformLoc;
GLuint viewLoc;
GLuint projectionLoc;
GLuint normalTransformLoc;
GLuint cameraPosLoc;
GLuint ambientColorLoc;
glm::mat4 trans;
glm::mat4 projection;
GLuint lightPoscLoc;
GLuint lightDirLoc;
GLuint diffuseTexLoc;
GLuint nightTexLoc;

GLuint SeconddiffuseTexLoc;
GLuint SecondnightTexLoc;

void LoadData() {
	NormalshaderProgram = LoadShaders("Shader/Phong_vertex.shader", "Shader/Phong_normal_fragment.shader");

	glUseProgram(NormalshaderProgram);
	colorLoc = glGetUniformLocation(NormalshaderProgram, "uniformColor");
	glUniform3f(colorLoc, 1.0f, 1.0f, 1.0f);

	modeltransformLoc = glGetUniformLocation(NormalshaderProgram, "u_model");
	viewLoc = glGetUniformLocation(NormalshaderProgram, "u_view");
	projectionLoc = glGetUniformLocation(NormalshaderProgram, "u_projection");

	normalTransformLoc = glGetUniformLocation(NormalshaderProgram, "u_normal");
	cameraPosLoc = glGetUniformLocation(NormalshaderProgram, "u_camera_pos");
	ambientColorLoc = glGetUniformLocation(NormalshaderProgram, "u_ambient_color");
	glUniform3f(ambientColorLoc, 0.1f, 0.1f, 0.1f);

	trans = glm::mat4(1.0f);
	glUniformMatrix4fv(modeltransformLoc, 1, GL_FALSE, glm::value_ptr(trans));


	projection = glm::mat4(1.0f);
	//glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	lightPoscLoc = glGetUniformLocation(NormalshaderProgram, "u_light_post");
	lightDirLoc = glGetUniformLocation(NormalshaderProgram, "u_light_dir");
	diffuseTexLoc = glGetUniformLocation(NormalshaderProgram, "texture_diffuse");
	nightTexLoc = glGetUniformLocation(NormalshaderProgram, "texture_normal");

	SeconddiffuseTexLoc = glGetUniformLocation(NormalshaderProgram, "diffuse_second");
	SecondnightTexLoc = glGetUniformLocation(NormalshaderProgram, "normal_second");



	glUniform1i(diffuseTexLoc, 0);
	glUniform1i(nightTexLoc, 1);
	glUniform1i(SeconddiffuseTexLoc, 2);
	glUniform1i(SecondnightTexLoc, 3);


	glUniform3f(lightPoscLoc, 0.0f, 0.0f, 10.0f);
	glUniform3f(lightDirLoc, 0.0f, 0.0f, -1.0f);
}