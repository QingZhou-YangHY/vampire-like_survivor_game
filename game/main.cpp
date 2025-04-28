#include "common_def.h"
#include "monster.h"
#include "m_test.h"
#include "player.h"
#include "bullet.h"

int main() {

	InitAll();

	Player player = Player({ WIDTH / 2, HIGH / 2 }, 10, 5);
	std::vector<M_test*> M_test_list;
	std::vector<Bullet*> bulletList;

	for (int i = 0; i < 3;i++) {
		bulletList.push_back(new Bullet());
	}

	ExMessage msg;

	BeginBatchDraw();

	while (true) {
		DWORD start_time = GetTickCount();

		//��������
		while (peekmessage(&msg)) {
			player.ProcessEvent(msg);
		}

		//���ݴ���
		//Player����
		player.Move();
		UpdataBulletPosition(bulletList, player);

		//Monster����
		TryGenerateM_test(M_test_list);
		for (auto monster : M_test_list) {
			monster->Move(player);
		}

		//��ͼ
		setbkcolor(BLACK);
		cleardevice();
		player.Drow();
		int counter = 0;
		for (auto bullet : bulletList) {
			bullet->Draw();
		}
		for (auto monster : M_test_list) {
			monster->Drow();
		}
		//�����ײ
		for (auto monster : M_test_list) {
			if (monster->CheckPlayerCollision(player)) {
				monster->Attack(&player);
				if (!player.CheckAlive()) {
					Sleep(1000);
					return 0;
				}
			}
		}
		for (auto monster : M_test_list) {
			for (auto bullet : bulletList) {
				if (monster->CheckBulletCollision(*bullet)) {
					monster->Hurt(player, *bullet);
				}
			}
		}
		//Ѫ������
		for (int i = 0;i < M_test_list.size();i++) {
			M_test* monster = M_test_list[i];
			if (!monster->CheckAlive()) {
				std::swap(M_test_list[i], M_test_list.back());
				M_test_list.pop_back();
				delete monster;
				printf("һֻ M_test ����\n");
			}
		}

		FlushBatchDraw();

		DWORD end_time = GetTickCount();
		DWORD delta_time = end_time - start_time;

		if (delta_time < 1000 / 144) {
			Sleep(1000 / 144 - delta_time);
		}
	}

	EndBatchDraw();

	return 0;
}