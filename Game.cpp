
#include "Game.h"

Game* Game::Instance=NULL;


Game::Game()
{
    p_window=NULL;
    p_renderer=NULL;
    p_Running=true;
}

Game* Game::GetInstance()
{
    if(Instance==NULL)
        {
            Instance=new Game();
        }
    return Instance;
}

Game::~Game()
{

}

bool Game::init(const char* title,int width,int height)
{
    if(SDL_Init(SDL_INIT_EVERYTHING)==0)
    {
        p_window=SDL_CreateWindow(title,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,width,height,SDL_WINDOW_SHOWN);

        if(p_window!=NULL)
        {
            p_renderer=SDL_CreateRenderer(p_window,-1,SDL_RENDERER_ACCELERATED);

            if(p_renderer!=NULL)
            {
                /*MTex=ManageTexture::GetInstance();
                MTex->load("Image/backgroud.png","BG",p_renderer);
                MTex->load("Image/run.png","run",p_renderer);
                MTex->load("Image/soldier1_40_65.png","soldier1",p_renderer);
                MTex->load("Image/jump.png","jump",p_renderer);
                MTex->load("Image/nor.png","nor",p_renderer);
                MTex->load("Image/jumpup.png","jumpup",p_renderer);
                MTex->load("Image/jumpdown.png","jumpdown",p_renderer);
                MTex->load("Image/santo.png","santo",p_renderer);*/
                p_GameStateMachine=new GameStateMachine();
                p_GameStateMachine->changeState(new MenuState());


                /*GameObjects.push_back(new Soldier(new LoaderParams(900,500,40,65,"soldier1")));
                GameObjects.push_back(new Player(new LoaderParams(500,300,50,75,"nor")));*/
            }
            else
            {
                std::cout<<"ERROR:"<<SDL_GetError()<<std::endl;
                return false;
            }
        }
        else
        {
            std::cout<<"ERROR2:"<<SDL_GetError()<<std::endl;
            return false;
        }

    }
    else
    {
        std::cout<<"ERROR3:"<<SDL_GetError()<<std::endl;
        return false;
    }
    return true;
}

void Game::clean()
{
    HandleInput::GetInstance()->clean();
    SDL_DestroyWindow(p_window);
    SDL_DestroyRenderer(p_renderer);
    SDL_Quit();
}

void Game::handleEvents()
{
    HandleInput::GetInstance()->update();
    if(HandleInput::GetInstance()->IsKeyDown(SDL_SCANCODE_RETURN))
    {
        p_GameStateMachine->changeState(new PlayState());
    }
}

void Game::update()
{
    /*for(GameObject* obj:GameObjects)
    {
        obj->update();
    }*/

    p_GameStateMachine->update();
}

void Game::render()
{
    SDL_RenderClear(p_renderer);

    /*for(GameObject* obj:GameObjects)
    {
        obj->draw();
    }*/


    p_GameStateMachine->render();


    SDL_RenderPresent(p_renderer);
}

void Game::quit()
{
    SDL_Quit();
}
