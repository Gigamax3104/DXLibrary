#include	"MainInclude.h"
#include	"ErrorCheck.h"
#include	<math.h>

enum JudgeMassage {
	Perfect = 0,
	Good = 1,
	Bad = 2
};

struct Circle {
	Vector2 pos;
	int radius;
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

static bool Comparison(double totalDistance,int totalRadius);
static void Draw(int size,double elapsedTime,const Massage* MASSAGE,const Box* BOX,const Circle* JUDGECIRCLE,Circle* musicalScore);
static JudgeMassage Judge(double distance, double radius,Massage* massage);
static void Display(const int* SE,Circle* judgeCircle, JudgeMassage* judge);
static void Reset(int* count, int* space, bool* play,int size, Circle* musicalScore);

Massage* Game(int* scene,const int* BGM,const int* SE,time_t nowtime) {
	ChangeVolumeSoundMem(150, BGM[2]);

	static bool play = true;
	static bool reset = false;

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

	Circle judgeCircle = { WIDTH / 2,HEIGHT / 2,50,WHITE};

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

	double d[MAX] = { 0 };
	int size2 = sizeof d / sizeof d[0];

	for (int i = 0; i < size2; i++) {
		d[i] = sqrt(pow(judgeCircle.pos.x - musicalScore[i].pos.x, 2)
			 + pow(judgeCircle.pos.y - musicalScore[i].pos.y, 2));
	}

	if (play && elapsedTime >= sqrt(pow(judgeCircle.pos.x - musicalScore->pos.x, 2)) / (SPEED * FPS)) {		
		PlaySoundMem(BGM[2], DX_PLAYTYPE_LOOP);
		play = false;
	}

	//if (CheckHitKey(KEY_INPUT_RETURN)) {
	//}　Enterキーを押すとメニュー画面へ移動するが、処理が未完成のためコメントアウト。

	Draw(size,elapsedTime,&judgeMassage,&box, &judgeCircle, musicalScore);

	CheckHitKey(KEY_INPUT_SPACE) ? space++ : space > 0 ? space = -1 : space = 0;

	if (space >= 1) {
		DrawCircle(judgeCircle.pos.x, judgeCircle.pos.y, judgeCircle.radius, LIGHTRED, TRUE);
	}

	for (int i = 0; i < size2; i++) {
		if (musicalScore[i].DestroyFlag) {
			if (space == 1 && Comparison(d[i], judgeCircle.radius + musicalScore[i].radius)) {
				JudgeMassage judge = Judge(d[i], judgeCircle.radius + musicalScore[i].radius, &judgeMassage);
				Display(SE, &judgeCircle, &judge);
				musicalScore[i].DestroyFlag = false;
				count++;
			}

			if (musicalScore[i].pos.x <= -musicalScore->radius) {
				JudgeMassage judge = Bad;
				judgeMassage.bad++;
				Display(SE, &judgeCircle, &judge);
				musicalScore[i].DestroyFlag = false;
				count++;
			}
		}
	}

	if (count == MAX) {
		reset = true;
		StopSoundMem(BGM[2]);
		Reset(&count, &space, &play,size, musicalScore);
		*scene = RESULT;
		return &judgeMassage;
	}
	else {
		return &judgeMassage;
	}
}

static bool Comparison(double totalDistance, int totalRadius) {
	return
		totalDistance <= totalRadius ? true : false;
}

static void Draw(int size,double elapsedTime,const Massage* MASSAGE, const Box* BOX,const Circle* JUDGECIRCLE, Circle* musicalScore) {

	DrawBox(BOX->pos[0].x, BOX->pos[0].y, BOX->pos[1].x, BOX->pos[1].y, BOX->color, TRUE);

	SetFontSize(30);
	DrawFormatString(BOX->pos[0].x + 35, BOX->pos[0].y + 30, BLACK, "Perfect: %d Good: %d Bad: %d",
		MASSAGE->perfect, MASSAGE->good, MASSAGE->bad);

	DrawCircle(JUDGECIRCLE->pos.x, JUDGECIRCLE->pos.y, JUDGECIRCLE->radius, JUDGECIRCLE->color, TRUE);

	for (int i = 0; i < size; i++) {
		if (elapsedTime >= (i + 1) * 2.17 * MINUTE / BPM && musicalScore[i].DestroyFlag) {
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
static void Display(const int* SE,Circle* judgeCircle, JudgeMassage* judge) {
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
	ChangeVolumeSoundMem(256, SE[*judge]);
	PlaySoundMem(SE[*judge], DX_PLAYTYPE_BACK);
}

static void Reset(int* count, int* space, bool* play,int size, Circle* musicalScore) {
	*count = 0;
	*space = 0;
	*play = true;

	for (int i = 0; i < size; i++) {
		musicalScore[i].pos.x = WIDTH + 50;
		musicalScore[i].pos.y = HEIGHT / 2;
		musicalScore[i].radius = 50;
		musicalScore[i].DestroyFlag = true;
	}
}
