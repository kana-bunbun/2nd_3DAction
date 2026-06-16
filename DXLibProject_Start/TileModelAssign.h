#pragma once
/// <summary>
/// マップタイルオブジェクトにモデルハンドルを渡す
/// </summary>
class TileModelAssign
{
public:
	TileModelAssign();
	~TileModelAssign();

	int GetPillarHandle() { return m_pillarHandle; }
	int GetWallHandle() { return m_wallHandle; }
private:
	int m_pillarHandle;
	int m_wallHandle;
};

