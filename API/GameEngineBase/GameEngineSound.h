#pragma once
#include "GameEngineNameObject.h"
#include <map>
#include "ThirdParty/inc/fmod.hpp"

class GameEngineSoundPlayer;

//fmodL.dll �� ����׿��̴�
// ���� :
class GameEngineSound : public GameEngineNameObject
{
public:
	// constrcuter destructer
	GameEngineSound();
	~GameEngineSound();

	// delete Function
	GameEngineSound(const GameEngineSound& _Other) = delete;
	GameEngineSound(GameEngineSound&& _Other) noexcept = delete;
	GameEngineSound& operator=(const GameEngineSound& _Other) = delete;
	GameEngineSound& operator=(GameEngineSound&& _Other) noexcept = delete;

private:
	FMOD::Sound* Sound;

///////////////////////////////////�Ŵ�����Ʈ ���� ���
public:
	static GameEngineSoundPlayer SoundPlayControl(const std::string& _Name);
	//��� 1ȸ�� ����
	static void SoundPlayOneShot(const std::string& _Name, int LoopCount = 0);
	static void Update();

///////////////////////////////////���ҽ� �Ŵ�����Ʈ
public:
	static GameEngineSound* FindRes(const std::string& _Name);
	static GameEngineSound* LoadRes(const std::string& _Path);
	static GameEngineSound* LoadRes(const std::string& _Path, const std::string& _Name);

	static void AllResourcesDestroy();
protected:
	bool Load(const std::string& _Path);
private:
	static std::map<std::string, GameEngineSound*> AllRes;
};

//���� ����� �����Ѵ�
class GameEngineSoundPlayer
{
	friend GameEngineSound;

public:
	void Stop();
	

	GameEngineSoundPlayer(const GameEngineSoundPlayer& _Other);
private:
	GameEngineSound* Sound_;
	FMOD::Channel* ControlHandle_;
	GameEngineSoundPlayer(GameEngineSound* _Sound, FMOD::Channel* _ControlHandle);
public:
	GameEngineSoundPlayer();
	~GameEngineSoundPlayer();
};

