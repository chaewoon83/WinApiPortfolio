#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class BossArmomsKnight : public GameEngineActor
{
public:
	// constrcuter destructer
	BossArmomsKnight();
	~BossArmomsKnight();

	// delete Function
	BossArmomsKnight(const BossArmomsKnight& _Other) = delete;
	BossArmomsKnight(BossArmomsKnight&& _Other) noexcept = delete;
	BossArmomsKnight& operator=(const BossArmomsKnight& _Other) = delete;
	BossArmomsKnight& operator=(BossArmomsKnight&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:

};

