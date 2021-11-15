#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <memory>
#include "Component.hpp"
#include "GraphicsEngineRenderer.hpp"
#include "ResourceManager.hpp"


// TODO: documentation
/**
 * @brief A small class to demonstrate loading sprites.
 * Sprite sheets are often used for loading characters,
 * environments, icons, or other images in a game.
 */
class SpriteComponent : public Component{
public:

    /**
     * @brief Constructor
     */
    SpriteComponent();

    // TODO
    SpriteComponent(ResourceManager* rm, SDL_Renderer* ren);

    /**
     * @brief Destructor
     */
    ~SpriteComponent();

    /**
     * @brief Initialize the sprite with parallax value 1
     * x and y is the world position (x, y). The top left corner
     * w an h and width and height
     * path is the file path string
     * ren is the renderer
     */
    void init(int x, int y, int w, int h, int firstFrame, int lastFrame, 
                int spriteWidth, int spriteHeight, int spriteSheetRows, int spriteSheetCols, std::string path);

    /**
     * @brief Initialize the sprite
     * x and y is the world position (x, y). The top left corner
     * w an h and width and height
     * path is the file path string
     * ren is the renderer
     * para is the parallax value
     */
	void init(int x, int y, int w, int h, int firstFrame, int lastFrame, 
                int spriteWidth, int spriteHeight, int spriteSheetRows, int spriteSheetCols, std::string path,
                float para);

	/**
     * @brief Sets the window of frames the sprite should read from
     * firstFrame is the first frame in the sequence
	 * lastFrame is the last frame in the sequence
     */
    void SetFrames(int firstFrame, int lastFrame);

	/**
     * @brief Sets the frame window to the window stored under animationName in m_animationList
     */
    void SetFrames(std::string animationName);

	/**
     * @brief Adds an animation to m_animationList.
	 * animationName is the name the animation will be stored under
	 * firstFrame is the first frame in the animation
	 * lastFrame is the last frame in the animation
     */
    void AddAnimation(std::string animationName, int firstFrame, int lastFrame);

    /**
     * @brief Updates the current frame each frame
     */
    void Update(GameObject& gameObject);

    /**
     * @brief Renders the current frame from the sprite sheet
     */
    void Render(SDL_Renderer* renderer) override;
	
    /**
     * @brief Change rendering position based on the camera perspective
     */
	void ApplyCamera(SDL_Rect cam);
	/**
     * @brief Offsets the sprite from its parent gameobject by the given amount
     */
	void SetSpriteOffset(int x, int y);
	
	void FlipHorizontal(bool flip);
	
	void FlipVertical(bool flip);

    int m_animateSpeed{1};

private:

	int m_xPos;
    int m_yPos;
	float parallax{1};

    // info about sprite sheet
	unsigned int m_currentFrame{0};
    unsigned int m_firstFrame{0};
	unsigned int m_lastFrame{27};

    int m_spriteWidth;
    int m_spriteHeight;
    int m_spriteSheetRows;
    int m_spriteSheetCols;

	int m_xOffset{0};
	int m_yOffset{0};
	
	bool renderFlipHorizontal{false};
	bool renderFlipVertical{false};
    
    int m_deltaFrames{0};

    // map to hold specificed animations. Key is the name of the animation,
    // and the value is the start and end frame for it
    std::map<std::string, std::unique_ptr<std::pair<int, int>>> m_animationList;

    // path to the sprite sheet
    std::string fileName;
    SDL_Texture* m_texture;

	SDL_Rect m_src;
	SDL_Rect m_dest;

    ResourceManager* m_rm;
    SDL_Renderer* m_ren;
};

#endif
