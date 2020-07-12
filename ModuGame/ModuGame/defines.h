#pragma once

enum CLIENT_SIZE
{
	CLIENT_SIZE_WIDTH = 414,
	CLIENT_SIZE_HEIGHT = 646,
};

enum SCENE_INDEX
{
	SCENE_INDEX_TITLE,
	SCENE_INDEX_SELECT,
	SCENE_INDEX_PAPER,
	SCENE_INDEX_PLANE
};

enum PAPER_DIRECTION
{
	UP,
	DOWN,
	RIGHT,
	LEFT,
	NONE,
};


enum PAPER_COLOR
{
	GREEN , YELLOW,   RED, BLUE, COLOREND
};

enum STAR
{
	STAR_YELLOW,
	STAR_GREEN,
	STAR_BLUE
};

enum PAPER_TURN
{
	NOW,
	NEXT
};

enum FEVERSTATE
{
	BASIC,
	SUPER,
	ULTRA
};
