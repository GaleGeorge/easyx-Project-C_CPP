#pragma once
#include<BasicWidget.h>
#include<vector>
struct ExMessage;
#include"chessPieces.h"
class CheckerBoard :public BasicWidget
{
public:
	CheckerBoard(int x,int y,int rows = 15,int cols = 15,int gridSize = 25);
	~CheckerBoard();
	void show();
	void eventLoop(const ExMessage&  msg);
	//�ж��Ƿ�����������
	bool judge();
public:
	const ExMessage* m_msg;

public:	//��������������±�
	std::vector<std::vector<ChessPieces>> m_map;
	int whoOp;			//��ǰ���Ƿ�������

	const int GRID_W;

	int m_rows;
	int m_cols;

	int opx;
	int opy;
	int opr;
	int opc;
};

