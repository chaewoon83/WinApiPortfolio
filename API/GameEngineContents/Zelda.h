#pragma once
#include <GameEngine/GameEngine.h>
// ���� : ���� ���� ////////////////////���߿� �̸� �ٲܰ�////////////////////////
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

};

