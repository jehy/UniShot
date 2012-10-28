#pragma once
#include "xml.h"
#include "allxml.h"
void ShowError(char* err,int Cryt=0);
void ShowError(CString err,int Cryt=0);
char* GetApplicationDir();
char* file_get_contents(char* url,int mode=1,int* BytesRead=NULL);
xml* GetItemChild(AllXml* mxml,xml* parent, char* name);
int file_put_contents(char* filename,char* data,int Bytes=-1);
bool FindProc(char* executable);
char* GetTextLastError();
char* GetTextError(int code);
void Sorry_Beta();
bool IsTrue(char* StrBool);
//bool KillProc(char* executable, int brutality);
int KILL_PROC_BY_NAME(const char *szToTerminate);
bool DirectoryExists(char* dir);
bool FileExists(char* file);