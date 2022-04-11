#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class Title19911992 : public GameEngineActor
{
public:
	// constrcuter destructer
	Title19911992();
	~Title19911992();

	// delete Function
	Title19911992(const Title19911992& _Other) = delete;
	Title19911992(Title19911992&& _Other) noexcept = delete;
	Title19911992& operator=(const Title19911992& _Other) = delete;
	Title19911992& operator=(Title19911992&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	GameEngineRenderer* NintendoLogo_;
	bool IsNintendoLogoExist_;
	bool IsNintendoLogoDeath_;
};

