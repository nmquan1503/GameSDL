#include "ManageSound.h"


ManageSound* ManageSound::Instance=NULL;

ManageSound* ManageSound::GetInstance()
{
    if(Instance==NULL)
    {
        Instance=new ManageSound();
    }
    return Instance;
}

ManageSound::ManageSound()
{
    Mix_OpenAudio(22050, AUDIO_S16, 2, 4096);
}

bool ManageSound::load(std::string fileName,std::string id,sound_type type)
{
    if(type==SOUND_MUSIC)
    {
        Mix_Music* p_Music=Mix_LoadMUS(fileName.c_str());
        if(p_Music==NULL)
        {
            std::cout<<"Error1:"<<Mix_GetError();
            return false;
        }
        Music_Map[id]=p_Music;
        return true;
    }
    else if(type==SOUND_SFX)
    {
        Mix_Chunk* p_Chunk=Mix_LoadWAV(fileName.c_str());
        if(p_Chunk==NULL)
        {
            std::cout<<"Error2:"<<Mix_GetError();
            return false;
        }
        SFX_Map[id]=p_Chunk;
        return true;
    }
    return false;
}

void ManageSound::playMusic(std::string id,int loop)
{
    Mix_PlayMusic(Music_Map[id],loop);
}

void ManageSound::playSound(std::string id,int loop)
{
    Mix_PlayChannel(-1,SFX_Map[id],loop);
}

ManageSound::~ManageSound()
{
    Mix_CloseAudio();
}

void ManageSound::clearFromMusicMap(std::string id)
{
    if(Music_Map[id]!=NULL)
        Music_Map.erase(id);
}

void ManageSound::clearFromSFXMap(std::string id)
{
    if(SFX_Map[id]!=NULL)
        SFX_Map.erase(id);
}

void ManageSound::fixVolumeMusic(int t)
{
    volume_music=std::min(128,std::max(0,t));
    Mix_VolumeMusic(volume_music);
}

void ManageSound::fixVolumeSFX(int t)
{
    volume_sfx=std::min(128,std::max(0,t));
    for(std::map<std::string,Mix_Chunk*>::iterator it= SFX_Map.begin();it!=SFX_Map.end();it++)
    {
        Mix_VolumeChunk(it->second,volume_sfx);
    }
}
