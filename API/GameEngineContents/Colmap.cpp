#include "Colmap.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngineBase/GameEngineInput.h>


Colmap::Colmap()
	:IsDeugModeOn_(false)
{
}

Colmap::~Colmap() 
{
}

void Colmap::Start()
{
	Map1F_1_Renderer_ = CreateRenderer("EastPalace1F_1_1F_ColMap.bmp");
	//Map1F_1_Renderer_->Off();
	float4 ImagePos = {};
	//렌더러는  0,0 을 기준으로 중앙에 배치된다 ( 그대로 쓰면 이미지 짤림 )
	//이미지, Rect는 0, 0 을 기준으로 오른쪽 아래에 배치된다
	ImagePos.x = (Map1F_1_Renderer_->GetImage()->GetScale().Half().x);
	ImagePos.y = (Map1F_1_Renderer_->GetImage()->GetScale().Half().y + 4128.0f);
	Map1F_1_Renderer_->SetPivot(ImagePos);

	Map1F_2_Renderer_ = CreateRenderer("EastPalace1F_2_1F_ColMap.bmp");
	//Map1F_2_Renderer_->Off();
	ImagePos = {};
	ImagePos.x = (Map1F_2_Renderer_->GetImage()->GetScale().Half().x);
	ImagePos.y = (Map1F_2_Renderer_->GetImage()->GetScale().Half().y);
	Map1F_1_Renderer_->SetPivot(ImagePos);

	GameEngineInput::GetInst()->CreateKey("DebugMode", '8');
}
 
void Colmap::Update()
{
	if (GameEngineInput::GetInst()->IsDown("DebugMode"))
	{
		if (false == IsDeugModeOn_)
		{
			IsDeugModeOn_ = true;
			Map1F_1_Renderer_->On();
			Map1F_2_Renderer_->On();
		}
		else
		{
			IsDeugModeOn_ = false;
			Map1F_1_Renderer_->Off();
			Map1F_2_Renderer_->Off();
		}
	}
}
void Colmap::Render()
{
	//DebugRectRender();

}
