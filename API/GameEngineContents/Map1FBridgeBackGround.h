#pragma once
#include <GameEngine/GameEngineActor.h>
class GameEngineRenderer;
// Ό³Έν :
class Map1FBridgeBackGround : public GameEngineActor
{
public:
	// constrcuter destructer
	Map1FBridgeBackGround();
	~Map1FBridgeBackGround();

	// delete Function
	Map1FBridgeBackGround(const Map1FBridgeBackGround& _Other) = delete;
	Map1FBridgeBackGround(Map1FBridgeBackGround&& _Other) noexcept = delete;
	Map1FBridgeBackGround& operator=(const Map1FBridgeBackGround& _Other) = delete;
	Map1FBridgeBackGround& operator=(Map1FBridgeBackGround&& _Other) noexcept = delete;
	static Map1FBridgeBackGround* GetInst()
	{
		return Inst_;
	}
	GameEngineRenderer* Renderer_1_;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	static Map1FBridgeBackGround* Inst_;
};

