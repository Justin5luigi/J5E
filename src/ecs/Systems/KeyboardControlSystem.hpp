#pragma once

#include "../ecs.hpp"
#include "../../events/eventhandler.hpp"
#include "../../events/KeyPressedEvent.hpp"

class KeyBoardControlSystem : public System
{
    public:
        KeyBoardControlSystem()
        {
        }
        
        void ListenToEvents(std::unique_ptr<EventHandler>& eventHandler)
        {
            //eventHandler->ListenToEvent<KeyPressedEvent>(this, &KeyBoardMovementSystem::KeyPressed);
            //eventHandler->ListenToEvent<KeyPressedEvent>(this, &KeyBoardMovementSystem::OnKeyPressed);
            eventHandler->ListenToEvent(this, &KeyBoardControlSystem::OnKeyPressed);
        }

        void OnKeyPressed(KeyPressedEvent& event)
        {
                std::string sym(1, event.keycode);
            Logger::Log(LOG_INFO,"[" + std::to_string(event.keycode) + "] " + sym + " key was pressed");
        }
  
};
