#pragma once

#include "ObeliskPCH.h"

namespace Obelisk {
struct Vertex {
    glm::vec3 Position;
    glm::vec3 Color;
    glm::vec2 TextureCoords;
};

class OBELISK_API Mesh {
    private:
        unsigned int m_VAO = 0;
        unsigned int m_VBO = 0;
        unsigned int m_EBO = 0;

        std::vector<Vertex> m_Vertices;
        std::vector<unsigned int> m_Indices;

        uint32_t m_MeshID = -1;
        static uint32_t s_NextMeshID;

    public:
        Mesh() = default;
        Mesh(std::vector<Vertex> const& vertices,
             std::vector<unsigned int> const& indices);
        ~Mesh() = default;

        void Bind() const;
        void Unbind() const;
};
}