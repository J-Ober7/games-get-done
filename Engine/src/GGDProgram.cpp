#include "GGDProgram.hpp"

GGDProgram::GGDProgram(int w, int h)
{
    // Setup our Renderer
    m_renderer = new GraphicsEngineRenderer(w, h);
    if (m_renderer != nullptr)
    {
        SDL_Log("Initializing Graphics Subsystem\n");
    }
    else
    {
        SDL_Log("No Graphics Subsystem initialized\n");
    }
    if (nullptr == m_renderer)
    {
        exit(1); // Terminate program if renderer
                 // cannot be created.
                 // (Optional) TODO:   Could put an error
                 //                    messeage, or try to
                 //                    reinitialize the engine
                 //                    with a different render
    }
    m_rm = &(ResourceManager::init());

    Collision_Factory.init(&TileMap_Factory);

    camera = {0, 0, w, h};

    std::cout << "Finished Start up" << std::endl;
}

GGDProgram::~GGDProgram(){}

void GGDProgram::UpdateCamera(){
	SDL_Rect cameraSDL{camera.x, camera.y, camera.w, camera.h};

    Sprite_Factory.ApplyCameraAll(cameraSDL);
    TileMap_Factory.ApplyCameraAll(cameraSDL);
}

// Update SDL, should be called at the end of the frame
void GGDProgram::Update()
{

    // check collisions first with future positions
    Collision_Factory.checkCollisions();

    // NEED TO DO SOMETHING ABOUT EVENT HANDLING
    //Clear log here?

    eventLog.clear();
	
	Collision_Factory.handleCollisions();
}

void GGDProgram::CheckInput()
{
    // Event handler that handles various events in SDL
    // that are related to input and output
    SDL_Event e;
    // Enable text input
    SDL_StartTextInput();
    //Handle events on queue
    while (SDL_PollEvent(&e) != 0)
    {
        InputEvent event;
        // User posts an event to quit
        // An example is hitting the "x" in the corner of the window.
        if (e.type == SDL_QUIT)
        {
            //*quit = true;
            event.type = "quit";
            eventLog.push_back(event);
        }
        else
        {
            if (e.type == SDL_KEYDOWN)
            {
                event.type = "key";
                event.isDown = true;
                event.id = SDL_GetKeyName(e.key.keysym.sym);
            }
            else if (e.type == SDL_KEYUP)
            {
                event.type = "key";
                event.isDown = false;
                event.id = SDL_GetKeyName(e.key.keysym.sym);
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                event.type = "mouse";
                event.isDown = true;
                switch(e.button.button) {
                    case SDL_BUTTON_LEFT:
                        event.id = "left";
                        break;
                    case SDL_BUTTON_RIGHT:
                        event.id = "right";
                        break;
                    case SDL_BUTTON_MIDDLE:
                        event.id = "middle";
                        break;
                    case SDL_BUTTON_X1:
                        event.id = "x1";
                        break;
                    case SDL_BUTTON_X2:
                        event.id = "x2";
                        break;
                }
                event.x = e.button.x;
                event.y = e.button.y;
            }
            else if (e.type == SDL_MOUSEBUTTONUP)
            {
                event.type = "mouse";
                event.isDown = false;
                switch(e.button.button) {
                    case SDL_BUTTON_LEFT:
                        event.id = "left";
                        break;
                    case SDL_BUTTON_RIGHT:
                        event.id = "right";
                        break;
                    case SDL_BUTTON_MIDDLE:
                        event.id = "middle";
                        break;
                    case SDL_BUTTON_X1:
                        event.id = "x1";
                        break;
                    case SDL_BUTTON_X2:
                        event.id = "x2";
                        break;
                }
                event.x = e.button.x;
                event.y = e.button.y;
            }
            eventLog.push_back(event);
        }
    }
}

void GGDProgram::RenderPresent()
{

    m_renderer->RenderPresent();
}

void GGDProgram::RenderClear()
{
    // Set the color of the empty framebuffer
    m_renderer->SetRenderDrawColor(110, 130, 170, 0xFF);
    // Clear the screen to the color of the empty framebuffer
    m_renderer->RenderClear();
}

void GGDProgram::startFrameLimit()
{
    start_tick = SDL_GetTicks();
}

void GGDProgram::closeFrameLimit(int FPS)
{
    if ((1000 / FPS) > SDL_GetTicks() - start_tick)
    {
        SDL_Delay((1000 / FPS) - (SDL_GetTicks() - start_tick));
    }
}

void GGDProgram::
Shutdown()
{
    if (nullptr != m_renderer)
    {
        delete m_renderer;
    }
}

// Delay rendering
void GGDProgram::delay(int milliseconds)
{
}

void GGDProgram::receive(int messageID)
{
    // messageID 1 means the game is over
    if (messageID == 1)
    {
        m_state = GameOver;
        //std::cout << "Game over" << std::endl;
    }

    Sound_Factory.DeleteAll();
    Transform_Factory.DeleteAll();
    Sprite_Factory.DeleteAll();
    TileMap_Factory.DeleteAll();
    Collision_Factory.shutDown();
}

void GGDProgram::initializeRendering(GameObject& go) {
    go.SetRenderer(m_renderer->GetRenderer());
}

Component* GGDProgram::requestComponent(std::string type) {

	if (type == "sprite") {
        return Sprite_Factory.RequestComponent(m_rm, m_renderer->GetRenderer());
    }

	if (type =="transform") {
        return Transform_Factory.RequestComponent();
    }

    if (type == "tilemap") {
        return TileMap_Factory.RequestComponent(m_rm, m_renderer->GetRenderer());
    }

    if (type == "physics") {
        return Physics_Factory.RequestComponent();
    }

    if (type == "collision") {
        return Collision_Factory.RequestComponent();
    }

    if (type == "sound") {
        return Sound_Factory.RequestComponent();
    }

    return nullptr;
}


TileMapComponent* GGDProgram::loadJSON(std::string path, int xSize, int ySize){
	//path = "./Assets/TileMapSimple.json";
	
	FILE* fp = fopen(path.c_str(), "r");
	
	if( fp == NULL){
		printf("something has gone wrong");
		return NULL;
	}
	
	char readBuffer[65536];
	rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	
	
	rapidjson::Document d;
	d.ParseStream(is);
	
	
	fclose(fp);
	
	TileMapComponent* tm = TileMap_Factory.RequestComponent(m_rm, m_renderer->GetRenderer());
	
	const rapidjson::Value& a = d["map"];
	
	int sheetRows = (d["setH"].GetInt())/(d["tileH"].GetInt());
	//printf(" Sheet Rows %i ", d["tileW"].GetInt());
	int sheetCols = d["setW"].GetInt()/(d["tileW"].GetInt());
	//printf(" Sheet Cols %i ", d["tileH"].GetInt());

	int numberOfColumns = a.Size();
	//printf(" Num Cols %i ", numberOfColumns);
	int numberOfRows = a[rapidjson::SizeType(0)].Size();

	
	tm->init(d["tileSet"].GetString(), sheetRows, sheetCols, d["tileW"].GetInt(), d["tileH"].GetInt(), xSize,ySize, numberOfColumns, numberOfRows);
	
	for (rapidjson::SizeType y = 0; y < numberOfColumns; y++){
		const rapidjson::Value& b = a[y];
		for(rapidjson::SizeType x = 0; x < numberOfRows; x++){
			//printf(" Value: %i ", b[x].GetInt());
			tm->SetTile(x, y, b[x].GetInt());
		}
		//printf("\n");
	}
	
	const rapidjson::Value& c = d["collision"];
	for(rapidjson::SizeType i = 0; i < c.Size(); i++){
		tm->addCollidableTile(c[i].GetInt());
		printf(" Value: %i ", c[i].GetInt());
	}
    printf("\n");
	
	
	//printf(d["tileSet"].GetString());
	return tm;
}