#include "ImageResource.h"
#include<DxLib.h>
ImageResource::ImageResource(int ID, int handle):
	ID(ID),
	m_handle(handle)
{

}

ImageResource::~ImageResource()
{
	if (m_handle != -1) {
	DeleteGraph(m_handle);
	}
	ID = -1;
}
