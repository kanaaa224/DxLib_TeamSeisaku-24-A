#include"DxLib.h"
#include"resourceLoad.h"
#include"PadInput.h"
#include"player.h"
#include"Apple.h"

int Stick;
int FPScountLeft = 0;
int FPScountRight = 0;
int Run = 0;
int Walk = 0;
int Stop = 0;
int RunImg;
int WalkImg;
int StopImg;
int FPS = 0;
int BlinkFPSFlg = 0;

void PLAYER::PlayerControll() {
	Stick = PAD_INPUT::GetStickX();	//スティックの状態取得
	PlayerLimit();

	//右歩き
	if (Stick > WALK_RIGHT && Stick < RUN_RIGHT) {
		if (PlayerLimit() == 0) {
			if (speed > WALK_SPEED) {
				speed -= 0.2;
			}
			else if (speed < WALK_SPEED) {
				speed += 0.2;
			}
			else{
				speed = WALK_SPEED;
			}
		}
		FPScountRight = 0;
		FPScountLeft = 0;
	}
	//左歩き
	else if (Stick < WALK_LEFT && Stick > RUN_LEFT) {
		if (PlayerLimit() == 0) {
			if (speed < WALK_SPEED * -1) {
				speed += 0.2;
			}
			else if (speed > WALK_SPEED * -1) {
				speed -= 0.2;
			}
			else {
				speed = WALK_SPEED * -1;
			}
			
		}
        FPScountRight = 0;
        FPScountLeft = 0;
	}
	//右ダッシュ
	else if (Stick >= RUN_RIGHT) {
		if (PlayerLimit() == 0) {
            FPScountLeft = 0;
			if (speed < 3) {
				speed += 0.2;
			}
			else {
				if (FPScountRight < 30 && FPScountRight % 2 == 0) {
					speed += SPEED_UP;
				}
				FPScountRight++;
			}
		}
	}
	//左ダッシュ
	else if(Stick <= RUN_LEFT) {
		if (PlayerLimit() == 0) {
            FPScountRight = 0;
			if (speed > -3 ) {
				speed -= 0.2;
			}
			else {
				if (FPScountLeft < 30 && FPScountLeft % 2 == 0) {
					speed -= SPEED_UP;
				}       
				FPScountLeft++;
			}
		}
	}
	//立ち止まり
	else if (Stick <= WALK_RIGHT && Stick >= WALK_LEFT) {
		if (PlayerLimit() == 0) {
			//慣性
			if (speed <= 0.2 && speed >= -0.2) {
				speed = 0;
                FPScountRight = 0;
                FPScountLeft = 0;
			}
			else if (speed > 0) {
				speed -= 0.2;
			}
			else if (speed < 0) {
				speed += 0.2;
			}
			else{
				speed = 0;
                FPScountRight = 0;
                FPScountLeft = 0;
			}
		}
	}
}

int PLAYER::PlayerLimit() {
	//プレイヤーの移動制限
	if (x < MOVE_LEFT_LIMIT) {
		speed = 0;
		x = MOVE_LEFT_LIMIT;
		return 1;
	}
	else if (x > MOVE_RIGHT_LIMIT) {
		speed = 0;
		x = MOVE_RIGHT_LIMIT;
		return 1;
	}
	else {
		x += speed;
		
		return 0;
	}
}

void PLAYER::DrawPlayer() {
    RunImg = Image::GetImages(IMG_RUN, Run);
    WalkImg = Image::GetImages(IMG_WALK, Walk);
    StopImg = Image::GetImages(IMG_STOP, Stop);
	if (flg == TRUE) {
		//右歩き
		if (speed > 0 && speed < 3 && x != MOVE_RIGHT_LIMIT) {
			if (FPS % 10 == 0) {
				Walk++;
				if (Walk > 2) {
					Walk = 0;
				}
			}
			DrawRotaGraph(x, y, IMAGE_RATE, 0, WalkImg, TRUE, TRUE);
		}
		//右ダッシュ
		else if (speed > 3 && x != MOVE_RIGHT_LIMIT) {
			if (FPS % 5 == 0) {
				Run += 2;
				if (Run > 7) {
					Run = 0;
				}
			}
			DrawRotaGraph(x, y, IMAGE_RATE, 0, RunImg, TRUE, TRUE);

		}
		//左歩き
		else if (speed < 0 && speed > -3 && x != MOVE_LEFT_LIMIT) {
			if (FPS % 10 == 0) {
				Walk++;
				if (Walk > 2) {
					Walk = 0;
				}
			}
			DrawRotaGraph(x, y, IMAGE_RATE, 0, WalkImg, TRUE, FALSE);
		}
		//左ダッシュ
		else if (speed < -2 && x != MOVE_LEFT_LIMIT) {
			if (FPS % 5 == 0) {
				Run += 2;
				if (Run > 7) {
					Run = 0;
				}
			}
			DrawRotaGraph(x, y, IMAGE_RATE, 0, RunImg, TRUE, FALSE);
		}
		//左右の入れ替わりの際にちらつきがなくなるように
		else if ((Stick < 500 && Stick > -500) || x <= MOVE_LEFT_LIMIT || x >= MOVE_RIGHT_LIMIT) {
            Stop = 0;
			DrawRotaGraph(x, y, IMAGE_RATE, 0, StopImg, TRUE, FALSE);
		}
		//立ち止まり
		else {
            Stop = 1;
			DrawRotaGraph(x, y, IMAGE_RATE, 0, StopImg, TRUE, FALSE);
		}
	}

	if (BlinkFlg == 0) {
		FPS++;
	}
	

	//毒リンゴ取得時の点滅
	SetPlayerBlinkFlg(Apple::GetBlinkFlg());
	if (BlinkFlg == 1) {
		//FPSカウント初期化(一度だけ)
		if (BlinkFPSFlg == 0) {
			FPS = 0;
			BlinkFPSFlg = 1;
		}
		//20fごとに切り替え
		if (FPS % 21 == 0) {
			if (flg == TRUE) {
				flg = FALSE;
			}
			else if (flg == FALSE) {
				flg = TRUE;
			}
		}
		FPS++;
		//120fで終了
		if (FPS % 120 == 0) {
			SetPlayerBlinkFlg(0);
			BlinkFPSFlg = 0;
			flg = TRUE;
            Apple::SetBlinkFlg(0);
		}
	}
}

//ポーズ中のプレイヤーの描画
void PLAYER::DrawPlayerPause() {
	if (flg == TRUE) {
		//右歩き
		if (speed > 0 && speed < 3 && x != MOVE_RIGHT_LIMIT) {
			DrawRotaGraph(x, y, IMAGE_RATE, 0, WalkImg, TRUE, TRUE);
		}
		//右ダッシュ
		else if (speed > 2 && x != MOVE_RIGHT_LIMIT) {
			DrawRotaGraph(x, y, IMAGE_RATE, 0, RunImg, TRUE, TRUE);
		}
		//左歩き
		else if (speed < 0 && speed > -3 && x != MOVE_LEFT_LIMIT) {
			DrawRotaGraph(x, y, IMAGE_RATE, 0, WalkImg, TRUE, FALSE);
		}
		//左ダッシュ
		else if (speed < -2 && x != MOVE_LEFT_LIMIT) {
			DrawRotaGraph(x, y, IMAGE_RATE, 0, RunImg, TRUE, FALSE);
		}
		//横向き
		else if ((Stick < 500 && Stick > -500) || x <= MOVE_LEFT_LIMIT || x >= MOVE_RIGHT_LIMIT) {
			DrawRotaGraph(x, y, IMAGE_RATE, 0, StopImg, TRUE, FALSE);
		}
		//立ち止まり
		else {
			DrawRotaGraph(x, y, IMAGE_RATE, 0, StopImg, TRUE, FALSE);
		}
	}
}


int PLAYER::ReturnPlayerX() {
	return x;
}
int PLAYER::ReturnPlayerY() {
	return y;
}

void PLAYER::SetPlayerX(int xPos) {
	x = xPos;
}

void PLAYER::SetPlayerBlinkFlg(int x) {
	BlinkFlg = x;
}

void PLAYER::PlayerInit() {
	flg = TRUE;
	x = 600;
	y = 600;
	speed = 0;
	BlinkFlg = 0;
}

void PLAYER::SetPlayerFlg(int Pflg) {
	flg = Pflg;
}

int PLAYER::GetPlayerBlinkFlg() {
	return BlinkFlg;
}

