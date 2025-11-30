#pragma once
#define WAITTIMER 33
#define FPS 1000 / WAITTIMER
#define BPM 130
#define SPEED 10
#define MAX 20
#define WIDTH 1080
#define HEIGHT 640
#include	<DxLib.h>

const int WHITE = 0xffffff;
const int RED = 0xff0000;
const int BLACK = 0x000000;

enum {
	TITLE,
	GAME,
	RESULT
};

struct Massage {
	int perfect;
	int good;
	int bad;
};

Massage* Game(int& scene,time_t time);