#pragma once

#include "ObeliskPCH.h"

namespace Obelisk {
class OBELISK_API Shader {
    private:
        unsigned int m_ProgramID;

        int m_Success = -1;
        char m_InfoLog[512] = {};

        static std::string LoadShaderSource(const std::string& filepath);
        [[nodiscard]] unsigned int GetUniformLocation(
            const std::string& uniformName) const;
        void CheckCompileErrors(unsigned int shader, const std::string& type);

    public:
        Shader() = default;
        Shader(const std::string& vertexPath, const std::string& fragmentPath);
        ~Shader();

        void Use() const;

        // Uniform utility functions
        void SetBool(const std::string& name, bool value) const;
        void SetInt(const std::string& name, int value) const;
        void SetFloat(const std::string& name, float value) const;
        void SetVec2(const std::string& name, const glm::vec2& value) const;
        void SetVec3(const std::string& name, const glm::vec3& value) const;
        void SetVec4(const std::string& name, const glm::vec4& value) const;
        void SetMat4(const std::string& name, const glm::mat4& value) const;
};
}  // namespace Obelisk