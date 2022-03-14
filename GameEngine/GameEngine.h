#pragma once
#include <map>
#include <string>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineDebug.h>

// ���� : ���� ����ü�� �������� ���� �������� ����ϴ� �༮�̴�.
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

	//���� ����� �����ӿ�ũ������
	//GameEngine�� init, loop, end �� �������� �� �����ؾ��Ѵ�.
	//������ ���ٰ� �ϴ��� �����ؾ��Ѵ�.
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

