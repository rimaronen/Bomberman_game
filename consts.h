#pragma once
#include <string>

// game board is logically divided into rows and columns of this width:
const int ROW_WIDTH = 75;
const int COL_WIDTH = 75;

// width and height of control bar
const float GAME_CONTROL_BAR_WIDTH = 64 * 6;
const float GAME_CONTROL_BAR_HEIGHT = 64 * 6;

// global font size
const unsigned CHARACTER_SIZE = 64;

// robot max extra lives number
const int MAX_LIVES = 3;

// these values represent unlimited time and 
const int UNLIMITED_TIME = -1;

// score factors for killing guards and finishing levels. added score is score factor * initial number of guards for the level. 
const int KILL_GUARDS_SCORE_FACTOR = 5;
const int PASSED_DOOR_SCORE_FACTOR = 20;

// character representations of items in the level files.
const char CHAR_EMPTY = ' ';
const char CHAR_DOOR = 'D';
const char CHAR_ROBOT = '/';
const char CHAR_GUARD = '!';
const char CHAR_SIMPLE_GUARD = 'S';
const char CHAR_CLEVER_GUARD = 'C';
const char CHAR_ROCK = '@';
const char CHAR_WALL = '#';
const char CHAR_BONUS = '+';
const char CHAR_HIDDEN_BONUS = '&';

// index for first frame in an animation's texture
const int START_IMG = 1;
