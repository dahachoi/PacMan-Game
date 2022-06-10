#include "CEnergizer.h"

using namespace std;

CEnergizer::CEnergizer(const float& x, const float& y){
	mX = x;
	mY = y;
	InitCoin();
}

void CEnergizer::InitCoin(){
	mCoin.setRadius(13);
	mCoin.setFillColor(sf::Color(255, 184, 174, 255));
	mCoin.setOrigin(mCoin.getGlobalBounds().width / 2, mCoin.getGlobalBounds().height / 2);

	mCoin.setPosition(sf::Vector2f(mX, mY));
}
