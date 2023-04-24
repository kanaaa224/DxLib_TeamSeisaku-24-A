#include "DxLib.h"
#include "resourceLoad.h"
#include "Apple.h"
#include "main.h"
#include"UI.h"

extern Image image;
extern Font font;

extern Game game;
extern UI ui;

int RED_AppleCount		= 0;
int BLUE_AppleCount		= 0;
int GOLD_AppleCount		= 0;
int POISON_AppleCount	= 0;
int AppleScore = 0;

/********************************
* ���U���g���
********************************/
void DrawResult() {

	RED_AppleCount		= ReturnRA();
	BLUE_AppleCount		= ReturnBL();
	GOLD_AppleCount		= ReturnGL();
	POISON_AppleCount	= ReturnPO();
	AppleScore			= ReturnScore();

	// �w�i�\��
	DrawGraph(0, 0, image.title, TRUE);

	//�ԁ@�@���@�Ł@�X�R�A
	DrawStringToHandle(160, 180, "�ԃ����S�F", 0x000000, font.handle_1_64, 0xffffff);
	DrawStringToHandle(160, 250, "�����S�F", 0x000000, font.handle_1_64, 0xffffff);
	DrawStringToHandle(160, 320, "�������S�F", 0x000000, font.handle_1_64, 0xffffff);
	DrawStringToHandle(160, 390, "�Ń����S�F", 0x000000, font.handle_1_64, 0xffffff);
	DrawStringToHandle(220, 460, "�X�R�A�F", 0x000000, font.handle_1_64, 0xffffff);

	//�J�E���g�\��
	DrawFormatStringFToHandle(500, 180, 0x000000, font.handle_1_64, "%d", RED_AppleCount);
	DrawFormatStringFToHandle(500, 250, 0x000000, font.handle_1_64, "%d", BLUE_AppleCount);
	DrawFormatStringFToHandle(500, 320, 0x000000, font.handle_1_64, "%d", GOLD_AppleCount);
	DrawFormatStringFToHandle(500, 390, 0x000000, font.handle_1_64, "%d", POISON_AppleCount);
	DrawFormatStringFToHandle(500, 460, 0x000000, font.handle_1_64, "%d", AppleScore);

	// �߂�\��
	DrawStringToHandle(420, 670, "ESC�L�[�܂���A�{�^���ł��ǂ�", 0x000000, font.handle_1_32, 0xffffff);

	// Space �Ń^�C�g��
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		game.mode = TITLE;
	};
};