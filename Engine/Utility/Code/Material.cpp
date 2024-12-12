#include "Engine_base.h"
#include "Material.h"

using namespace Engine;


Material::Material()
{
}

Material::~Material()
{
}

Material::Material(Material& other)
{
}

Material::Material(LPDIRECT3DDEVICE9& device)
{
}

void Material::start(void)
{
}

void Material::awake(void)
{
}

void Material::update(void)
{
}

void Material::lateUpdate(void)
{
}

void Material::fixedUpdate(void)
{
}

void Material::render(void)
{
}

Component* Material::clone(void)
{
	return new Material(*this);
}

void Material::setMaterial(void)
{
}