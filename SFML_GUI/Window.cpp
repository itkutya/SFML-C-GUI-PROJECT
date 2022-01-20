#include "pch.h"

#include "Window.h"

Window::Window(const char* t) : title(t)
{
    this->modes = sf::VideoMode::getFullscreenModes();
    for (std::size_t i = 0; i < modes.size(); ++i)
    {
        this->string.push_back(std::to_string(modes[i].width) + "x" + std::to_string(modes[i].height));
    }

    this->main_menu.CreateDropdown(this->string, "Resolution");

    this->window = std::make_unique<sf::RenderWindow>();
    this->window->create(this->modes[this->main_menu.getActiveElement("Resolution")], this->title, sf::Style::Default);
    this->window->setFramerateLimit(60);

    this->main_menu.CreateButton("Quit");
    this->main_menu.CreateButton("Quit2");
    this->main_menu.CreateToggle("Fullscreen");
    this->main_menu.CreateSlider("Volume");
    this->main_menu.CreateImage("Profile");

    this->event = sf::Event();
    this->mousePos = sf::Vector2f();

    if ((float)VERSION != this->main_menu.getVersion())
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
                std::cout << "Scrolling up!\n";
            }
            else if (event.mouseWheel.delta < 0)
            {
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

    this->window->draw(this->main_menu);

    this->window->display();
}

void Window::update()
{
    this->mousePos = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));

    bool togglestate = this->main_menu.getState("Fullscreen");
    float slidervalue = this->main_menu.getValue("Volume");
    int dropdownactive = this->main_menu.getActiveElement("Resolution");

    this->main_menu.update(mousePos, this->event);
    
    if (this->main_menu.onButtonClick("Quit"))
    {
        std::cout << "Quit button has been pushed!\nQuiting the application!\n";
        this->window->close();
    }
    if (this->main_menu.onButtonClick("Quit2"))
    {
        std::cout << "Quit2 has been pushed!\nThe application will not quiting!\n";
    }
    
    if (togglestate != this->main_menu.getState("Fullscreen") && this->main_menu.getState("Fullscreen"))
    {
        this->window->create(this->modes[this->main_menu.getActiveElement("Resolution")], this->title, sf::Style::Fullscreen);
        this->window->setFramerateLimit(60);
        std::cout << "Toggle 0 is true!\nFullscreen has been turned on!\n";
    }
    else if (togglestate != this->main_menu.getState("Fullscreen") && !this->main_menu.getState("Fullscreen"))
    {
        this->window->create(this->modes[this->main_menu.getActiveElement("Resolution")], this->title, sf::Style::Default);
        this->window->setFramerateLimit(60);
        std::cout << "Toggle 0 is false!\nFullscreen has been turned off!\n";
    }

    if (slidervalue != this->main_menu.getValue("Volume"))
    {
        std::cout << this->main_menu.getValue("Volume") << "\n";
    }

    if (dropdownactive != this->main_menu.getActiveElement("Resolution"))
    {
        if (this->main_menu.getState("Fullscreen"))
        {
            std::cout << "Window resized to: " << this->string[this->main_menu.getActiveElement("Resolution")] << "\n";
            this->window->create(this->modes[this->main_menu.getActiveElement("Resolution")], this->title, sf::Style::Fullscreen);
            this->window->setFramerateLimit(60);
        }
        if (!this->main_menu.getState("Fullscreen"))
        {
            std::cout << "Window resized to: " << this->string[this->main_menu.getActiveElement("Resolution")] << "\n";
            this->window->create(this->modes[this->main_menu.getActiveElement("Resolution")], this->title, sf::Style::Default);
            this->window->setFramerateLimit(60);
        }
    }

    this->PollEvents();
}