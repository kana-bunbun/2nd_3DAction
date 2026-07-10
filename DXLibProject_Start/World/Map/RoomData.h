#pragma once
#include<vector>

class RoomData
{
public:
	void SetUp(int id, std::vector<int>idList);
	void Teardown();
	void SetRoomIdAll(int Id);
	const std::vector<int>& GetIDList()const { return m_idList; }
private:
	std::vector<int> m_idList;


	int m_id = -1;

};

