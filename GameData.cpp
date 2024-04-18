#include "GameData.h"

GameData* GameData::Instance=NULL;

GameData* GameData::GetInstance()
{
    if(Instance==NULL)
    {
        Instance=new GameData();
    }
    return Instance;
}

void GameData::loadData(const char* filename)
{
    tinyxml2::XMLDocument doc;

    if (doc.LoadFile(filename) != tinyxml2::XML_SUCCESS) {
        return;
    }

    const tinyxml2::XMLElement* root = doc.FirstChildElement("game_data");
    if (!root) {
        return;
    }

    gold = root->FirstChildElement("gold") ? root->FirstChildElement("gold")->IntAttribute("quantity", 0) : 0;
    gem = root->FirstChildElement("gem") ? root->FirstChildElement("gem")->IntAttribute("quantity", 0) : 0;

    const tinyxml2::XMLElement* spellsElement = root->FirstChildElement("spells");
    if (spellsElement) {
        const tinyxml2::XMLElement* spellElement = spellsElement->FirstChildElement("spell");
        while (spellElement) {
            const char* spellType = spellElement->Attribute("type");
            if (spellType) {
                if (std::strcmp(spellType, "hp") == 0) {
                    hp_spell = spellElement->IntAttribute("quantity", 0);
                } else if (std::strcmp(spellType, "mana") == 0) {
                    mana_spell = spellElement->IntAttribute("quantity", 0);
                } else if (std::strcmp(spellType, "damage") == 0) {
                    damage_spell = spellElement->IntAttribute("quantity", 0);
                }
                else if (std::strcmp(spellType, "hp_x2") == 0) {
                    hp_x2_spell = spellElement->IntAttribute("quantity", 0);
                }
                else if (std::strcmp(spellType, "mana_x2") == 0) {
                    mana_x2_spell = spellElement->IntAttribute("quantity", 0);
                }
                else if (std::strcmp(spellType, "speed") == 0) {
                    speed_spell = spellElement->IntAttribute("quantity", 0);
                }
            }
            spellElement = spellElement->NextSiblingElement("spell");
        }
    }
    const tinyxml2::XMLElement* playerElement = root->FirstChildElement("player");
    if(playerElement)
    {
        const tinyxml2::XMLElement* player=playerElement->FirstChildElement("attribute");
        while(player)
        {
            const char* type=player->Attribute("type");
            if(type)
            {
                if(std::strcmp(type,"hp")==0)
                {
                    hp_player=player->IntAttribute("quantity",0);
                }
                else if(std::strcmp(type,"mana")==0)
                {
                    mana_player=player->IntAttribute("quantity",0);
                }
                else if(std::strcmp(type,"damage")==0)
                {
                    damage_player=player->IntAttribute("quantity",0);
                }
                else if(std::strcmp(type,"speed")==0)
                {
                    speed_player=player->IntAttribute("quantity",0);
                }
                else if(std::strcmp(type,"dart")==0)
                {
                    dart_level=player->IntAttribute("quantity",0);
                }
            }
            player=player->NextSiblingElement("attribute");
        }
    }
    const tinyxml2::XMLElement* achieveElement=root->FirstChildElement("achievement");
    if(achieveElement)
    {
        const tinyxml2::XMLElement* achieve=achieveElement->FirstChildElement("attribute");
        while(achieve)
        {
            const char* type=achieve->Attribute("type");
            if(type)
            {
                if(std::strcmp(type,"score")==0)
                {
                    best_score=achieve->IntAttribute("quantity",0);
                }
                else if(std::strcmp(type,"time")==0)
                {
                    best_time=achieve->IntAttribute("quantity",0);
                }
            }
            achieve=achieve->NextSiblingElement("attribute");
        }
    }
}

void GameData::saveData(const char* filename)
{
     tinyxml2::XMLDocument doc;

    tinyxml2::XMLElement* root = doc.NewElement("game_data");
    doc.InsertFirstChild(root);

    tinyxml2::XMLElement* goldElement = doc.NewElement("gold");
    goldElement->SetAttribute("quantity", gold);
    root->InsertEndChild(goldElement);

    tinyxml2::XMLElement* gemElement = doc.NewElement("gem");
    gemElement->SetAttribute("quantity", gem);
    root->InsertEndChild(gemElement);




    tinyxml2::XMLElement* spellsElement = doc.NewElement("spells");
    root->InsertEndChild(spellsElement);

    tinyxml2::XMLElement* hpSpellElement = doc.NewElement("spell");
    hpSpellElement->SetAttribute("type", "hp");
    hpSpellElement->SetAttribute("quantity", hp_spell);
    spellsElement->InsertEndChild(hpSpellElement);

    tinyxml2::XMLElement* manaSpellElement = doc.NewElement("spell");
    manaSpellElement->SetAttribute("type", "mana");
    manaSpellElement->SetAttribute("quantity", mana_spell);
    spellsElement->InsertEndChild(manaSpellElement);

    tinyxml2::XMLElement* damageSpellElement = doc.NewElement("spell");
    damageSpellElement->SetAttribute("type", "damage");
    damageSpellElement->SetAttribute("quantity", damage_spell);
    spellsElement->InsertEndChild(damageSpellElement);

    tinyxml2::XMLElement* hpX2SpellElement = doc.NewElement("spell");
    hpX2SpellElement->SetAttribute("type", "hp_x2");
    hpX2SpellElement->SetAttribute("quantity", hp_x2_spell);
    spellsElement->InsertEndChild(hpX2SpellElement);

    tinyxml2::XMLElement* manaX2SpellElement = doc.NewElement("spell");
    manaX2SpellElement->SetAttribute("type", "mana_x2");
    manaX2SpellElement->SetAttribute("quantity", mana_x2_spell);
    spellsElement->InsertEndChild(manaX2SpellElement);

    tinyxml2::XMLElement* speedSpellElement = doc.NewElement("spell");
    speedSpellElement->SetAttribute("type", "speed");
    speedSpellElement->SetAttribute("quantity", speed_spell);
    spellsElement->InsertEndChild(speedSpellElement);





    tinyxml2::XMLElement* playerElement = doc.NewElement("player");
    root->InsertEndChild(playerElement);

    tinyxml2::XMLElement* hpElement = doc.NewElement("attribute");
    hpElement->SetAttribute("type", "hp");
    hpElement->SetAttribute("quantity", hp_player);
    playerElement->InsertEndChild(hpElement);

    tinyxml2::XMLElement* manaElement = doc.NewElement("attribute");
    manaElement->SetAttribute("type", "mana");
    manaElement->SetAttribute("quantity", mana_player);
    playerElement->InsertEndChild(manaElement);

    tinyxml2::XMLElement* damageElement = doc.NewElement("attribute");
    damageElement->SetAttribute("type", "damage");
    damageElement->SetAttribute("quantity", damage_player);
    playerElement->InsertEndChild(damageElement);

    tinyxml2::XMLElement* speedElement = doc.NewElement("attribute");
    speedElement->SetAttribute("type", "speed");
    speedElement->SetAttribute("quantity", speed_player);
    playerElement->InsertEndChild(speedElement);

    tinyxml2::XMLElement* dartElement = doc.NewElement("attribute");
    dartElement->SetAttribute("type", "dart");
    dartElement->SetAttribute("quantity", dart_level);
    playerElement->InsertEndChild(dartElement);



    tinyxml2::XMLElement* achieveElement=doc.NewElement("achievement");
    root->InsertEndChild(achieveElement);

    tinyxml2::XMLElement* scoreElement=doc.NewElement("attribute");
    scoreElement->SetAttribute("type","score");
    scoreElement->SetAttribute("quantity",best_score);
    achieveElement->InsertEndChild(scoreElement);

    tinyxml2::XMLElement* timeElement=doc.NewElement("attribute");
    timeElement->SetAttribute("type","time");
    timeElement->SetAttribute("quantity",best_time);
    achieveElement->InsertEndChild(timeElement);


    doc.SaveFile(filename);
}


