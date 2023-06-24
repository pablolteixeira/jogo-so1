#ifndef window_h
#define window_h

#include <iostream>
#include <png.h>
#include <SFML/Graphics.hpp>

class Window
{
public:
    Window();

    void run();

    void draw_texture(unsigned int texture, int length, int height, float angle);
};

#endif