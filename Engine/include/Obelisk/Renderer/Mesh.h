#pragma once

#include "ObeliskPCH.h"

namespace Obelisk {
struct OBELISK_API Vertex {
    glm::vec3 Position;
    glm::vec3 Color;
    glm::vec2 TextureCoords;
};

class OBELISK_API Mesh {
    private:
        unsigned int m_VAO = 0;
        unsigned int m_VBO = 0;
        unsigned int m_EBO = 0;

        int m_NumVertices = 0;
        int m_NumIndices = 0;

        uint32_t m_MeshID = -1;
        static uint32_t s_NextMeshID;

    public:
        Mesh() = default;
        Mesh(std::vector<Vertex> const& vertices,
             std::vector<unsigned int> const& indices);
        ~Mesh() = default;

        void Bind() const;
        static void Unbind();

        [[nodiscard]] int GetNumberOfVertices() const {
            return m_NumVertices;
        };

        [[nodiscard]] int GetNumberOfIndices() const {
            return m_NumIndices;
        };
};
}