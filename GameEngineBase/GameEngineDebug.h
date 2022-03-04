#pragma once
#include <crtdbg.h>
#include <string>
#include <windows.h>
#include <assert.h>


// Ό³Έν :
class GameEngineDebug
{
public:
	static void LeakCheckOn();
	static void MsgBoxAssert(const std::string& _Text);

protected:

private:
	// constrcuter destructer
	GameEngineDebug();
	~GameEngineDebug();

	// delete Function
	GameEngineDebug(const GameEngineDebug& _Other) = delete;
	GameEngineDebug(GameEngineDebug&& _Other) noexcept = delete;
	GameEngineDebug& operator=(const GameEngineDebug& _Other) = delete;
	GameEngineDebug& operator=(GameEngineDebug&& _Other) noexcept = delete;

};

