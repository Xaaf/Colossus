#ifndef COLOSSUS_SHADER_H
#define COLOSSUS_SHADER_H

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

    private:
        void checkStatusErrors(unsigned int object, const char* type) const;
};
}  // namespace Colossus

#endif  // COLOSSUS_SHADER_H
