#pragma once

// ����Ϊ��Ƴߴ�

// ���ڴ�С
constexpr float WINDOW_WIDTH = 256;
constexpr float WINDOW_HEIGHT = 224;

// ��ͷλ��
constexpr float ARROWS_X = 75;
constexpr float ARROWS_Y = 132;
constexpr float ARROWS_DIS = 15;

// �м��ɫ��Ϸ�����С
constexpr float CENTER_WIDTH = 208;
constexpr float CENTER_HEIGHT = 208;

// �����С
constexpr float BLOCK_SIZE = 8;

// ̹�˴�С
constexpr float TANK_SIZE = 16;

// ���̹�˳�ʼλ��
constexpr float PLAYER1_START_X = 80;
constexpr float PLAYER1_START_Y = 8;

constexpr float PLAYER2_START_X = 128;
constexpr float PLAYER2_START_Y = 8;

// �з�̹�˳�ʼλ��
constexpr float ENEMY1_STAR_X = 8;
constexpr float ENEMY1_STAR_Y = 200;

constexpr float ENEMY2_STAR_X = 104;
constexpr float ENEMY2_STAR_Y = 200;

constexpr float ENEMY3_STAR_X = 200;
constexpr float ENEMY3_STAR_Y = 200;

// ��Ӫλ��
constexpr float CAMP_X = 104;
constexpr float CAMP_Y = 8;

// �ӵ���С
constexpr float BULLET_SIZE = 4;

// �з�̹������
constexpr unsigned char ENEMIES_COUNT = 20;

enum class Dir {
    LEFT = 0, UP, RIGHT, DOWN
};
