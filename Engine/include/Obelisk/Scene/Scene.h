#pragma once

#include "Entity.h"
#include "ObeliskPCH.h"

namespace Obelisk {
class OBELISK_API Scene {
    private:
        std::vector<Entity*> m_Entities;

    public:
        void AddEntity(Entity* entity) { m_Entities.push_back(entity); }

        std::vector<Entity*>& GetEntities() { return m_Entities; }
};
}  // namespace Obelisk