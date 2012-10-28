#include "stdafx.h"
//#include "allxml.h"
#include "common_funcs.h"
/*void ShowError(CString err)
{
	MessageBox(NULL,err,"Error",MB_OK);			
	exit(2);
}*/


char* AllXml::GetTextContents()
{
	//CString FileContents;
	char* FileContents=Save2(this->GetItemOnlyChild(this->MainElement,"xml",1),0);
	return(FileContents);
}


char* AllXml::Save2(xml* parent, int offset)
{

	CString FileContents;
	CString NewContents;
	bool found=0;
	for(int i=0;i<this->vec.size();i++)
	{
		if(this->vec[i]->parent==parent)
		{
			//CString fuck;
			//fuck.Format("child of %s is equal to %s",parent->name,MenuXml.vec[i]->name);
			//MessageBox(NULL,fuck,"",MB_OK);
			found=1;
			char* NewC=Save2(this->vec[i],offset+1);
			NewContents.Append(NewC);
			delete(NewC);
		}
	}
	if (found==0)
	{
		for(int n=0;n<offset;n++)FileContents.Append("	");
		/*<tag>*/FileContents+="<";FileContents+=parent->name;FileContents+=">";
		/*value*/FileContents+=parent->subtext;
		/*</tag>*/FileContents+="</";FileContents+=parent->name;FileContents+=">";
		FileContents.Append("\n");
	}
	else
	{
			for(int n=0;n<offset;n++)FileContents.Append("	");
			FileContents+="<";FileContents+=parent->name;FileContents+=">";
			FileContents.Append("\n");
			
			FileContents.Append(NewContents);
			//delete(NewContents);
			for(int n=0;n<offset;n++)FileContents.Append("	");
			FileContents+="</";FileContents+=parent->name;FileContents+=">";
			FileContents.Append("\n");
	
	}
	//file_put_contents(filename,);
	char* contents=new char[FileContents.GetLength()+1];
	strcpy_s(contents,FileContents.GetLength()+1,FileContents);
	//FileContents.ReleaseBuffer();
	//NewContents.ReleaseBuffer();
	return contents;
}
int AllXml::parse2 (CString subtext, CString MyTag,int offset, xml* parent, XmlItems* vec)
{
	xml* newxml;
	int pos,pos2;
	int offset0=offset;
	CString err,name;
	newxml=new(xml)(parent);
	int i=0;
	while(true)
	{
		i++;
		if(i>1000)ShowError("Too many xml work; Seems like an error! Terminating!");
		pos=subtext.Find("<",offset);		
		if(pos==-1)
		{
			err.Format("Couldn't find opening bracket for closing tag for '%s'!",MyTag);
			ShowError(err.GetBuffer(err.GetLength()));
		}
		//if(pos==-1)break;
		pos++;
		pos2=subtext.Find(">",pos);
		if(pos2==-1)
		{
			err.Format("Couldn't find closing bracket for closing tag for '%s'!",MyTag);
			ShowError(err.GetBuffer(err.GetLength()));
		}
		name=subtext.Mid(pos,(pos2-pos));
		if(name[0]=='/')
		{
			name=name.Right(name.GetLength()-1);
			if(!name.CompareNoCase(MyTag))
			{
				newxml->SetName(MyTag);
				if(_stricmp(MyTag,"item")==0)newxml->SetSubtext(subtext.Mid(offset0,pos-offset0-1).Trim());
				else newxml->SetSubtext(subtext.Mid(offset,pos-offset-1));
				vec->push_back(newxml);
				return pos2+1;
			}
			else
			{
				err.Format("Found closing tag %s instead of %s!",name,MyTag);
				ShowError(err.GetBuffer(err.GetLength()));
			}
		}
		else offset=parse2(subtext,name,(pos2+1),newxml,vec);
	}
}
AllXml::AllXml()
{
}
AllXml::~AllXml()
{
	for (int i=0;i<vec.size();i++)
		delete(vec[i]);
}

void AllXml::Parse (CString text, CString MainTag)
{
	xml* main=new xml(NULL);
	this->MainElement=main;
	vec.push_back(main);
	CString MainTag1="<"+MainTag+">";
	int pos=text.Find(MainTag1,0);
	if(pos==-1)
	{
		CString err="Main tag '"+MainTag1+"' not found!";
		ShowError(err.GetBuffer(err.GetLength()));
	}
	parse2(text, MainTag,(pos+MainTag1.GetLength()),main,&vec);
}


xml* AllXml::GetItemOnlyChild(xml* parent, char* name,bool necc)
{
	for(int i=0;i<vec.size();i++)
		if((vec[i]->parent!=NULL)&&(vec[i]!=NULL)&&(vec[i]->name!=NULL))
			if((_stricmp(vec[i]->name,name)==0)&&(vec[i]->parent==parent))return vec[i];
	
	if(necc)
	{
		CString err;
		err="failed to get XML item (";
		err.Append(parent->name);
		err.Append(")'s child (");
		err.Append(name);
		err.Append(")\n\nFull item's xml:\n\n");
		err.Append(parent->subtext);
		err.Append(")\n\nTerminating...");
		ShowError(err.GetBuffer(err.GetLength()));
	}
	return NULL;
}
bool AllXml::DeleteItem(xml* item)
{
	for(int i=0;i<vec.size();i++)
	{
		if(vec[i]==item)
		{
			vec.delete_by_value(vec[i]);
			for(int i=0;i<vec.size();i++)
				if(vec[i]->parent==item)
					DeleteItem(vec[i]);
			break;
		}
	}
	return true;
}

