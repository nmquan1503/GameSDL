#ifndef _GameData_h_
#define _GameData_h_

#include<iostream>
#include<vector>
#include<map>

#include "tinyxml2.h"

class GameData
{
private:
    int gold;
    int gem;
    int hp_spell;
    int mana_spell;
    int damage_spell;
    int hp_x2_spell;
    int mana_x2_spell;
    int speed_spell;

    int hp_player;
    int mana_player;
    int damage_player;
    int speed_player;
    int dart_level;

    int best_score;
    int best_time;

    static GameData* Instance;
    GameData():gold(0),gem(0),hp_spell(0),mana_spell(0),damage_spell(0),
                hp_x2_spell(0),mana_x2_spell(0),speed_spell(0),
                hp_player(0),mana_player(0),damage_player(0),speed_player(0),dart_level(1),
                best_score(0),best_time(0){}
    ~GameData(){}

public:
    static GameData* GetInstance();

    int GetGold(){return gold;}
    int GetGem(){return gem;}
    int GetHpSpell(){return hp_spell;}
    int GetManaSpell(){return mana_spell;}
    int GetDamageSpell(){return damage_spell;}
    int GetHpPlayer(){return hp_player;}
    int GetManaPlayer(){return mana_player;}
    int GetDamagePlayer(){return damage_player;}
    int GetSpeedPlayer(){return speed_player;}
    int GetHpX2(){return hp_x2_spell;}
    int GetManaX2(){return mana_x2_spell;}
    int GetSpeedSpell(){return speed_spell;}
    int GetLevelDart(){return dart_level;}
    int GetBestScore(){return best_score;}
    int GetBestTime(){return best_time;}

    void SetGold(int t){gold+=t;}
    void SetGem(int t){gem+=t;}
    void SetHpSpell(int t){hp_spell+=t;}
    void SetManaSpell(int t){mana_spell+=t;}
    void SetDamageSpell(int t){damage_spell+=t;}
    void SetHpPlayer(int t){hp_player+=t;}
    void SetManaPlayer(int t){mana_player+=t;}
    void SetDamagePlayer(int t){damage_player+=t;}
    void SetSpeedPlayer(int t){speed_player+=t;}
    void SetHpX2(int t){hp_x2_spell+=t;}
    void SetManaX2(int t){mana_x2_spell+=t;}
    void SetSpeedSpell(int t){speed_spell+=t;}
    void SetLevelDart(int t){dart_level+=t;}
    void SetBestScore(int t){best_score=t;}
    void SetBestTime(int t){best_time=t;}

    void loadData(const char* fileName);
    void saveData(const char* fileName);


};


#endif // _GameData_h_
