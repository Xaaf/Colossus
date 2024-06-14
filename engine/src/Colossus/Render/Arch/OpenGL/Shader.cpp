#include "Colossus/Render/Arch/OpenGL/Shader.h"
#include <filesystem>
#include <fstream>
#include <sstream>

using namespace Colossus;

Shader::~Shader() { glDeleteProgram(programId); }

void Shader::create(const char *vertexPath, const char *fragmentPath) {
    std::string vertexSource, fragmentSource;
    std::ifstream vertexFile, fragmentFile;

    LOG_TRACE("Shader",
              "Vertex path: " << std::filesystem::absolute(vertexPath));
    LOG_TRACE("Shader",
              "Fragment path: " << std::filesystem::absolute(fragmentPath));
    LOG_TRACE("Shader",
              "Current working directory: " << std::filesystem::current_path());

    // Make sure ifstreams can throw exceptions
    vertexFile.exceptions(std::ifstream ::failbit | std::ifstream::badbit);
    fragmentFile.exceptions(std::ifstream ::failbit | std::ifstream::badbit);

    try {
        LOG_TRACE("Shader", "Opening vertex file...");
        vertexFile.open(vertexPath);

        std::stringstream vertexStream;
        vertexStream << vertexFile.rdbuf();

        vertexFile.close();
        vertexSource = vertexStream.str();
    } catch (std::ifstream::failure &e) {
        LOG_ERROR("Shader",
                  "Unable to read shader file! (" << vertexPath << ")");
    }

    try {
        LOG_TRACE("Shader", "Opening fragment file...");
        fragmentFile.open(fragmentPath);

        std::stringstream fragmentStream;
        fragmentStream << fragmentFile.rdbuf();

        fragmentFile.close();
        fragmentSource = fragmentStream.str();
    } catch (std::ifstream::failure &e) {
        LOG_ERROR("Shader",
                  "Unable to read shader file! (" << fragmentPath << ")");
    }

    const char *vertexCode = vertexSource.c_str();
    const char *fragmentCode = fragmentSource.c_str();

    LOG_TRACE("Shader", "Vertex source:\n" << vertexCode);
    LOG_TRACE("Shader", "Fragment source:\n" << fragmentCode);

    // Compile shaders
    unsigned int vertexId, fragmentId;

    vertexId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexId, 1, &vertexCode, nullptr);
    glCompileShader(vertexId);
    checkStatusErrors(vertexId, "VERTEX");
    LOG_INFO("Shader", "Compiled vertex shader (" << vertexPath << ")");

    fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentId, 1, &fragmentCode, nullptr);
    glCompileShader(fragmentId);
    checkStatusErrors(fragmentId, "FRAGMENT");
    LOG_INFO("Shader", "Compiled fragment shader (" << fragmentPath << ")");

    // Create & link Shader program
    programId = glCreateProgram();
    glAttachShader(programId, vertexId);
    glAttachShader(programId, fragmentId);
    glLinkProgram(programId);
    checkStatusErrors(programId, "PROGRAM");

    // Cleanup
    glDeleteShader(vertexId);
    glDeleteShader(fragmentId);
}

void Shader::use() const { glUseProgram(programId); }

void Shader::checkStatusErrors(unsigned int object, const char *type) const {
    int success;
    char infoLog[512];

    if (type != "PROGRAM") {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(object, 512, nullptr, infoLog);
            LOG_ERROR("Shader", "Failed to compile object (" << type << ").");
            LOG_ERROR("Shader", infoLog);
        }
    } else {
        glGetProgramiv(object, GL_LINK_STATUS, &success);

        if (!success) {
            glGetProgramInfoLog(object, 512, nullptr, infoLog);
            LOG_ERROR("Shader",
                      "Failed to link program (" << programId << ").");
            LOG_ERROR("Shader", infoLog);
        }
    }
}

void Shader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(programId, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(programId, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(programId, name.c_str()), value);
}