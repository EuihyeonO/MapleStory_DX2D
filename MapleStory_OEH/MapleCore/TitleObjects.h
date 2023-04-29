#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineSpriteRenderer;
class TitleObjects : public GameEngineActor
{

public:

	TitleObjects();
	~TitleObjects();

	TitleObjects(const TitleObjects& _Other) = delete;
	TitleObjects(TitleObjects&& _Other) noexcept = delete;
	TitleObjects& operator=(const TitleObjects& _Other) = delete;
	TitleObjects& operator=(TitleObjects&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void TimeCounting();

	void Create_LoginBox();
	void Create_ChannelButton();
	void Create_FrameObject();
	void Create_CharSelectButton();
	void Create_CharacterObject();
	void Create_CharCreateObject();
	void EmptySlotAnimation();

	std::shared_ptr<GameEngineSpriteRenderer> Frame;
	std::shared_ptr<GameEngineSpriteRenderer> BackGround;
	std::shared_ptr<GameEngineSpriteRenderer> Logo;

	std::shared_ptr<GameEngineSpriteRenderer> WorldSelectLope;
	std::shared_ptr<GameEngineSpriteRenderer> WorldSelectFixture;

	std::shared_ptr<GameEngineSpriteRenderer> ChScroll;

	//로그인창
	std::shared_ptr<GameEngineSpriteRenderer> LoginBoard;
	std::shared_ptr<GameEngineSpriteRenderer> SignUp;
	std::shared_ptr<GameEngineSpriteRenderer> Login;
	std::shared_ptr<GameEngineSpriteRenderer> HomePage;
	std::shared_ptr<GameEngineSpriteRenderer> Exit;
	std::shared_ptr<GameEngineSpriteRenderer> SaveEmail;
	std::shared_ptr<GameEngineSpriteRenderer> FindEmail;
	std::shared_ptr<GameEngineSpriteRenderer> FindPass;
	std::shared_ptr<GameEngineSpriteRenderer> Check;

	//채널
	std::shared_ptr<GameEngineSpriteRenderer> Demetos;
	std::shared_ptr<GameEngineSpriteRenderer> Bellokan;
	std::shared_ptr<GameEngineSpriteRenderer> Bera;
	std::shared_ptr<GameEngineSpriteRenderer> Broa;
	std::shared_ptr<GameEngineSpriteRenderer> Mardia;
	std::shared_ptr<GameEngineSpriteRenderer> Skania;
	std::shared_ptr<GameEngineSpriteRenderer> Stierce;
	std::shared_ptr<GameEngineSpriteRenderer> Akenia;
	std::shared_ptr<GameEngineSpriteRenderer> Zenis;
	std::shared_ptr<GameEngineSpriteRenderer> Kastia;
	std::shared_ptr<GameEngineSpriteRenderer> Kiny;
	std::shared_ptr<GameEngineSpriteRenderer> Croa;
	std::shared_ptr<GameEngineSpriteRenderer> Yellond;
	std::shared_ptr<GameEngineSpriteRenderer> Plana;
	
	//캐릭터선택창
	std::shared_ptr<GameEngineSpriteRenderer> CharSelectBox;
	std::shared_ptr<GameEngineSpriteRenderer> CharCreate;
	std::shared_ptr<GameEngineSpriteRenderer> CharSelect;
	std::shared_ptr<GameEngineSpriteRenderer> CharDelete;

	//캐릭터 관련 오브젝트
	std::shared_ptr<GameEngineSpriteRenderer> EmptySlot1;
	std::shared_ptr<GameEngineSpriteRenderer> EmptySlot2;
	std::shared_ptr<GameEngineSpriteRenderer> EmptySlot3;

	std::shared_ptr<GameEngineSpriteRenderer> EmptyAnimation1;
	std::shared_ptr<GameEngineSpriteRenderer> EmptyAnimation2;
	std::shared_ptr<GameEngineSpriteRenderer> EmptyAnimation3;
	
	//캐릭터 생성창 오브젝트
	std::shared_ptr<GameEngineSpriteRenderer> CharInfo;
	std::shared_ptr<GameEngineSpriteRenderer> InfoScroll;
	std::shared_ptr<GameEngineSpriteRenderer> Dice;
	std::shared_ptr<GameEngineSpriteRenderer> OkButton;
	std::shared_ptr<GameEngineSpriteRenderer> NoButton;

	//프레임에 달려있는 버튼
	std::shared_ptr<GameEngineSpriteRenderer> ToLogin;
	std::shared_ptr<GameEngineSpriteRenderer> SelectedWorld;
	std::shared_ptr<GameEngineSpriteRenderer> SelectWorldStage;
	std::shared_ptr<GameEngineSpriteRenderer> SelectCharStage;
	std::shared_ptr<GameEngineSpriteRenderer> CreateCharStage;



	float EmptyAniTimeCount = 0.0f;
	int EmptyAniIndex = 0;

	int ScrollIndex = 0;

	float CurTime = 0.0f;
	float PrevTime = 0.0f;
	float TimeCount = 0.0f;
};

