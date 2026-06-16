#pragma once
#include"../Component/Transform.h"
#include"../../Utility/Vector3.h"
class MapDraw
{
public:
	MapDraw();
	~MapDraw();

	void Draw();
	void DrawMap();
	void DrawMiniMap();
	bool InDevideList(size_t id);
	void DrawMark();
	void SetMarkPos(Transform markPos) { m_markPos = markPos; }
private:
	Transform m_markPos;
	int m_cursorHandle;
};

