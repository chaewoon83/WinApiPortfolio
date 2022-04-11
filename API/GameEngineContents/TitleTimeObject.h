#pragma once
#include "TitleBackGround.h"
#include "TitleLogo.h"
#include "TitleTriangle.h"

// Ό³Έν :
class TitleTimeObject : public GameEngineActor
{
public:
	static float TimeLine_;



public:
	// constrcuter destructer
	TitleTimeObject();
	~TitleTimeObject();

	// delete Function
	TitleTimeObject(const TitleTimeObject& _Other) = delete;
	TitleTimeObject(TitleTimeObject&& _Other) noexcept = delete;
	TitleTimeObject& operator=(const TitleTimeObject& _Other) = delete;
	TitleTimeObject& operator=(TitleTimeObject&& _Other) noexcept = delete;


protected:	
	void Start() override;
	void Update() override;
	void Render() override;

private:

};

