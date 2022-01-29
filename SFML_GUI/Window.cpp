#include "pch.h"

#include "Window.h"

void Window::printf()
{
    std::cout << "f\n";
}

void Window::recreateWindow()
{
    std::cout << "Window resized to: " << this->string[this->main_menu.getState("Resolution")] << "\n";
    this->window->create(this->modes[this->main_menu.getState("Resolution")], this->title, this->style);
    this->window->setFramerateLimit(60);
}

void Window::setFullscreen()
{
    if (this->main_menu.getState("Fullscreen") == 1)
    {
        this->style = sf::Style::Fullscreen;
        this->recreateWindow();
    }
    else if(this->main_menu.getState("Fullscreen") == 0)
    {
        this->style = sf::Style::Default;
        this->recreateWindow();
    }
}

void Window::setVolume()
{
    std::cout << this->main_menu.getState("Volume") << "\n";
}

Window::Window(const char* t) : title(t)
{
    this->CreateVideoModes();
    this->CheckVersion();

    this->main_menu.CreateDropdown("Resolution", this->string, std::bind(&Window::recreateWindow, this));

    this->window = std::make_unique<sf::RenderWindow>();
    this->window->create(this->modes[this->main_menu.getState("Resolution")], this->title, sf::Style::Default);
    this->window->setFramerateLimit(60);

    this->main_menu.CreateButton("Quit", std::bind(&Window::Quit, this));
    this->main_menu.CreateButton("Quit2", std::bind(&Window::printf, this));
    this->main_menu.CreateToggle("Fullscreen", std::bind(&Window::setFullscreen, this));
    this->main_menu.CreateSlider("Volume", std::bind(&Window::setVolume, this));
    this->main_menu.CreateImage("Profile");

    this->event = sf::Event();
    this->mousePos = sf::Vector2f();
}

Window::~Window()
{

}

bool Window::IsOpen()
{
	return this->window->isOpen();
}

void Window::Quit()
{
    this->window->close();
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

const void Window::CreateVideoModes()
{
    this->modes = sf::VideoMode::getFullscreenModes();
    for (std::size_t i = 0; i < modes.size(); ++i)
        this->string.push_back(std::to_string(modes[i].width) + "x" + std::to_string(modes[i].height));
}

const void Window::CheckVersion()
{
    if ((float)VERSION != this->main_menu.getVersion())
        std::cout << "Old version detected!\n";
    else
        std::cout << "You are up to date!\n";
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
    this->main_menu.update(mousePos, this->event);
    this->PollEvents();
}