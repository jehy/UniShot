#include "stdafx.h"
#include "xml.h"
xml::xml(xml* parent)
{
	this->parent=parent;
	this->name=NULL;
	this->subtext=NULL;
//	vec.add(this);
}
xml::~xml()
{
	if(name!=NULL)
		delete[] name;
	if(subtext!=NULL)
		delete[] subtext;
}
void xml::SetName(const char* text)
{
	if(name!=NULL)
		delete []name;
	size_t z=strlen(text)+1;
	name=new char[z];
	strcpy_s(this->name,z,text);
}
void xml::SetSubtext(const char* text)
{
	if(subtext!=NULL)delete []subtext;
	size_t z=strlen(text)+1;
	this->subtext=new char[z];
	strcpy_s(this->subtext,z,text);
}
