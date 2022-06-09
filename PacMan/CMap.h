#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

#include "Direction.h"
class CMap
{
public:
	CMap();

	void Render(sf::RenderTarget*);
	bool UpdateCollision(float&, float&, const DIRECTION&);
private:

	std::vector<std::string> mMapSketch = {
		"                            ",
		"                            ",
		"                            ",
		"# ##########################",
		"#            ##            #",
		"# #### ##### ## ##### #### #",
		"# #  # #   # ## #   # #  # #",
		"# #### ##### ## ##### #### #",
		"#                          #",
		"# #### ## ######## ## #### #",
		"# #### ## ######## ## #### #",
		"#      ##    ##    ##      #",
		"###### ##### ## ##### ######",
		"     # ##### ## ##### #     ",
		"     # ##          ## #     ",
		"     # ## ###  ### ## #     ",
		"###### ## #      # ## ######",
		"          #      #          ",
		"###### ## #      # ## ######",
		"     # ## ######## ## #     ",
		"     # ##          ## #     ",
		"     # ## ######## ## #     ",
		"###### ## ######## ## ######",
		"#            ##            #",
		"# ####	##### ## ##### #### #",
		"# #### ##### ## ##### #### #",
		"#   ##                ##   #",
		"### ## ## ######## ## ## ###",
		"### ## ## ######## ## ## ###",
		"#      ##    ##    ##      #",
		"# ########## ## ########## #",
		"# ########## ## ########## #",
		"#                          #",
		"############################",
		"                            ",
		"                            ",
	};

	//Walls
	sf::Sprite mWalls;
	sf::Texture mWallsTexture;

	void InitVariables();
	void InitMap();

	void InitWalls();

};

