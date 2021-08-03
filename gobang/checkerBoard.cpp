#include "checkerBoard.h"
CheckerBoard::CheckerBoard(int x, int y,int rows,const int cols,int gridSize)
	:BasicWidget(x,y, gridSize*rows-1, gridSize*cols-1), 
	whoOp(ChessPieces::Black), 
	GRID_W(gridSize),
	m_rows(rows),m_cols(cols),
	m_map(rows)
{
	for (int i = 0; i < rows; i++)
	{
		for (int k = 0; k < cols; k++)
		{
			m_map[i].push_back(ChessPieces(m_x + i * 25, m_y +k*25, ChessPieces::None));
		}	
	}
	std::cout << m_map.size() <<"   " << m_map[0].size() << std::endl;
}

CheckerBoard::~CheckerBoard()
{
	for (const auto& p : m_map)
	{
		//delete[] p;
	}
}

void CheckerBoard::show()
{
	setlinecolor(BLACK);
	//��������
	for (int i = 0; i < 15; i++)
	{
		if (i == 0 || i == 14)
		{
			setlinestyle(PS_SOLID, 2);
		}
		else
		{
			setlinestyle(PS_SOLID, 1);
		}
		line(m_x, i * GRID_W + m_y, m_x + GRID_W * 14, i * GRID_W + m_y);	//����
		line(i * GRID_W + m_x, m_y, i * GRID_W + m_x, m_y + GRID_W * 14);	//����
	}

	setfillcolor(BLACK);
	//�м�ĵ�
	solidcircle(7 * GRID_W + m_x, 7 * GRID_W + m_y, 5);
	//����
	solidcircle(3 * GRID_W + m_x, 3 * GRID_W + m_y, 5);
	//����
	solidcircle(3 * GRID_W + m_x, (7 + 4) * GRID_W + m_y, 5);
	//����
	solidcircle((7 + 4) * GRID_W + m_x, 3 * GRID_W + m_y, 5);
	//����
	solidcircle((7 + 4) * GRID_W + m_x, (7 + 4) * GRID_W + m_y, 5);

	for (auto chess_vec : m_map)
	{
		for (auto chess : chess_vec)
		{
			chess.draw();
		}
	}

	//������ɫ���
	setlinecolor(BLUE);
	rectangle(opx - 12, opy - 12, opx + 12, opy + 12);

}

void CheckerBoard::eventLoop(const ExMessage& msg)
{
	m_msg = &msg;
	//�����겻����������
	if (m_msg->x < m_x || m_msg->x > m_x + m_w || m_msg->y<m_y || m_msg->y > m_y + m_h)
	{
		opx = -50;
		opy = -50;
		return;
	}
	//������±�У׼
	for (int i = 0; i < 15; i++)
	{
		for (int k = 0; k < 15; k++)
		{
			int gridx = (k + 3) * GRID_W;	//��ǰ�������Ͻǵ�����
			int gridy = (i + 3) * GRID_W;
			if (abs(msg.x - gridx) < 12 && abs(msg.y - gridy) < 12)
			{
				opx = gridx;
				opy = gridy;
				opr = i;
				opc = k;
			}
		}
	}


	//���������£����Ҵ˴�û������
	if (msg.message == WM_LBUTTONDOWN && m_map[opr][opc] == ChessPieces::None)
	{
		//�����ӷ�������
		m_map[opr][opc] = ChessPieces(opx,opy,(ChessPieces::ColorPiece)whoOp);
		whoOp = -whoOp;	
	}
}
//�ж��Ƿ�����������
bool CheckerBoard::judge()
{
	int r = opr;
	int c = opc;
	//ȷ����ǰ����һ���µ���
	int who = -whoOp;
	//��� �в�ͬ
	for (int i = c - 4; i <= c; i++)
	{
		if (i >= 0 && i <= m_cols  - 4
			&& who == m_map[r][i] && who == m_map[r][i + 1]
			&& who == m_map[r][i + 2] && who == m_map[r][i + 3]
			&& who == m_map[r][i + 4])
		{
			return true;
		}
	}
	//����
	for (int i = r - 4; i <= r; i++)
	{
		if (i >= 0 && i <= m_rows - 4
			&& who == m_map[i][c] && who == m_map[i + 1][c]
			&& who == m_map[i + 2][c] && who == m_map[i + 3][c]
			&& who == m_map[i + 4][c])
		{
			return true;
		}
	}
	//б�� /
	for (int i = r - 4, k = c - 4; i <= r, k <= c; i++, k++)
	{
		if (i >= 0 && i <= m_rows - 4 && k >= 0 && k <= m_cols - 4
			&& who == m_map[i][k] && who == m_map[i + 1][k + 1]
			&& who == m_map[i + 2][k + 2] && who == m_map[i + 3][k + 3]
			&& who == m_map[i + 4][k + 4])
		{
			return true;
		}
	}
	//б�� \ 
	for (int i = r - 4, k = c + 4; i <= r, k >= c; i++, k--)
	{
		if (i >= 0 && i <= m_rows - 4 && k >= 0 && k <= m_cols - 4
			&& who == m_map[i][k] && who == m_map[i + 1][k - 1]
			&& who == m_map[i + 2][k - 2] && who == m_map[i + 3][k - 3]
			&& who == m_map[i + 4][k - 4])
		{
			return true;
		}
	}
	return false;
}
