#pragma once

#include "../ecs.hpp"
#include "../../events/eventhandler.hpp"
#include "../../events/KeyPressedEvent.hpp"

#define MAXBITS 1024

class KeyBoardControlSystem : public System
{
    public:
        KeyBoardControlSystem()
        {
        }
        std::bitset<MAXBITS> keyBoardMask;
        std::unordered_map<int, SDL_Keycode> int2Keycode;
        std::unordered_map<std::string, int> keycodeDict;
        int keys = 0;
        
        void ListenToEvents(std::unique_ptr<EventHandler>& eventHandler)
        {
            //eventHandler->ListenToEvent<KeyPressedEvent>(this, &KeyBoardMovementSystem::KeyPressed);
            //eventHandler->ListenToEvent<KeyPressedEvent>(this, &KeyBoardMovementSystem::OnKeyPressed);
            eventHandler->ListenToEvent(this, &KeyBoardControlSystem::OnKeyPressed);
            //just an initialized for now
            keycodeDict["d"] = keys++;
            int2Keycode[keys] = 100;
        }

        void OnKeyPressed(KeyPressedEvent& event)
        {
            std::string sym(1, event.keycode);
            //Logger::Log(LOG_INFO,"[" + std::to_string(event.keycode) + "] " + sym + " key was pressed");
            if (keycodeDict.count(sym)) 
            { 
                    keycodeDict[sym] = keys++; 
                    int2Keycode[keys] = event.keycode;
            }
            keyBoardMask.set(keycodeDict[sym]);
        }

        bool isKeyPressed(int key)
        {
                std::bitset<MAXBITS> keyMask;
                keyMask.set(key);
                return ((keyMask & keyBoardMask) == keyMask);
        }

        void ClearKeyBoardMask() { keyBoardMask.reset(); }

        int GetKey(std::string keysym) 
        { 
            return keycodeDict[keysym];
         }
  
};
