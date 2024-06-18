#ifndef SHADER_H
#define SHADER_H

#include "cspch.h"

namespace Colossus {
class Shader {
    private:
        unsigned int programId = 0;

    public:
        Shader() = default;
        ~Shader();

        void create(const char* vertexPath, const char* fragmentPath);

        void use() const;

        void setBool(const std::string& name, bool value) const;
        void setInt(const std::string& name, int value) const;
        void setFloat(const std::string& name, float value) const;

        unsigned int getId() const;

    private:
        void checkStatusErrors(unsigned int object, const char* type) const;
};
}  // namespace Colossus

#endif  // SHADER_H
