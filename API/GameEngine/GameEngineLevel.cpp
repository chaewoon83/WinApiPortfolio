#include "GameEngineLevel.h"
//delete (*StartActor)�� �ϱ����� (�ҿ����� ���� ������ ���ֱ� ���Ͽ�)
#include "GameEngineActor.h"
#include "GameEngineCollision.h"

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
	std::map<int, std::list<GameEngineActor*>>::iterator GroupStart = AllActor_.begin();
	std::map<int, std::list<GameEngineActor*>>::iterator GroupEnd = AllActor_.end();
	std::list<GameEngineActor*>::iterator StartActor;
	std::list<GameEngineActor*>::iterator EndActor;


	for (; GroupStart != GroupEnd; ++GroupStart)
	{
		std::list<GameEngineActor*>& Group = GroupStart->second;

		//Renderer�� ȣ��ȴ�
		StartActor = Group.begin();
		EndActor = Group.end();

		for (; StartActor != EndActor; ++StartActor)
		{
			if (false == (*StartActor)->IsUpdate())
			{
				continue;
			}
			(*StartActor)->Rendering();
		}
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

