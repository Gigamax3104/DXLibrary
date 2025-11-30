#include	<stdlib.h>
#include	<time.h>
#include	"MainInclude.h"

static void TitleScene(int time,int& scene);
static void ResultScene(Massage* massage);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	SetWindowText("リズムゲーム");
	SetGraphMode(WIDTH, HEIGHT, 32);
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1) return -1;
	SetBackgroundColor(0, 0, 0);
	SetDrawScreen(DX_SCREEN_BACK);

	time_t startTime = time(NULL);
	int scene = TITLE;
	Massage* score = nullptr;
	while (1) {
		ClearDrawScreen();

		int nowTime = (int)(time(NULL) - startTime);

		SetFontSize(30);
		DrawFormatString(0, 0, WHITE, "%dfps", FPS);

		switch (scene) {
		case TITLE:
			TitleScene(nowTime, scene); break;
		case GAME:
			score = Game(scene,time(NULL)); break;
		case RESULT:
			ResultScene(score); break;
		}

		ScreenFlip();
		WaitTimer(WAITTIMER);
		if (ProcessMessage() == -1) break;
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;
	}

	DxLib_End();
	return 0;

}

static void TitleScene(int time,int& scene) {
	SetFontSize(100);
	DrawString(WIDTH / 2 - 300, 100, "Rythem Game", WHITE);

	SetFontSize(50);
	if (time % 2 != 0)DrawString(WIDTH / 2 - 140, HEIGHT - 110, "Push SPACE", WHITE);
	if (CheckHitKey(KEY_INPUT_SPACE) == 1) scene = GAME;
}

static void ResultScene(Massage* massage) {
	SetFontSize(100);
	DrawString(WIDTH / 2 - 110, 100, "結果", RED);
	SetFontSize(50);
	DrawFormatString(220, HEIGHT - 200, WHITE, "Perfect:%d Good:%d Bad:%d", massage->perfect, massage->good, massage->bad);
	DrawString(350, HEIGHT - 100, "ESCキーで終了", WHITE);
}