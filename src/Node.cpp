#include "Node.h"
#include "SFML/Graphics.hpp"

Node::Node(int x, int y, sf::Texture* texture, bool passable)
{
    this->passable = passable;
    start = false;
    ending = false;
    nodeSize = 64;
    pos.height = x;
    pos.width = y;
    rect.setSize(sf::Vector2f((float)x*nodeSize, (float)y*nodeSize));
    rect.setOrigin(0.0f, 0.0f);
    rect.setSize(sf::Vector2f(100, 100));

    //sArrow.setTexture(*texture);

    setFill();

    rect.setOutlineThickness(2);
    rect.setOutlineColor(sf::Color(0, 0, 0));

}

Node::~Node()
{
    //dtor
}

void Node::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //states.transform *= getTransform();

    target.draw(rect, states);

    //target.draw(sArrow);
}

void Node::update()
{
    rect.setPosition((float)(pos.height*nodeSize),(float)(pos.width*nodeSize));
    setFill();
}

void Node::setFill()
{
    if(start == true)
    {
       rect.setFillColor(sf::Color(0, 255, 0, 255));
    }
    else if(ending == true)
    {
        rect.setFillColor(sf::Color(0, 0, 255, 255));
    }
    else if(passable == true)
    {
        rect.setFillColor(sf::Color(255, 255, 255, 255));
    }
    else if(passable == false)
    {
        rect.setFillColor(sf::Color(255, 0, 0, 255));
    }

}

void Node::setPassable()
{
    if(passable == true)
    {
        passable = false;
    }
    else
    {
        passable = true;
    }
}

sf::FloatRect Node::getBounds() const
{
    return getTransform().transformRect(rect.getGlobalBounds());
}
