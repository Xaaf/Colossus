#include "Obelisk/Renderer/Shader.h"
#include <filesystem>
#include <fstream>

namespace Obelisk {
Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
    std::string vertexSource = LoadShaderSource(vertexPath);
    const char* vertexCStr = vertexSource.c_str();

    std::string fragmentSource = LoadShaderSource(fragmentPath);
    const char* fragmentCStr = fragmentSource.c_str();

    unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexCStr, nullptr);
    glCompileShader(vertex);
    CheckCompileErrors(vertex, "vertex");

    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentCStr, nullptr);
    glCompileShader(fragment);
    CheckCompileErrors(fragment, "fragment");

    m_ProgramID = glCreateProgram();
    glAttachShader(m_ProgramID, vertex);
    glAttachShader(m_ProgramID, fragment);
    glLinkProgram(m_ProgramID);

    CheckCompileErrors(m_ProgramID, "program");

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader() {
    if (m_ProgramID) {
        glDeleteProgram(m_ProgramID);
        LOG_TRACE("ShaderProgramID " << m_ProgramID << " destroyed.");
        m_ProgramID = 0;
    }
}

std::string Shader::LoadShaderSource(const std::string& filepath) {
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        // Use AssetManager to get the full path
        std::filesystem::path fullPath =
            AssetManager::GetAssetPath("shaders/" + filepath);

        // Check if asset exists before trying to open
        if (!AssetManager::AssetExists("shaders/" + filepath)) {
            LOG_ERROR("Shader file not found: " << filepath);
            LOG_ERROR("Searched path: " << fullPath.string());
            LOG_ERROR(AssetManager::GetDebugInfo());
            return "";
        }

        file.open(fullPath);

        if (!file.is_open()) {
            LOG_ERROR("Failed to open shader file: " << fullPath.string());
            return "";
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();

        LOG_TRACE("Successfully loaded shader: " << fullPath.string());
        return buffer.str();
    } catch (const std::ifstream::failure& e) {
        LOG_ERROR("Failed to read shader file \"" << filepath
                                                  << "\": " << e.what());
        LOG_ERROR(AssetManager::GetDebugInfo());
        return "";
    }
}

unsigned int Shader::GetUniformLocation(const std::string& uniformName) const {
    const unsigned int location =
        glGetUniformLocation(m_ProgramID, uniformName.c_str());
    return location;
}

void Shader::CheckCompileErrors(unsigned int shader, const std::string& type) {
    if (type == "program") {
        glGetProgramiv(shader, GL_LINK_STATUS, &m_Success);

        if (!m_Success) {
            glGetProgramInfoLog(shader, 512, nullptr, m_InfoLog);
            LOG_ERROR("Unable to link shader program!\n>" << m_InfoLog);
        }
    } else {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &m_Success);

        if (!m_Success) {
            glGetShaderInfoLog(shader, 512, nullptr, m_InfoLog);
            LOG_ERROR("Unable to compile " << type << " shader!\n>"
                                           << m_InfoLog);
        }
    }
}

void Shader::Use() const { glUseProgram(m_ProgramID); }

void Shader::SetBool(const std::string& name, bool value) const {
    Use();
    glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetInt(const std::string& name, int value) const {
    Use();
    glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetFloat(const std::string& name, float value) const {
    Use();
    glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetVec2(const std::string& name, const glm::vec2& value) const {
    Use();
    glUniform2f(GetUniformLocation(name), value.x, value.y);
}

void Shader::SetVec3(const std::string& name, const glm::vec3& value) const {
    Use();
    glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
}

void Shader::SetVec4(const std::string& name, const glm::vec4& value) const {
    Use();
    glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);
}

void Shader::SetMat4(const std::string& name, const glm::mat4& value) const {
    Use();
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &value[0][0]);
}
}  // namespace Obelisk