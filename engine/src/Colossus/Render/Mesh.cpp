#include "Colossus/Render/Mesh.h"
#include <utility>

using namespace Colossus;

Mesh::Mesh(const std::vector<float>& vertices, const std::vector<int>& indices)
    : vertices(vertices), indices(indices) {}

const float* Mesh::getVertices() const { return vertices.data(); }

const int* Mesh::getIndices() const { return indices.data(); }

size_t Mesh::getVerticesSize() const { return vertices.size() * sizeof(float); }

size_t Mesh::getIndicesSize() const { return indices.size() * sizeof(int); }
