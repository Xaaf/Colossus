#pragma once

#include "ObeliskPCH.h"

namespace Obelisk {
struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
    glm::vec3 color;

    Vertex(glm::vec3 pos, glm::vec3 norm, glm::vec2 tex,
           glm::vec3 col = glm::vec3(1.0f))
        : position(pos), normal(norm), texCoords(tex), color(col) {
    }
};

class Mesh {
    private:
        uint32_t m_MeshID;
        std::vector<Vertex> m_Vertices;
        std::vector<unsigned int> m_Indices;

        GLuint m_VAO, m_VBO, m_EBO;

        static uint32_t s_NextMeshID;

    public:
        Mesh(const std::vector<Vertex>& vertices,
             const std::vector<unsigned int>& indices);
        ~Mesh();

        void Bind() const {
            glBindVertexArray(m_VAO);
        };

        void Unbind() const {
            glBindVertexArray(0);
        };

        [[nodiscard]] const std::vector<Vertex>& GetVertices() const {
            return m_Vertices;
        }

        [[nodiscard]] const std::vector<unsigned int>& GetIndices() const {
            return m_Indices;
        }

        [[nodiscard]] uint32_t GetMeshID() const { return m_MeshID; }

        static uint32_t GetNextMeshID() { return s_NextMeshID; }

    private:
        void LoadData(const std::vector<Vertex>& vector,
                      const std::vector<unsigned int>& indices);
};
}