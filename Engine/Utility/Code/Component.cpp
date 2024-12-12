#include "Engine_base.h"
#include "Component.h"

using namespace Engine;


Component::Component(void) : device(nullptr), isClone(false)
{
}

Component::Component(LPDIRECT3DDEVICE9& _device) : device(_device), isClone(false)
{
}

Component::Component(const Component& other) : device(other.device), isClone(true)
{
}

Component::~Component(void)
{
}
