#include "GameEngineLevel.h"
//delete (*StartActor)를 하기위해 (불완전한 형식 오류를 없애기 위하여)
#include "GameEngineActor.h"
#include "GameEngineCollision.h"
#include "GameEngineRenderer.h"
#include <GameEngineBase/GameEngineDebug.h>

bool GameEngineLevel::IsDebug = false;

GameEngineLevel::GameEngineLevel()
	: CameraPos_(float4::ZERO)
{
}



GameEngineLevel::~GameEngineLevel()
{
	std::map<int, std::list<GameEngineActor*>>::iterator GroupStart = AllActor_.begin();
	std::map<int, std::list<GameEngineActor*>>::iterator GroupEnd = AllActor_.end();
	std::list<GameEngineActor*>::iterator StartActor;
	std::list<GameEngineActor*>::iterator EndActor;

	for (; GroupStart != GroupEnd; ++GroupStart)
	{
		std::list<GameEngineActor*>& Group = GroupStart->second;

		StartActor = Group.begin();
		EndActor = Group.end();

		for (; StartActor != EndActor; ++StartActor)
		{
			if ((*StartActor) == nullptr)
			{
				continue;
			}
			delete (*StartActor);
			(*StartActor) = nullptr;
		}
	}
}

void GameEngineLevel::ActorUpdate()
{
	std::map<int, std::list<GameEngineActor*>>::iterator GroupStart = AllActor_.begin();
	std::map<int, std::list<GameEngineActor*>>::iterator GroupEnd = AllActor_.end();
	std::list<GameEngineActor*>::iterator StartActor;
	std::list<GameEngineActor*>::iterator EndActor;


	for (; GroupStart != GroupEnd; ++GroupStart)
	{
		std::list<GameEngineActor*>& Group = GroupStart->second;

		StartActor = Group.begin();
		EndActor = Group.end();

		for (; StartActor != EndActor; ++StartActor)
		{
			(*StartActor)->ReleaseUpdate();
			(*StartActor)->AddAccTime(GameEngineTime::GetDeltaTime());
			if (false == (*StartActor)->IsUpdate())
			{
				continue;
			}
			(*StartActor)->Update();
		}
	}

	// 체인지 오더 단계 
	for (size_t i = 0; i < ChangeOrderList.size(); i++)
	{
		ChangeOrderItem& Data = ChangeOrderList[i];
		AllActor_[Data.TargetObject->GetOrder()].remove(Data.TargetObject);
		Data.TargetObject->GameEngineUpdateObject::SetOrder(Data.ChangeOrder);
		AllActor_[Data.TargetObject->GetOrder()].push_back(Data.TargetObject);
	}

	ChangeOrderList.clear();
}

void GameEngineLevel::ActorLevelChangeStart(GameEngineLevel* _PrevLevel) {

	{
		std::map<int, std::list<GameEngineActor*>>::iterator GroupStart;
		std::map<int, std::list<GameEngineActor*>>::iterator GroupEnd;

		std::list<GameEngineActor*>::iterator StartActor;
		std::list<GameEngineActor*>::iterator EndActor;

		GroupStart = AllActor_.begin();
		GroupEnd = AllActor_.end();

		for (; GroupStart != GroupEnd; ++GroupStart)
		{
			std::list<GameEngineActor*>& Group = GroupStart->second;

			StartActor = Group.begin();
			EndActor = Group.end();


			for (; StartActor != EndActor; ++StartActor)
			{
				if (false == (*StartActor)->IsUpdate())
				{
					continue;
				}

				(*StartActor)->LevelChangeStart(_PrevLevel);
			}
		}
	}
}

GameEngineActor* GameEngineLevel::FindActor(const std::string& _Name)
{
	std::map<std::string, GameEngineActor*>::iterator FindIter = RegistActor_.find(_Name);

	if (RegistActor_.end() == FindIter)
	{
		return nullptr;
	}

	return FindIter->second;
}

void GameEngineLevel::RegistActor(const std::string& _Name, GameEngineActor* _Actor)
{
	if (RegistActor_.end() != RegistActor_.find(_Name))
	{
		MsgBoxAssert("이미 존재하는 이름으로 또 등록하려고 했습니다.");
	}

	RegistActor_.insert(std::map<std::string, GameEngineActor*>::value_type(_Name, _Actor));
}

void GameEngineLevel::ActorLevelChangeEnd(GameEngineLevel* _NextLevel) {
	{
		std::map<int, std::list<GameEngineActor*>>::iterator GroupStart;
		std::map<int, std::list<GameEngineActor*>>::iterator GroupEnd;

		std::list<GameEngineActor*>::iterator StartActor;
		std::list<GameEngineActor*>::iterator EndActor;

		GroupStart = AllActor_.begin();
		GroupEnd = AllActor_.end();

		for (; GroupStart != GroupEnd; ++GroupStart)
		{
			std::list<GameEngineActor*>& Group = GroupStart->second;

			StartActor = Group.begin();
			EndActor = Group.end();


			for (; StartActor != EndActor; ++StartActor)
			{
				if (false == (*StartActor)->IsUpdate())
				{
					continue;
				}

				(*StartActor)->LevelChangeEnd(_NextLevel);
			}
		}
	}
}

bool SortY(GameEngineRenderer* _Left, GameEngineRenderer* _Right)
{
	return _Left->GetSortingPivot().y < _Right->GetSortingPivot().y;
}



void GameEngineLevel::ActorRender()
{

	{
		std::map<int, std::list<GameEngineRenderer*>>::iterator GroupStart = AllRenderer_.begin();
		std::map<int, std::list<GameEngineRenderer*>>::iterator GroupEnd = AllRenderer_.end();

		std::list<GameEngineRenderer*>::iterator StartRenderer;
		std::list<GameEngineRenderer*>::iterator EndRenderer;

		for (; GroupStart != GroupEnd; ++GroupStart)
		{
			std::list<GameEngineRenderer*>& Group = GroupStart->second;

			// 그 그룹간에만 소팅이 됩니다
			if (IsYSort_.end() != IsYSort_.find(GroupStart->first))
			{
				Group.sort(SortY);
			}
			StartRenderer = Group.begin();
			EndRenderer = Group.end();
			for (; StartRenderer != EndRenderer; ++StartRenderer)
			{
				if (false == (*StartRenderer)->IsUpdate())
				{
					continue;
				}
				//delete를 할 수 있는 권한은 Actor에게 있다. 목록에서만 제외
				(*StartRenderer)->Render();
			}
		}
	}

	std::map<int, std::list<GameEngineActor*>>::iterator GroupStart = AllActor_.begin();
	std::map<int, std::list<GameEngineActor*>>::iterator GroupEnd = AllActor_.end();
	std::list<GameEngineActor*>::iterator StartActor;
	std::list<GameEngineActor*>::iterator EndActor;


	for (; GroupStart != GroupEnd; ++GroupStart)
	{
		std::list<GameEngineActor*>& Group = GroupStart->second;

		//Actor 개개인의 Render()함수가 호출된다
		StartActor = Group.begin();
		EndActor = Group.end();

		for (; StartActor != EndActor; ++StartActor)
		{
			(*StartActor)->Render();
		}
	}
}

void GameEngineLevel::CollisionDebugRender()
{
	if (false == IsDebug)
	{
		return;
	}

	std::map<std::string, std::list<GameEngineCollision*>>::iterator GroupStart = AllCollision_.begin();
	std::map<std::string, std::list<GameEngineCollision*>>::iterator GroupEnd = AllCollision_.end();

	std::list<GameEngineCollision*>::iterator StartCollision;
	std::list<GameEngineCollision*>::iterator EndCollision;

	for (; GroupStart != GroupEnd; ++GroupStart)
	{
		std::list<GameEngineCollision*>& Group = GroupStart->second;
		StartCollision = Group.begin();
		EndCollision = Group.end();
		for (; StartCollision != EndCollision; ++StartCollision)
		{
			if (false == (*StartCollision)->IsUpdate())
			{
				continue;
			}
			(*StartCollision)->DebugRender();
		}
	}
}

void GameEngineLevel::ActorRelease()
{

	//액터를 delete하기전에 레벨 안에있는 collision 삭제하기
	{
		std::map<int, std::list<GameEngineRenderer*>>::iterator GroupStart = AllRenderer_.begin();
		std::map<int, std::list<GameEngineRenderer*>>::iterator GroupEnd = AllRenderer_.end();

		std::list<GameEngineRenderer*>::iterator StartRender;
		std::list<GameEngineRenderer*>::iterator EndRender;

		for (; GroupStart != GroupEnd; ++GroupStart)
		{
			std::list<GameEngineRenderer*>& Group = GroupStart->second;
			StartRender = Group.begin();
			EndRender = Group.end();
			for (; StartRender != EndRender;)
			{
				if (false == (*StartRender)->IsDeath())
				{
					++StartRender;
					continue;
				}
				//delete를 할 수 있는 권한은 Actor에게 있다. 목록에서만 제외
				StartRender = Group.erase(StartRender);
			}
		}
	}

	//액터를 delete하기전에 레벨 안에있는 collision 삭제하기
	{
		std::map<std::string, std::list<GameEngineCollision*>>::iterator GroupStart = AllCollision_.begin();
		std::map<std::string, std::list<GameEngineCollision*>>::iterator GroupEnd = AllCollision_.end();

		std::list<GameEngineCollision*>::iterator StartCollision;
		std::list<GameEngineCollision*>::iterator EndCollision;

		for (; GroupStart != GroupEnd; ++GroupStart)
		{
			std::list<GameEngineCollision*>& Group = GroupStart->second;
			StartCollision = Group.begin();
			EndCollision = Group.end();
			for (; StartCollision != EndCollision;)
			{
				if (false == (*StartCollision)->IsDeath())
				{
					++StartCollision;
					continue;
				}
				//delete를 할 수 있는 권한은 Actor에게 있다. 목록에서만 제외
				StartCollision = Group.erase(StartCollision);
			}
		}
	}
	//액터삭제
	{

		std::map<int, std::list<GameEngineActor*>>::iterator GroupStart = AllActor_.begin();
		std::map<int, std::list<GameEngineActor*>>::iterator GroupEnd = AllActor_.end();
		std::list<GameEngineActor*>::iterator StartActor;
		std::list<GameEngineActor*>::iterator EndActor;


		for (; GroupStart != GroupEnd; ++GroupStart)
		{
			std::list<GameEngineActor*>& Group = GroupStart->second;

			//IsDeath를 확인후 true면 delete한다
			StartActor = Group.begin();
			EndActor = Group.end();

			for (; StartActor != EndActor;)
			{
				if (true == (*StartActor)->IsDeath())
				{
					delete (*StartActor);
					StartActor = Group.erase(StartActor);
					continue;
				}
				//삭제가 안되었다면 collision이나 renderer확인
				(*StartActor)->Release();
				// 만약 List.erase(iteratorValue)를 하게 된다면 자동적으로 ++StartActor값을 리턴해주기때문에
				// StartActor = Group.erase(StartActor); 일땐 ++StartActor를 하면안된다
				// 따라서 밖에 따로 ++StartActor를 해준다
				++StartActor;
			}
		}
	}
}

void GameEngineLevel::AddCollision(const std::string& _GroupName,
	GameEngineCollision* _Collision)
{
	_Collision->CollisionName_ = _GroupName;
	//find 후 create까지
	AllCollision_[_GroupName].push_back(_Collision);
}

void GameEngineLevel::ChangeUpdateOrder(GameEngineActor* _Actor, int _NewOreder)
{
	if (_Actor->GetOrder() == _NewOreder)
	{
		return;
	}
	ChangeOrderList.push_back({ _Actor ,_NewOreder });
}


void GameEngineLevel::AddRenderer(GameEngineRenderer* _Renderer)
{
	AllRenderer_[_Renderer->GetOrder()].push_back(_Renderer);
}

void GameEngineLevel::ChangeRenderOrder(GameEngineRenderer* _Renderer, int _NewOrder)
{
	if (_Renderer->GetOrder() == _NewOrder)
	{
		return;
	}

	AllRenderer_[_Renderer->GetOrder()].remove(_Renderer);
	_Renderer->GameEngineUpdateObject::SetOrder(_NewOrder);
	AllRenderer_[_Renderer->GetOrder()].push_back(_Renderer);
}

void GameEngineLevel::ObjectLevelMoveCheck(GameEngineLevel* _NextLevel)
{
	{
		std::map<int, std::list<GameEngineRenderer*>>::iterator GroupStart = AllRenderer_.begin();
		std::map<int, std::list<GameEngineRenderer*>>::iterator GroupEnd = AllRenderer_.end();

		std::list<GameEngineRenderer*>::iterator StartRenderer;
		std::list<GameEngineRenderer*>::iterator EndRenderer;


		for (; GroupStart != GroupEnd; ++GroupStart)
		{
			std::list<GameEngineRenderer*>& Group = GroupStart->second;
			StartRenderer = Group.begin();
			EndRenderer = Group.end();
			for (; StartRenderer != EndRenderer; )
			{
				if (false == (*StartRenderer)->GetActor()->NextLevelOn_)
				{
					++StartRenderer;
					continue;
				}

				GameEngineRenderer* Object = *StartRenderer;
				_NextLevel->AllRenderer_[Object->GetOrder()].push_back(Object);


				StartRenderer = Group.erase(StartRenderer);
			}
		}
	}

	// 콜리전은 레벨도 관리하고 있으므로
	{
		std::map<std::string, std::list<GameEngineCollision*>>::iterator GroupStart = AllCollision_.begin();
		std::map<std::string, std::list<GameEngineCollision*>>::iterator GroupEnd = AllCollision_.end();

		std::list<GameEngineCollision*>::iterator StartCollision;
		std::list<GameEngineCollision*>::iterator EndCollision;


		for (; GroupStart != GroupEnd; ++GroupStart)
		{
			std::list<GameEngineCollision*>& Group = GroupStart->second;
			StartCollision = Group.begin();
			EndCollision = Group.end();
			for (; StartCollision != EndCollision; )
			{
				if (false == (*StartCollision)->GetActor()->NextLevelOn_)
				{
					++StartCollision;
					continue;
				}

				GameEngineCollision* Object = *StartCollision;
				_NextLevel->AllCollision_[Object->CollisionName_].push_back(Object);

				StartCollision = Group.erase(StartCollision);
			}
		}

	}


	// 액터의 삭제
	{
		std::map<int, std::list<GameEngineActor*>>::iterator GroupStart;
		std::map<int, std::list<GameEngineActor*>>::iterator GroupEnd;

		std::list<GameEngineActor*>::iterator StartActor;
		std::list<GameEngineActor*>::iterator EndActor;

		GroupStart = AllActor_.begin();
		GroupEnd = AllActor_.end();

		for (; GroupStart != GroupEnd; ++GroupStart)
		{
			std::list<GameEngineActor*>& Group = GroupStart->second;

			StartActor = Group.begin();
			EndActor = Group.end();
			for (; StartActor != EndActor; )
			{
				if (true == (*StartActor)->NextLevelOn_)
				{
					// 여기서 옮겨간다.
					GameEngineActor* Object = *StartActor;
					Object->SetLevel(_NextLevel);
					Object->NextLevelOff();
					_NextLevel->AllActor_[Object->GetOrder()].push_back(Object);

					StartActor = Group.erase(StartActor);
					continue;
				}

				++StartActor;
			}
		}
	}
}