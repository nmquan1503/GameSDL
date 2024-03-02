
#include "tinyxml.h"

#include <iostream>
#include <vector>

class GameObject;

class StateParser
{
private:
    void parseObjects(TiXmlElement* pStateRoot, std::vector<GameObject*> *pObjects);
    void parseTextures(TiXmlElement* pStateRoot, std::vector<std::string> *pTextureIDs);
public:
    bool parseState(const char* stateFile, std::string stateID, std::vector<GameObject*> *pObjects);
};
