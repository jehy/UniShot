#include "stdafx.h"
#include "Tlhelp32.h"
#include "common_funcs.h"
#ifdef MAIN_APP
extern ExitClass ExitProgram;
#elif defined PLUGIN_APP
extern HANDLE DieEvent;
#elif defined SETUP_APP
#else
#endif


void ShowError(char* err, int Cryt)
{
	if(Cryt)
	{
#ifdef MAIN_APP
		SetEvent(ExitProgram.ExitEvent);
#elif defined PLUGIN_APP
		SetEvent(DieEvent);
#elif defined SETUP_APP
#else
#endif
	}
	MessageBox(NULL,err,"Error",MB_ICONERROR);
	if(Cryt)
	{
		Sleep(100);
		exit(3);
	}
}

void ShowError(CString err, int Cryt)
{
	if(Cryt)
		ShowError(err.GetBuffer(),Cryt);
	else
		ShowError(err.GetBuffer());
}

bool IsTrue(char* StrBool)
{
	if(!_stricmp(StrBool,"true"))return 1;
	else if (!_stricmp(StrBool,"false"))return 0;
	else if (!strcmp(StrBool,"1"))return 1;
	else if (!strcmp(StrBool,"0"))return 0;
	else ShowError("WTF is this boolean?!",1);
	return 0;
}
void Sorry_Beta()
{
	MessageBox(NULL,"Sorry, it's still kinda beta function","Sorry",MB_OK);
}

char* GetTextError(int code)
{
	char* szBuf=new char[255]; 
    LPVOID lpMsgBuf;
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM,
        NULL,
        code,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );
    wsprintf(szBuf,"Windows reported error %d: %s",code, lpMsgBuf);  
    LocalFree(lpMsgBuf);
	return szBuf;
}

char* GetTextLastError()
{
	return GetTextError(GetLastError());//szBuf;
}



bool FindProc(char* executable)
{
	HANDLE hProcessSnap;
	HANDLE hProcess;
	PROCESSENTRY32 pe32;
	DWORD dwPriorityClass;
	CString title;
	hProcessSnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
	if( hProcessSnap == INVALID_HANDLE_VALUE )
		MessageBox(NULL,"CreateToolhelp32Snapshot (of processes)","Error!",MB_OK);
	pe32.dwSize = sizeof( PROCESSENTRY32 );
	if( !Process32First( hProcessSnap, &pe32 ) )
	{
		MessageBox(NULL,"Process32First","Error!",MB_OK);
		CloseHandle( hProcessSnap );     // Must clean up the snapshot object!	
	}
	do
	{
		title=pe32.szExeFile;
		//running.AddString(title);
		dwPriorityClass = 0;
		hProcess = OpenProcess(PROCESS_ALL_ACCESS,FALSE,pe32.th32ProcessID);
		if( hProcess == NULL )
		{
			//Error with system processes!
			//err="OpenProcess";
			//MessageBox(err,title,MB_OK);
		}
		else CloseHandle(hProcess);
		CString exec=executable;
		exec=exec.Right(exec.GetLength()-exec.ReverseFind('\\')-1);
		if(_stricmp(exec,title)==0)
		{
			CloseHandle(hProcessSnap);
			return true;
		}
	} 
	while(Process32Next(hProcessSnap, &pe32 ));
	CloseHandle(hProcessSnap);
	return false;
}
/*
bool KillProc(char* WindowCaption, char* executable, int brutality)
{
	if(WindowCaption!=NULL)
	{
		HWND wnd=FindWindow(
		PostMessage(AppHandle, WM_QUIT, 0, 0);
	}
}*/

char* GetApplicationDir()
{
	char* p=new char[355];
	int z=GetModuleFileName(NULL,p,355);
	CString path=p;
	delete(p);
	path=path.Left(path.ReverseFind('\\')+1);
	int s=path.GetLength()+1;
	p=new char[s];
	//p=path.Left(pos+1).GetBuffer();
	strcpy_s(p,s,path);
	return p;
}


int file_put_contents(char* filename,char* data,int Bytes)
{
	FILE *stream;
	size_t  numwritten;
	// Open file in text mode:
	if( fopen_s( &stream, filename, "w+t" ) == 0 )
	{
	  // Write 25 characters to stream
		unsigned int s=(unsigned int)strlen(data);
		if((Bytes!=-1)&&(s>Bytes))
			s=Bytes;
	  numwritten = fwrite(data, sizeof(char),s, stream );
	  //printf( "Wrote %d items\n", numwritten );
	  fclose( stream );
	}
	else
	  ShowError( "Problem opening the file\n" );
	return 1;
}


char* file_get_contents(char* url,int mode,int* BytesRead)
{
  FILE * pFile;
  long lSize;
  char * buffer;
  size_t result;
  fopen_s(&pFile, url, "r+t" );
  if (pFile==NULL)
  {
	if(mode!=0)
	{
		CString err="Failed to open file '";
		err.Append(url);
		err.Append("'");
		ShowError(err,0);
	}
	return NULL;
  }
  // obtain file size:
  fseek (pFile , 0 , SEEK_END);
  lSize = ftell (pFile);
  if(BytesRead!=NULL)
	  *BytesRead=lSize;
  rewind (pFile);
  // allocate memory to contain the whole file:
  buffer = new char[(sizeof(char)*lSize)];
  //if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}
  // copy the file into the buffer:
  result = fread (buffer,1,lSize,pFile);
  //f (result != lSize) {fputs ("Reading error",stderr); exit (3);}
  /* the whole file is now loaded in the memory buffer. */
  // terminate
  fclose (pFile);
  return buffer;
  //free (buffer);
}






int KILL_PROC_BY_NAME(const char *szToTerminate)
{

int param = 2;

BOOL bResult,bResultm;
DWORD aiPID[1000],iCb=1000,iNumProc,iV2000=0;
DWORD iCbneeded,i,iFound=0;
char szName[MAX_PATH],szToTermUpper[MAX_PATH];
HANDLE hProc,hSnapShot,hSnapShotm;
OSVERSIONINFO osvi;
    HINSTANCE hInstLib;
int iLen,iLenP,indx;
    HMODULE hMod;
PROCESSENTRY32 procentry;      
MODULEENTRY32 modentry;

// Transfer Process name into "szToTermUpper" and
// convert it to upper case
iLenP=(int)strlen(szToTerminate);
if(iLenP<1 || iLenP>MAX_PATH) return 7;
for(indx=0;indx<iLenP;indx++)
szToTermUpper[indx]=toupper(szToTerminate[indx]);
szToTermUpper[iLenP]=0;

     // PSAPI Function Pointers.
     BOOL (WINAPI *lpfEnumProcesses)( DWORD *, DWORD cb, DWORD * );
     BOOL (WINAPI *lpfEnumProcessModules)( HANDLE, HMODULE *,
        DWORD, LPDWORD );
     DWORD (WINAPI *lpfGetModuleBaseName)( HANDLE, HMODULE,
        LPTSTR, DWORD );

      // ToolHelp Function Pointers.
      HANDLE (WINAPI *lpfCreateToolhelp32Snapshot)(DWORD,DWORD) ;
      BOOL (WINAPI *lpfProcess32First)(HANDLE,LPPROCESSENTRY32) ;
      BOOL (WINAPI *lpfProcess32Next)(HANDLE, LPPROCESSENTRY32) ;
      BOOL (WINAPI *lpfModule32First)(HANDLE,LPMODULEENTRY32) ;
      BOOL (WINAPI *lpfModule32Next)(HANDLE,LPMODULEENTRY32) ;

// First check what version of Windows we're in
osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    bResult=GetVersionEx(&osvi);
if(!bResult)     // Unable to identify system version
    return 5;

// At Present we only support Win/NT/2000/XP or Win/9x/ME
if((osvi.dwPlatformId != VER_PLATFORM_WIN32_NT) &&
(osvi.dwPlatformId != VER_PLATFORM_WIN32_WINDOWS))
return 6;

    if(osvi.dwPlatformId==VER_PLATFORM_WIN32_NT)
{
// Win/NT or 2000 or XP

         // Load library and get the procedures explicitly. We do
         // this so that we don't have to worry about modules using
         // this code failing to load under Windows 9x, because
         // it can't resolve references to the PSAPI.DLL.
         hInstLib = LoadLibraryA("PSAPI.DLL");
         if(hInstLib == NULL)
            return 3;

         // Get procedure addresses.
         lpfEnumProcesses = (BOOL(WINAPI *)(DWORD *,DWORD,DWORD*))
            GetProcAddress( hInstLib, "EnumProcesses" ) ;
         lpfEnumProcessModules = (BOOL(WINAPI *)(HANDLE, HMODULE *,
            DWORD, LPDWORD)) GetProcAddress( hInstLib,
            "EnumProcessModules" ) ;
         lpfGetModuleBaseName =(DWORD (WINAPI *)(HANDLE, HMODULE,
            LPTSTR, DWORD )) GetProcAddress( hInstLib,
            "GetModuleBaseNameA" ) ;

         if(lpfEnumProcesses == NULL ||
            lpfEnumProcessModules == NULL ||
            lpfGetModuleBaseName == NULL)
            {
               FreeLibrary(hInstLib);
               return 8;
            }

bResult=lpfEnumProcesses(aiPID,iCb,&iCbneeded);
if(!bResult)
{
// Unable to get process list, EnumProcesses failed
            FreeLibrary(hInstLib);
return 9;
}

// How many processes are there?
iNumProc=iCbneeded/sizeof(DWORD);

// Get and match the name of each process
for(i=0;i<iNumProc;i++)
{
// Get the (module) name for this process
        strcpy(szName,"Unknown");
// First, get a handle to the process
        hProc=OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ,FALSE,
aiPID[i]);
        // Now, get the process name
        if(hProc)
{
               if(lpfEnumProcessModules(hProc,&hMod,sizeof(hMod),&iCbneeded) )
   {
                  iLen=lpfGetModuleBaseName(hProc,hMod,szName,MAX_PATH);
   }
}
        CloseHandle(hProc);
    if (param == 1 ) //if list
		;
//     cout << szName << endl;
else
// We will match regardless of lower or upper case
#ifdef BORLANDC
            if(strcmp(strupr(szName),szToTermUpper)==0)
#else
if(strcmp(_strupr(szName),szToTermUpper)==0)
#endif
{
// Process found, now terminate it
iFound=1;
// First open for termination

if (param == 2) {
hProc=OpenProcess(PROCESS_TERMINATE,FALSE,aiPID[i]);
if(hProc)
{
if(TerminateProcess(hProc,0))
{
// process terminated
CloseHandle(hProc);
                        FreeLibrary(hInstLib);
return 0;
}
else
{
// Unable to terminate process
CloseHandle(hProc);
                        FreeLibrary(hInstLib);
return 4;
}
}
else
{
// Unable to open process for termination
                    FreeLibrary(hInstLib);
return 2;
}
}
}
}
}

if(osvi.dwPlatformId==VER_PLATFORM_WIN32_WINDOWS)
{
// Win/95 or 98 or ME

hInstLib = LoadLibraryA("Kernel32.DLL");
if( hInstLib == NULL )
return 10;

// Get procedure addresses.
// We are linking to these functions of Kernel32
// explicitly, because otherwise a module using
// this code would fail to load under Windows NT,
// which does not have the Toolhelp32
// functions in the Kernel 32.
lpfCreateToolhelp32Snapshot=
(HANDLE(WINAPI *)(DWORD,DWORD))
GetProcAddress( hInstLib,
"CreateToolhelp32Snapshot" ) ;
lpfProcess32First=
(BOOL(WINAPI *)(HANDLE,LPPROCESSENTRY32))
GetProcAddress( hInstLib, "Process32First" ) ;
lpfProcess32Next=
(BOOL(WINAPI *)(HANDLE,LPPROCESSENTRY32))
GetProcAddress( hInstLib, "Process32Next" ) ;
lpfModule32First=
(BOOL(WINAPI *)(HANDLE,LPMODULEENTRY32))
GetProcAddress( hInstLib, "Module32First" ) ;
lpfModule32Next=
(BOOL(WINAPI *)(HANDLE,LPMODULEENTRY32))
GetProcAddress( hInstLib, "Module32Next" ) ;
if( lpfProcess32Next == NULL ||
lpfProcess32First == NULL ||
    lpfModule32Next == NULL ||
lpfModule32First == NULL ||
lpfCreateToolhelp32Snapshot == NULL )
{
FreeLibrary(hInstLib);
return 12;
}

// The Process32.. and Module32.. routines return names in all uppercase

// Get a handle to a Toolhelp snapshot of all the systems processes.

hSnapShot = lpfCreateToolhelp32Snapshot(
TH32CS_SNAPPROCESS, 0 ) ;
if( hSnapShot == INVALID_HANDLE_VALUE )
{
FreeLibrary(hInstLib);
return 13;
}

        // Get the first process' information.
        procentry.dwSize = sizeof(PROCESSENTRY32);
        bResult=lpfProcess32First(hSnapShot,&procentry);

        // While there are processes, keep looping and checking.
        while(bResult)
        {
    // Get a handle to a Toolhelp snapshot of this process.
    hSnapShotm = lpfCreateToolhelp32Snapshot(
    TH32CS_SNAPMODULE, procentry.th32ProcessID) ;
    if( hSnapShotm == INVALID_HANDLE_VALUE )
{
CloseHandle(hSnapShot);
    FreeLibrary(hInstLib);
    return 13;
}
// Get the module list for this process
modentry.dwSize=sizeof(MODULEENTRY32);
bResultm=lpfModule32First(hSnapShotm,&modentry);

// While there are modules, keep looping and checking
while(bResultm)
{
        if (param == 1 ) //if list
			;
//     cout << szName << endl;
else if (strcmp(modentry.szModule,szToTermUpper)==0)
{
    // Process found, now terminate it
    iFound=1;
    // First open for termination
    hProc=OpenProcess(PROCESS_TERMINATE,FALSE,procentry.th32ProcessID);
    if(hProc)
{
    if(TerminateProcess(hProc,0))
{
    // process terminated
CloseHandle(hSnapShotm);
CloseHandle(hSnapShot);
CloseHandle(hProc);
                FreeLibrary(hInstLib);
    return 0;
}
    else
{
    // Unable to terminate process
CloseHandle(hSnapShotm);
CloseHandle(hSnapShot);
CloseHandle(hProc);
                FreeLibrary(hInstLib);
    return 4;
}
}
    else
{
    // Unable to open process for termination
CloseHandle(hSnapShotm);
CloseHandle(hSnapShot);
            FreeLibrary(hInstLib);
    return 2;
}
}
else
{  // Look for next modules for this process
modentry.dwSize=sizeof(MODULEENTRY32);
bResultm=lpfModule32Next(hSnapShotm,&modentry);
}
}

//Keep looking
CloseHandle(hSnapShotm);
            procentry.dwSize = sizeof(PROCESSENTRY32);
            bResult = lpfProcess32Next(hSnapShot,&procentry);
        }
CloseHandle(hSnapShot);
}
if(iFound==0)
{
FreeLibrary(hInstLib);
return 1;
}
FreeLibrary(hInstLib);
return 0;
}

bool DirectoryExists(char* dir)
{
	DWORD z=GetFileAttributes(dir);
	if(z==INVALID_FILE_ATTRIBUTES)
		return FALSE;
	if(z&&FILE_ATTRIBUTE_DIRECTORY)
		return TRUE;
	return FALSE;
}


bool FileExists(char* file)
{
	DWORD z=GetFileAttributes(file);
	if(z==INVALID_FILE_ATTRIBUTES)
		return FALSE;
	return TRUE;
}