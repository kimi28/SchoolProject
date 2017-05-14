#include "NPCObject.h"



NPCObject::NPCObject()
{
	this->image = new Gdiplus::Image(L"resource\\Npc_1.png");
	this->rect = { 0, 0, 0, 0 };

	this->rect.Width = image->GetWidth();
	this->rect.Height = image->GetHeight();
}


NPCObject::~NPCObject()
{
}
