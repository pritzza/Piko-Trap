#include "GameStatePlatform.h"

#include <iostream>

#include "../Game.h"

#include "../event/EntityCollisionEvent.h"
#include "../event/GameStateMachineOperationEvent.h"

#include "../gfx/sprite/SpriteID.h"

#include <SFML/Window/Keyboard.hpp>

void GameStatePlatform::load()
{
	std::cout << "platform load\n";
	const AABB testCollider{ 0, 0, 100, 100 };
	const sf::Vector2f p1Pos{ 100, 100 };
	const sf::Vector2f p2Pos{ 300, 200 };
	p1.init(p1Pos, SpriteID::Test, testCollider);
	p2.init(p2Pos, SpriteID::Test, testCollider);

	level.load(20, 10);
	
	// event bus debugging
	GameStateMachine& gsm{ this->data.gameStateMachine };
	EventBus bus{ this->data.eventBus };

	GameStateMachineOperationEvent addState1{ GameStateMachineOperation(GameStateMachineOperationType::AddState, GameStateID::Title) };
	bus.publish(&addState1);
	GameStateMachineOperationEvent addState2{ GameStateMachineOperation(GameStateMachineOperationType::AddState, GameStateID::LevelEditor) };
	bus.publish(&addState2);
}

void GameStatePlatform::unload()
{
	std::cout << "platform unload\n";
}

void GameStatePlatform::handleInput()
{
	std::cout << "platform input\n";

	// p1
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		p1.setVel({ 100,0 });

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		p1.setVel({ -100,0 });

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		p1.setVel({ 0,100 });

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		p1.setVel({ 0,-100 });

	// p2
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		p2.setVel({ 100,0 });

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		p2.setVel({ -100,0 });

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		p2.setVel({ 0,100 });

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		p2.setVel({ 0,-100 });

	GameStateMachine& gsm{ this->data.gameStateMachine };
	EventBus bus{ this->data.eventBus };

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		GameStateMachineOperationEvent changeState{ GameStateMachineOperation(GameStateMachineOperationType::ChangeCurrentState, GameStateID::Title) };
		bus.publish(&changeState);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		GameStateMachineOperationEvent changeState{ GameStateMachineOperation(GameStateMachineOperationType::ChangeCurrentState, GameStateID::LevelEditor) };
		bus.publish(&changeState);
	}
}

void GameStatePlatform::update(const double dt, const double pt)
{
	std::cout << "platform update\n";

	p1.update(dt);
	p2.update(dt);

	if (p1.getAABB().isColliding(p2.getAABB()))
	{
		EntityCollisionEvent e{ p1, p2 };
		this->data.eventBus.publish(&e);
	}
}

void GameStatePlatform::render() const
{
	std::cout << "platform render\n";

	Renderer& renderer{ this->data.renderer };

	renderer.preRender();

	renderer.render(p1.getSprite());
	renderer.render(p2.getSprite());

	renderer.render(level);

	renderer.postRender();
}