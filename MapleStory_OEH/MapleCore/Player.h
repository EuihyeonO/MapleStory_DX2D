#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineTexture.h>

class GameEngineSpriteRenderer;
class Player : public GameEngineActor
{
	friend class BuffList;
public:
 
	static Player* GetCurPlayer()
	{
		return CurPlayer;
	}

	void SetColMap(const std::string_view& _MapName)
	{		
		ColMap = GameEngineTexture::Find(_MapName);
	}

	const std::string_view& GetMoveType() const
	{
		return MoveType;
	}

	const int GetAniIndex() const
	{
		return AniIndex;
	}

	void SetMoveType(const std::string_view& _MoveType);

	void SetMovable(bool _Bool)
	{
		isMovable = _Bool;
	}

	const std::string_view& GetLeftRightDir() const
	{
		return LeftRightDir;
	}

	const float4 GetWeaponPos() const;

	void SetLeft();
	void SetRight();

	Player();
	~Player();

	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	
	static Player* CurPlayer;
	std::shared_ptr<GameEngineTexture> ColMap;

	void TimeCounting();
	void CameraUpdate();

	float CurTime = 0.0f;
	float PrevTime = 0.0f;
	float TimeCount = 0.0f;
	
	float4 PlayerPos = {0,0};

	//키 관련
	int GetStateByKeyInput() const;
	void CreateAllKey();

	//움직임관련

	void GravityUpdate(float _DeltaTime);
	void ActingUpdate(float _DeltaTime);

	void Idle();
	void Move(float _DeltaTime);
	void Swing();
	void Jump(float _DeltaTime);
	void JumpUpdate(float _DeltaTime);

	bool isGround = false;
	bool isKeyJump = false;
	bool isSwing = false;

	bool isMovable = true;

	float Gravity = 200.0f;
	float GravityAccel = 1000.0f;

	float JumpPower = 585.0f;
	float JumpXMove = 0.0f;

	float BasicMoveSpeed = 100.0f;
	float MoveSpeed = 100.0f;

	//스킬관련
	
	void LuckySeven();
	void Haste();

	float Range = 100.0f;

	std::shared_ptr<class BuffList> MyBuffList;

	std::function<void(Player&)> QSkill = nullptr;
	std::function<void(Player&)> WSkill = nullptr;

	std::shared_ptr<class GameEngineCollision> RangeCheck = nullptr;
	//std::list<std::function<bool(Player&)>> BuffList;

	//std::function<bool(Player&)> DelSkill = nullptr;
	//std::function<bool(Player&)> InsertSkill = nullptr;
	//std::function<bool(Player&)> PageDownSkill = nullptr;
	//std::function<bool(Player&)> PageUpSkill = nullptr;
	//std::function<bool(Player&)> ScrollSkill = nullptr;
	//std::function<bool(Player&)> HomeSkill = nullptr;
	//std::function<bool(Player&)> EndSkill = nullptr;
	//std::function<bool(Player&)> ScreenSkill = nullptr;


	//텍스쳐 관련 
	void SetAllTexturePosVector();
	void SetBodyTexturePosVector();
	void SetCoatTexturePosVector();
	void SetPantsTexturePosVector();
	void SetWeaponTexturePosVector();
	void SetHairAndFaceTexturePosVector();
	void TextureUpdate();
	void TextureAnimationUpdate();
	void TexturePosUpdate();

	int WeaponType = 0;

	float AnimationCount = 0.0f;
	int AniIndex = 0;

	std::string MoveType = "";

	std::string LeftRightDir = ""; //좌우 방향
	std::string FrontBackDir = "Front"; //앞뒤 방향 ( ex 사다리를 탔을 땐 뒤 )

	std::string HairName = "Toven";
	std::string HairStatus = "Hair"; //모자를 썼는지 안썼는지

	std::string FaceName = "Face1";
	std::string Expression = "Default";

	std::string SkinType = "Basic";

	std::string CoatName = "";
	std::string PantsName = "";

	std::string WeaponName = "";

	std::map <std::string, std::vector<float>> AniFrameList;

	std::map<std::string, std::vector<float4>> BodyOriginPos;
	std::map<std::string, std::vector<float4>> BodyNavelPos;
	std::map<std::string, std::vector<float4>> BodyNeckPos;
	std::map<std::string, std::vector<float4>> ArmOriginPos;
	std::map<std::string, std::vector<float4>> ArmToNavelPos;
	std::map<std::string, std::vector<float4>> ArmHandPos;

	std::map<std::string, float4> HeadOriginPos;
	std::map<std::string, float4> HeadToNeckPos;
	std::map<std::string, float4> HeadBrowPos;

	std::map<std::string, std::map<std::string, float4>> HairOriginPos;
	std::map<std::string, std::map<std::string, float4>> HairToBrowPos;

	std::map<std::string, std::map<std::string, float4>> FaceOriginPos;
	std::map<std::string, std::map<std::string, float4>> FaceToBrowPos;

	std::map<std::string, std::map<std::string, std::vector<float4>>> CoatOriginPos;
	std::map<std::string, std::map<std::string, std::vector<float4>>> CoatToNavelPos;

	std::map<std::string, std::map<std::string, std::vector<float4>>> CoatArmOriginPos;
	std::map<std::string, std::map<std::string, std::vector<float4>>> CoatArmToNavelPos;

	std::map<std::string, std::map<std::string, std::vector<float4>>> PantsOriginPos;
	std::map<std::string, std::map<std::string, std::vector<float4>>> PantsToNavelPos;

	std::map<std::string, std::map<std::string, std::vector<float4>>> WeaponOriginPos;
	std::map<std::string, std::map<std::string, std::vector<float4>>> WeaponToHandPos;
	std::map<std::string, std::map<std::string, std::vector<float4>>> WeaponToNavelPos;

	std::shared_ptr<GameEngineSpriteRenderer> Body;
	std::shared_ptr<GameEngineSpriteRenderer> Arm;
	std::shared_ptr<GameEngineSpriteRenderer> Head;
	std::shared_ptr<GameEngineSpriteRenderer> Coat;
	std::shared_ptr<GameEngineSpriteRenderer> CoatArm;
	std::shared_ptr<GameEngineSpriteRenderer> Pants;
	std::shared_ptr<GameEngineSpriteRenderer> Weapon;
	std::shared_ptr<GameEngineSpriteRenderer> Hair;
	std::shared_ptr<GameEngineSpriteRenderer> Face;

};

