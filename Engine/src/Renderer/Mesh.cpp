#include "Obelisk/Renderer/Mesh.h"

namespace Obelisk {
uint32_t Mesh::s_NextMeshID = 0;

Mesh::Mesh(std::vector<Vertex> const& vertices,
           std::vector<unsigned int> const& indices) {
    m_MeshID = s_NextMeshID++;

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);

    // Bind and set VBO data
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(),
                 vertices.data(), GL_STATIC_DRAW);

    // Bind and set EBO data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(),
                 indices.data(), GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)offsetof(Vertex, Color));
    glEnableVertexAttribArray(1);

    // Texture Coords attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)offsetof(Vertex, TextureCoords));
    glEnableVertexAttribArray(2);

    // Cleanup
    glBindVertexArray(0);

    m_NumVertices = vertices.size();
    m_NumIndices = indices.size();

    LOG_TRACE("MeshID " << m_MeshID << " created");
}

Mesh::~Mesh() {
    if (m_VAO) {
        glDeleteVertexArrays(1, &m_VAO);
    }

    if (m_VBO) {
        glDeleteBuffers(1, &m_VBO);
    }

    if (m_EBO) {
        glDeleteBuffers(1, &m_EBO);
    }

    LOG_TRACE("MeshID " << m_MeshID << " destroyed");
}

void Mesh::Bind() const { glBindVertexArray(m_VAO); }

void Mesh::Unbind() { glBindVertexArray(0); }
}  // namespace Obelisk