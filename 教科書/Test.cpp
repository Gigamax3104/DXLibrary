#include	<DxLib.h>
#include	<math.h>
#include	<stdlib.h>
#include	<time.h>
#define MAX 10
#define RADIUS 50
#define SPEED 10

const int WIDTH = 960, HEIGHT = 640;
const int WHITE = GetColor(255, 255, 255);
const int RED = GetColor(255, 0, 0);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	srand((unsigned int)time(NULL));

	SetWindowText("画面遷移");
	SetGraphMode(WIDTH, HEIGHT, 32);
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1) return -1;
	SetBackgroundColor(0, 0, 0);
	SetDrawScreen(DX_SCREEN_BACK);

	enum {
		TITLE,
		PLAY,
		MENU,
		CLEAR,
		OVER
	};
	int scene = TITLE;
	int timer = 0;
	//int x1 = 0, y1 = 0, w1 = 120, h1 = 80;
	//int x2 = WIDTH / 2, y2 = HEIGHT / 2, w2 = 160, h2 = 240;

	while (1) {
		ClearDrawScreen();

		timer++;
		SetFontSize(16);
		DrawFormatString(0, 0, WHITE, "%d", timer);

		switch (scene) {
		case TITLE:
			SetFontSize(50);
			DrawString(100, 50, "タイトル画面", WHITE);
			SetFontSize(20);
			DrawString(100, 200, "Sキーを押すとゲーム開始", WHITE);
			if (CheckHitKey(KEY_INPUT_S) == 1)scene = PLAY;
			break;

		case PLAY:
			SetFontSize(50);
			DrawString(100, 50, "ゲームプレイ画面", WHITE);
			SetFontSize(20);
			DrawString(100, 200, "Mキーでメニュー画面へ", WHITE);
			SetFontSize(20);
			DrawString(100, 300, "Oキーでゲームオーバー", RED);
			if (CheckHitKey(KEY_INPUT_M) == 1)scene = MENU;
			if (CheckHitKey(KEY_INPUT_O) == 1){
				scene = OVER;
				timer = 0;
			}
			break;

		case MENU:
			SetFontSize(50);
			DrawString(100, 50, "メニュー画面", 0x000000);
			SetFontSize(20);
			DrawString(100, 200, "Rキーでゲームに戻る", WHITE);
			if (CheckHitKey(KEY_INPUT_R) == 1) scene = PLAY; break;
		case CLEAR:
			break;

		case OVER:
			SetFontSize(50);
			DrawString(100, 50, "GAME OVER", RED);
			if (timer > 30 * 5) scene = TITLE;
			break;
		}
		//GetMousePoint(&x1, &y1);
		//int color1 = GetColor(255, 255, 0);
		//int color2 = GetColor(0, 0, 255);

		//int dx = abs((x1 - x2));
		//int dy = abs((y1 - y2));

		//if (dx <= (w1 + w2) / 2 && dy <= (h1 + h2) / 2) {
		//	color1 = GetColor(255, 0, 0);
		//	color2 = GetColor(255, 0, 0);
		//}

		//DrawBox(x1 - w1 / 2, y1 - h1 / 2, x1 + w1 / 2, y1 + h1 / 2, color1, TRUE);
		//DrawBox(x2 - w2 / 2, y2 - h2 / 2, x2 + w2 / 2, y2 + h2 / 2, color2, TRUE);

		ScreenFlip();
		WaitTimer(33);
		if (ProcessMessage() == -1) break;
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;
	}

	DxLib_End();
	return 0;

}
//int move[2] = { 400,200 };
//int move2[2] = { 100,300 };
//int enemySpeed[2] = { 10,10 };

//DrawCircle(move[0], move[1], RADIUS, GetColor(0, 255, 255), TRUE);

//if (CheckHitKey(KEY_INPUT_A) || CheckHitKey(KEY_INPUT_LEFT)) move[0] -= SPEED;
//if (CheckHitKey(KEY_INPUT_D) || CheckHitKey(KEY_INPUT_RIGHT)) move[0] += SPEED;
//if (CheckHitKey(KEY_INPUT_W) || CheckHitKey(KEY_INPUT_UP)) move[1] -= SPEED;
//if (CheckHitKey(KEY_INPUT_S) || CheckHitKey(KEY_INPUT_DOWN)) move[1] += SPEED;

//if (move[0] <= RADIUS) move[0] = RADIUS;
//else if (move[0] >= WIDTH - RADIUS) move[0] = WIDTH - RADIUS;

//if (move[1] <= RADIUS) move[1] = RADIUS;
//else if (move[1] >= HEIGHT - RADIUS) move[1] = HEIGHT - RADIUS;

//if (timer >= 100) {
//	DrawCircle(move2[0], move2[1], RADIUS, GetColor(255, 0, 0), TRUE);
//	move2[0] += enemySpeed[0];
//	move2[1] += enemySpeed[1];

//	if (move2[0] <= RADIUS || move2[0] >= WIDTH - RADIUS) enemySpeed[0] *= -1;
//	if (move2[1] <= RADIUS || move2[1] >= HEIGHT - RADIUS) enemySpeed[1] *= -1;

//	if (move2[0] + RADIUS == move[0] - RADIUS || move2[0] - RADIUS == move[0] + RADIUS
//		|| move2[1] + RADIUS == move[1] - RADIUS || move2[1] - RADIUS == move[1] + RADIUS) break;
//}
//DrawLine(0, 0, WIDTH, HEIGHT, GetColor(255, 0, 0));
//DrawBox(0, HEIGHT - 400, 200, HEIGHT - 100, GetColor(0, 255, 0), TRUE);
//DrawBox(WIDTH - 200, 100, WIDTH - 100, 200, GetColor(0, 0, 255), TRUE);
//DrawOval(400, 400, 200, 100, GetColor(255, 0, 255), FALSE);
//DrawTriangle(600, 0, 500, 300, 700, 300, GetColor(255, 192, 0), TRUE);
//DrawPixel(400, 200, GetColor(0, 0, 0));
//if (CheckHitKey(KEY_INPUT_UP)) DrawString(0, 20, "上キー", WHITE);
//if (CheckHitKey(KEY_INPUT_DOWN)) DrawString(0, 40, "下キー", WHITE);
//if (CheckHitKey(KEY_INPUT_LEFT)) DrawString(0, 60, "左キー", WHITE);
//if (CheckHitKey(KEY_INPUT_RIGHT)) DrawString(0, 80, "右キー", WHITE);

//int mousePosX, mousePosY;
//GetMousePoint(&mousePosX, &mousePosY);
//DrawFormatString(400, 0, WHITE, "(%d,%d)", mousePosX, mousePosY);

//if (GetMouseInput() & MOUSE_INPUT_LEFT) DrawString(400, 20, "左ボタン", WHITE);
//if (GetMouseInput() & MOUSE_INPUT_RIGHT) DrawString(400, 40, "右ボタン", WHITE);

	//int imgBG = LoadGraph("image/bg.png");//画像のコードを返す関数
	//int imgDog[4] = {
	//	LoadGraph("image/dog0.png"),
	//	LoadGraph("image/dog1.png"),
	//	LoadGraph("image/dog2.png"),
	//	LoadGraph("image/dog3.png"),
	//};

	//int dogX = 0, dogY = 400;
	//int limitUnder = dogY;
	//double dogSpeed = 10;
	//double timerSpeed = 5;
	//bool Change = false;
		//DrawGraph(0, 0, imgBG, FALSE);

		//dogX = dogX + dogSpeed;


		//if (dogX > WIDTH || dogX < -240) {
		//	Change ? Change = false : Change = true;
		//	dogSpeed *= -1;
		//	dogY = (rand() % (500 - limitUnder)) + limitUnder;
		//}
		//
		//Change ? DrawTurnGraph(dogX,dogY, imgDog[(timer / (int)timerSpeed) % 4], TRUE) : DrawGraph(dogX, dogY, imgDog[(timer / (int)timerSpeed)/*timerSpeedで割ることによって遅くさせている*/ % 4], TRUE);
		//if (timer % 100 == 0) {
		//	dogSpeed += 0.25;
		//	timerSpeed -= 0.1;
		//} 

	//int bgm = LoadSoundMem("sound/battle.mp3");
	//int se = LoadSoundMem("sound/recover.mp3");
	//ChangeVolumeSoundMem(128, bgm);
	//PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);
	//bool playJudge = true;
		//DrawString(0, 20, "Sキーを押すとBGMを停止します。", WHITE);
		//DrawString(0, 40, "スペースキーを押すと効果音を出力します。", WHITE);

		//if (CheckHitKey(KEY_INPUT_S)) {
		//	if (playJudge) {
		//		StopSoundMem(bgm);
		//		playJudge = false;
		//	}
		//	else {
		//		PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);
		//		playJudge = true;
		//	}
		//}

		//if (CheckHitKey(KEY_INPUT_SPACE)) PlaySoundMem(se, DX_PLAYTYPE_BACK);

	//int x1 = 0, y1 = 0,r1 = 50;
	//int x2 = WIDTH / 2, y2 = HEIGHT / 2, r2 = 150;
		//int color1 = GetColor(255, 255, 0);
		//int color2 = GetColor(0, 0, 255);
		//int d = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
		//DrawFormatString(0, 20, WHITE, "中心間距離 %d", d);

		//if (d <= r1 + r2) {
		//	color1 = GetColor(255, 0, 0);
		//	color2 = GetColor(255, 0, 0);
		//}

		//DrawCircle(x1, y1, r1, color1, TRUE);
		//DrawCircle(x2, y2, r2, color2, TRUE);
