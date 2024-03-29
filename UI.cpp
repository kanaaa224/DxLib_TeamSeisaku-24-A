#include"DxLib.h"
#include"UI.h"
#include"main.h"
#include"init.h"
#include"resourceLoad.h"
#include"Apple.h"
#include <string>
#include"Pause.h"

using std::string;
using std::to_string;

void UI::DrawTimeLimit()
{
	//変数を文字列に変換
	std::string str = std::to_string(gTimeLimit);

	//ポーズ中ではないなら計測
	if (GetPauseFlg() == 0) {
		if ((gFpsCnt++) % 28 == 0) {
			gTimeLimit = gTimeLimit - 1;
		}
	}
	//制限時間表示
	DrawStringToHandle(1005, 50, "制限時間", 0x000000, Font::GetFonts(FONT_1_64), 0xffffff);
	DrawStringToHandle(1100, 150, str.c_str(), 0x000000, Font::GetFonts(FONT_1_64), 0xffffff);
	
	//リザルト遷移
	if (gTimeLimit <= 0)
	{
        Game::ModeSet(RESULT);
	}
}

void UI::DrawImg()
{
	//UIの背景
	DrawBox(1000, 0, 1280, 780, 0xd5e458, TRUE);
	DrawBox(1000, 0, 1280, 780, 0x000000, FALSE);
	//りんごの画像
	DrawRotaGraph(1030, 350, 0.125, 0, Image::GetImages(IMG_APPLE, REDAPPLE), TRUE);
	DrawRotaGraph(1140, 350, 0.125, 0, Image::GetImages(IMG_APPLE, BLUEAPPLE), TRUE);
	DrawRotaGraph(1250, 350, 0.125, 0, Image::GetImages(IMG_APPLE, GOLDAPPLE), TRUE);
}

void UI::SetUI(int cnt, int time) {
	gFpsCnt = cnt;
	gTimeLimit = time;
}
