#include "DxLib.h"
#include "resourceLoad.h"
#include "main.h"
#include "PadInput.h"
#include "player.h"
#include "title.h"
#include "test.h"
#include "help.h"
#include "ranking.h"
#include "ranking_name_input.h"
#include "end.h"
#include "init.h"
#include "result.h"
#include"UI.h"
#include "Apple.h"
#include "Pause.h"

PLAYER player;
Apple apple;
UI ui;

/********************************
* ゲームモード変数初期化
********************************/
int Game::mode = 0;
int Game::snd_flg = 0;

/********************************
* ゲームモード処理
********************************/
void Game::ModeSet(int m) {
    mode = m;
};
int Game::ModeGet() {
    return mode;
};
void Game::SndFlgSet(int m) {
    snd_flg = m;
};
int Game::SndFlgGet() {
    return snd_flg;
};

/********************************
* DxLib 開始
********************************/
int WINAPI WinMain(_In_ HINSTANCE  hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR LpCmdLine, _In_ int NCmdShow) {
	// タイトルを設定
	SetMainWindowText("りんごおとし");

	// 他のDxLibと競合しないように
	SetMainWindowClassName("りんごおとし");

	// ウインドウモードで起動
	ChangeWindowMode(TRUE);

	// ウインドウのサイズ
	SetGraphMode(1280, 720, 32);

	// DXライブラリの初期化処理
	if (DxLib_Init() == -1)return -1;

	// 描画先画面を裏にする（ダブルバッファリング）
	SetDrawScreen(DX_SCREEN_BACK);

    // FPSの計測と表示を行うローカル変数の宣言
    LONGLONG nowTime = GetNowHiPerformanceCount();
    LONGLONG oldTime = nowTime;
    LONGLONG fpsCheckTime;
    double deltaTime = 0;
    int fpsCounter = 0;
    int fps = 0;
	// ループ前にFPS計測を初期化
	fpsCheckTime = GetNowHiPerformanceCount();
	fps = 0;
	fpsCounter = 0;

	double nextTime;

	// リソースを読み込んで、他の .cpp でもメンバー変数で利用可能にする関数（島袋）
	if (Image::LoadImages() == -1)return -1;
	if (Sound::LoadSounds() == -1)return -1;
	if (Font::LoadFonts() == -1)return -1;

	// ランキングデータの読込
	if (ReadRanking() == -1) return -1;

	// ゲームループ
	while ((ProcessMessage() == 0) && (Game::ModeGet() != 99) && (!(PAD_INPUT::JudgeButton(XINPUT_BUTTON_BACK)))) {
		// 画面の初期化
		ClearDrawScreen();

		//コントローラーの入力を取得
		//コントローラーのMODEを押すと左スティックと十字ボタンの入力が逆になる
		PAD_INPUT::InputController();

		//ゲームモードと画面遷移
		switch (Game::ModeGet()) {
		case TITLE:
			// タイトル
			Title::Draw();
			if (CheckSoundMem(Sound::GetSounds(SND_BGM_SUB)) == 0) {
				PlaySoundMem(Sound::GetSounds(SND_BGM_SUB), DX_PLAYTYPE_LOOP, TRUE);
			}
			break;

		case INIT:
			// ゲーム初期化
			GameInit();
			StopSoundMem(Sound::GetSounds(SND_BGM_SUB));
			apple.SetBlinkFlg(0);
            apple.AppleInit();
			player.SetPlayerFlg(TRUE);
            player.PlayerInit();
			ui.SetUI(0,60);
			break;

		case MAIN:
			// 背景表示
			DrawGraph(0, 0, Image::GetImages(IMG_TITLE, 0), TRUE);
			
			// 開発用 - Rキーで強制リザルト
			if (CheckHitKey(KEY_INPUT_R)) {
                Game::ModeSet(RESULT);
			};

			if (PAD_INPUT::JudgeButton(XINPUT_BUTTON_START) == 1) { //ポーズ
				if (GetPauseFlg() == 0) {
					SetPauseFlg(1);
				}
				else {
					SetPauseFlg(0);
				}
			}
			// プレイヤー開始
			if (GetPauseFlg() == 0) {
				if (Game::SndFlgGet() == 0) {		//最初だけはじめから再生
					//BGM
					PlaySoundMem(Sound::GetSounds(SND_BGM_MAIN), DX_PLAYTYPE_LOOP, TRUE);
                    Game::SndFlgSet(1);
				}
				else {
					//BGM
					PlaySoundMem(Sound::GetSounds(SND_BGM_MAIN), DX_PLAYTYPE_LOOP, FALSE);
				}

				player.PlayerControll();
				player.DrawPlayer();
				ui.DrawImg();
				ui.DrawTimeLimit();

				apple.HitBoxPlayer();
				
				//リンゴ
				apple.FallApple();

				apple.GetPlayerX(player.ReturnPlayerX());
				apple.GetPlayerY(player.ReturnPlayerY());

			}
			else {
				//BGM
				StopSoundMem(Sound::GetSounds(SND_BGM_MAIN));
				for (int i = 0; i < 10; i++) {
					if (apple.ReturnAppleFlg(i) == TRUE) {
						//リンゴの表示
						DrawRotaGraph(apple.ReturnAppleX(i), apple.ReturnAppleY(i), 0.19, 0, apple.ReturnAppleImg(i), TRUE);
					}
				}
				player.DrawPlayerPause();
				ui.DrawImg();
				ui.DrawTimeLimit();
                apple.DrawPause();
				DrawStringToHandle(200, 310, "-- ポーズ中 --", 0x000000, Font::GetFonts(FONT_1_128), 0xffffff);
			}
			break;

		case HELP:
			// ヘルプ画面（島袋）
			Help::Draw();
			break;

		case RESULT:
			//BGM
			StopSoundMem(Sound::GetSounds(SND_BGM_MAIN));
			if (CheckSoundMem(Sound::GetSounds(SND_BGM_SUB)) == 0) {
				PlaySoundMem(Sound::GetSounds(SND_BGM_SUB), DX_PLAYTYPE_LOOP, TRUE);
			}
            Game::SndFlgSet(0);
			// リザルト画面
			DrawResult();
			break;

		case INPUTNAME:
			// ランキング入力画面（島袋）
            RankingNameInput::Draw();
			break;

		case RANKING:
			// ランキング画面
			DrawRanking();
			break;

		case END:
			// エンド画面
			DrawEnd();
			break;

		case TEST:
			// テストで、画像やフォント表示（島袋）（タイトルでTを押して発動）
            Test::Draw();
			break;
		}
		
		// 裏画面の内容を表画面に反映する
		ScreenFlip();

		// １ループ時点のシステム時間を取得
		oldTime = nowTime;
		nowTime = GetNowHiPerformanceCount();

		// １ループの時間経過を求める
		deltaTime = (nowTime - oldTime) / 1000000.0F;

		// １秒間のFPSを計測する、１秒ごとに初期化する
		fpsCounter++;
		if (nowTime - fpsCheckTime > 1000000) { // 1000000(240FPS) 500000(120FPS) 250000(60FPS)
			fps = fpsCounter;
			fpsCounter = 0;
			fpsCheckTime = nowTime;
		}

		// FPS60 固定
		nextTime = GetNowCount();
		nextTime += 16.6666666666667;
		if (nextTime > GetNowCount()) {
			WaitTimer(nextTime - GetNowCount());
		}
    };

	// DXライブラリ使用の終了処理
	DxLib_End();

	// プログラムの終了
	return 0;
};
