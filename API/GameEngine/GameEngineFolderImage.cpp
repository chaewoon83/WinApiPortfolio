#include "GameEngineFolderImage.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include "GameEngineImageManager.h"


GameEngineFolderImage::GameEngineFolderImage()
{

}

GameEngineFolderImage::~GameEngineFolderImage()
{
	for (size_t i = 0; i < Images_.size(); i++)
	{
		delete Images_[i];
		Images_[i] = nullptr;
	}
}

bool GameEngineFolderImage::Load(const std::string& _Path)
{
	// 디렉토리, 리소스폴더 경로 지정
	GameEngineDirectory ResourcesDir = GameEngineDirectory(_Path);;

	// 폴더안에 모든 이미지 파일을 찾는다.
	std::vector<GameEngineFile> PlayerImageFileList = ResourcesDir.GetAllFile("bmp");

	Images_.reserve(PlayerImageFileList.size());

	for (size_t i = 0; i < PlayerImageFileList.size(); ++i)
	{
		// 새로운 이미지 생성
		GameEngineImage* Image = new GameEngineImage();

		//이미지 로드
		if (false == Image->Load(PlayerImageFileList[i].GetFullPath()))
		{
			MsgBoxAssert("폴더 이미지 로드중 실패한 이미지가 존재합니다.");
		}
		//이미지 벡터안에 넣기
		Images_.push_back(Image);
	}

	return true;
}
