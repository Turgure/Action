#include "DxLib.h"
#include "Sound.h"
using namespace std;

void Sound::initialize(){
	loadSETable();
	loadBGMTable();
	//tempBGMVolume.set(100);
}

void Sound::update(){
	for(auto se : seTable){
		if( se.playflag ){
			PlaySoundMem(se.handle, DX_PLAYTYPE_BACK);
			se.playflag = false;
		}
	}

	if(!playingBGM){
		PlaySoundMem(playingBGM, DX_PLAYTYPE_BACK);
	}
}

bool Sound::playBGM(unsigned int id){
	//if(undefined) return false;
	return bgmTable[id].playflag = true;
}

bool Sound::playBGM(const string name){
	//if(undefined) return false;
	for(auto bgm : bgmTable){
		if(bgm.title == name) return bgm.playflag = true;
	}
}

bool Sound::replayBGM(){
	if( CheckSoundMem(playingBGM) == 0 ){
		PlaySoundMem(playingBGM, DX_PLAYTYPE_LOOP, false);
		return true;
	}
	return false;
}

bool Sound::stopBGM(){
	if(playingBGM){
		StopSoundMem(playingBGM);
		playingBGM = -1;
		return true;
	}
	return false;
}

bool Sound::playSE(unsigned int id){
	//if(undefined) return false;
	return seTable[id].playflag = true;
	
}

bool Sound::playSE(const string name){
	//if(undefined) return false;
	for(auto se : seTable){
		if(se.title == name) return se.playflag = true;
	}
}

//void Sound::fadeMusic(int start, int end, int delay){
//	tempBGMVolume.set(min(start, 100));
//	tempBGMVolume.set(max(end, 0), delay);
//}
//
//void Sound::fadeMusic(int end, int delay){
//	tempBGMVolume.set(max(end, 0), delay);
//}


/*
void Sound::loadBGMTable(){
	DXFileStream file("bgm/bgm.tsv");
	if(!file){
		DebugPrintln("BGM定義ファイルが見つかりません。\n");
		return;
	}
	BGMTable.clear();

	while(!file.eof()){
		BGMData current_bgm;
		current_bgm.filename = "bgm/";
		// 1行読む
		char buf[256];
		file.gets(buf, 256);
		// 1文字目が / ならコメントなので飛ばす
		if(buf[0] == '/') continue;

		// セルを取得
		RDM::TSVLineReader line(buf);
		line.ignoreSpace = false;
		while(!line.isEol()){
			string& cell = line.getCell();
			if(cell.empty()) break;
			// セル内容処理
			switch(line.getIndex()){
				case 0: current_bgm.dataname	= cell;break;
				case 1: current_bgm.filename	+= cell;break;
				case 2: current_bgm.loopPos		= stoi(cell);break;
				case 3: current_bgm.title		= cell;break;
			}
			// 1セル処理完了
		}
		// 1行処理完了
		// BGMを追加
		if(!current_bgm.title.empty()){
			BGMTable.push_back(current_bgm);
			BGMNameTable[Hash32(current_bgm.dataname.c_str())] = BGMTable.size() - 1;
		}
	}
}

void Sound::loadSETable(){
	InitSoundMem();
	SetCreateSoundDataType(DX_SOUNDDATATYPE_MEMNOPRESS);

	DXFileStream file("data2/se/se.tsv");
	if(!file){
		DebugPrintln("SE定義ファイルが見つかりません。\n");
		return;
	}
	BGMTable.clear();

	while(!file.eof()){
		struct CSeData{
			string filename;
			unsigned int name;
			int volume;
		} currentSE;
		currentSE.filename = "data2/se/";
		currentSE.volume = 100;

		// 1行読む
		char buf[256];
		file.gets(buf, 256);
		// 1文字目が / ならコメントなので飛ばす
		if(buf[0] == '/') continue;

		// セルを取得
		RDM::TSVLineReader line(buf);
		while(!line.isEol()){
			string& cell = line.getCell();
			if(cell.empty()) break;
			// セル内容処理
			switch(line.getIndex()){
				case 0: currentSE.name		= Hash32(cell.c_str());break;
				case 1: currentSE.filename	+= cell;break;
				case 2: currentSE.volume	= stoi(cell);break;
			}
			// 1セル処理完了
		}
		// 1行処理完了
		// SEを追加
		if(!currentSE.filename.empty()){
			int sound = LoadSoundMem( currentSE.filename.c_str() );
			if(sound != -1){
				se.push_back(SEData());
				se.back().handle = sound;
				se.back().playflag = false;
				se.back().volume = currentSE.volume;
				setVolumeToSoundInPercent(se.back().volume, sound);
				SENameTable[currentSE.name] = se.size() - 1;
				DebugPrintln(Dix::Str() << "SE '" << currentSE.filename << "' をロードしました。Volume: "<<currentSE.volume<<"% Key: " << currentSE.name << "\n");
			}else{
				DebugPrintln(Dix::Str() << "SE '" << currentSE.filename << "' が見つかりません。\n");
			}
		}
	}
}
*/
