#include "PrecompileHeader.h"
#include "BuffList.h"
#include "Player.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <ctime>

BuffList::BuffList()
{
}

BuffList::~BuffList()
{
}

void BuffList::Start()
{
	TimeCounting();
}

void BuffList::Update(float _DeltaTime)
{
	TimeCounting();

	if(OnBuffList.size() != 0)
	{
		BuffUpdate();
	}
}

void BuffList::Render(float _DeltaTime) 
{
}

void BuffList::BuffOn(const std::string_view& _BuffName, std::function<void(Player&)> _EndFunction, float MaxLiveTime)
{
	if (IsBuffOn(_BuffName) == true)
	{
		return;
	}

	std::shared_ptr<Buff> NewBuff = std::make_shared<Buff>();
	NewBuff->BuffIcon = CreateComponent<GameEngineSpriteRenderer>();


	std::string BuffName = GameEngineString::ToUpper(_BuffName.data());
	NewBuff->BuffIcon->SetScaleToTexture(BuffName + "icon.png");

	NewBuff->LiveTime = 0.0f;
	NewBuff->MaxLiveTime = MaxLiveTime;

	NewBuff->EndFunction = _EndFunction;

	OnBuffList[BuffName] = NewBuff;
}

bool BuffList::IsBuffOn(const std::string_view& _BuffName)
{
	if (OnBuffList.size() == 0)
	{
		return false;
	}

	std::string BuffName = GameEngineString::ToUpper(_BuffName.data());

	std::map<std::string, std::shared_ptr<Buff>>::iterator Start = OnBuffList.begin();
	std::map<std::string, std::shared_ptr<Buff>>::iterator End = OnBuffList.end();

	for (; Start != End; Start++)
	{
		if (Start->first == BuffName)
		{
			return true;
		}
	}

	return false;
}

bool BuffList::IsBuffEnd(const std::string_view& _BuffName)
{

	std::string BuffName = GameEngineString::ToUpper(_BuffName.data());

	if (OnBuffList[BuffName] == nullptr)
	{
		MsgAssert("Null인 Buff를 참조하려고 했습니다. (호출 함수 BuffList::IsBuffEnd) ");
	}

	return OnBuffList[BuffName]->isBuffEnd() == true;
}

void BuffList::BuffUpdate()
{
	if (OnBuffList.size() == 0)
	{
		return;
	}

	float4 CameraPos = GetLevel()->GetMainCamera()->GetTransform()->GetWorldPosition();
	float4 HalfScreenSize = GameEngineWindow::GetScreenSize().half();
	int Count = 0;

	std::map<std::string, std::shared_ptr<Buff>>::iterator Start = OnBuffList.begin();
	std::map<std::string, std::shared_ptr<Buff>>::iterator End = OnBuffList.end();

	for (; Start != End;)
	{
		Start->second->BuffTimer(TimeCount);

		//끝난 버프 제거
		if (Start->second->isBuffEnd() == true)
		{
			if(Start->second->EndFunction != nullptr)
			{
				Start->second->EndFunction(*Player::GetCurPlayer());
			}

			Start->second->BuffIcon->Death();
			Start = OnBuffList.erase(Start);
			continue;
		}	

		//위치 정렬
		GameEngineTransform* BuffIconTransForm = Start->second->BuffIcon->GetTransform();

		BuffIconTransForm->SetLocalPosition({ CameraPos.x + HalfScreenSize.x - 16, CameraPos.y + HalfScreenSize.y - 16 });
		BuffIconTransForm->AddLocalPosition({ static_cast<float>(Count * (-32)), 0 });

		Start++;
		Count++;
	}
}

void BuffList::Rebuff(const std::string_view& _BuffName)
{
	std::string BuffUpperName = GameEngineString::ToUpper(_BuffName);
	
	if (IsBuffOn(BuffUpperName) == false)
	{
		return;
	}

	OnBuffList[BuffUpperName]->LiveTime = 0.0f;
}

void BuffList::TimeCounting()
{
	CurTime = static_cast<float>(clock());
	TimeCount = (CurTime - PrevTime) / 1000.0f;
	PrevTime = CurTime;
}