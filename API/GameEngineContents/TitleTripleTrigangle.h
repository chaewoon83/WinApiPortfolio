#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class TitleTripleTrigangle : public GameEngineActor
{
public:
	// constrcuter destructer
	TitleTripleTrigangle();
	~TitleTripleTrigangle();

	// delete Function
	TitleTripleTrigangle(const TitleTripleTrigangle& _Other) = delete;
	TitleTripleTrigangle(TitleTripleTrigangle&& _Other) noexcept = delete;
	TitleTripleTrigangle& operator=(const TitleTripleTrigangle& _Other) = delete;
	TitleTripleTrigangle& operator=(TitleTripleTrigangle&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	GameEngineRenderer* TripleTriangle_;
	bool isTripleTriangleExist_;
};

