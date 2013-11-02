#pragma once

class Input{
public:
	static Input& getInstance(){
		static Input instance;
		return instance;
	}

	void initialize();
	void update();

	bool pushed(int keyID, bool judge_once = true);
	bool pushing(int keyID);
	bool released(int keyID);
	
	bool pushingUntil(int keyID, int frame);
	bool pushingPer(int keyID, int frame);
	
	int getFrame(int keyID);

private:
	Input(){}

	int key[256];
	int prevkey[256];
};
