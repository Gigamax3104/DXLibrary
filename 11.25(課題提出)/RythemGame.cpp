#include	"MainInclude.h"
#include	<math.h>
#include	<time.h>

enum JudgeMassage {
	Perfect = 0,
	Good = 1,
	Bad = 2
};

struct Circle {
	Vector2 pos;
	double radius;
	int color;
	bool DestroyFlag;
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
static void Draw(int size,double elapsedTime,const Massage* massage,const Box* box,const Circle* judgeCircle,Circle* musicalScore);
static JudgeMassage Judge(double distance, double radius,Massage* massage);
static void Display(int se[], const Circle* judgeCircle, JudgeMassage* judge);
static void Reset(int& count, int& space, bool& play,int size, Circle* musicalScore);

Massage* Game(int& scene,time_t nowtime) {
	static int se[] = {
		LoadSoundMem("sound/和太鼓でドン.mp3"),
		LoadSoundMem("sound/小鼓（こつづみ）.mp3"),
		LoadSoundMem("sound/間抜け4.mp3")
	};

	static int bgm = LoadSoundMem("sound/Euphoria_Walk.mp3");
	ChangeVolumeSoundMem(150, bgm);

	static bool play = true;
	static bool reset = false;
	bool returnBool = false;

	static time_t fixedTime = time(NULL);
	if (reset) {
		fixedTime = time(NULL); //リトライしたときにリセット
	}

	double elapsedTime = (double)(nowtime - fixedTime);

	static int count = 0;
	static int space = 0;
	static Massage judgeMassage = { 0,0,0 };
	if (reset) {
		judgeMassage.perfect = 0;
		judgeMassage.good = 0;
		judgeMassage.bad = 0;
		reset = false;
	}

	static Box box = { 10,HEIGHT - 100,WIDTH / 2 - 50,HEIGHT - 10,WHITE };

	static Circle judgeCircle = { WIDTH / 2,HEIGHT / 2,50,WHITE};

	static Circle musicalScore[MAX] = {
		WIDTH + 50,HEIGHT / 2,50,RED,true,
		WIDTH + 50,HEIGHT / 2,50,RED,true,
		WIDTH + 50,HEIGHT / 2,50,RED,true,
		WIDTH + 50,HEIGHT / 2,50,RED,true,
		WIDTH + 50,HEIGHT / 2,50,RED,true,
		WIDTH + 50,HEIGHT / 2,50,RED,true,
		WIDTH + 50,HEIGHT / 2,50,RED,true,
		WIDTH + 50,HEIGHT / 2,50,RED,true,
		WIDTH + 50,HEIGHT / 2,50,RED,true,
		WIDTH + 50,HEIGHT / 2,50,RED,true,
		WIDTH + 50,HEIGHT / 2,50,RED,true,
		WIDTH + 50,HEIGHT / 2,50,RED,true,
		WIDTH + 50,HEIGHT / 2,50,RED,true,
		WIDTH + 50,HEIGHT / 2,50,RED,true,
		WIDTH + 50,HEIGHT / 2,50,RED,true,
		WIDTH + 50,HEIGHT / 2,50,RED,true,
		WIDTH + 50,HEIGHT / 2,50,RED,true,
		WIDTH + 50,HEIGHT / 2,50,RED,true,
		WIDTH + 50,HEIGHT / 2,50,RED,true,
		WIDTH + 50,HEIGHT / 2,50,RED,true
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

	Draw(size,elapsedTime,&judgeMassage,&box, &judgeCircle, musicalScore);

	int nowspace = CheckHitKey(KEY_INPUT_SPACE);

	if (space == 0 && nowspace >= 1) {
		DrawCircle(judgeCircle.pos.x, judgeCircle.pos.y, judgeCircle.radius, RED, TRUE);
	}

	space = nowspace;

	for (int i = 0; i < size2; i++) {
		if (musicalScore[i].DestroyFlag) {
			if (space == 1 && Comparison(d[i], judgeCircle.radius + musicalScore[i].radius)) {
				JudgeMassage judge = Judge(d[i], judgeCircle.radius + musicalScore[i].radius, &judgeMassage);
				Display(se, &judgeCircle, &judge);
				musicalScore[i].DestroyFlag = false;
				count++;
			}

			if (musicalScore[i].pos.x <= -musicalScore->radius) {
				JudgeMassage judge = Bad;
				judgeMassage.bad++;
				Display(se, &judgeCircle, &judge);
				musicalScore[i].DestroyFlag = false;
				count++;
			}
		}
	}

	if (count == MAX) {
		reset = true;
		//StopSoundMem(bgm);
		Reset(count, space, play,size, musicalScore);
		//scene = RESULT;
		//return &judgemassage;
	}

	if (returnBool) {
		return &judgeMassage;
	}
}

static int Comparison(int totalDistance, int totalRadius) {
	return
		totalDistance <= totalRadius ? 1 : 0;
}

static void Draw(int size,double elapsedTime,const Massage* massage, const Box* box, const Circle* judgeCircle, Circle* musicalScore) {

	DrawBox(box->pos[0].x, box->pos[0].y, box->pos[1].x, box->pos[1].y, box->color, TRUE);

	SetFontSize(30);
	DrawFormatString(box->pos[0].x + 35, box->pos[0].y + 30, BLACK, "Perfect: %d Good: %d Bad: %d",
		massage->perfect,massage->good, massage->bad);

	DrawCircle(judgeCircle->pos.x, judgeCircle->pos.y, judgeCircle->radius, judgeCircle->color, TRUE);

	for (int i = 0; i < size; i++) {
		if (elapsedTime >= (double)(i + 1) * 60 / BPM && musicalScore[i].DestroyFlag) {
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

static void Reset(int& count, int& space, bool& play,int size, Circle* musicalScore) {
	count = 0;
	space = 0;
	play = true;

	for (int i = 0; i < size; i++) {
		musicalScore[i].pos.x = WIDTH + 50;
		musicalScore[i].pos.y = HEIGHT / 2;
		musicalScore[i].radius = 50;
		musicalScore[i].DestroyFlag = true;
	}
}
