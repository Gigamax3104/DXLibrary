#include	"MainInclude.h"
#include	<math.h>
#include	<stdlib.h>

struct Circle {
	Vector2 pos;
	int radius;
};

bool hitCircleCircle(const Circle* circle);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	SetWindowText("âÊñ ëJà⁄");
	SetGraphMode(WIDTH, HEIGHT, 32);
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1) return -1;
	SetBackgroundColor(0, 0, 0);
	SetDrawScreen(DX_SCREEN_BACK);

	Circle circle[2] = {
		400,300,100,
		400,400,80
	};

	SetFontSize(100);
	hitCircleCircle(circle) ? DrawString(WIDTH / 2 - 200, HEIGHT / 2, "è’ìÀ", WHITE) :DrawString(WIDTH / 2 - 200, HEIGHT / 2, "Notè’ìÀ", WHITE);

	ScreenFlip();
	WaitTimer(5000);
	DxLib_End();
	return 0;

}

bool hitCircleCircle(const Circle* circle) {
	double d = sqrt((circle[0].pos.x - circle[1].pos.x) * (circle[0].pos.x - circle[1].pos.x)
		+ (circle[0].pos.y - circle[1].pos.y) * (circle[0].pos.y - circle[1].pos.y));

	return
		d <= circle[0].radius + circle[1].radius ? true : false;
}