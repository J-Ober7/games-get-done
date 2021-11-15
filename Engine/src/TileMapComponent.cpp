#include <iostream>
#include <iomanip>
#include <algorithm>

#include "TileMapComponent.hpp"

// Creates a new tile map.
// rows and cols are how many different tiles there are in the sprite sheet
//
// _TileWidth and _TileHeight are the size of each individual
// tile in the sprite sheet.
// (Typically this works best if they are square for this implementation.)
//
// _mapX, and _mapY are the size of the tilemap. This is the actual
// number of tiles in the game that the player sees, not how many tiles
// are in the actual sprite sheet file loaded.
TileMapComponent::TileMapComponent()
{
}

TileMapComponent::TileMapComponent(ResourceManager *rm, SDL_Renderer *ren)
{
    m_rm = rm;
    m_ren = ren;
}

// Destructor
TileMapComponent::~TileMapComponent()
{
    // Remove our TileMap
    delete[] m_Tiles;
}

void TileMapComponent::init(std::string tileSheetFileName, int rows, int cols, int spriteX, int spriteY, int _TileWidth, int _TileHeight, int _mapX, int _mapY)
{
    init(tileSheetFileName, rows, cols, spriteX, spriteY, _TileWidth, _TileHeight, _mapX, _mapY, 1);
}

void TileMapComponent::init(std::string tileSheetFileName, int rows, int cols, int spriteX, int spriteY, int _TileWidth, int _TileHeight, int _mapX, int _mapY, float para)
{
    if (nullptr == m_ren)
    {
        SDL_Log("No valid renderer found");
    }

    // Setup variables
    m_Rows = rows;
    m_Cols = cols;
	m_spriteTileX = spriteX;
	m_spriteTileY = spriteY;
    m_TileWidth = _TileWidth;
    m_TileHeight = _TileHeight;
    m_MapX = _mapX;
    m_MapY = _mapY;
    parallax = para;
    fileName = tileSheetFileName;
    m_Texture = m_rm->getTexture(m_ren, tileSheetFileName);

    // Setup the TileMap array
    // This sets each tile to '0'
    m_Tiles = new int[m_MapX * m_MapY];
    for (int i = 0; i < m_MapX * m_MapY; i++)
    {
        m_Tiles[i] = -1; // Default value is no tile.
    }
}

void TileMapComponent::addCollidableTile(int tileType)
{
    impassableTileTypes.push_back(tileType);
}

// Helper function to gegenerate a simlpe map
void TileMapComponent::GenerateSimpleMap()
{
    background = false;
    for (int y = 0; y < m_MapY; y++)
    {
        for (int x = 0; x < m_MapX; x++)
        {
            if (y == 0)
            {
                SetTile(x, y, 12);
            }
            else if (y == m_MapY - 1)
            {
                SetTile(x, y, 0);
            }
            else
            {
                if (y == m_MapY - 2 && (x == 12 || x == 19 || x == 24 || x == 31))
                {
                    SetTile(x, y, 8);
                }
                else if (y == m_MapY - 3 && (x == 24 || x == 12 || x == 19 || x == 24 || x == 31))
                {
                    SetTile(x, y, 8);
                }
                else if (y == m_MapY - 4 && (x == 19 || x == 24 || x == 31))
                {
                    SetTile(x, y, 8);
                }
                else if (y == m_MapY - 5 && (x == 1 || x == 2 || x == 3))
                {
                    SetTile(x, y, 8);
                }
                else
                {
                    SetTile(x, y, -1);
                }
            }
        }
    }
}

void TileMapComponent::GenerateBGMap()
{
    background = true;
    for (int y = 0; y < m_MapY; y++)
    {
        for (int x = 0; x < m_MapX; x++)
        {
            SetTile(x, y, 26);
        }
    }
}

// Helper function to print out the tile map
// to the console
void TileMapComponent::PrintMap()
{
    for (int y = 0; y < m_MapY; y++)
    {
        for (int x = 0; x < m_MapX; x++)
        {
            std::cout << std::setw(3) << GetTileType(x, y);
        }
        std::cout << "\n";
    }
}

// Sets a tile a certain type
void TileMapComponent::SetTile(int x, int y, int type)
{
    m_Tiles[y * m_MapX + x] = type;
}

// Returns what the tile is at a specific position.
int TileMapComponent::GetTileType(int x, int y)
{
    return m_Tiles[y * m_MapX + x];
}

// render TileMap
void TileMapComponent::Render(SDL_Renderer *ren)
{
    if (nullptr == m_ren)
    {
        SDL_Log("No valid renderer found");
    }

    SDL_Rect Src, Dest;
    for (int y = 0; y < m_MapY; y++)
    {
        for (int x = 0; x < m_MapX; x++)
        {
            // Select our Tile
            int currentTile = GetTileType(x, y);
            if (currentTile > -1)
            {
                // Reverse lookup, given the tile type
                // and then figuring out how to select it
                // from the texture atlas.
                Src.x = (currentTile % m_Cols) * m_spriteTileX;
                Src.y = (currentTile / m_Cols) * m_spriteTileY;
                Src.w = m_spriteTileX;
                Src.h = m_spriteTileY;
                // Render our Tile at this location
                Dest.x = x * m_TileWidth - (camera.x * parallax) + position.x;
                Dest.y = y * m_TileHeight - (camera.y * parallax) + position.y;
                Dest.w = m_TileWidth;
                Dest.h = m_TileHeight;
                SDL_RenderCopy(m_ren, m_Texture, &Src, &Dest);
				if(std::find(impassableTileTypes.begin(), impassableTileTypes.end(), currentTile) != impassableTileTypes.end() && debug){
					SDL_SetRenderDrawColor(ren, 0xFF, 0x00, 0x00, 0xFF);
					SDL_RenderDrawRect(ren, &Dest);
				}
            }
        }
    }
}

void TileMapComponent::Update(GameObject &gameObject)
{
    position = gameObject.position;
    printf("x %i y %i", position.x, position.y);
}

void TileMapComponent::ApplyCamera(SDL_Rect cam)
{
    camera = cam;
}

// Note: Collisions determined assuming objects have NOT yet been moved
void TileMapComponent::CheckCollsion(CollisionComponent *collider)
{
    // if this tilemap holds background tiles, return (no collisions)
    if (background)
    {
        return;
    }
    // top left corner: collider->gameObject->position.x, position.y
    // top right corner: collider->gameobject->position.x + position.w, position.y
    // bottom left corner: collider->gameObject->position.x, position.y + position.h
    // bottom right corner: collider->gameObject->position.x + position.w, position.y + position.h
    //int leftX = collider->parent->position.x + collider->parent->m_xVel;
    int leftX = collider->parent->position.x;
    int rightX = leftX + collider->parent->position.w;

    //int topY = collider->parent->position.y + collider->parent->m_yVel;
    int topY = collider->parent->position.y;
    int bottomY = topY + collider->parent->position.h;

    float otherCenterX = leftX + 0.5f * collider->parent->position.w;
    float otherCenterY = topY + 0.5f * collider->parent->position.h;

    // check if we are within bounds of tile map
    if (leftX < 0 + position.x || topY < 0 + position.y|| rightX > m_MapX * m_TileWidth + position.x || bottomY > m_MapY * m_TileHeight + position.y)
    {
        return;
    }
    printf("hi \n");
    // calculate list of all tiles collidable intersects with

    std::vector<int> intersectingTiles(1);
    /*int leftMostTilePos = leftX/ m_TileWidth;
    int rightMostTilePos = rightX % m_TileWidth == 0 ? rightX / m_TileWidth - 1: rightX / m_TileWidth;
    int topMostTilePos = topY / m_TileHeight;
    int bottomMostTilePos = bottomY % m_TileHeight == 0 ? bottomY / m_TileHeight - 1: bottomY / m_TileHeight;*/

    int leftMostTilePos = (leftX - position.x) / m_TileWidth;
    int rightMostTilePos = (rightX - position.x) % m_TileWidth == 0 ? (rightX - position.x) / m_TileWidth - 1: (rightX - position.x) / m_TileWidth;
    int topMostTilePos = (topY - position.y) / m_TileHeight;
    int bottomMostTilePos = (bottomY - position.y) % m_TileHeight == 0 ? (bottomY - position.y) / m_TileHeight - 1: (bottomY - position.y) / m_TileHeight;

    printf("left tile %i right tile %i top tile %i bottom tile %i", leftMostTilePos, rightMostTilePos, topMostTilePos, bottomMostTilePos);
    // Add any collisions to be handled to the collision's parent
    auto beginIt = impassableTileTypes.begin();
    auto endIt = impassableTileTypes.end();

    int tileLeft, tileRight, tileTop, tileBottom;

    for (int tileXPos = leftMostTilePos; tileXPos <= rightMostTilePos; tileXPos++)
    {
        for (int tileYPos = topMostTilePos; tileYPos <= bottomMostTilePos; tileYPos++)
        {
            
            //printf("Tile ID x: %d y: %d\n", tileXPos, tileYPos);
            if (std::find(beginIt, endIt, GetTileType(tileXPos, tileYPos)) != endIt)
            {
                
                tileLeft = (tileXPos * m_TileWidth) + position.x;
                tileRight = (tileLeft + m_TileWidth)+ position.x;
                tileTop = (tileYPos * m_TileHeight)+ position.y;
                tileBottom = (tileTop + m_TileHeight)+ position.y;

                float tileCenterX = tileLeft + 0.5f * m_TileWidth + position.x;
                float tileCenterY = tileTop + 0.5f * m_TileHeight+ position.y;

                int ymin = tileTop > topY ? tileTop : topY;
                int ymax = tileBottom < bottomY ? tileBottom : bottomY;
                int ysize = ymax - ymin;

                int xmin = tileLeft > leftX ? tileLeft : leftX;
                int xmax = tileRight < rightX ? tileRight : rightX;
                int xsize = xmax - xmin;

                if (xsize > ysize)
                {
                    //Bottom Collision
                    if (otherCenterY > tileCenterY)
                    {
                        collider->parent->collisions.push_back(new Collision{CollisionType::Bottom, "none", ysize});
                        printf("Bottom collision\n");
                    }
                    else
                    {
                        collider->parent->collisions.push_back(new Collision{CollisionType::Top, "none", ysize});
                        printf("Top collision\n");
                    }
                } else {
                    //Left Collision
                    if (otherCenterX > tileCenterX)
                    {
                        collider->parent->collisions.push_back(new Collision{CollisionType::Left, "none", xsize});
                        printf("left collision\n");
                    }
                    else
                    {
                        collider->parent->collisions.push_back(new Collision{CollisionType::Right, "none", xsize});
                        printf("right collision\n");
                    }
                }
            }
        }
    }
// std::cout << "top left" << topLeftTileType << " top right " << topRightTileType << " bottom right " << bottomRightTileType << " bottom left " << bottomLeftTileType << std::endl;
}
