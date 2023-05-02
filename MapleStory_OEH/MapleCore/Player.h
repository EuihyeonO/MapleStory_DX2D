#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineSpriteRenderer;
class Player : public GameEngineActor
{

public:

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

	void TimeCounting();
	void AnimationUpdate();
	void FashionTextureUpdate();
	void FashionPosUpdate();

	float AnimationCount = 0.0f;
	int AniIndex = 0;

	float CurTime = 0.0f;
	float PrevTime = 0.0f;
	float TimeCount = 0.0f;

	GameEngineTransform PlayerTransForm;
	float4 PlayerPos = {0,0};

	std::string MoveType = "";
	std::string SkinType = "Basic";

	std::string LeftRightDir = ""; //�¿� ����
	std::string FrontBackDir = "Front"; //�յ� ���� ( ex ��ٸ��� ���� �� �� )

	std::string HairName = "Toven";
	std::string HairStatus = "Hair"; //���ڸ� ����� �Ƚ����

	std::string FaceName = "Face1";
	std::string Expression = "Default";

	std::map <std::string, float> AniFrameList;

	std::map<std::string, std::vector<std::pair<float4, float4>>> ArmScaleAndPosList;
	std::map<std::string, std::vector<std::pair<float4, float4>>> BodyScaleAndPosList;
	std::map<std::string, std::vector<std::pair<float4, float4>>> HeadScaleAndPosList;
	
	std::map<std::string, std::map<std::string, std::map<std::string, std::pair<float4, float4>>>> HairScaleAndPosList;
	std::map<std::string, std::map<std::string, std::pair<float4, float4>>> FaceScaleAndPosList;
	

	std::shared_ptr<GameEngineSpriteRenderer> Body;
	std::shared_ptr<GameEngineSpriteRenderer> Arm;
	std::shared_ptr<GameEngineSpriteRenderer> Head;

	std::shared_ptr<GameEngineSpriteRenderer> Hair;
	std::shared_ptr<GameEngineSpriteRenderer> Face;

	std::shared_ptr<GameEngineSpriteRenderer> TopClothe;
};

