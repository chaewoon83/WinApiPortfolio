#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class UIMagicMeter : public GameEngineActor
{
public:
	// constrcuter destructer
	UIMagicMeter();
	~UIMagicMeter();

	// delete Function
	UIMagicMeter(const UIMagicMeter& _Other) = delete;
	UIMagicMeter(UIMagicMeter&& _Other) noexcept = delete;
	UIMagicMeter& operator=(const UIMagicMeter& _Other) = delete;
	UIMagicMeter& operator=(UIMagicMeter&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:

};

