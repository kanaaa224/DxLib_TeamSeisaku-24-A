#include "DxLib.h"
#include "resourceLoad.h"

#include "main.h"


int FPSCount = 0;


/********************************
* エンド画面
********************************/
void DrawEnd() {
	if (FPSCount++ < 300) {

		// 背景表示
		DrawGraph(0, 0, Image::GetImages(IMG_TITLE, 0), TRUE);

		//背景BOX
		DrawBox(165, 145, 1030, 650, 0xeee8aa, TRUE);

		// Thank you for playing
		DrawStringToHandle(10, 10, "Thank you for playing", 0x000000, Font::GetFonts(FONT_1_128), 0xffffff);

		//製作者
		DrawStringToHandle(170, 150, "製作者", 0x000000, Font::GetFonts(FONT_0_32), 0xffffff);
		DrawStringToHandle(170, 200, "国際電子ビジネス専門学校", 0x000000, Font::GetFonts(FONT_0_16), 0xffffff);
		DrawStringToHandle(170, 230, "新里滉規　北村隼士 島袋 叶望　玉城流叶　豊元一成",0x000000, Font::GetFonts(FONT_0_16), 0xffffff);

		// 謝辞
		DrawStringToHandle(170, 270, "使用した素材", 0x000000, Font::GetFonts(FONT_0_32), 0xffffff);
		DrawStringToHandle(170, 330, "プレイヤー画像（歩く）         pictogramming（豊元一成）https://pictogramming.org/?page_id=2919", 0x000000, Font::GetFonts(FONT_0_16), 0xffffff);
		DrawStringToHandle(170, 360, "プレイヤー画像（走る)          pictogramming（北村隼士）https://pictogramming.org/?page_id=2919", 0x000000, Font::GetFonts(FONT_0_16), 0xffffff);
		DrawStringToHandle(170, 390, "りんご画像                     illustAC（ゆゆこ）https://www.ac-illust.com/", 0x000000, Font::GetFonts(FONT_0_16), 0xffffff);
		DrawStringToHandle(170, 420, "ゲーム背景画像                 いらすとや　https://www.irasutoya.com/", 0x000000, Font::GetFonts(FONT_0_16), 0xffffff);

		DrawStringToHandle(170, 450, "フォント                       ＢＯＯＴＨ（ぼんのう堂）　https://booth.pm/ja", 0x000000, Font::GetFonts(FONT_0_16), 0xffffff);

		DrawStringToHandle(170, 480, "ゲームメインBGM                ＤＯＶＡーＳＹＮＤＲＯＭＥ　（shimtone） https://dova-s.jp/", 0x000000, Font::GetFonts(FONT_0_16), 0xffffff);
		DrawStringToHandle(170, 510, "ゲームメイン外BGM              ＭｕｓＭＵｓ　https://musmus.main.jp/", 0x000000, Font::GetFonts(FONT_0_16), 0xffffff);

		DrawStringToHandle(170, 540, "りんご取得時SE                 効果音ラボ　https://soundeffect-lab.info/", 0x000000, Font::GetFonts(FONT_0_16), 0xffffff);
		DrawStringToHandle(170, 570, "毒りんご取得時SE               効果音ラボ　https://soundeffect-lab.info/", 0x000000, Font::GetFonts(FONT_0_16), 0xffffff);
		DrawStringToHandle(170, 600, "タイトルでの選択時             効果音ラボ　https://soundeffect-lab.info/", 0x000000, Font::GetFonts(FONT_0_16), 0xffffff);
		DrawStringToHandle(170, 630, "タイトルでのカーソル移動時SE   効果音ラボ　https://soundeffect-lab.info/", 0x000000, Font::GetFonts(FONT_0_16), 0xffffff);

		if (CheckHitKey(KEY_INPUT_ESCAPE)) {
            Game::ModeSet(EXIT);
		};

		if (FPSCount == 300) {
            Game::ModeSet(EXIT);
		}
	}
};