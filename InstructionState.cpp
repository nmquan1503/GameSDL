#include "InstructionState.h"

std::string InstructionState::p_InsID="INSTRUCTION";

void InstructionState::update()
{
    Vector2D* vec=HandleInput::GetInstance()->GetMousePos();
    Vector2D scr_pos=static_cast<SDLGameObject*>(p_gameObjects[1])->GetPos();
    if(HandleInput::GetInstance()->GetMouse(0))
    {

        if(vec->GetX()>0&&vec->GetX()<60&&vec->GetY()>0&&vec->GetY()<60&&p_scrolling==false)
        {
            Game::GetInstance()->GetGameStateMachine()->popState();
        }

        if((vec->GetX()>scr_pos.GetX()&&vec->GetX()<scr_pos.GetX()+21&&vec->GetY()>115&&vec->GetY()<585)||p_scrolling==true)
        {


            p_scrolling=true;
            int y_new=std::max(115,std::min((int)(vec->GetY()-150),285));
            static_cast<SDLGameObject*>(p_gameObjects[1])->SetPos(Vector2D(992,y_new));
            for(int i=0; i<p_gameObjects.size(); i++)
            {
                if(i!=1)
                    static_cast<MenuButton*>(p_gameObjects[i])->SetVel(Vector2D(0,(-y_new+y_scr)*2));
            }
            y_scr=y_new;
        }
    }
    else

        p_scrolling=false;


    for(GameObject* i:p_gameObjects)
        i->update();
}

void InstructionState::render()
{
    p_gameObjects[0]->draw();

    ManageTexture::GetInstance()->draw("scroll1",990,113,25,474,Game::GetInstance()->GetRenderer(),true);

    for(int i=1;i<p_gameObjects.size();i++)
        p_gameObjects[i]->draw();


    ManageTexture::GetInstance()->draw("return",0,0,60,60,Game::GetInstance()->GetRenderer(),true);

}

bool InstructionState::onEnter()
{
    ManageTexture::GetInstance()->load("Image/instruction.png","instruction",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/scroll1.png","scroll1",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/scroll2.png","scroll2",Game::GetInstance()->GetRenderer());

    p_gameObjects.push_back(new SDLGameObject(new LoaderParams(0,0,1020,940,"instruction")));
    p_gameObjects.push_back(new SDLGameObject(new LoaderParams(992,115,21,300,"scroll2")));


    return true;
}

bool InstructionState::onExit()
{
    ManageTexture::GetInstance()->clearFromTexMap("instruction");
    ManageTexture::GetInstance()->clearFromTexMap("scroll1");
    ManageTexture::GetInstance()->clearFromTexMap("scroll2");

    for(GameObject* i:p_gameObjects)
        i->clean();
    p_gameObjects.clear();
    return true;
}
