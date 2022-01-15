#include "pch.h"

#include "Window.h"

Window::Window(const char* t) : title(t)
{
    this->modes = sf::VideoMode::getFullscreenModes();
    for (std::size_t i = 0; i < modes.size(); ++i)
    {
        this->string.push_back(std::to_string(modes[i].width) + "x" + std::to_string(modes[i].height));
    }
    this->dropdown = new GUI::Dropdown(this->string);

    this->window = std::make_unique<sf::RenderWindow>();
    this->window->create(this->modes[this->dropdown->getActiveElement()], this->title, sf::Style::Default);
    this->window->setFramerateLimit(60);

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
    delete this->dropdown;
}

bool Window::IsOpen()
{
	return this->window->isOpen();
}

const void Window::PollEvents()
{
    while (this->window->pollEvent(this->event))
    {
        if (this->event.type == sf::Event::Closed)
        {
            this->window->close();
        }
        else if (event.type == sf::Event::MouseWheelMoved)
        {
            if (event.mouseWheel.delta > 0)
            {
                this->dropdown->scrool = 1;
                std::cout << "Scrolling up!\n";
            }
            else if (event.mouseWheel.delta < 0)
            {
                this->dropdown->scrool = -1;
                std::cout << "Scrolling down!\n";
            }
        }
    }
}

const void Window::Quit()
{
    this->window->close();
}

void Window::draw()
{
    this->window->clear();

    this->window->draw(this->button);
    this->window->draw(this->toggle);
    this->window->draw(this->slider);

    this->window->draw(*this->dropdown);

    this->window->display();
}

void Window::update()
{
    this->mousePos = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));

    this->button.update(this->mousePos, this->event);
    if (this->button.onButtonClick(0))
    {
        std::cout << "Button 0 has been pushed!\nQuiting the application!\n";
        this->window->close();
    }

    bool togglestate = this->toggle.getState(0);
    this->toggle.update(this->mousePos, this->event);
    if (togglestate != this->toggle.getState(0) && this->toggle.getState(0))
    {
        this->window->create(this->modes[this->dropdown->getActiveElement()], this->title, sf::Style::Fullscreen);
        this->window->setFramerateLimit(60);
        this->toggle.m_pressed = false;
        std::cout << "Toggle 0 is true!\nFullscreen has been turned on!\n";
    }
    else if (togglestate != this->toggle.getState(0) && !this->toggle.getState(0))
    {
        this->window->create(this->modes[this->dropdown->getActiveElement()], this->title, sf::Style::Default);
        this->window->setFramerateLimit(60);
        this->toggle.m_pressed = false;
        std::cout << "Toggle 0 is false!\nFullscreen has been turned off!\n";
    }

    this->slider.update(this->mousePos, this->event);
    this->toggle.m_shapes[0]->setScale(1.f, this->slider.getValue(0));

    int active = this->dropdown->getActiveElement();
    this->dropdown->update(this->mousePos, this->event);
    if (active != this->dropdown->getActiveElement())
    {
        if (this->toggle.getState(0))
        {
            std::cout << "Window resized to: " << this->string[this->dropdown->getActiveElement()] << "\n";
            this->window->create(this->modes[this->dropdown->getActiveElement()], this->title, sf::Style::Fullscreen);
            this->window->setFramerateLimit(60);
        }
        if (!this->toggle.getState(0))
        {
            std::cout << "Window resized to: " << this->string[this->dropdown->getActiveElement()] << "\n";
            this->window->create(this->modes[this->dropdown->getActiveElement()], this->title, sf::Style::Default);
            this->window->setFramerateLimit(60);
        }
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