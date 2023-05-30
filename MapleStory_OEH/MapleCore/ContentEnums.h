#pragma once

enum class State
{
	Move = 0,
	Jump,
	Swing,
	Qskill,
	Wskill,
	Eskill,
	Up,
	Down,
};

enum class WeaponType
{
	OneHandWeapon,
	Claw,
};

enum class RenderOrder
{
	BasicMap,
	NPC,
	Player,
	Weapon,
	Monster,
	Skill,
	UI,
	Mouse,
};

enum class CollisionOrder
{
	Range,
	Player,
	Monster,
	Boss,
	Star,
	Weapon,
	UI,
	Mouse,
	RopeAndLadder,
	SkillMoveIcon,
	QuickSlotSkill,
};

enum class MonsterName
{
	GreenSnail,

};

