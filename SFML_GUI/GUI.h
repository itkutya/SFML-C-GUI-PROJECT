#pragma once

namespace GUI
{
	class Button : public sf::Drawable, public sf::Transformable
	{
	public:
		Button();
		virtual ~Button();

		void update(const sf::Vector2f& mousePos, sf::Event& event);
		const bool onButtonClick(unsigned short int index);

	private:
		std::vector<sf::RectangleShape> m_shapes;
		std::vector<sf::Color> m_backgrounds;
		std::vector<sf::Text> m_texts;
		std::vector<bool> m_states;
		bool m_pressed = false;
		sf::Font m_font;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
	};

	class Toggle : public sf::Drawable, public sf::Transformable
	{
	public:
		Toggle();
		virtual ~Toggle();

		void update(const sf::Vector2f& mousePos, sf::Event& event);
		const bool getState(unsigned short int index);

		bool m_pressed = false;
	private:
		std::vector<sf::RectangleShape> m_shapes;
		std::vector<sf::Color> m_backgrounds;
		std::vector<sf::Text> m_texts;
		std::vector<bool> m_states;
		sf::Font m_font;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
	};
}