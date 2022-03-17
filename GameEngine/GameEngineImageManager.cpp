#include "GameEngineImageManager.h"


static GameEngineImageManager* Inst_ = new GameEngineImageManager();

GameEngineImageManager::GameEngineImageManager() 
{
}

GameEngineImageManager::~GameEngineImageManager() 
{
}

GameEngineImage* GameEngineImageManager::Create(const std::string& _Name, float4 _Scale)
{
	if (AllRes.end() != AllRes.find(_Name))
	{
		MsgBoxAssert("이미 존재하는 이름의 리소스를 또 만드려고 했습니다");
	}

	GameEngineImage* NewImage = new GameEngineImage();
	NewImage->SetName(_Name);
	AllRes.insert(std::make_pair(_Name, NewImage));
	if (false == NewImage->Create(_Scale))
	{
		delete NewImage;
		MsgBoxAssert((_Name + "이미지를 생성하는데 실패했습니다").c_str());
		return;
	}
}