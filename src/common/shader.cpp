/*
 *
 * Copyright © 2010-2011 Balázs Tóth <tbalazs@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#include <iostream>
#include <fstream>

#include "shader.hpp"

Shader::Shader() {
}

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath, const char* geometryShaderPath) {
    geometryProgram = 0;

    shaderFromFile(vertexShaderPath, GL_VERTEX_SHADER, vertexProgram);
    shaderFromFile(fragmentShaderPath, GL_FRAGMENT_SHADER, fragmentProgram);
    if (geometryShaderPath)
        shaderFromFile(geometryShaderPath, GL_GEOMETRY_SHADER, geometryProgram);
    linkShaders(vertexProgram, fragmentProgram, geometryProgram, shaderProgram);
    glDeleteShader(vertexProgram);
    glDeleteShader(fragmentProgram);
}

Shader::~Shader() {
}

void Shader::shaderFromFile(const char* shaderPath, GLenum shaderType, GLuint& handle) {
    char* shaderSource = NULL;
    int len = 0;
    int errorFlag = -1;

    if (!fileToString(shaderPath, shaderSource, len)) {
        std::cout << "Error loading shader: " << shaderPath << std::endl;
        return;
    }

    handle = glCreateShader(shaderType);

    glShaderSource(handle, 1, (const char**) &shaderSource, &len);
    glCompileShader(handle);
    delete[] shaderSource;

    glGetShaderiv(handle, GL_COMPILE_STATUS, &errorFlag);
    if (!errorFlag) {
        std::cout << "Shader compile error: " << shaderPath << std::endl;
        std::cout << getShaderInfoLog(handle) << std::endl;
        return;
    }
}

void Shader::linkShaders(GLuint& vertexShader, GLuint& fragmentShader, GLuint& geometryShader, GLuint& handle) {
    int errorFlag = -1;

    handle = glCreateProgram();
    glAttachShader(handle, vertexShader);
    glAttachShader(handle, fragmentShader);
    if (geometryShader != 0) {
        glAttachShader(handle, geometryShader);
        glProgramParameteri(handle, GL_GEOMETRY_VERTICES_OUT_EXT, 4);
        glProgramParameteri(handle, GL_GEOMETRY_INPUT_TYPE_EXT, GL_POINTS);
        glProgramParameteri(handle, GL_GEOMETRY_OUTPUT_TYPE_EXT, GL_POINTS);

        const char* varname = "celldata";
        glTransformFeedbackVaryings(handle, 1, &varname, GL_SEPARATE_ATTRIBS_EXT);
    }

    glLinkProgram(handle);
    glGetProgramiv(handle, GL_LINK_STATUS, &errorFlag);
    if (!errorFlag) {
        std::cout << "Shader link error: " << std::endl;
        std::cout << getProgramInfoLog(handle) << std::endl;
        return;
    }
}

std::string Shader::getShaderInfoLog(GLuint& object) {
    int logLength = 0;
    int charsWritten = 0;
    char* tmpLog;
    std::string log;

    glGetShaderiv(object, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        tmpLog = new char[logLength];
        glGetShaderInfoLog(object, logLength, &charsWritten, tmpLog);
        log = tmpLog;
        delete[] tmpLog;
    }

    return log;
}

std::string Shader::getProgramInfoLog(GLuint& object) {
    int logLength = 0;
    int charsWritten = 0;
    char *tmpLog;
    std::string log;

    glGetProgramiv(object, GL_INFO_LOG_LENGTH, &logLength);

    if (logLength > 0) {
        tmpLog = new char[logLength];
        glGetProgramInfoLog(object, logLength, &charsWritten, tmpLog);
        log = tmpLog;
        delete[] tmpLog;
    }
    return log;
}

bool Shader::fileToString(const char* path, char*& out, int& len) {
    std::ifstream file(path, std::ios::ate | std::ios::binary);
    if (!file.is_open()) {
        return false;
    }
    len = file.tellg();
    out = new char[len + 1];
    file.seekg(0, std::ios::beg);
    file.read(out, len);
    file.close();
    out[len] = 0;
    return true;
}

void Shader::enable() {
    glUseProgram(shaderProgram);
}

void Shader::disable() {
    glUseProgram(0);
}

void Shader::bindUniformBool(const char* name, bool b) {
    GLuint boolLocation = glGetUniformLocation(shaderProgram, name);
    glUniform1f(boolLocation, b);
}

void Shader::bindUniformInt(const char* name, int i) {
    GLuint vectorLocation = glGetUniformLocation(shaderProgram, name);
    glUniform1i(vectorLocation, i);
}

void Shader::bindUniformInt2(const char* name, int i1, int i2) {
    GLuint vectorLocation = glGetUniformLocation(shaderProgram, name);
    glUniform2i(vectorLocation, i1, i2);
}

void Shader::bindUniformFloat(const char* name, float f) {
    GLuint location = glGetUniformLocation(shaderProgram, name);
    glUniform1f(location, f);
}

void Shader::bindUniformFloat2(const char* name, float f1, float f2) {
    GLuint location = glGetUniformLocation(shaderProgram, name);
    glUniform2f(location, f1, f2);
}

void Shader::bindUniformFloat3(const char* name, float f1, float f2, float f3) {
    GLuint location = glGetUniformLocation(shaderProgram, name);
    glUniform3f(location, f1, f2, f3);
}

void Shader::bindUniformTexture(const char* name, GLuint texture, GLuint unit) {
    GLuint location = glGetUniformLocation(shaderProgram, name);
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(location, unit);
}

void Shader::bindAttribLocation(GLuint id, const char* name) {
    glEnableVertexAttribArray(id);
    glBindAttribLocation(shaderProgram, id, name);
}

void Shader::bindUniformMatrix(const char* name, float* m, unsigned int arraySize) {
    GLuint location = glGetUniformLocation(shaderProgram, name);
    glUniformMatrix4fv(location, arraySize, false, m);
}

void Shader::bindUniformVector(const char* name, float* m, unsigned int arraySize) {
    GLuint location = glGetUniformLocation(shaderProgram, name);
    glUniform3fv(location, arraySize, m);
}

void Shader::bindUniformFloat4Array(const char* name, float* m, unsigned int arraySize) {
    GLuint location = glGetUniformLocation(shaderProgram, name);
    glUniform4fv(location, arraySize, m);
}

void Shader::bindUniformIntArray(const char* name, int* iv, unsigned int arraySize) {
    GLuint location = glGetUniformLocation(shaderProgram, name);
    glUniform1iv(location, arraySize, iv);
}
