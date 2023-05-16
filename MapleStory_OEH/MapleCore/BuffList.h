#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <functional>
#include <Map>

class GameEngineSpriteRenderer;
class BuffList : public GameEngineActor
{
	friend class Player;

public:
	struct Buff
	{
		std::shared_ptr<GameEngineSpriteRenderer> BuffIcon;
		float LiveTime;
		float MaxLiveTime;

		std::function<void(class Player&)> EndFunction;

	public:
		bool isBuffEnd()
		{
			if (MaxLiveTime <= LiveTime)
			{
				return true;
			}
			else 
			{ 
				return false; 
			}
		}

		void BuffTimer(float _TimeCount)
		{
			LiveTime += _TimeCount;
		}
	};

	size_t GetOnBuffListSize()
	{
		return OnBuffList.size();
	}
public:

	BuffList();
	~BuffList();

	BuffList(const BuffList& _Other) = delete;
	BuffList(BuffList&& _Other) noexcept = delete;
	BuffList& operator=(const BuffList& _Other) = delete;
	BuffList& operator=(BuffList&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:
	void TimeCounting();
	float CurTime = 0.0f;
	float PrevTime = 0.0f;
	float TimeCount = 0.0f;
	
	void Rebuff(const std::string_view& _BuffName);
	void BuffOn(const std::string_view& _BuffName, std::function<void(class Player&)> _EndFunction, float MaxLiveTime);
	bool IsBuffOn(const std::string_view& _BuffName);
	bool IsBuffEnd(const std::string_view& _BuffName);
	void BuffUpdate();

	std::map<std::string, std::shared_ptr<Buff>> OnBuffList;
};

