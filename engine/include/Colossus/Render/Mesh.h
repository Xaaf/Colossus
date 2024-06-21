#ifndef MESH_H
#define MESH_H

#include "cspch.h"

namespace Colossus {
class Mesh {
    private:
        std::vector<float> vertices;
        std::vector<int> indices;
        // std::vector<Texture> textures; <-- Need to consider this for models
        // loaded through assimp. Alternative is maybe storing these in a Model
        // class instead? Deserves some thought...

    public:
        Mesh(const std::vector<float>& vertices, const std::vector<int>& indices);

        [[nodiscard]] const float* getVertices() const;
        [[nodiscard]] const int* getIndices() const;

        [[nodiscard]] size_t getVerticesSize() const;
        [[nodiscard]] size_t getIndicesSize() const;
};
}

#endif  // MESH_H
