#include "UIHeart.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include "PlayerLink.h"

UIHeart::UIHeart() 
{
}

UIHeart::~UIHeart() 
{
}


//UIHeart
//1. coordinate(644, 96) size(28 28)
//1. 658, 110
//2. + 4, +size
//2~10
void UIHeart::Start()
{
	float4 Padding = {32, 0};
	SetPosition({ 658, 110 });
	AllHearts.reserve(20);
	for (int i = 0; i < 10; i++)
	{
		AllHearts.push_back(CreateRenderer());
		AllHearts[i]->CreateAnimation("UIFullHeart.bmp", "FullHeart", 0, 0, 1.0f, false);
		AllHearts[i]->CreateAnimation("UIHalfHeart.bmp", "HalfHeart", 0, 0, 1.0f, false);
		AllHearts[i]->CreateAnimation("UIEmptyHeart.bmp", "EmptyHeart", 0, 0, 1.0f, false);
		AllHearts[i]->SetPivot(Padding * static_cast<float>(i));
		AllHearts[i]->ChangeAnimation("FullHeart");
	}

	std::vector<GameEngineRenderer*>::iterator Iter = AllHearts.begin();
	for (; Iter != AllHearts.end(); ++Iter)
	{
		(*Iter)->CameraEffectOff();
	}

}
 
void UIHeart::Update()
{
	int Hearts = PlayerLink::GetPlayerHp() / 2;
	int Hearts2 = PlayerLink::GetPlayerHp() % 2;
	if (20 == PlayerLink::GetPlayerHp())
	{
		for (size_t i = 0; i < 10; i++)
		{
			AllHearts[i]->ChangeAnimation("FullHeart");
		}

	}

	if (19 == PlayerLink::GetPlayerHp())
	{
		for (size_t i = 0; i < 10; i++)
		{
			AllHearts[i]->ChangeAnimation("FullHeart");
		}

		for (size_t i = 9; i < 10; i++)
		{
			AllHearts[i]->ChangeAnimation("HalfHeart");
		}

	}

	if (18 == PlayerLink::GetPlayerHp())
	{
		for (size_t i = 0; i < 9; i++)
		{
			AllHearts[i]->ChangeAnimation("FullHeart");
		}

		for (size_t i = 9; i < 10; i++)
		{
			AllHearts[i]->ChangeAnimation("EmptyHeart");
		}

	}

	if (17 >= PlayerLink::GetPlayerHp())
	{
		if (Hearts2 == 0)
		{
			for (int i = 0; i < Hearts; i++)
			{
				AllHearts[i]->ChangeAnimation("FullHeart");
			}

			for (int i = Hearts; i < 10; i++)
			{
				AllHearts[i]->ChangeAnimation("EmptyHeart");
			}
		}
		else
		{
			for (int i = 0; i < Hearts - Hearts2 + 1; i++)
			{
				AllHearts[i]->ChangeAnimation("FullHeart");
			}

			for (int i = Hearts - Hearts2 + 1; i < Hearts - Hearts2 + 2; i++)
			{
				AllHearts[i]->ChangeAnimation("HalfHeart");
			}

			for (int i = Hearts - Hearts2 + 2; i < 10; i++)
			{
				AllHearts[i]->ChangeAnimation("EmptyHeart");
			}
		}
	}
}
void UIHeart::Render()
{
	//DebugRectRender();

}
