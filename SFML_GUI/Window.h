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
		//TODO: Put draw on different thread
		//TODO: State system
		//TODO: Audio system, audio source for 3D sounds
		//TODO: Make it so you can change the area of the images
		//TODO:	Zoomable images
		//TODO: Find a way to change the images
		//TODO: Fix the dropdown class
		//TODO: Add comments
		//TODO: Optimailise the code

		const void PollEvents();
		const void Quit();
		const float getVersion();

		//TODO: Delete this later
		void clear_screen(char fill = ' ') {
			COORD tl = { 0,0 };
			CONSOLE_SCREEN_BUFFER_INFO s;
			HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
			GetConsoleScreenBufferInfo(console, &s);
			DWORD written, cells = s.dwSize.X * s.dwSize.Y;
			FillConsoleOutputCharacter(console, fill, cells, tl, &written);
			FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
			SetConsoleCursorPosition(console, tl);
		}
};