#pragma once

class GameStateMachine;
class ResourceManager;

class EventBus;
class PhysicsHandler;
class Window;
class Renderer;
class Timer;

struct GameData final
{
	GameStateMachine& gameStateMachine;

	ResourceManager& textureManager;

	EventBus& eventBus;

	PhysicsHandler& physicsHandler;

	Window& window;
	Renderer& renderer;

	Timer& timer;

	unsigned& targetFrameRate;

	bool& isRunning;
};