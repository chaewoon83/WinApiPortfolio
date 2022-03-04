#include "GameEngineDebug.h"

GameEngineDebug::GameEngineDebug() 
{
}

GameEngineDebug::~GameEngineDebug() 
{
}

void GameEngineDebug::LeakCheckOn()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
}

void GameEngineDebug::MsgBoxAssert(const std::string& _Text)
{
	MessageBeep(0);
	//�׳� �ڱ��ڽ� ����, �ȳ����� �˾Ƽ� window�� ����
	MessageBoxA(nullptr, _Text.c_str());
	assert(false);
}

