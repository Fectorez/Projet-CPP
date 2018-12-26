#include "pch.h"
#include "Entity.h"


Entity::Entity()
{}


Entity::~Entity()
{}

void Entity::hide()
{
	m_hidden = true;
}

void Entity::show()
{
	m_hidden = false;
}

bool Entity::isHidden() const
{
	return m_hidden;
}
