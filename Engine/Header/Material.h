#pragma once
#include "Component.h"


namespace Engine
{
	class Material : public Component
	{
	public:
		Material(void);
		virtual ~Material(void);
		explicit Material(Material& other);
		explicit Material(LPDIRECT3DDEVICE9& device);

		virtual void start(void) override;
		virtual void awake(void) override;
		virtual void update(void) override;
		virtual void lateUpdate(void) override;
		virtual void fixedUpdate(void) override;
		virtual void render(void) override;
		virtual Component* clone(void) override;

		void setMaterial(void);
	private:
		D3DMATERIAL9 material
	};

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
}