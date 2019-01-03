#pragma once

#include "PhysicsManager.h"

class Entity
{
public:
	Entity();
	~Entity();
	void hide();
	void show();
	bool isHidden() const;
	void setManager(PhysicsManager* manager);

	virtual void update() = 0;
	virtual void draw(sf::RenderWindow& window) = 0;

protected:
	PhysicsManager* m_manager = nullptr;

private:
	bool m_hidden = false;
};

