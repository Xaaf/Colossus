#ifndef RENDERERINTERFACE_H
#define RENDERERINTERFACE_H

namespace Colossus {
class RendererInterface {
    public:
        virtual ~RendererInterface() = default;

        virtual bool initialise() = 0;
        virtual bool create() = 0;
        virtual void render() = 0;
};
}  // namespace Colossus

#endif  // RENDERERINTERFACE_H
