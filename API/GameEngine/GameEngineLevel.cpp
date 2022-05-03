#include "GameEngineLevel.h"
//delete (*StartActor)�� �ϱ����� (�ҿ����� ���� ������ ���ֱ� ���Ͽ�)
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

	// ü���� ���� �ܰ� 
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
		MsgBoxAssert("�̹� �����ϴ� �̸����� �� ����Ϸ��� �߽��ϴ�.");
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

			// �� �׷찣���� ������ �˴ϴ�
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
				//delete�� �� �� �ִ� ������ Actor���� �ִ�. ��Ͽ����� ����
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

		//Actor �������� Render()�Լ��� ȣ��ȴ�
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

	//���͸� delete�ϱ����� ���� �ȿ��ִ� collision �����ϱ�
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
				//delete�� �� �� �ִ� ������ Actor���� �ִ�. ��Ͽ����� ����
				StartRender = Group.erase(StartRender);
			}
		}
	}

	//���͸� delete�ϱ����� ���� �ȿ��ִ� collision �����ϱ�
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
				//delete�� �� �� �ִ� ������ Actor���� �ִ�. ��Ͽ����� ����
				StartCollision = Group.erase(StartCollision);
			}
		}
	}
	//���ͻ���
	{

		std::map<int, std::list<GameEngineActor*>>::iterator GroupStart = AllActor_.begin();
		std::map<int, std::list<GameEngineActor*>>::iterator GroupEnd = AllActor_.end();
		std::list<GameEngineActor*>::iterator StartActor;
		std::list<GameEngineActor*>::iterator EndActor;


		for (; GroupStart != GroupEnd; ++GroupStart)
		{
			std::list<GameEngineActor*>& Group = GroupStart->second;

			//IsDeath�� Ȯ���� true�� delete�Ѵ�
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
				//������ �ȵǾ��ٸ� collision�̳� rendererȮ��
				(*StartActor)->Release();
				// ���� List.erase(iteratorValue)�� �ϰ� �ȴٸ� �ڵ������� ++StartActor���� �������ֱ⶧����
				// StartActor = Group.erase(StartActor); �϶� ++StartActor�� �ϸ�ȵȴ�
				// ���� �ۿ� ���� ++StartActor�� ���ش�
				++StartActor;
			}
		}
	}
}

void GameEngineLevel::AddCollision(const std::string& _GroupName,
	GameEngineCollision* _Collision)
{
	_Collision->CollisionName_ = _GroupName;
	//find �� create����
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

	// �ݸ����� ������ �����ϰ� �����Ƿ�
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


	// ������ ����
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
					// ���⼭ �Űܰ���.
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