#ifndef TEXTURE_H
#define TEXTURE_H

#include "cspch.h"

namespace Colossus {
class Texture {
    private:
        int width, height;
        int channels;

        unsigned char* data;
        unsigned int texture;

    public:
        Texture() = default;
        ~Texture();

        void create(const char* texturePath);
        [[nodiscard]] unsigned int getId() const;
};
}  // namespace Colossus

#endif  // TEXTURE_H
