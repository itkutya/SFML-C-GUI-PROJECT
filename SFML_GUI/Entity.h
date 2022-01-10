#pragma once

class Entity : public sf::Drawable, public sf::Transformable
{
public:
    Entity();
    virtual ~Entity();

    //Boolean so we cannot spam gui element functions
    bool m_pressed = false;
    //Count for how many types we have of a certain entity
    unsigned short int m_count = 0;

    //General shape of an entity
    std::vector<sf::RectangleShape> m_shapes;
    //Texture for image, and for entities
    std::vector<sf::Texture> m_textures;
    //Default color of an entity, or background color
    std::vector<sf::Color> m_backgrounds;

    //Font
    sf::Font m_font;
    //Text for entities that has them
    std::vector<sf::Text> m_texts;

    //This function is defined for each and every entity, loads data.
    virtual void load_data() = 0;

private:
    //General draw function
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
};

