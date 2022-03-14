#pragma once
#include <map>
#include <string>
#include <GameEngineBase/GameEngineDebug.h>

// ���� : ���� ����ü�� �������� ���� �������� ����ϴ� �༮�̴�.
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

	//���� ����� �����ӿ�ũ������
	//GameEngine�� init, loop, end �� �������� �� �����ؾ��Ѵ�.
	//������ ���ٰ� �ϴ��� �����ؾ��Ѵ�.
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
	//���� NewLevel�� �ƴ� GameEngineLevel* Level �� ���� ���� ����
	//Loading �Լ��� ��� �츮�� ���� �� ���� �� �� ���� protected�� �ɷ��ִ�
	//�׷��� GameENgineLevel �ȿ� friend GameEngine�� �� ����
	//GameEngineLevel�� protected �Լ��� Loading�� �ҷ����� , �������̵� �� ������ ������ �ε��� �ҷ�������.
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

