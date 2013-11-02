#pragma once
#include <memory>
#include "Graphic.h"

/* 
 * シーン基底クラス
 * 全シーンクラスの基底クラス。このクラスのmain()を起動することで場面が切り替わる。
 */
class SceneManager;
class BaseScene{
	friend class SceneManager;
public:
	BaseScene();
	virtual ~BaseScene(){}
	
protected:
	virtual void start(){}     ///< @brief 起動処理
	virtual void update(){}    ///< @brief フレーム更新
	virtual void terminate(){} ///< @brief 終了処理
	void setNextScene(std::shared_ptr<BaseScene> scene);

private:
	BaseScene(const BaseScene&);
	BaseScene operator=(const BaseScene&);
	std::shared_ptr<BaseScene> main(); ///< シーン実行
	bool processLoop();

	static bool running;
	bool looping; ///< @brief ループ中フラグ @detail ループ中フラグ。falseの状態でupdate()を抜けるとシーンが終了する。
	std::shared_ptr<BaseScene> next_scene;
};


/* 
 * シーン管理クラス
 * シーンの遷移と実行を管理するクラス
 */
class SceneManager{
public:
	static void run(std::shared_ptr<BaseScene> starter);

private:
	static bool running; ///< 実行中フラグ　
	static std::shared_ptr<BaseScene> current;
};
