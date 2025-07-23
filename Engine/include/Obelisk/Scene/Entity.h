#pragma once

#include "ObeliskPCH.h"
#include "Obelisk/Components/Transform.h"
#include "Obelisk/Renderer/Mesh.h"
#include "Obelisk/Renderer/Shader.h"
#include "Obelisk/Renderer/Texture.h"

namespace Obelisk {
class OBELISK_API Entity {
    private:
        std::shared_ptr<Mesh> m_Mesh;
        std::shared_ptr<Shader> m_Shader;
        std::shared_ptr<Texture> m_Texture;

        Transform m_Transform;

    public:
        Entity();
        Entity(std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader,
               std::shared_ptr<Texture> texture);

        void SetMesh(std::shared_ptr<Mesh> mesh);
        void SetShader(std::shared_ptr<Shader> shader);
        void SetTexture(std::shared_ptr<Texture> texture);

        Transform& GetTransform() { return m_Transform; }

        std::shared_ptr<Mesh> GetMesh() const;
        std::shared_ptr<Shader> GetShader() const;
        std::shared_ptr<Texture> GetTexture() const;

        void Draw() const;
};
}  // namespace Obelisk