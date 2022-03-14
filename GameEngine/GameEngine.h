#pragma once
#include <map>
#include <string>
#include <GameEngineBase/GameEngineDebug.h>

// 설명 : 게임 그자체의 시작점과 끝점 실행중을 담당하는 녀석이다.
class GameEngineLevel;
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
	static void Start()
	{
		GameEngineDebug::LeakCheckOn();
		GameType UserGame;
		UserContents_ = &UserGame;
		WindowCreate();
		EngineEnd();
	}

	static GameEngine* GlobalEngine()
	{
		if (nullptr == UserContents_)
		{
			MsgBoxAssert("GlobalEngine ERROR Engine is not started");
			return nullptr;
		}
		return UserContents_;
	}

	void ChangeLevel(const std::string _Name);

protected:
	//굳이 NewLevel이 아닌 GameEngineLevel* Level 을 새로 만든 이유
	//Loading 함수의 경우 우리가 따로 더 실행 할 수 없게 protected로 걸려있다
	//그래서 GameENgineLevel 안에 friend GameEngine을 한 다음
	//GameEngineLevel의 protected 함수인 Loading을 불러오면 , 오버라이드 된 각각의 레벨의 로딩이 불러와진다.
	template<typename LevelType>
	void CreateLevel(const std::string _Name)
	{
		LevelType* NewLevel = new LevelType();
		NewLevel->SetName(_Name);
		GameEngineLevel* Level = NewLevel;
		Level->Loading();
		AllLevels_.insert(std::make_pair(_Name, NewLevel));
	}	



private:
	static std::map<std::string, GameEngineLevel*> AllLevels_;
	static GameEngineLevel* CurrentLevel_;
	static GameEngineLevel* NextLevel_;
	static GameEngine* UserContents_;

	static void WindowCreate();

	static void EngineStart();
	static void EngineLoop();
	static void EngineEnd();
};

