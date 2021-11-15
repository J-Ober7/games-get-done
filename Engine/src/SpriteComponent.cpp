#include "SpriteComponent.hpp"

SpriteComponent::SpriteComponent(){
}

SpriteComponent::SpriteComponent(ResourceManager* rm, SDL_Renderer* ren){
    m_rm = rm;
    m_ren = ren;
}

SpriteComponent::~SpriteComponent() {
}

void SpriteComponent::init(int x, int y, int w, int h, int firstFrame, int lastFrame, 
                int spriteWidth, int spriteHeight, int spriteSheetRows, int spriteSheetCols, std::string path,
                float para){
	m_dest.x = x;
    m_dest.y = y;
    m_dest.w = w;
    m_dest.h = h;
	parallax = para;
	fileName = path;
    m_texture = m_rm->getTexture(m_ren, path);

    m_firstFrame = firstFrame;
    m_lastFrame = lastFrame;
    m_currentFrame = firstFrame;

    m_spriteWidth = spriteWidth;
    m_spriteHeight = spriteHeight;
    m_spriteSheetRows = spriteSheetRows;
    m_spriteSheetCols = spriteSheetCols;
}

// Set the sprite position
void SpriteComponent::init(int x, int y, int w, int h, 
                        int firstFrame, int lastFrame,
                        int spriteWidth, int spriteHeight, int spriteSheetRows, int spriteSheetCols, 
                        std::string path){
    init(x, y, w, h, firstFrame, lastFrame, spriteWidth, spriteHeight, spriteSheetRows, spriteSheetCols, path, 1);
}

// set the current animation's frames
void SpriteComponent::SetFrames(int firstFrame, int lastFrame) {
    m_firstFrame = firstFrame;
    m_lastFrame = lastFrame;
    //m_deltaFrames = m_animateSpeed;
}

void SpriteComponent::SetFrames(std::string animationName) {
    std::pair<int, int>* frames = m_animationList[animationName].get();
    if (frames->second != 0) {
        SetFrames(frames->first, frames->second);
        //SDL_Log("Switched animation");
    } else {
        SDL_Log("Error: no animation found");
    }
}

void SpriteComponent::AddAnimation(std::string animationName, int firstFrame, int lastFrame) {
    m_animationList[animationName] = std::make_unique<std::pair<int,int>>(std::make_pair(firstFrame, lastFrame));
}

void SpriteComponent::Update(GameObject & gameObject){

    m_deltaFrames++;
    if (m_deltaFrames>=m_animateSpeed) {
         m_deltaFrames = 0;
    //SDL_Log("sprite update");
    // The part of the image that we want to render
        m_currentFrame += 1;
        if(m_currentFrame>m_lastFrame || 
            m_currentFrame>=m_spriteSheetCols*m_spriteSheetRows-1 || 
            m_currentFrame<m_firstFrame) {

            m_currentFrame=m_firstFrame;
        }
    }

    // Here I am selecting which frame I want to draw
    // from our sprite sheet. Think of this as just
    // using a mouse to draw a rectangle around the
    // sprite that we want to draw.
    m_src.x = m_spriteWidth * (m_currentFrame % m_spriteSheetCols);
    m_src.y = m_spriteHeight * (m_currentFrame / m_spriteSheetCols);
    m_src.w = m_spriteWidth;
    m_src.h = m_spriteHeight;

    // Where we want the rectangle to be rendered at.
    // This is an actual 'quad' that will draw our
    // source image on top of.	
    m_dest.x = gameObject.position.x + m_xOffset;
    m_dest.y = gameObject.position.y + m_yOffset;
    //m_dest.w = gameObject.position.w;
    //m_dest.h = gameObject.position.h;
}

void SpriteComponent::Render(SDL_Renderer* ren){
    //SDL_Log("sprite render");
	SDL_RendererFlip flip;
	if(renderFlipHorizontal && renderFlipVertical){
		flip = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
	} else if (renderFlipHorizontal){
		flip = SDL_FLIP_HORIZONTAL; 
	}else if (renderFlipVertical){
		flip = SDL_FLIP_VERTICAL; 
	} else {
		flip = SDL_FLIP_NONE;
	}
    SDL_RenderCopyEx(ren, m_texture, &m_src, &m_dest, 0, NULL, flip);
    if (parent->debug) {
        SDL_SetRenderDrawColor(ren, 0xFF, 0x00, 0x00, 0xFF);
        SDL_Rect debugRect{m_dest.x - m_xOffset, m_dest.y - m_yOffset, parent->position.w, parent->position.h};
        SDL_RenderDrawRect(ren, &debugRect);
    }
}

void SpriteComponent::ApplyCamera(SDL_Rect cam) {
	m_dest.x -= (cam.x * parallax);
    m_dest.y -= (cam.y * parallax);
}

void SpriteComponent::SetSpriteOffset(int x, int y){
	m_xOffset = x;
	m_yOffset = y;
}

void SpriteComponent::FlipHorizontal(bool flip){
	renderFlipHorizontal = flip;
	
}
	
void SpriteComponent::FlipVertical(bool flip){
	renderFlipVertical = flip;
}