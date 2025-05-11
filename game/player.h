#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "common_def.h"
#include "character.h"

constexpr LEVAL BASELEVALGAP = 10;

class Player {
public:
	Player(POINT t_position, int t_life, int t_attack);
	virtual ~Player(){}

	POINT GetPosition() const;

	void SetAttack(const ATTACK& newAttack);
	ATTACK GetAttack(void) const;

	void ProcessEvent(const ExMessage& msg);//����ƶ�����
	void Move();//�ƶ�

	void Hurt(const ATTACK& monsterAttack);//����
	void SetLife(const LIFE& newlife);//�ı�����
	bool CheckAlive() const;
	//true->alive;
	//false->not alive

	void AddExperience(const LEVAL& add);
	void CheckLeval();
	void SetExperience(LEVAL newExperience);
	void LevalUp(void);
	void SetLeval(LEVAL newLaval);
	double GetLevalPercent(void) const;
	LEVAL GetLeval(void) const;
	//�ȼ�����
	void Drow() const;

private:
	POINT position;
	SPEED speed = 5;
	LIFE life;
	ATTACK attack;
	LEVAL leval = 0;
	LEVAL experience = 0;
	bool is_move_up = false,
		is_move_left = false,
		is_move_down = false,
		is_move_right = false;
};

#endif // !_PLAYER_H_
