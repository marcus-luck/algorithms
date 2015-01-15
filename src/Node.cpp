#include "Node.h"
#include "SFML/Graphics.hpp"
#include <string>
#include "toString.hpp"

Node::Node(int x, int y, sf::Texture& texture, sf::Font& font1, bool passable)
: start(false)
, ending(false)
, passable(passable)
, nodeSize(64)
, fValue(0)
, mParent(nullptr)
{
    pos.x = x;
    pos.y = y;
    setPosition(pos.x, pos.y);

    rect.setSize(sf::Vector2f((float)x*nodeSize, (float)y*nodeSize));
    rect.setOrigin(0.0f, 0.0f);
    rect.setSize(sf::Vector2f(100, 100));

    sArrow.setTexture(texture);
    sArrow.setOrigin(sArrow.getLocalBounds().width/2, sArrow.getLocalBounds().height/2 );
    sArrow.setPosition((float)(pos.x*nodeSize+nodeSize/2),(float)(pos.y*nodeSize+nodeSize/2));

    setFill();

    rect.setOutlineThickness(2);
    rect.setOutlineColor(sf::Color(0, 0, 0));
    rect.setPosition((float)(pos.x*nodeSize),(float)(pos.y*nodeSize));

    h_text.setFont(font1);
    h_text.setCharacterSize(12);
    h_text.setColor(sf::Color(255,0,0,255));
    h_text.setOrigin(0.0f, 0.0f);
	h_text.setPosition((float)(pos.x*nodeSize+5),(float)(pos.y*nodeSize));

    f_text.setFont(font1);
    f_text.setCharacterSize(12);
    f_text.setColor(sf::Color(0,0,255,255));
    f_text.setOrigin(0.0f, 0.0f);
	f_text.setPosition((float)(pos.x*nodeSize+50),(float)(pos.y*nodeSize));
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
    target.draw(f_text);

    if(mParent != nullptr)
    {
        target.draw(sArrow);
    }

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

void Node::setF(int moveCost)
{
    fValue = moveCost + heuristic;
    f_text.setString(toString(fValue));
}

void Node::setDirection(parentDirection direction)
{
    switch(direction)
    {
    case LEFT:
        sArrow.setRotation(180);
        break;

    case RIGHT:
        sArrow.setRotation(0);
        break;

    case UP:
        sArrow.setRotation(270);
        break;

    case DOWN:
        sArrow.setRotation(90);
        break;
    }


}


