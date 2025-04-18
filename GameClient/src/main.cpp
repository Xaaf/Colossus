#include "Obelisk/ObeliskAPI.h"

int main() {
    Obelisk::ObeliskAPI::Get().Init();
    Obelisk::ObeliskAPI::Get().Run();
    Obelisk::ObeliskAPI::Get().Shutdown();

    return 0;
}