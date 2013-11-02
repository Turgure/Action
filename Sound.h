#pragma once
#include <string>
#include <vector>
#include <unordered_map>
//#include "Fader.h"

class Sound{
private:
	struct Data{
		std::string filename;
		std::string title;
		int handle;
		int volume;
		bool playflag;
	};

	struct BGMData : public Data{
		BGMData():loopPos(0){}
		int loopPos;
	};
	struct SEData : public Data{};

public:
	static Sound getInstance(){
		static Sound instance;
		return instance;
	}

	void initialize();
	void update();

	bool playBGM(unsigned int id);
	bool playBGM(const std::string name);
	bool replayBGM();
	bool stopBGM();

	bool playSE(unsigned int id);
	bool playSE(const std::string name);

	void fadeMusic(int start, int end, int delay);
	void fadeMusic(int end, int delay);

private:
	Sound(){}
	void loadBGMTable(){}	//TODO:
	void loadSETable(){}	//TODO:
	
	std::vector<BGMData> bgmTable;
	std::vector<SEData> seTable;
	int playingBGM;
};
