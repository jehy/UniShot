#pragma once

class xml
{
public:
	xml(xml* parent);
	~xml();
//private:
public:
	xml* parent;
	char* name;
	char* subtext;
	void SetName(const char* text);
	void SetSubtext(const char* text);
};
