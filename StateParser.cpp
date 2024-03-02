
#include "StateParser.h"

bool StateParser::parseState(const char* stateFile, std::string stateID, std::vector<GameObject*> *pObjects)
{

    TiXmlDocument xmlDoc;

    if(!xmlDoc.LoadFile(stateFile))
    {
        cerr << xmlDoc.ErrorDesc() << "\n";
        return false;
    }

    TiXmlElement* pRoot = xmlDoc.RootElement();

    TiXmlElement* pStateRoot = 0;

    for(TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e =
                e->NextSiblingElement())
    {
        if(e->Value() == stateID)
        {
            pStateRoot = e;
        }
    }

    TiXmlElement* pTextureRoot = 0;

    for(TiXmlElement* e = pStateRoot->FirstChildElement(); e !=
            NULL; e = e->NextSiblingElement())
    {
        if(e->Value() == string("TEXTURES"))
        {
            pTextureRoot = e;
        }
    }

    parseTextures(pTextureRoot, pTextureIDs);

    TiXmlElement* pObjectRoot = 0;

    for(TiXmlElement* e = pStateRoot->FirstChildElement(); e !=
            NULL; e = e->NextSiblingElement())
    {
        if(e->Value() == string("OBJECTS"))
        {
            pObjectRoot = e;
        }
    }
    parseObjects(pObjectRoot, pObjects);
    return true;
}

void StateParser::parseTextures(TiXmlElement* pStateRoot,
                                std::vector<std::string> *pTextureIDs)
{
    for(TiXmlElement* e = pStateRoot->FirstChildElement(); e !=
            NULL; e = e->NextSiblingElement())
    {
        string filenameAttribute = e->Attribute("filename");
        string idAttribute = e->Attribute("ID");
        pTextureIDs->push_back(idAttribute); // push into list
        TheTextureManager::Instance()->load(filenameAttribute,
                                            idAttribute, TheGame::Instance()->getRenderer());
    }
}

void StateParser::parseObjects(TiXmlElement *pStateRoot,
                               std::vector<GameObject *> *pObjects)
{
    for(TiXmlElement* e = pStateRoot->FirstChildElement(); e !=
            NULL; e = e->NextSiblingElement())
    {
        int x, y, width, height, numFrames, callbackID, animSpeed;
        string textureID;
        e->Attribute("x", &x);
        e->Attribute("y", &y);
        e->Attribute("width",&width);
        e->Attribute("height", &height);
        e->Attribute("numFrames", &numFrames);
        e->Attribute("callbackID", &callbackID);
        e->Attribute("animSpeed", &animSpeed);
        textureID = e->Attribute("textureID");
        GameObject* pGameObject = TheGameObjectFactory::Instance()
                                  ->create(e->Attribute("type"));
        pGameObject->load(new LoaderParams
                          (x,y,width,height,textureID,numFrames,callbackID, animSpeed));
        pObjects->push_back(pGameObject);
    }
}
