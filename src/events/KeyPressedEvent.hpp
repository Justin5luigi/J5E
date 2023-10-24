#pragma once

#include "event.hpp"
#include <SDL2/SDL.h>
#include <string>

class KeyPressedEvent : public Event
{
    public:
        SDL_Keycode keycode;
        KeyPressedEvent(SDL_Keycode key) : keycode(key) {}
};
