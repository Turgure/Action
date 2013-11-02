#include "DxLib.h"
#include "Input.h"

void Input::initialize(){
	for(int i = 0; i < 256; i++){
		key[i] = 0;
		prevkey[i] = 0;
	}
}

void Input::update(){
	char tmpKey[256];
	GetHitKeyStateAll(tmpKey);
	for(int i = 0; i < 256; i++){
		prevkey[i] = key[i];

		if(tmpKey[i] != 0){//i”Ô‚ÌƒL[‚ª‰Ÿ‚³‚ê‚½‚ç
			++key[i];
		} else {
			key[i] = 0;
		}
	}
}

bool Input::pushed(int keyID, bool judge_once){
	if(prevkey[keyID] == 0 && key[keyID] == 1){
		if(judge_once) key[keyID] = INT_MIN;
		return true;
	}
	return false;
}

bool Input::pushing(int keyID){
	return (prevkey[keyID] > 0 && key[keyID] > 0);
}

bool Input::released(int keyID){
	return (prevkey[keyID] == 1 && key[keyID] == 0);
}

bool Input::pushingUntil(int keyID, int frame){
	return (key[keyID] > frame);
}

bool Input::pushingPer(int keyID, int frame){
	return (key[keyID] % frame == 0);
}

int Input::getFrame(int keyID){
	return key[keyID];
}