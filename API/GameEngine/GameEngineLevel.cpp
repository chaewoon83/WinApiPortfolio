#include "GameEngineLevel.h"
//delete (*StartActor)�� �ϱ����� (�ҿ����� ���� ������ ���ֱ� ���Ͽ�)
#include "GameEngineActor.h"
#include "GameEngineCollision.h"
#include "GameEngineRenderer.h"


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
			if (false == (*StartActor)->IsUpdate())
			{
				continue;
			}
			(*StartActor)->Update();
		}
	}
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
	//find �� create����
	AllCollision_[_GroupName].push_back(_Collision);
}


void GameEngineLevel::AddRenderer(GameEngineRenderer* _Renderer)
{
	AllRenderer_[_Renderer->GetOrder()].push_back(_Renderer);
}

void GameEngineLevel::ChangeRenderOrder(GameEngineRenderer* _Renderer, int _NewOrder)
{
	AllRenderer_[_Renderer->GetOrder()].remove(_Renderer);
	_Renderer->GameEngineUpdateObject::SetOrder(_NewOrder);
	AllRenderer_[_Renderer->GetOrder()].push_back(_Renderer);
}
