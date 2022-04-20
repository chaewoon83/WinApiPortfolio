#pragma once
#include <GameEngine/GameEngine.h>
// 설명 : 예제 게임 ////////////////////나중에 이름 바꿀것////////////////////////
class Zelda : public GameEngine
{
public:
	// constrcuter destructer
	Zelda();
	~Zelda();

	// delete Function
	Zelda(const Zelda& _Other) = delete;
	Zelda(Zelda&& _Other) noexcept = delete;
	Zelda& operator=(const Zelda& _Other) = delete;
	Zelda& operator=(Zelda&& _Other) noexcept = delete;

	void GameInit() override;
	void GameLoop() override;
	void GameEnd() override;

protected:

private:
	void GetImageFromFolder(const std::string& _Folder);
	void GetSoundFromFolder();
	void ImageCutter(const std::string& _Image, int _x, int _y);

	void TotalImageGetFromFolder();
	void TotalImageCut();
};

