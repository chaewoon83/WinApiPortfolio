#pragma once
#include <map>
#include <string>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineDebug.h>

// 설명 : 게임 그자체의 시작점과 끝점 실행중을 담당하는 녀석이다.
class GameEngine
{
public:
	// constrcuter destructer
	GameEngine();
	virtual ~GameEngine();

	// delete Function
	GameEngine(const GameEngine& _Other) = delete;
	GameEngine(GameEngine&& _Other) noexcept = delete;
	GameEngine& operator=(const GameEngine& _Other) = delete;
	GameEngine& operator=(GameEngine&& _Other) noexcept = delete;

	//내가 만드는 프레임워크에서는
	//GameEngine의 init, loop, end 이 세가지를 꼭 구현해야한다.
	//내용이 없다고 하더라도 구현해야한다.
	virtual void GameInit() = 0;
	virtual void GameLoop() = 0;
	virtual void GameEnd() = 0;
	template<typename GameType>
	static void start()
	{
		GameEngineDebug::LeakCheckOn();
		GameType UserGame;
		UserContents_ = &UserGame;
		WindowCreate();
	}

protected:
	template<typename LevelType>
	void CreateLevel(const std::string _Level)
	{
		LevelType* NewLevel = new LevelType();
		AllLevels_.insert(std::make_pair(_Level, NewLevel));
	}


private:
	static std::map<std::string, GameEngineLevel*> AllLevels_;
	static GameEngine* UserContents_;

	void WindowCreate();

	static void EngineStart();
	static void EngineLoop();
	static void EngineEnd();
};

