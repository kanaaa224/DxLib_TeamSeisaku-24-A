#include "Pause.h"

int PauseFlg = 0; //１ならポーズ中０なら通常

int GetPauseFlg() {
	return PauseFlg;
}

int SetPauseFlg(int num) {
	PauseFlg = num;
	return PauseFlg;
}