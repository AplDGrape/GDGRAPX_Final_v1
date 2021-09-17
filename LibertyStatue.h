#pragma once
#include "main.h"

ObjData LibertyStatueData;

void InitializeLibertyStatue() {
	LoadObjFile(&LibertyStatueData, "Liberty/LibertStatue.obj");

	GLfloat StatueOffsets[] = { 0.0f, -1.0f, -1.0f };

	LoadObjToMemory(
		&LibertyStatueData,
		1.0f,
		StatueOffsets
	);
}

void BindLibertyStatueArray() {
	glBindVertexArray(LibertyStatueData.vaoId);
}

void DrawLibertyStatue() {
	glActiveTexture(GL_TEXTURE0);
	GLuint libertyTexture = LibertyStatueData.textures[LibertyStatueData.materials[0].diffuse_texname];
	glBindTexture(GL_TEXTURE_2D, libertyTexture);
	
	glActiveTexture(GL_TEXTURE1);
	GLuint normalTexture = LibertyStatueData.textures[LibertyStatueData.materials[0].bump_texname];
	glBindTexture(GL_TEXTURE_2D, normalTexture);

	glActiveTexture(GL_TEXTURE3);
	GLuint SecondTexture = LibertyStatueData.textures[LibertyStatueData.materials[1].diffuse_texname];
	glBindTexture(GL_TEXTURE_2D, SecondTexture);

	glActiveTexture(GL_TEXTURE4);
	GLuint SecondnormalTexture = LibertyStatueData.textures[LibertyStatueData.materials[1].bump_texname];
	glBindTexture(GL_TEXTURE_2D, SecondnormalTexture);

	//glEnable(GL_BLEND);
	glDrawElements(GL_TRIANGLES, LibertyStatueData.numFaces, GL_UNSIGNED_INT, (void*)0);
	//glDisable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, 0);
}