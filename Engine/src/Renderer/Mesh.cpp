#include "Obelisk/Renderer/Mesh.h"

namespace Obelisk {
uint32_t Mesh::s_NextMeshID = 0;

Mesh::Mesh(const std::vector<Vertex>& vertices,
           const std::vector<unsigned int>& indices) {
    m_MeshID = s_NextMeshID++;

    LoadData(vertices, indices);
}

Mesh::~Mesh() {
    // Cleanup buffers
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
}

void Mesh::LoadData(const std::vector<Vertex>& vertices,
                    const std::vector<unsigned int>& indices) {
    // Generate buffers
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    // Bind the VAO
    glBindVertexArray(m_VAO);

    // Bind VBO and load vertices
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3),
                 &vertices[0], GL_STATIC_DRAW);

    // Bind EBO and load indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
                 &indices[0], GL_STATIC_DRAW);

    // Enable vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3),
                          (void*)0);

    // Unbind the VAO
    glBindVertexArray(0);
}
}