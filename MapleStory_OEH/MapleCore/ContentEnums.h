#pragma once

enum class State
{
	Move = 0,
	Jump,
	Swing,
	ShiftSkill,
	InsSkill,
	HomeSkill,
	PgUpSkill,
	CtrlSkill,
	DelSkill,
	EndSkill,
	PgDnSkill,
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
	PlayerPoint,
	Monster,
	Boss,
	Star,
	Weapon,
	UI,
	Mouse,
	RopeAndLadder,
	SkillMoveIcon,
	QuickSlotSkill,
	DropItem,
	foothold,
	Channel,
};

enum class MonsterName
{
	GreenSnail,

};

enum class ItemType
{
	Equip,
	Use,
	Etc,
	Setup,
	Cash,
};

enum class EquipType
{
	Coat,
	Pants,
	Shoes,
	Weapon,
	Cap,
};
