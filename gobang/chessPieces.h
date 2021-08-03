#pragma once
class ChessPieces
{
public:
	enum ColorPiece { None = 0, Black = -1, White =1 };	//������ɫ 0û���� -1����  1����
	ChessPieces();
	ChessPieces(int x, int y, ChessPieces::ColorPiece colorPiece);
	void draw();
	bool operator==(const ChessPieces& right)const;
	bool operator<(const ChessPieces& right)const;
	int operator[](int index)const;
	operator int();
private:
	int m_x;
	int m_y;
	ColorPiece m_colorPiece;
};

