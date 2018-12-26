#pragma once
class Entity
{
public:
	Entity();
	~Entity();
	void hide();
	void show();
	bool isHidden() const;

	virtual void update() = 0;
	virtual void draw(sf::RenderWindow& window) = 0;

private:
	bool m_hidden = false;
};

