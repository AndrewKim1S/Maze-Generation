#include "Cell.h"


Cell::Cell() {

}

Cell::Cell(int x, int y, int length) {
		position.x = x;
		position.y = y;
		size.x = length;
		size.y = length;

		state = State::Path;
		top = true;
		left = true;
		right = true;
		bottom = true;

		shape = sf::RectangleShape();
		shape.setSize(size);
		shape.setPosition(position.x, position.y);
		shape.setFillColor(cellColor);

		float borderWeight = length/18;

		sf::Vector2f horizontalWallSize = sf::Vector2f();
		horizontalWallSize.x = length;
		horizontalWallSize.y = borderWeight;

		sf::Vector2f verticalWallSize = sf::Vector2f();
		verticalWallSize.x = borderWeight;
		verticalWallSize.y = length;

		topWall = sf::RectangleShape();
		topWall.setSize(horizontalWallSize);
		topWall.setPosition(position.x, position.y);
		topWall.setFillColor(wallColor);

		bottomWall = sf::RectangleShape();
		bottomWall.setSize(horizontalWallSize);
		bottomWall.setPosition(position.x, position.y + length - borderWeight);
		bottomWall.setFillColor(wallColor);

		leftWall = sf::RectangleShape();
		leftWall.setSize(verticalWallSize);
		leftWall.setPosition(position.x, position.y);
		leftWall.setFillColor(wallColor);

		rightWall = sf::RectangleShape();
		rightWall.setSize(verticalWallSize);
		rightWall.setPosition(position.x + length - borderWeight, position.y);
		rightWall.setFillColor(wallColor);
}

Cell::~Cell() {

}

void Cell::setState(State s) {
		state = s;
}

void Cell::render(sf::RenderTarget* target) {
		target->draw(shape);
		if(top) {
				target->draw(topWall);
		}	if(bottom) {
				target->draw(bottomWall);
		}	if(left) {
				target->draw(leftWall);
		} if(right) {
				target->draw(rightWall);
		} 
}

void Cell::removeWall(int wall){
		switch(wall) {
				case 1:
						top = false;
						break;
				case 2:
						left = false;
						break;
				case 3:
						right = false;
						break;
				case 4:
						bottom = false;
						break;
				default:
						break;
		}
}

void Cell::reset() {
		top = true;
		left = true;
		right = true;
		bottom = true;

		state = State::Path;
}
