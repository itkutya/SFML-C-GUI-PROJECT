#pragma once

#include "Timer.h"

#include "GUI.h"

#define VERSION 0.1

class Window
{
	public:
		Window(sf::VideoMode vm = sf::VideoMode(600, 600), const char* t = "Default title.");
		virtual ~Window();

		bool IsOpen();

		void update();
		void draw();
	private:
		sf::RenderWindow window;
		sf::VideoMode videomode;
		const char* title;

		sf::Event event;
		sf::Vector2f mousePos;

		GUI::Button button;
		GUI::Toggle toggle;

		//TODO: More GUI elements (Image, Dropdown, etc...)
		//TODO: Save location of GUI elements, editor state
		//TODO: Make 1 big .cpp and .h GUI file
		//TODO: Make it so you can change the area of the images
		//TODO:	Zoomable images
		//TODO: Find a way to change the images
		//TODO: Fix the dropdown class
		
		//TODO: Audio system, audio source for 3D sounds <-- <3 Want to do this!!!
		//TODO: Put draw on different thread
		//TODO: State system
		//TODO: Add comments
		//TODO: Optimailise the code

		const void PollEvents();
		const void Quit();
		const float getVersion();
};