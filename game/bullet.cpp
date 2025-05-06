#include "bullet.h"

const int fullAngle = 360;

Bullet::Bullet() {}

POINT Bullet::GetPosition(void) const { return position; }
void Bullet::SetPosition(POINT newPosition) { position = newPosition; }

DISTANCE Bullet::GetRepell(void) const { return repell; }//���˾���
_SIZE Bullet::GetRedius(void) const { return redius; }//�ӵ��뾶
DISTANCE Bullet::GetOrbitalRedius() const { return orbitalRedius; }//���й���뾶
ATTACK Bullet::GatAttack(void) const { return attack; }

void Bullet::Draw() const { circle(position.x, position.y, redius); }
//�����ӵ�λ��