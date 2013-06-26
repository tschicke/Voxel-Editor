/*
 * Shader.h
 *
 *  Created on: Feb 2, 2013
 *      Author: Tyler
 */

#ifndef SHADER_H_
#define SHADER_H_

#include <glm/glm.hpp>

#include "Common.h"

class Shader {
public:
	Shader();
	virtual ~Shader();

	bool loadShader(const char * filePath, shader_type_t shaderType);
	void deleteShader();

	unsigned int getShaderID();
	bool isLoaded();
private:
	unsigned int shaderID;
	shader_type_t shaderType;
	bool loaded;
};

class ShaderProgram {
public:
	ShaderProgram();
	virtual ~ShaderProgram();

	void createProgram();
	void deleteProgram();

	bool addShader(Shader* shader);
	bool linkProgram();

	void useProgram();

	unsigned int getProgramID();

	// Setting vectors
	void setUniform(const char * sName, glm::vec2* vVectors, int iCount = 1);
	void setUniform(const char * sName, const glm::vec2 vVector);
	void setUniform(const char * sName, glm::vec3* vVectors, int iCount = 1);
	void setUniform(const char * sName, const glm::vec3 vVector);
	void setUniform(const char * sName, glm::vec4* vVectors, int iCount = 1);
	void setUniform(const char * sName, const glm::vec4 vVector);

	// Setting floats
	void setUniform(const char * sName, float* fValues, int iCount = 1);
	void setUniform(const char * sName, const float fValue);

	// Setting integers
	void setUniform(const char * sName, int* iValues, int iCount = 1);
	void setUniform(const char * sName, const int iValue);

	// Setting 4x4 matrices
	void setUniform(const char * sName, glm::mat4* mMatrices, int iCount = 1);
	void setUniform(const char * sName, const glm::mat4 mMatrix);

private:
	unsigned int programID;
	bool created, linked;
};

#endif /* SHADER_H_ */
