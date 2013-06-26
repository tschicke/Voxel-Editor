/*
 * Shader.cpp
 *
 *  Created on: Feb 2, 2013
 *      Author: Tyler
 */

#include <iostream>

#include <GL/glew.h>
#include <fstream>
#include <string>
#include <vector>

#include "Shader.h"

/*********************
 *******Shader********
 *********************/

Shader::Shader() {
	shaderType = 0;
	shaderID = 0;
	loaded = false;
}

Shader::~Shader() {
}

bool Shader::loadShader(const char * filePath, shader_type_t shaderType) {
	std::string shaderCode;

	std::ifstream shaderStream(filePath, std::ios::in);
	if (shaderStream.is_open()) {
		std::string line = "";
		while (getline(shaderStream, line)) {
			shaderCode += '\n' + line;
		}
		shaderStream.close();
	} else {
		std::cerr << "Couldn't open file\n";
		return false;
	}

	shaderID = glCreateShader(shaderType);

	const char * sourcePointer = shaderCode.c_str();
	glShaderSource(shaderID, 1, &sourcePointer, NULL);
	glCompileShader(shaderID);

	int compilationStatus = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compilationStatus);

	if (compilationStatus == GL_FALSE) {
		char infoLog[1024];
		int logLength;
		glGetShaderInfoLog(shaderID, 1024, &logLength, infoLog);
		std::cerr << "Error! Shader File " << filePath << " wasn't compiled! The compiler returned:\n\n" << infoLog << '\n';
		return false;
	}

	this->shaderType = shaderType;
	loaded = true;

	return true;
}

void Shader::deleteShader() {
	if (!loaded) {
		return;
	}
	loaded = false;
	glDeleteShader(shaderID);
}

bool Shader::isLoaded() {
	return loaded;
}

unsigned int Shader::getShaderID() {
	return shaderID;
}

/*********************
 ***Shader Program****
 *********************/

ShaderProgram::ShaderProgram() {
	created = false;
	linked = false;
	programID = 0;
}

ShaderProgram::~ShaderProgram() {

}

void ShaderProgram::createProgram() {
	programID = glCreateProgram();
	created = true;
}

void ShaderProgram::deleteProgram() {
	if (!linked) {
		return;
	}

	created = false;
	linked = false;
	glDeleteProgram(programID);
}

bool ShaderProgram::addShader(Shader * shader) {
	if (!shader->isLoaded() || !created) {
		return false;
	}
	glAttachShader(programID, shader->getShaderID());

	return true;
}

bool ShaderProgram::linkProgram() {
	if(!created){
		std::cerr << "Program not created";
		return false;
	}
	glLinkProgram(programID);
	int linkStatus = 0;
	glGetProgramiv(programID, GL_LINK_STATUS, &linkStatus);
	linked = (linkStatus == GL_TRUE);
	return linked;
}

void ShaderProgram::useProgram() {
	if (linked) {
		glUseProgram(programID);
	}
}

unsigned int ShaderProgram::getProgramID() {
	return programID;
}

// Setting floats

void ShaderProgram::setUniform(const char * sName, float* fValues, int iCount) {
	int iLoc = glGetUniformLocation(programID, sName);
	glUniform1fv(iLoc, iCount, fValues);
}

void ShaderProgram::setUniform(const char * sName, const float fValue) {
	int iLoc = glGetUniformLocation(programID, sName);
	glUniform1fv(iLoc, 1, &fValue);
}

// Setting vectors

void ShaderProgram::setUniform(const char * sName, glm::vec2* vVectors, int iCount) {
	int iLoc = glGetUniformLocation(programID, sName);
	glUniform2fv(iLoc, iCount, (GLfloat*) vVectors);
}

void ShaderProgram::setUniform(const char * sName, const glm::vec2 vVector) {
	int iLoc = glGetUniformLocation(programID, sName);
	glUniform2fv(iLoc, 1, (GLfloat*) &vVector);
}

void ShaderProgram::setUniform(const char * sName, glm::vec3* vVectors, int iCount) {
	int iLoc = glGetUniformLocation(programID, sName);
	glUniform3fv(iLoc, iCount, (GLfloat*) vVectors);
}

void ShaderProgram::setUniform(const char * sName, const glm::vec3 vVector) {
	int iLoc = glGetUniformLocation(programID, sName);
	glUniform3fv(iLoc, 1, (GLfloat*) &vVector);
}

void ShaderProgram::setUniform(const char * sName, glm::vec4* vVectors, int iCount) {
	int iLoc = glGetUniformLocation(programID, sName);
	glUniform4fv(iLoc, iCount, (GLfloat*) vVectors);
}

void ShaderProgram::setUniform(const char * sName, const glm::vec4 vVector) {
	int iLoc = glGetUniformLocation(programID, sName);
	glUniform4fv(iLoc, 1, (GLfloat*) &vVector);
}

// Setting 4x4 matrices

void ShaderProgram::setUniform(const char * sName, glm::mat4* mMatrices, int iCount) {
	int iLoc = glGetUniformLocation(programID, sName);
	glUniformMatrix4fv(iLoc, iCount, GL_FALSE, (GLfloat*) mMatrices);
}

void ShaderProgram::setUniform(const char * sName, const glm::mat4 mMatrix) {
	int iLoc = glGetUniformLocation(programID, sName);
	glUniformMatrix4fv(iLoc, 1, GL_FALSE, (GLfloat*) &mMatrix);
}

// Setting integers

void ShaderProgram::setUniform(const char * sName, int* iValues, int iCount) {
	int iLoc = glGetUniformLocation(programID, sName);
	glUniform1iv(iLoc, iCount, iValues);
}

void ShaderProgram::setUniform(const char * sName, const int iValue) {
	int iLoc = glGetUniformLocation(programID, sName);
	glUniform1i(iLoc, iValue);
}

