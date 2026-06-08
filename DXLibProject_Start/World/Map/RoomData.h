#pragma once
#include<vector>

class RoomData
{
public:
	void SetUp(int id, std::vector<int>idList);
	void Teardown();
	void SetRoomIdAll(int Id);
private:
	std::vector<int> m_idList;


	int m_id = -1;

};

