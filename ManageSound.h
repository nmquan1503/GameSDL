#ifndef _ManageSound_h_
#define _ManageSound_h_


#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>

#include <iostream>
#include <map>


enum sound_type
{
    SOUND_MUSIC=0,
    SOUND_SFX=1
};

class ManageSound
{
private:
    static ManageSound* Instance;
    ManageSound();
    ~ManageSound();
    std::map<std::string,Mix_Chunk*>SFX_Map;
    std::map<std::string,Mix_Music*>Music_Map;

    ManageSound(const ManageSound&);
    ManageSound &operator=(const ManageSound&);
public:
    static ManageSound* GetInstance();
    bool load(std::string fileName,std::string id,sound_type type);
    void playSound(std::string id,int loop);
    void playMusic(std::string id,int loop);

};



#endif // _ManageSound_h_
