#include "Node.h"
#include "SFML/Graphics.hpp"
#include <string>
#include "toString.hpp"

Node::Node(int x, int y, sf::Texture* texture, sf::Font* font1, bool passable)
{
    this->passable = passable;
    start = false;
    ending = false;
    nodeSize = 64;
    pos.x = x;
    pos.y= y;
    setPosition(pos.x, pos.y);
    rect.setSize(sf::Vector2f((float)x*nodeSize, (float)y*nodeSize));
    rect.setOrigin(0.0f, 0.0f);
    rect.setSize(sf::Vector2f(100, 100));

    //sArrow.setTexture(tex);

    setFill();

    rect.setOutlineThickness(2);
    rect.setOutlineColor(sf::Color(0, 0, 0));
    rect.setPosition((float)(pos.x*nodeSize),(float)(pos.y*nodeSize));

    h_text.setFont(*font1);
    h_text.setCharacterSize(12);
    h_text.setColor(sf::Color(255,0,0,255));
    h_text.setOrigin(0.0f, 0.0f);
	h_text.setPosition((float)(pos.x*nodeSize),(float)(pos.y*nodeSize));


}

Node::~Node()
{
    //dtor
}

void Node::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //states.transform *= getTransform();

    target.draw(rect);
    target.draw(h_text);
    target.draw(sArrow);
}

void Node::update()
{

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

void Node::setHeuristic(int heuristic)
{
	this->heuristic = heuristic;

	h_text.setString(toString(heuristic));
}


