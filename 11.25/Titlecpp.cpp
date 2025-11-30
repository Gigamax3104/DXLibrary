#include	<stdlib.h>
#include	<time.h>
#include	"MainInclude.h"

static void TitleScene(int time,int& scene,const int bgm[]);
static void ResultScene(Massage* massage,const int bgm[]);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	SetWindowText("リズムゲーム");
	SetGraphMode(WIDTH, HEIGHT, 32);
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1) return -1;
	SetBackgroundColor(0, 0, 0);
	SetDrawScreen(DX_SCREEN_BACK);

	time_t startTime = time(NULL);
	int scene = TITLE;

	static const int bgm[] = {
		LoadSoundMem("sound/8bit_Game_Menu.mp3"),
		LoadSoundMem("sound/Red_Glow.mp3")
	};

	Massage* score = nullptr;
	while (1) {
		ClearDrawScreen();

		int nowTime = (int)(time(NULL) - startTime);

		SetFontSize(30);
		DrawFormatString(0, 0, WHITE, "%dfps", FPS);

		switch (scene) {
		case TITLE:
			TitleScene(nowTime, scene,bgm); break;
		case GAME:
			score = Game(scene,time(NULL)); break;
		case RESULT:
			ResultScene(score,bgm); break;
		}

		ScreenFlip();
		WaitTimer(WAITTIMER);
		if (ProcessMessage() == -1) break;
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;
	}

	DxLib_End();
	return 0;

}

static void TitleScene(int time,int& scene,const int bgm[]) {
	static bool play = true;

	if (play) {
		ChangeVolumeSoundMem(256, bgm[0]);
		PlaySoundMem(bgm[0], DX_PLAYTYPE_LOOP);
		play = false;
	}

	SetFontSize(100);
	DrawString(WIDTH / 2 - 300, 100, "Rythem Game", WHITE);

	SetFontSize(50);
	if (time % 2 != 0)DrawString(WIDTH / 2 - 140, HEIGHT - 110, "Push SPACE", WHITE);
	if (CheckHitKey(KEY_INPUT_SPACE) == 1) {
		StopSoundMem(bgm[0]);
		scene = GAME;
	}
}

static void ResultScene(Massage* massage,const int bgm[]) {
	static bool play = true;

	if (play) {
		ChangeVolumeSoundMem(256, bgm[1]);
		PlaySoundMem(bgm[1], DX_PLAYTYPE_LOOP);
		play = false;
	}

	SetFontSize(100);
	DrawString(WIDTH / 2 - 110, 100, "結果", RED);
	SetFontSize(50);
	DrawFormatString(230, HEIGHT - 200, WHITE, "Perfect:%d Good:%d Bad:%d", massage->perfect, massage->good, massage->bad);
	DrawString(360, HEIGHT - 100, "ESCキーで終了", WHITE);
}