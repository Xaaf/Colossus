#ifndef COLOSSUS_TEXTURE_H
#define COLOSSUS_TEXTURE_H

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
        unsigned int getId() const;
};
}  // namespace Colossus

#endif  // COLOSSUS_TEXTURE_H
