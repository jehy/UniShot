#pragma once
//#include "afxtempl.h";
template <class Contents> class mvector
//template <class T, int i> class TestClass 
{
public:
	mvector(int SuggestedCount=2);
	~mvector();
public:
	void push_back(Contents NewElement);
	void Clear_And_Delete_Elements();
	void minimize();
	int delete_by_value(Contents Element);
	int size();
	Contents operator [](int index);
	Contents* handles; 
	//bool operator [];
	int RealCount;
	int RealSize;
};

///////////////////////////////


template <class Contents>
void mvector <Contents>::Clear_And_Delete_Elements()
{
	for(int i=0;i<RealCount;i++)
		delete(handles[i]);
	RealCount=0;
}

template <class Contents>
int mvector <Contents>::delete_by_value(Contents Element)
{
	for(int i=0;i<RealCount;i++)
	{
		if(handles[i]==Element)
		{
			delete(handles[i]);
			RealCount--;
			handles[i]=handles[RealCount];
			handles[RealCount]=NULL;
			return 1;
			//break;
		}
	}
	return 0;
}

template <class Contents>
mvector <Contents>::mvector(int SuggestedCount=2)
{
	RealCount=0;
	RealSize=SuggestedCount;
	handles=new Contents[SuggestedCount];
}
//template <class T, int i>
//T TestClass<T,i>::testFunc(T* p1) 

template <class Contents>
mvector <Contents>::~mvector()
{
/*	for(int i=0;i<RealCount;i++)
	{
		delete handles[i];
	}*/
	//THIS VECTOR DOES NOT FREE MEMORY FOR ELEMENTS!!!
	delete []handles;
}


template <class Contents>
void mvector <Contents>::push_back(Contents NewElement)
{
        if(RealSize==RealCount)//we need to expand
        {
                RealSize=RealSize*2;
                Contents* temp=new Contents[RealSize];
                memcpy (temp, handles, sizeof(Contents)*RealCount);
                delete [] handles;
                handles=temp;
        }
        memcpy_s(&handles[RealCount],sizeof(handles[RealCount]), &NewElement, sizeof(NewElement));
        //handles[RealCount]=NewElement;
        RealCount++;
}

template <class Contents>
Contents  mvector <Contents>::operator [](int index)
{
	if(index<RealCount)
		return handles[index];
	MessageBox(NULL,"Index out of bounds!","Error",MB_OK);
	return NULL;
}

template <class Contents>
void mvector <Contents>::minimize()
{
	if(RealSize!=RealCount)//we need to work
	{
		RealSize=RealCount;
		Contents* temp=(Contents*)new HANDLE[RealSize];
		memcpy (temp, handles, sizeof(Contents)*RealCount);
		delete [] handles;
		handles=temp;
	}
}

template <class Contents>
int mvector <Contents>::size()
{
	return RealCount;
}
