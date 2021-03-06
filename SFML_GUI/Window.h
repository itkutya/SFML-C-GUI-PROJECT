#pragma once

#include "Timer.h"

#include "GUI.h"

class Window
{
	public:
		Window(const char* t = "Default title.");
		virtual ~Window();

		bool IsOpen();

		void update();
		void draw();
	private:
		sf::RenderWindow window;
		const char* title;

		int style = sf::Style::Default;
		int fps_limit = 60;

		sf::Event event;
		sf::Vector2f mousePos;

		GUI::Menu main_menu;

		std::vector<sf::VideoMode> modes;
		std::vector<std::string> string;

		std::vector<std::string> av_fps;

		//TODO: Add inputbox
		//TODO: Save location of GUI elements, editor state
		//TODO: Make it so you can change the area of the images
		//TODO:	Zoomable images
		//TODO: Find a way to change the images
		//TODO: Fix the dropdown class
		//
		//TODO: Audio system, audio source for 3D sounds <-- <3 Want to do this!!!
		//TODO: Put draw on different thread
		//TODO: State system
		//TODO: Add comments
		//TODO: Optimailise the code

		const void PollEvents();
		void Quit();
		const void CreateVideoModes();
		const void CreateAvFPS();
		const void CheckVersion();

		void printf();
		void recreateWindow();
		void setFullscreen();
		void setVolume();
		void setFPSLimit();
};