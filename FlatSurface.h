#pragma once
#include "main.h"

ObjData FlatSurfaceData;

void InitializeFlatSurface() {
	LoadObjFile(&FlatSurfaceData, "Road/untitled.obj");

	GLfloat SurfaceOffsets[] = { 0.0f, -1.1f, -1.5f };

	LoadObjToMemory(
		&FlatSurfaceData,
		1.0f,
		SurfaceOffsets
	);
}

void BindFlatSurfaceArray() {
	glBindVertexArray(FlatSurfaceData.vaoId);
}

void DrawFlatSurface() {
	glActiveTexture(GL_TEXTURE0);
	GLuint roadTexture = FlatSurfaceData.textures[FlatSurfaceData.materials[0].diffuse_texname];
	glBindTexture(GL_TEXTURE_2D, roadTexture);

	glActiveTexture(GL_TEXTURE1);
	GLuint normalTexture = FlatSurfaceData.textures[FlatSurfaceData.materials[0].bump_texname];
	glBindTexture(GL_TEXTURE_2D, normalTexture);

	glActiveTexture(GL_TEXTURE3);
	GLuint SecondTexture = FlatSurfaceData.textures[FlatSurfaceData.materials[1].diffuse_texname];
	glBindTexture(GL_TEXTURE_2D, SecondTexture);

	glActiveTexture(GL_TEXTURE4);
	GLuint SecondnormalTexture = FlatSurfaceData.textures[FlatSurfaceData.materials[1].bump_texname];
	glBindTexture(GL_TEXTURE_2D, SecondnormalTexture);

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDrawElements(GL_TRIANGLES, FlatSurfaceData.numFaces, GL_UNSIGNED_INT, (void*)0);
	//glDisable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, 0);
}
