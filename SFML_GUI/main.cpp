#include "Window.h"

int main()
{
    Window window(sf::VideoMode(800, 600), "SFML GUI");

    try 
    {
        while (window.IsOpen())
        {
            window.update();
            window.draw();
        }
    }
    catch (const std::exception& e) 
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}