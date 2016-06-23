//
//  shader.h
//  gl
//
//  Created by cnhao on 16/6/18.
//  Copyright © 2016年 cnhao. All rights reserved.
//

#ifndef shader_h
#define shader_h

#include <GL/glew.h>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

class Shader
{
public:
    GLuint program;
    Shader(const string vertexSourcePath, const string fragmentSourcePath);
    void use();
};


Shader::Shader(const string vertexSourcePath, const string fragmentSourcePath)
{
    string vertexCode;
    string fragmentCode;
    stringstream vShaderStream, fShaderStream;
//    try {
    ifstream vShaderFile(vertexSourcePath);
    ifstream fShaderFile(fragmentSourcePath);
    vShaderFile.exceptions (std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::badbit);
        
    
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();
        
    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();
        
    vShaderFile.close();
    fShaderFile.close();
        
        
//    } catch (ifstream::failure e) {
//        cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
//    }
    
    GLint success;
    GLchar infoLog[512];
    
    const GLchar* vShaderCode = vertexCode.c_str();
    const GLchar* fShaderCode = fragmentCode.c_str();
    GLuint vertex, fragment;
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "GL_COMPILE_STATUS_VERTEX ERROR" << infoLog << std::endl;
    }
    
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "GL_COMPILE_STATUS_FRAGMENT ERROR" << infoLog << std::endl;
    }
    
    this->program = glCreateProgram();
    glAttachShader(this->program, vertex);
    glAttachShader(this->program, fragment);
    glLinkProgram(this->program);
    glGetProgramiv(this->program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->program, 512, NULL, infoLog);
        std::cout << "GL_LINK_STATUS_SHADER_PROGRAM ERROR" <<  infoLog << std::endl;
    }
    
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    
    
}

void Shader::use()
{
    glUseProgram(this->program);
}

#endif /* shader_h */
