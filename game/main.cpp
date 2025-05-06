#include "common_def.h"
#include "character.h"
#include "collision.h"
#include "bulletlist.h"
#include "exballlist.h"
#include "m_testlist.h"

int main() {

	InitAll();

	Player player = Player({ WIDTH / 2, HIGH / 2 }, 10, 5);
	M_testList m_testList = M_testList();
	BulletList bulletList = BulletList();
	ExballList exballList = ExballList();
	ExMessage msg;
	BeginBatchDraw();

	while (true) {
		TIME start_time = GetTickCount();

		//��������
		while (peekmessage(&msg)) {
			player.ProcessEvent(msg);
		}

		//���ݴ���
		//Player����
		player.Move();
		bulletList.UpdataBulletPosition(player);

		//Monster����
		m_testList.TryGenerateM_test();
		m_testList.Move(player);

		//��ͼ
		setbkcolor(BLACK);
		cleardevice();
		player.Drow();
		bulletList.Draw();
		m_testList.Draw();
		exballList.Draw();
		//�����ײ
		m_testList.CheckCollision(M_testCollision(), player);
		m_testList.CheckCollision(bulletList, player);
		exballList.CheckAlive(player);
		//Ѫ������
		m_testList.CheckAlive(exballList);
		if (!player.CheckAlive()) {
			Sleep(1000);
			return 0;
		}

		FlushBatchDraw();

		TIME end_time = GetTickCount();
		TIME delta_time = end_time - start_time;

		if (delta_time < 1000 / 144) {
			Sleep(1000 / 144 - delta_time);
		}
	}

	EndBatchDraw();

	return 0;
}