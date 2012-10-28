#pragma once
#include "xml.h"
#include "mvector.h"
typedef mvector <xml*> XmlItems;
class AllXml
{	
public:
	AllXml();
	~AllXml();
public:
	void Parse (CString text, CString MainTag);
	bool DeleteItem(xml* item);
	//bool DeleteItemChildren(xml* item);
	XmlItems vec;
	xml* MainElement;
	xml* GetItemOnlyChild(xml* parent, char* name,bool necc=0);
//private:
	char* GetTextContents();
	char* Save2(xml* parent, int offset);
	int parse2 (CString subtext, CString MyTag,int offset, xml* parent, XmlItems* vec);
	//xml* ItemParam(xml* item, char* name);
//	xml** GetChildren(xml* parent);
};