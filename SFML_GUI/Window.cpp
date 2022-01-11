#include "pch.h"

#include "Window.h"

Window::Window(sf::VideoMode vm, const char* t)
	            :	videomode(vm), title(t)
{
	this->window.create(this->videomode, this->title);
    this->window.setFramerateLimit(60);

    this->event = sf::Event();
    this->mousePos = sf::Vector2f();

    if ((float)VERSION != this->getVersion())
    {
        std::cout << "Old version detected!\n";
    }
    else
    {
        std::cout << "You are up to date!\n";
    }
}

Window::~Window()
{

}

bool Window::IsOpen()
{
	return this->window.isOpen();
}

const void Window::PollEvents()
{
    while (this->window.pollEvent(this->event))
    {
        if (this->event.type == sf::Event::Closed)
            this->window.close();
    }
}

const void Window::Quit()
{
    this->window.close();
}

void Window::draw()
{
    this->window.clear();

    this->window.draw(this->button);
    this->window.draw(this->toggle);

    this->window.display();
}

void Window::update()
{
    this->mousePos = this->window.mapPixelToCoords(sf::Mouse::getPosition(this->window));

    this->button.update(this->mousePos, this->event);
    if (this->button.onButtonClick(0))
    {
        this->clear_screen();
        std::cout << "Button 0 has been pushed!\nConsol has been erased!\n";
    }

    bool togglestate = this->toggle.getState(0);
    this->toggle.update(this->mousePos, this->event);
    if (togglestate != this->toggle.getState(0) && this->toggle.getState(0))
    {
        this->window.create(sf::VideoMode::getFullscreenModes()[0], this->title, sf::Style::Fullscreen);
        this->toggle.m_pressed = false;
        std::cout << "Toggle 0 is true!\nFullscreen has been turned on!\n";
    }
    else if (togglestate != this->toggle.getState(0) && !this->toggle.getState(0))
    {
        this->window.create(this->videomode, this->title, sf::Style::Default);
        this->toggle.m_pressed = false;
        std::cout << "Toggle 0 is false!\nFullscreen has been turned off!\n";
    }

    this->PollEvents();
}

const float Window::getVersion()
{
    std::fstream file("resources/gui.txt");
    if (!file.good())
    {
        std::ofstream outfile("resources/gui.txt");
        outfile << "Reqierd data about entities are missing!";
        outfile.close();
        throw std::runtime_error("Restart requierd!");
    }
    file.close();

    std::ifstream data;
    data.open("resources/gui.txt");
    if (data.is_open())
    {
        std::string string = "";
        float version = 0.f;
        while (data >> string)
        {
            if (string == "#VERSION")
            {
                data >> version;
                data.close();

                return version;
            }
        }
    }
    else
    {
        throw std::runtime_error("Cannot open data file.");
    }
    data.close();

    return 0.f;
}