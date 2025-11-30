#include	"11.25/MainInclude.h"
#include	<math.h>
#include	<stdlib.h>

struct Vector2 {
	int x;
	int y;
};

struct Box {
	Vector2 pos;
	Vector2 length;
};

int hitRectRect(Box* box);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	SetWindowText("âÊñ ëJà⁄");
	SetGraphMode(WIDTH, HEIGHT, 32);
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1) return -1;
	SetBackgroundColor(0, 0, 0);
	SetDrawScreen(DX_SCREEN_BACK);

	Box box[2] = {
		0,0,500,1000,
		300,500,800,300
	};

	SetFontSize(100);
	hitRectRect(box) ? DrawString(WIDTH / 2 - 200, HEIGHT / 2, "è’ìÀ", WHITE) : DrawString(WIDTH / 2 - 200, HEIGHT / 2, "Notè’ìÀ", WHITE);

	ScreenFlip();
	WaitTimer(5000);
	DxLib_End();
	return 0;

}

int hitRectRect(Box* box) {
	int dx = abs(box[0].pos.x - box[1].pos.x);
	int dy = abs(box[0].pos.y - box[1].pos.y);

	return
		dx <= (box[0].length.x + box[1].length.x) / 2 && dy <= (box[0].length.y + box[1].length.y) / 2 ? 1 : 0;
}