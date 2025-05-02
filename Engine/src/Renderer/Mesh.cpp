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

    // Vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    // Cleanup
    glBindVertexArray(0);

    LOG_TRACE("MeshID" << m_MeshID << " created");
}

Mesh::~Mesh() {
}

void Mesh::Bind() const {
    LOG_TRACE("Binding MeshID " << m_MeshID);
    glBindVertexArray(m_VAO);
}

void Mesh::Unbind() const {
    LOG_TRACE("Unbinding MeshID " << m_MeshID);
    glBindVertexArray(0);
}
}