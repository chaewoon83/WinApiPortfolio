#pragma once
#include <GameEngine/GameEngineActor.h>
class GameEngineRenderer;
// Ό³Έν :
class Map1FBridge : public GameEngineActor
{
public:
	// constrcuter destructer
	Map1FBridge();
	~Map1FBridge();

	// delete Function
	Map1FBridge(const Map1FBridge& _Other) = delete;
	Map1FBridge(Map1FBridge&& _Other) noexcept = delete;
	Map1FBridge& operator=(const Map1FBridge& _Other) = delete;
	Map1FBridge& operator=(Map1FBridge&& _Other) noexcept = delete;

	static Map1FBridge* GetInst()
	{
		return Inst_;
	}
	GameEngineRenderer* Renderer_1_;
	GameEngineRenderer* Renderer_2_;
protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	static Map1FBridge* Inst_;

};

