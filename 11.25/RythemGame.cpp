#include	"MainInclude.h"
#include	<math.h>
#include	<time.h>
#define BLUE 0x0000ff

enum JudgeMassage {
	Perfect,
	Good,
	Bad
};

struct Vector2 {
	int x;
	int y;
};

struct Circle {
	Vector2 pos;
	int radius;
	int color;
};

struct Box {
	Vector2 pos[2];
	int color;
};

const char* massage[] = {
	"Perfect!!",
	"Good",
	"Bad..."
};

static int Comparison(int totalDistance,int totalRadius);
static void Draw(int& index,int size,double elapsedTime,const Massage* massage,const Box* box,Circle* judgeCircle,Circle* musicalScore);
static JudgeMassage Judge(double distance, double radius,Massage* massage);
static void Display(int se[], const Circle* judgeCircle, JudgeMassage* judge);

Massage* Game(int& scene,time_t nowtime) {
	static int se[] = {
		LoadSoundMem("sound/òaëæå€Ç≈ÉhÉì.mp3"),
		LoadSoundMem("sound/è¨å€ÅiÇ±Ç¬Ç√Ç›Åj.mp3"),
		LoadSoundMem("sound/ä‘î≤ÇØ4.mp3")
	};

	static int bgm = LoadSoundMem("sound/Euphoria_Walk.mp3");
	ChangeVolumeSoundMem(150, bgm);

	static bool play = true;

	static time_t fixedTime = time(NULL);
	double elapsedTime = (double)(nowtime - fixedTime);

	static bool suffer = true;

	static int space = 0;
	static int index = 0;
	static Massage massage = { 0,0,0 };

	static Box box = { 10,HEIGHT - 100,WIDTH / 2 - 50,HEIGHT - 10,WHITE };

	static Circle judgeCircle = { WIDTH / 2,HEIGHT / 2,50,WHITE};

	static Circle musicalScore[MAX] = {
		WIDTH + 50,HEIGHT / 2,50,RED,
		WIDTH + 50,HEIGHT / 2,50,RED,
		WIDTH + 50,HEIGHT / 2,50,RED,
		WIDTH + 50,HEIGHT / 2,50,RED,
		WIDTH + 50,HEIGHT / 2,50,RED,
		WIDTH + 50,HEIGHT / 2,50,RED,
		WIDTH + 50,HEIGHT / 2,50,RED,
		WIDTH + 50,HEIGHT / 2,50,RED,
		WIDTH + 50,HEIGHT / 2,50,RED,
		WIDTH + 50,HEIGHT / 2,50,RED,
		WIDTH + 50,HEIGHT / 2,50,RED,
		WIDTH + 50,HEIGHT / 2,50,RED,
		WIDTH + 50,HEIGHT / 2,50,RED,
		WIDTH + 50,HEIGHT / 2,50,RED,
		WIDTH + 50,HEIGHT / 2,50,RED,
		WIDTH + 50,HEIGHT / 2,50,RED,
		WIDTH + 50,HEIGHT / 2,50,RED,
		WIDTH + 50,HEIGHT / 2,50,RED,
		WIDTH + 50,HEIGHT / 2,50,RED,
		WIDTH + 50,HEIGHT / 2,50,RED
	};

	int size = sizeof musicalScore / sizeof musicalScore[0];

	int d[MAX] = { 0 };
	int size2 = sizeof d / sizeof d[0];

	for (int i = 0; i < size2; i++) {
		d[i] = sqrt(pow(judgeCircle.pos.x - musicalScore[i].pos.x, 2)
			 + pow(judgeCircle.pos.y - musicalScore[i].pos.y, 2));
	}

	ClearDrawScreen();

	if (play && elapsedTime >= sqrt(pow(judgeCircle.pos.x - musicalScore->pos.x, 2)) / (SPEED * FPS)) {		
		PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);
		play = false;
	}

	DrawFormatString(0, 0, WHITE, "%dfps", FPS);

	Draw(index,size,elapsedTime,&massage,&box, &judgeCircle, musicalScore);

	if (CheckHitKey(KEY_INPUT_SPACE) == 1) {
		space++;
	}
	else {
		space > 0 ? space = -1 : space = 0;
	}

	if (space >= 1) {
		DrawCircle(judgeCircle.pos.x, judgeCircle.pos.y, judgeCircle.radius, RED, TRUE);
	}

	for (int i = index; i < size2; i++) {
		if (space == 1 && Comparison(d[i], judgeCircle.radius + musicalScore[i].radius)) {
			if (suffer) {
				JudgeMassage judge = Judge(d[i], judgeCircle.radius + musicalScore[i].radius, &massage);
				Display(se,&judgeCircle, &judge);
				index++;
				suffer = false;
			}
		}
	
		if (musicalScore[i].pos.x <= -50) {
			index++;
		}
	}

	if (index == MAX) {
		StopSoundMem(bgm);
		scene = RESULT;
		return &massage;
	}

	suffer = true;
}

static int Comparison(int totalDistance, int totalRadius) {
	return
		totalDistance <= totalRadius ? 1 : 0;
}

static void Draw(int& index,int size,double elapsedTime,const Massage* massage, const Box* box, Circle* judgeCircle, Circle* musicalScore) {

	DrawBox(box->pos[0].x, box->pos[0].y, box->pos[1].x, box->pos[1].y, box->color, TRUE);

	SetFontSize(30);
	DrawFormatString(box->pos[0].x + 35, box->pos[0].y + 30, BLACK, "Perfect: %d Good: %d Bad: %d",
		massage->perfect,massage->good, massage->bad);

	DrawCircle(judgeCircle->pos.x, judgeCircle->pos.y, judgeCircle->radius, judgeCircle->color, TRUE);

	for (int i = index; i < size; i++) {
		if (elapsedTime >= (i + 1) * 2.17 * 60 / BPM) {
			musicalScore[i].pos.x -= SPEED;
			DrawCircle(musicalScore[i].pos.x, musicalScore[i].pos.y,
					   musicalScore[i].radius, musicalScore[i].color, TRUE);
		}
	}
}

static JudgeMassage Judge(double distance, double radius,Massage* massage) {
	
	if (radius - distance < radius * 0.3) {
		massage->bad++;
		return Bad;
	}
	else if (radius - distance < radius * 0.8) {
		massage->good++;
		return Good;
	}
	else {
		massage->perfect++;
		return Perfect;
	}
}
static void Display(int se[], const Circle* judgeCircle, JudgeMassage* judge) {
	const int color[] = {
		RED,WHITE,BLUE
	};

	const Vector2 pos[] = {
		judgeCircle->pos.x - 70, judgeCircle->pos.y + 50,
		judgeCircle->pos.x - 30, judgeCircle->pos.y + 50,
		judgeCircle->pos.x - 40, judgeCircle->pos.y + 50
	};

	SetFontSize(30);
	DrawFormatString(pos[*judge].x, pos[*judge].y, color[*judge], "%s", massage[*judge]);
	DrawCircle(judgeCircle->pos.x, judgeCircle->pos.y, judgeCircle->radius, RED, TRUE);
	ChangeVolumeSoundMem(256,se[*judge]);
	PlaySoundMem(se[*judge], DX_PLAYTYPE_BACK);
}

