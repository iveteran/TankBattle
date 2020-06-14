#pragma once

// �߿��С
#define BORDER_WIDTH 100

//���ڴ�С
#define WINDOW_WIDTH	(256 + BORDER_WIDTH)
#define WINDOW_HEIGHT	224

//��ͷλ��
#define ARROWS_X        75
#define ARROWS_Y        132
#define ARROWS_DIS      15

//�м��ɫ��Ϸ����
#define CENTER_WIDTH	208
#define CENTER_HEIGHT	208

//��Ϸ����������½ǵ�����
#define CENTER_X		((WINDOW_WIDTH - CENTER_WIDTH) / 2)
#define CENTER_Y		(WINDOW_HEIGHT - CENTER_HEIGHT)

//�����С
#define BLOCK_SIZE      8

//̹�˴�С
#define TANK_SIZE       16

// ̹�˳�ʼλ��
#define PLAYER1_START_X 80
#define PLAYER1_START_Y 8

#define PLAYER2_START_X 128
#define PLAYER2_START_Y 8

// ��Ӫλ��
#define CAMP_X          104
#define CAMP_Y          8

//�ӵ���С
#define BULLET_SIZE     4

enum class Dir {
	LEFT = 0, UP, RIGHT, DOWN
};
