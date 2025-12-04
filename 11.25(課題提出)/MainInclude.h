#pragma once
#define WAITTIMER 33
#define FPS 1000 / WAITTIMER
#define BPM 130
#define SPEED 10
#define MAX 20
#define WIDTH 1080
#define HEIGHT 640
#include	<DxLib.h>
#include	<time.h>

const int WHITE = 0xffffff;
const int RED = 0xff0000;
const int LIGHTRED = 0xff7575;
const int BLACK = 0x000000;
const int BLUE = 0x0000ff;


enum {
	TITLE,
	GAME,
	MENU,
	RESULT
};

struct Massage {
	int perfect;
	int good;
	int bad;
};

struct Vector2 {
	int x;
	int y;
};

Massage* Game(int* scene, const int* BGM, const int* SE, time_t time);
