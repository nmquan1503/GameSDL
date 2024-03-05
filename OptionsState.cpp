
#include "OptionsState.h"

std::string OptionsState::p_OptionsID="OPTIONS";

void OptionsState::update()
{
    if(HandleInput::GetInstance()->GetMouse(0))
    {
        Vector2D* vec=HandleInput::GetInstance()->GetMousePos();
        if(vec->GetX()>=250&&vec->GetX()<=313&&vec->GetY()>=190&&vec->GetY()<=253&&music_fix==false&&sfx_fix==false)
        {
            Game::GetInstance()->GetGameStateMachine()->changeState(new MenuState());
        }
        else if(((vec->GetX()>=385&&vec->GetX()<=687&&vec->GetY()>=258&&vec->GetY()<=288)||sfx_fix==true)&&music_fix==false)
        {
            sfx_fix=true;
            int t=std::min(128,std::max(0,(int)((vec->GetX()-23-385)/2)));
            ManageSound::GetInstance()->fixVolumeSFX(t);
            static_cast<SDLGameObject*>(p_gameObjects[0])->SetPos(Vector2D(385+2*t,258));
        }
        else if(((vec->GetX()>=385&&vec->GetX()<=687&&vec->GetY()>=313&&vec->GetY()<=343)||music_fix==true)&&sfx_fix==false)
        {
            music_fix=true;
            int t=std::min(128,std::max(0,(int)((vec->GetX()-23-385)/2)));
            ManageSound::GetInstance()->fixVolumeMusic(t);
            static_cast<SDLGameObject*>(p_gameObjects[1])->SetPos(Vector2D(385+2*t,313));

        }


    }
    else
        {
            sfx_fix=false;
            music_fix=false;
        }


    for(GameObject* i:p_gameObjects)
        i->update();
}

void OptionsState::render()
{
    ManageTexture::GetInstance()->draw("soundmenu",250,190,510,210,Game::GetInstance()->GetRenderer(),true);
    for(GameObject* i:p_gameObjects)
        i->draw();
}

bool OptionsState::onEnter()
{

    ManageTexture::GetInstance()->load("Image/soundmenu.png","soundmenu",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/sound3.png","sound",Game::GetInstance()->GetRenderer());

    ManageSound::GetInstance()->load("Audio/SoundMenu.mp3","soundmenu",SOUND_MUSIC);


    ManageSound::GetInstance()->playMusic("soundmenu",-1);

    int v1=ManageSound::GetInstance()->GetVolumeSFX();
    int v2=ManageSound::GetInstance()->GetVolumeMusic();

    p_gameObjects.push_back(new SDLGameObject(new LoaderParams(385+2*v1,258,46,30,"sound")));
    p_gameObjects.push_back(new SDLGameObject(new LoaderParams(385+2*v2,313,46,30,"sound")));
    return true;
}

bool OptionsState::onExit()
{
    ManageTexture::GetInstance()->clearFromTexMap("soundmenu");
    ManageTexture::GetInstance()->clearFromTexMap("sound");

    ManageSound::GetInstance()->clearFromMusicMap("soundmenu");
    for(GameObject* i:p_gameObjects)
        i->clean();
    p_gameObjects.clear();

    return true;
}
