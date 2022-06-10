#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <utility>

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

#include "Direction.h"
#include "CCoin.h"
#include "CEnergizer.h"

class CMap
{
public:
	CMap();

	void Render(sf::RenderTarget*);
	bool UpdateWallCollision(float&, float&, const DIRECTION&);
	int UpdateCoinCollision(const float&, const float&);
private:

	std::vector<std::string> mMapSketch = {
		"                            ",
		"                            ",
		"                            ",
		"############################",
		"#cccccccccccc##cccccccccccc#",
		"#c####c#####c##c#####c####c#",
		"#e#  #c#   #c##c#   #c#  #e#",
		"#c####c#####c##c#####c####c#",
		"#cccccccccccccccccccccccccc#",
		"#c####c##c########c##c####c#",
		"#c####c##c########c##c####c#",
		"#cccccc##cccc##cccc##cccccc#",
		"######c##### ## #####c######",
		"     #c##### ## #####c#     ",
		"     #c##          ##c#     ",
		"     #c## ###  ### ##c#     ",
		"######c## #      # ##c######",
		"      c   #      #   c      ",
		"######c## #      # ##c######",
		"     #c## ######## ##c#     ",
		"     #c##          ##c#     ",
		"     #c## ######## ##c#     ",
		"######c## ######## ##c######",
		"#cccccccccccc##cccccccccccc#",
		"#c####c#####c##c#####c####c#",
		"#c####c#####c##c#####c####c#",
		"#ecc##ccccccc  ccccccc##cce#",
		"###c##c##c########c##c##c###",
		"###c##c##c########c##c##c###",
		"#cccccc##cccc##cccc##cccccc#",
		"#c##########c##c##########c#",
		"#c##########c##c##########c#",
		"#cccccccccccccccccccccccccc#",
		"############################",
		"                            ",
		"                            ",
	};

	//Walls
	sf::Sprite mWalls;
	sf::Texture mWallsTexture;

	//map of coins
	std::map<std::pair<int, int>, CCoin*> mCoins;

	void InitVariables();
	void InitMap();

	void InitWalls();
	void InitCoins();

};

