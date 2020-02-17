#include "Shader.h"
#include "debug.h"
#include <iostream>

Shader& Shader::Use() {
    glUseProgram(this->ID);
    return *this;
}

// TODO: Delete program.

void Shader::Compile(const GLchar* vertexSource, const GLchar* fragmentSource,
                     const GLchar* geometrySource) {
    GLuint sVertex, sFragment, gShader;

    // Vertex Shader
    GL(sVertex = glCreateShader(GL_VERTEX_SHADER));
    GL(glShaderSource(sVertex, 1, &vertexSource, NULL));
    GL(glCompileShader(sVertex));
    CheckCompileErrors(sVertex, "VERTEX");

    // Fragment Shader
    GL(sFragment = glCreateShader(GL_FRAGMENT_SHADER));
    GL(glShaderSource(sFragment, 1, &fragmentSource, NULL));
    GL(glCompileShader(sFragment));
    CheckCompileErrors(sFragment, "FRAGMENT");

    // If geometry shader source code is given, also compile geometry shader
    if (geometrySource != nullptr) {
        GL(gShader = glCreateShader(GL_GEOMETRY_SHADER));
        GL(glShaderSource(gShader, 1, &geometrySource, NULL));
        GL(glCompileShader(gShader));
        CheckCompileErrors(gShader, "GEOMETRY");
    }

    // Shader Program
    this->ID = glCreateProgram();
    GL(glAttachShader(this->ID, sVertex));
    GL(glAttachShader(this->ID, sFragment));
    if (geometrySource != nullptr)
        GL(glAttachShader(this->ID, gShader));
    GL(glLinkProgram(this->ID));
    CheckCompileErrors(this->ID, "PROGRAM");

    // Delete the shaders as they're linked into our program now and no longer necessery
    GL(glDeleteShader(sVertex));
    GL(glDeleteShader(sFragment));
    if (geometrySource != nullptr)
        GL(glDeleteShader(gShader));
}

void Shader::SetFloat(const GLchar* name, GLfloat value, GLboolean useShader) {
    if (useShader)
        this->Use();
    GLint location;
    GL(location = glGetUniformLocation(this->ID, name));
    GL(glUniform1f(location, value));
}

void Shader::SetInteger(const GLchar* name, GLint value, GLboolean useShader) {
    if (useShader)
        this->Use();
    GLint location;
    GL(location = glGetUniformLocation(this->ID, name));
    GL(glUniform1i(location, value));
}

void Shader::SetVector2f(const GLchar* name, GLfloat x, GLfloat y, GLboolean useShader) {
    if (useShader)
        this->Use();
    GLint location;
    GL(location = glGetUniformLocation(this->ID, name));
    GL(glUniform2f(location, x, y));
}

void Shader::SetVector2f(const GLchar* name, const glm::vec2& value, GLboolean useShader) {
    if (useShader)
        this->Use();
    GLint location;
    GL(location = glGetUniformLocation(this->ID, name));
    glUniform2f(location, value.x, value.y);
}

void Shader::SetVector3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader) {
    if (useShader)
        this->Use();
    GLint location;
    GL(location = glGetUniformLocation(this->ID, name));
    glUniform3f(location, x, y, z);
}

void Shader::SetVector3f(const GLchar* name, const glm::vec3& value, GLboolean useShader) {
    if (useShader)
        this->Use();
    GLint location;
    GL(location = glGetUniformLocation(this->ID, name));
    glUniform3f(location, value.x, value.y, value.z);
}

void Shader::SetVector4f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w,
                         GLboolean useShader) {
    if (useShader)
        this->Use();
    GLint location;
    GL(location = glGetUniformLocation(this->ID, name));
    glUniform4f(location, x, y, z, w);
}

void Shader::SetVector4f(const GLchar* name, const glm::vec4& value, GLboolean useShader) {
    if (useShader)
        this->Use();
    GLint location;
    GL(location = glGetUniformLocation(this->ID, name));
    glUniform4f(location, value.x, value.y, value.z, value.w);
}

void Shader::SetMatrix4(const GLchar* name, const glm::mat4& matrix, GLboolean useShader) {
    if (useShader)
        this->Use();
    GLint location;
    GL(location = glGetUniformLocation(this->ID, name));
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}


void Shader::CheckCompileErrors(GLuint object, std::string type) {
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM") {
        GL(glGetShaderiv(object, GL_COMPILE_STATUS, &success));
        if (!success) {
            GL(glGetShaderInfoLog(object, 1024, NULL, infoLog));
            std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
                      << infoLog << "\n -- --------------------------------------------------- -- "
                      << std::endl;
        }
    } else {
        GL(glGetProgramiv(object, GL_LINK_STATUS, &success));
        if (!success) {
            GL(glGetProgramInfoLog(object, 1024, NULL, infoLog));
            std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
                      << infoLog << "\n -- --------------------------------------------------- -- "
                      << std::endl;
        }
    }
}