#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class Background : public GameEngineActor
{
public:
	// constrcuter destructer
	Background();
	~Background();

	// delete Function
	Background(const Background& _Other) = delete;
	Background(Background&& _Other) noexcept = delete;
	Background& operator=(const Background& _Other) = delete;
	Background& operator=(Background&& _Other) noexcept = delete;

	inline GameEngineRenderer* GetRenderer()
	{
		return Renderer_;
	}

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	GameEngineRenderer* Renderer_;
};

