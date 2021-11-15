#ifndef GGDPROGRAM
#define GGDPROGRAM

// ==================== Libraries ==================
// Depending on the operating system we use
// The paths to SDL are actually different.
// The #define statement should be passed in
// when compiling using the -D argument.
// This gives an example of how a programmer
// may support multiple platforms with different
// dependencies.
#if defined(LINUX) || defined(MINGW)
    #include <SDL2/SDL.h>
#else // This works for Mac
    #include <SDL.h>
#endif

// The glad library helps setup OpenGL extensions.
//#include <glad/glad.h>

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <memory>
#include <iterator>
#include <cstdio>
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"


#include "GameObject.hpp"
#include "Component.hpp"
#include "SpriteComponent.hpp"
#include "SpriteFactory.hpp"
#include "TransformComponent.hpp"
#include "TransformFactory.hpp"
#include "TileMapComponent.hpp"
#include "TileMapFactory.hpp"
#include "PhysicsComponent.hpp"
#include "PhysicsFactory.hpp"
#include "SoundComponent.hpp"
#include "SoundFactory.hpp"
#include "CollisionSystem.hpp"
#include "Event.hpp"
// Purpose:
// This class sets up a full graphics program using SDL
//
//

struct RectWrapper {
    int x;
    int y;
    int w;
    int h;
};

/**
 * @brief Represents the current state of the game (i.e. is the game over, is it resetting, or is it playing)
 */
enum GameState {
    GameOver,
    Reset,
    GamePlay
};

class GGDProgram{
public:

    // Constructor
    GGDProgram(int w, int h);
    // Destructor
    ~GGDProgram();
	
    /**
     * @brief Checks for inputs and stores it in the EventLog
     */
    void CheckInput();

    /**
     * @brief Per frame update
     */
    void Update();

    /**
     * @brief Per frame render. Renders everything
     */
    void RenderPresent();

	/**
	 * @brief clears the screen
	 */
	void RenderClear();

    /**
     * @brief Initialization and shutdown pattern
     * Explicitly call 'Shutdown' to terminate the engine
     */
    void Shutdown();
	
	/**
     * @brief Marks the time at the start of the frame, used in tandem with closeFrameLimit to cap framerate
     */
	void startFrameLimit();
	
	/**
     * @brief checks the marked time, and if not enough time has passed it delays so that the given frame rate is met
	 * - FPS: the target frame rate requested
     */
	void closeFrameLimit(int FPS);
	
	/**
     * @brief Delays rendering by the given number of milliseconds
	 * - milliseconds: the amount of time to be delayed in milliseconds
     */
    void delay(int milliseconds);
	/**
	 * @brief used for sending messages to components, currently un-implemented
	 */
    void receive(int messageID) ;//override;
	/**
	 * @brief DEPRECIATED: was used to mark a game object for rendering, no longer required
	 */
	void initializeRendering(GameObject& go);
	
	void UpdateCamera();
	
	TileMapComponent* loadJSON(std::string path, int xSize, int ySize);

	Component* requestComponent(std::string type);

    RectWrapper camera;

    std::vector<InputEvent> eventLog;


private:
	// Engine Subsystem
    // Setup the Graphics Rendering Engine
    GraphicsEngineRenderer* m_renderer = nullptr;

    // The singleton Resource manager for this engine
    ResourceManager* m_rm = nullptr;

    // the current state of the game
    GameState m_state;	
	


	// Creating Component Factories NOTE: This won't work
	TileMapFactory TileMap_Factory;
	SpriteFactory Sprite_Factory;
	TransformFactory Transform_Factory;
	//ControllerFactory Controller_Factory;
	PhysicsFactory Physics_Factory;
	SoundFactory Sound_Factory;
	CollisionSystem Collision_Factory;
	
	//a tracked time used for frame capping
	Uint32 start_tick;
};

#endif
