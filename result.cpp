#include "DxLib.h"
#include "resourceLoad.h"
#include <string>
#include "Apple.h"
#include "main.h"
#include "UI.h"
#include "ranking.h"
#include "PadInput.h"
#include "result.h"

using std::string;
using std::to_string;


/********************************
* リザルト画面
********************************/
void DrawResult() { // 未完成

	//文字列変換	個数を増分する表示はフォントが適応されないため文字列に変換
	std::string RED = "赤リンゴ：" + std::to_string(AppleCount::ReturnRA());		//REDに赤リンゴ：個数の文字列を作成　
	std::string BLUE = "青リンゴ：" + std::to_string(AppleCount::ReturnBL());		//BLUEに青リンゴ：個数の文字列を作成
	std::string GOLD = "黄リンゴ：" + std::to_string(AppleCount::ReturnGL());		//GOLDに金リンゴ：個数の文字列を作成
	std::string POISON = "毒リンゴ：" + std::to_string(AppleCount::ReturnPO());	//POISONに毒リンゴ：個数の文字列を作成
	std::string SCORE = "スコア：" + std::to_string(AppleCount::ReturnScore());	//SCOREにスコア：スコアの文字列を作成

	// 背景表示
	DrawGraph(0, 0, Image::GetImages(IMG_TITLE, 0), TRUE);

	//リザルト
	DrawStringToHandle(320, 70, "RESULT", 0x000000, Font::GetFonts(FONT_1_64), 0xffffff);

	//背景　白
	DrawBox(300, 160, 800, 550, 0xFDF5E6, TRUE);
	DrawBox(300, 160, 801, 551, 0x000000, FALSE);

	//赤　青　黄　毒　スコア の文字列(String)を文字(Char)に変換
	DrawStringToHandle(320, 180, RED.c_str(), 0x000000, Font::GetFonts(FONT_1_64), 0xffffff);
	DrawStringToHandle(320, 250, BLUE.c_str(), 0x000000, Font::GetFonts(FONT_1_64), 0xffffff);
	DrawStringToHandle(320, 320, GOLD.c_str(), 0x000000, Font::GetFonts(FONT_1_64), 0xffffff);
	DrawStringToHandle(320, 390, POISON.c_str(), 0x000000, Font::GetFonts(FONT_1_64), 0xffffff);
	DrawStringToHandle(320, 460, SCORE.c_str(), 0x000000, Font::GetFonts(FONT_1_64), 0xffffff);

	// 次へ
	DrawStringToHandle(530, 670, "Bボタンですすむ", 0x000000, Font::GetFonts(FONT_1_32), 0xffffff);
	// 仮、ボタンで分岐させる処理
	if (PAD_INPUT::JudgeButton(XINPUT_BUTTON_B) == 1) {
		if (GetRankingFlg() == 1) {
            Game::ModeSet(INPUTNAME);
		}
		else {
            Game::ModeSet(RANKING);
		}
	};
	// キーボード対応
	if (CheckHitKey(KEY_INPUT_SPACE)) {
		if (GetRankingFlg() == 1) {
            Game::ModeSet(INPUTNAME);
		}
		else {
            Game::ModeSet(RANKING);
		}
	};

};