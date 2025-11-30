#include	"MainInclude.h"
#include	<math.h>
#include	<stdlib.h>

struct Vector2 {
	int x;
	int y;
};

struct Circle {
	Vector2 pos;
	int radius;
};

void CircleDraw(Circle* circle);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	SetWindowText("‰æ–Ê‘JˆÚ");
	SetGraphMode(WIDTH, HEIGHT, 32);
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1) return -1;
	SetBackgroundColor(0, 0, 0);
	SetDrawScreen(DX_SCREEN_BACK);

	Circle circle = {WIDTH / 2,HEIGHT / 2,100};
	SetFontSize(50);

	while (1) {
		ClearDrawScreen();

		CircleDraw(&circle);

		ScreenFlip();
		WaitTimer(33);
		if (ProcessMessage() == 1) break;
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;
	}

	DxLib_End();
	return 0;

}

void CircleDraw(Circle* circle) {
	static int space = 0;
	static bool fill = false;

	fill ? DrawString(circle->pos.x - 150, circle->pos.y + circle->radius + 50, "“h‚è‚Â‚Ô‚µ‚ ‚è", WHITE) :
		DrawString(circle->pos.x - 150, circle->pos.y + circle->radius + 50, "“h‚è‚Â‚Ô‚µ‚È‚µ", WHITE);
	DrawCircle(circle->pos.x, circle->pos.y, circle->radius, RED, FALSE);

	CheckHitKey(KEY_INPUT_SPACE) ? space++ :
	space > 0 ? space = -1 : space = 0;

	if (space == 1) {
		fill ? fill = false : fill = true;
	}

	if (fill) {

		DrawCircle(circle->pos.x, circle->pos.y, circle->radius, RED, TRUE);
	}
	else{
		DrawCircle(circle->pos.x, circle->pos.y, circle->radius, RED, FALSE);
	}
}