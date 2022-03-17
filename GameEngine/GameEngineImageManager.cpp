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
		MsgBoxAssert("�̹� �����ϴ� �̸��� ���ҽ��� �� ������� �߽��ϴ�");
	}

	GameEngineImage* NewImage = new GameEngineImage();
	NewImage->SetName(_Name);
	AllRes.insert(std::make_pair(_Name, NewImage));
	if (false == NewImage->Create(_Scale))
	{
		delete NewImage;
		MsgBoxAssert((_Name + "�̹����� �����ϴµ� �����߽��ϴ�").c_str());
		return;
	}
}