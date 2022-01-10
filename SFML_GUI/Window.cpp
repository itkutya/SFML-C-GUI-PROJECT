#include "Window.h"

Window::Window(sf::VideoMode vm, const char* t)
	            :	videomode(vm), title(t)
{
	this->window.create(this->videomode, this->title);
    //this->window.setVerticalSyncEnabled(true);
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

    this->window.draw(this->buttons);
    this->window.draw(this->toggels);
    this->window.draw(this->sliders);
    this->window.draw(this->images);
    this->window.draw(this->dropdowns);

    this->window.display();
}

void Window::update()
{
    this->mousePos = this->window.mapPixelToCoords(sf::Mouse::getPosition(this->window));

    this->buttons.update(this->mousePos, this->event);
    this->toggels.update(this->mousePos, this->event);
    this->sliders.update(this->mousePos, this->event);
    this->images.update(this->mousePos, this->event);
    this->dropdowns.update(this->mousePos, this->event);

    this->window.setSize(sf::Vector2u(this->dropdowns.setActiveElement().width, this->dropdowns.setActiveElement().height));

    if (this->buttons.getClicked(0) && !this->toggels.getState(0))
    {
        std::cout << "Button 0 has been clicked.\n";
        this->Quit();
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