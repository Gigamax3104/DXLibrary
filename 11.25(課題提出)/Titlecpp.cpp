#include	"MainInclude.h"
#include	<stdlib.h>
#include	"ErrorCheck.h"

static void TitleScene(int time,int* scene,const int* BGM);
static void ResultScene(int* scene,const Massage* MASSAGE,const int* BGM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	SetWindowText("リズムゲーム");
	SetGraphMode(WIDTH, HEIGHT, 32);
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1) return -1;
	SetBackgroundColor(0, 0, 0);
	SetDrawScreen(DX_SCREEN_BACK);

	time_t startTime = time(NULL);
	int scene = TITLE;

	Massage* score = nullptr; //スコア保持のための変数(ヌルポインタで初期化)

	const int BGM[] = {
		LoadSoundMem("sound/8bit_Game_Menu.mp3"),
		LoadSoundMem("sound/Red_Glow.mp3"),
		LoadSoundMem("sound/Euphoria_Walk.mp3")
	};
	const int BGMSIZE = sizeof BGM / sizeof BGM[0];

	const int SE[] = {
		LoadSoundMem("sound/和太鼓でドン.mp3"),
		LoadSoundMem("sound/小鼓（こつづみ）.mp3"),
		LoadSoundMem("sound/間抜け4.mp3")
	};
	const int SESIZE = sizeof SE / sizeof SE[0];

	while (1) {
		ClearDrawScreen();

		for (int i = 0; i < BGMSIZE; i++) {
			if (IntErrorCheck(&BGM[i])) {
				SetFontSize(30);
				DrawString(0, 30 * i, "音を読み込むことができませんでした。", RED);
			}
		}

		for (int i = 0; i < SESIZE; i++) {
			if (IntErrorCheck(&SE[i])) {
				SetFontSize(30);
				DrawString(0, BGMSIZE * 30 + 30 * i, "音を読み込むことができませんでした。", RED);
			}
		}

		int nowTime = (int)(time(NULL) - startTime); //経過時間を記録するための変数

		SetFontSize(30);
		DrawFormatString(0, 0, WHITE, "%dfps", FPS); //FPS(左上)表示

		switch (scene) {
		case TITLE:
			TitleScene(nowTime, &scene, BGM); break; //タイトル画面の処理
		case GAME:
			score = Game(&scene,BGM,SE,time(NULL)); break;
		case RESULT:
			ResultScene(&scene,score, BGM); break;
		}

		ScreenFlip();
		WaitTimer(WAIT);
		if (ProcessMessage() == -1) break;
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;
	}

	for(int i = 0; i < BGMSIZE; i++) DeleteSoundMem(BGM[i]);
	for (int i = 0; i < SESIZE; i++) DeleteSoundMem(SE[i]);
	DxLib_End();
	return 0;

}

static void TitleScene(int time,int* scene,const int* BGM) {
	static bool play = true;

	if (play) {
		ChangeVolumeSoundMem(256, BGM[0]);
		PlaySoundMem(BGM[0], DX_PLAYTYPE_LOOP);
		play = false;
	}

	SetFontSize(100);
	DrawString(WIDTH / 2 - 300, 100, "Rythem Game", WHITE);

	SetFontSize(50);
	if (time % 2 != 0)DrawString(WIDTH / 2 - 140, HEIGHT - 110, "Push SPACE", WHITE);
	if (CheckHitKey(KEY_INPUT_SPACE) == 1) {
		play = true;
		StopSoundMem(BGM[0]);
		*scene = GAME;
	}
}

static void ResultScene(int* scene,const Massage* MASSAGE,const int* BGM) {
	static bool play = true;

	if (play) {
		ChangeVolumeSoundMem(256, BGM[1]);
		PlaySoundMem(BGM[1], DX_PLAYTYPE_LOOP);
		play = false;
	}

	SetFontSize(100);
	DrawString(WIDTH / 2 - 110, 100, "結果", RED);
	SetFontSize(50);
	DrawFormatString(230, HEIGHT - 200, WHITE, "Perfect:%d Good:%d Bad:%d", MASSAGE->perfect, MASSAGE->good, MASSAGE->bad);
	DrawString(80, HEIGHT - 150, "Xキーでタイトル画面へ : Rでリトライ\n           ESCキーで終了", WHITE);
	if (CheckHitKey(KEY_INPUT_R)) {
		play = true;
		StopSoundMem(BGM[1]);
		*scene = GAME;
	}
	else if (CheckHitKey(KEY_INPUT_X)) {
		play = true;
		StopSoundMem(BGM[1]);
		*scene = TITLE;
	}
}