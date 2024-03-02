
#include <string>
#include <map>

#include "GameObject.h"
#include "Player.h"

class BaseCreator
{
public:
    virtual GameObject* createGameObject() const =0;
    virtual ~BaseCreator(){}
};

class GameObjectFactory
{
public:
    bool registerType(std::string typeID, BaseCreator* pCreator)
    {
        std::map<std::string ,BaseCreator*>:: iterator it=p_creators.find(typeID);
        if(it!=p_creators.end())
        {
            delete pCreator;
            return false;
        }
        p_creators[typeID]=pCreator;
        return true;
    }

    GameObject* create(std::string typeID)
    {
        std::map<std::string ,BaseCreator*>:: iterator it=p_creators.find(typeID);
        if(it==p_creators.end())
        {
            return NULL;
        }
        BaseCreator* pCreator=(*it).second;
        return pCreator->createGameOject();
    }

    GameObjectFactory* GetInstance()
    {
        if(Instance==NULL)
        {
            Instance=new GameObjectFactory();
        }
        return Instance;
    }

private:
    std::map<std::string, BaseCreator*>p_creators;
    static GameObjectFactory* Instance=NULL;
    GameObjectFactory(){}
};

class PlayerCreator : public BaseCreator
{
    GameObject* createGameObject() const
    {
        return new Player();
    }
};
