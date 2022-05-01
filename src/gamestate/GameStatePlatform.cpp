#include "GameStatePlatform.h"

#include <iostream>

#include "../Game.h"

#include "../event/EntityCollisionEvent.h"
#include "../event/GameStateMachineOperationEvent.h"

void GameStatePlatform::load()
{
	std::cout << "platform load\n";

	p1.init(AABB{ 100, 100, 100, 100 });
	p2.init(AABB{ 100, 100, 100, 100 });

	level.load(20, 10);
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		if (gsm.isLoaded(GameStateID::Platform))
		{
			GameStateMachineOperationEvent addState{ GameStateMachineOperation(GameStateMachineOperationType::AddState, GameStateID::Platform) };
			bus.publish(&addState);
		}
		GameStateMachineOperationEvent changeState{ GameStateMachineOperation(GameStateMachineOperationType::ChangeCurrentState, GameStateID::Platform) };
		bus.publish(&changeState);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		if (gsm.isLoaded(GameStateID::LevelEditor))
		{
			GameStateMachineOperationEvent addState{ GameStateMachineOperation(GameStateMachineOperationType::AddState, GameStateID::Title) };
			bus.publish(&addState);
		}
		GameStateMachineOperationEvent changeState{ GameStateMachineOperation(GameStateMachineOperationType::ChangeCurrentState, GameStateID::Title) };
		bus.publish(&changeState);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		if (gsm.isLoaded(GameStateID::LevelEditor))
		{
			GameStateMachineOperationEvent addState{ GameStateMachineOperation(GameStateMachineOperationType::AddState, GameStateID::LevelEditor) };
			bus.publish(&addState);
		}
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