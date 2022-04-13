#pragma once
#include "GameEngineNameObject.h"
#include <map>
#include "ThirdParty/inc/fmod.hpp"

class GameEngineSoundPlayer;

//fmodL.dll 은 디버그용이다
// 설명 :
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

///////////////////////////////////매니지먼트 사운드 기능
public:
	static GameEngineSoundPlayer SoundPlayControl(const std::string& _Name);
	//재생 1회만 가능
	static void SoundPlayOneShot(const std::string& _Name, int LoopCount = 0);
	static void Update();

///////////////////////////////////리소스 매니지먼트
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

//사운드 재생을 제어한다
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

