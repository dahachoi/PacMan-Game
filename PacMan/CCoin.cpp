#include "CCoin.h"

using namespace std;

CCoin::CCoin(const float& x, const float& y)
	:mX(x), mY(y)
{
	InitCoin();
}

void CCoin::InitCoin() {
	mCoin.setRadius(5);
	mCoin.setFillColor(sf::Color(255, 184, 174, 255));
	mCoin.setOrigin(mCoin.getGlobalBounds().width / 2, mCoin.getGlobalBounds().height / 2);

	mCoin.setPosition(sf::Vector2f(mX, mY));
}

void CCoin::Render(sf::RenderTarget* target) {
	target->draw(mCoin);
}