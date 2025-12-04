#include	"MainInclude.h"

static void StringDraw(const char** massage,const Vector2* pos);
static void ChangePos(int choice,Vector2* pos);

bool Menu(int* scene,time_t* fixedTime) {
	int choice = 0;
	int hitS = 0;
	int hitW = 0;
	int hitDown = 0;
	int hitUp = 0;

	const char* massage[] = {
	"再開",
	"タイトルに戻る"
	};

	Vector2 pos[] = {
		0,0,
	};

	while (1) {
		int nowS = CheckHitKey(KEY_INPUT_S);
		int nowW = CheckHitKey(KEY_INPUT_W);
		int nowDown = CheckHitKey(KEY_INPUT_DOWN);
		int nowUp = CheckHitKey(KEY_INPUT_UP);

		if ((nowW == 1 && hitW == 0) || (nowUp == 1 && hitUp == 0)) {
			choice--;
			ChangePos(choice, pos);
		}
		else if ((nowDown == 1 && hitDown == 0) || (nowS == 1 && hitS == 0)) {
			choice++;
			ChangePos(choice,pos);
		}

		hitS = nowS;
		hitW = nowW;
		hitDown = nowDown;
		hitUp = nowUp;

		StringDraw(massage, pos);

		if (CheckHitKey(KEY_INPUT_X) || (CheckHitKey(KEY_INPUT_RETURN) && choice == 0)) {
			*fixedTime = time(NULL) - *fixedTime;
			break;
		}
		else if (CheckHitKey(KEY_INPUT_RETURN) && choice == 1) {
			*scene = TITLE;
			return true;
		}
	}

	return false;
}

static void StringDraw(const char** massage,const Vector2* pos) {
	int y = 0;

	SetFontSize(50);
	while (pos != nullptr) {
		DrawString(50, 50 * y, *massage, WHITE);
		pos++;
		massage++;
		y++;
	}
}

static void ChangePos(int choice,Vector2* pos) {
	while (pos != nullptr) {
		pos->y = 50 * choice;
		pos++;
		choice++;
	}
}