#include "stdafx.h"
#include "CameraControl.h"
#include "CameraControlDlg.h"
#include "CLifeViewDlg.h"

Hotkeys hotkeys;
Triggers triggers;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define WM_USER_DOWNLOAD_COMPLETE		WM_APP+1
#define WM_USER_PROGRESS_REPORT			WM_APP+2
extern bool mode_offline; 

CString PhotoSavePath;
// CCameraControlDlg 
CLifeViewDlg* LifeViewDlg=NULL;

BOOL CCameraControlDlg::PreTranslateMessage(MSG* pMsg) 
{
  //catch hotkeys
  if(pMsg->message==WM_KEYDOWN)
  {
    //CString x;
    //x.Format("%d",pMsg->wParam);
    //MessageBox(x);
    hotkey* h=hotkeys.Find(pMsg->wParam);
    if(h!=NULL)
        RunAction(h->action);
  }
  return CDialog::PreTranslateMessage(pMsg);
}

void CCameraControlDlg::RunAction(char* action)
{
  if(strcmp(action,"Shoot")==0)
    this->Shoot();
  else if(strcmp(action,"Focus")==0)
    this->FocusPhoto();
  else if(strcmp(action,"NextTab")==0)
    this->SetNextFocus();
  else if(strcmp(action,"IncrementNumber")==0)
    this->IncrementNumber();
  else if(strcmp(action,"DecrementNumber")==0)
    this->DecrementNumber();
}

CCameraControlDlg::CCameraControlDlg(CWnd* pParent )
	: CDialog(CCameraControlDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCameraControlDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);

  DDX_Control(pDX, IDC_BUTTON1, _btnTakePicture);
  DDX_Control(pDX, IDC_PROGRESS1, _progress);
  DDX_Control(pDX, IDC_COMBO1, _comboAEMode);
  DDX_Control(pDX, IDC_COMBO2, _comboTv);
  DDX_Control(pDX, IDC_COMBO3, _comboAv);
  DDX_Control(pDX, IDC_COMBO4, _comboIso);
  DDX_Control(pDX, IDC_COMBO5, _comboMeteringMode);
  DDX_Control(pDX, IDC_COMBO6, _comboExposureComp);
  DDX_Control(pDX, IDC_COMBO7, _comboImageQuality);
  DDX_Control(pDX, IDC_BUTTON2, _btnStartEVF);
  DDX_Control(pDX, IDC_BUTTON3, _btnEndEVF);
  DDX_Control(pDX, IDC_BUTTON4, _btnFocusNear3);
  DDX_Control(pDX, IDC_BUTTON5, _btnFocusNear2);
  DDX_Control(pDX, IDC_BUTTON6, _btnFocusNear1);
  DDX_Control(pDX, IDC_BUTTON7, _btnFocusFar1);
  DDX_Control(pDX, IDC_BUTTON8, _btnFocusFar2);
  DDX_Control(pDX, IDC_BUTTON9, _btnFocusFar3);
  DDX_Control(pDX, IDC_BUTTON10, _btnFocusUp);
  DDX_Control(pDX, IDC_BUTTON11, _btnFocusLeft);
  DDX_Control(pDX, IDC_BUTTON12, _btnFocusRight);
  DDX_Control(pDX, IDC_BUTTON13, _btnFocusDown);
  DDX_Control(pDX, IDC_BUTTON14, _btnZoomFit);
  DDX_Control(pDX, IDC_BUTTON15, _btnZoomZoom);
  DDX_Control(pDX, IDC_BUTTON16, _btnPressingHalfway);
  DDX_Control(pDX, IDC_BUTTON17, _btnPressingCompletely);
  DDX_Control(pDX, IDC_BUTTON18, _btnPressingOff);
  DDX_Control(pDX, IDC_BUTTON21, _btnEvfAfON);
  DDX_Control(pDX, IDC_BUTTON22, _btnEvfAfOFF);
  DDX_Control(pDX, IDC_COMBO8, _comboEvfAFMode);
  DDX_Control(pDX, IDC_CHECK1, Lifeview);
  DDX_Control(pDX, IDC_COMBO10, drivebox);
  DDX_Control(pDX, IDC_EDIT2, settings_file);
  DDX_Control(pDX, IDC_EDIT3, filedir);
  DDX_Control(pDX, IDC_EDIT4, projectdir);
  DDX_Control(pDX, IDC_BUTTON26, shootbtn);
  DDX_Control(pDX, IDC_EDIT1, prefix);
  DDX_Control(pDX, IDC_EDIT5, current_page);
  DDX_Control(pDX, IDC_EDIT6, number_signs);
  DDX_Control(pDX, IDC_EDIT7, _edit);
  DDX_Control(pDX, IDC_BUTTON27, focusbtn);
  DDX_Control(pDX, IDC_EDIT8, PictureWidthT);
  DDX_Control(pDX, IDC_EDIT9, PictureHeightT);
  DDX_Control(pDX, IDC_EDIT10, AutoStepT);
  DDX_Control(pDX, IDC_EDIT11, NumberT);
  DDX_Control(pDX, IDC_EDIT12, prefix2T);
  DDX_Control(pDX, IDC_CHECK2, AutoStepEnabled);
}

BEGIN_MESSAGE_MAP(CCameraControlDlg, CDialog)
	ON_MESSAGE(WM_USER_DOWNLOAD_COMPLETE, OnDownloadComplete)
	ON_MESSAGE(WM_USER_PROGRESS_REPORT, OnProgressReport)
	ON_WM_CLOSE()
  ON_BN_CLICKED(IDOK, &CCameraControlDlg::OnBnClickedOk)
  ON_BN_CLICKED(IDCANCEL, &CCameraControlDlg::OnBnClickedCancel)

	ON_BN_CLICKED(IDC_CHECK1, &CCameraControlDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_BUTTON19, &CCameraControlDlg::OnBnClickedButton19)
	ON_BN_CLICKED(IDC_BUTTON23, &CCameraControlDlg::OnBnClickedButton23)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON24, &CCameraControlDlg::SelectFileDir)
	ON_BN_CLICKED(IDC_BUTTON26, &CCameraControlDlg::Shoot)
ON_BN_CLICKED(IDC_BUTTON27, &CCameraControlDlg::FocusPhoto)
ON_BN_CLICKED(IDC_BUTTON28, &CCameraControlDlg::OpenFileDir)
ON_EN_CHANGE(IDC_EDIT1, &CCameraControlDlg::OnEnChangeEdit1)
//ON_EN_SETFOCUS(IDC_EDIT8, &CCameraControlDlg::OnEnSetfocusEdit8)
//ON_EN_SETFOCUS(IDC_EDIT9, &CCameraControlDlg::OnEnSetfocusEdit9)
ON_BN_CLICKED(IDC_BUTTON30, &CCameraControlDlg::IncrementNumber)
ON_BN_CLICKED(IDC_BUTTON29, &CCameraControlDlg::DecrementNumber)
ON_EN_CHANGE(IDC_EDIT11, &CCameraControlDlg::OnEnChangeNumber)
ON_BN_CLICKED(IDC_CHECK2, &CCameraControlDlg::CheckAutoStep)
//ON_EN_SETFOCUS(IDC_EDIT11, &CCameraControlDlg::OnEnSetfocusEdit11)
//ON_EN_KILLFOCUS(IDC_EDIT11, &CCameraControlDlg::OnEnKillfocusEdit11)
//ON_EN_KILLFOCUS(IDC_EDIT8, &CCameraControlDlg::OnEnKillfocusEdit8)
//ON_EN_KILLFOCUS(IDC_EDIT9, &CCameraControlDlg::OnEnKillfocusEdit9)
END_MESSAGE_MAP()


// CCameraControlDlg message handlers


BOOL CCameraControlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();


	// A set value of the camera is acquired. 
	// The value to which the camera can be set is acquired.

	//load drive combo box
	//Sleep(5000);
	TCHAR szPath[MAX_PATH];
	strcpy_s(szPath, MAX_PATH, _T("?"));

	this->DlgDirListComboBox(szPath,IDC_COMBO10,0,DDL_DRIVES);
	SetDropDownHeight(&drivebox,drivebox.GetCount());
	//drivebox.SetCurSel(0);

	this->InitProgramSett();
	//this->InitPhotoSett();

  //auto define aspect ratio for currect photo device

  
  SetBigFont(&prefix);
  SetBigFont(&NumberT);
  SetBigFont(&prefix2T);
  SetBigFont(&current_page);
  SetBigFont(&PictureWidthT);
  SetBigFont(&PictureHeightT);

  //move to left size of the screen
  this->MoveWindow(20,20,380,800,1);
  
  LifeViewDlg=new CLifeViewDlg();
  LifeViewDlg->SetControl(this);
  LifeViewDlg->Create(IDD_DIALOG1,NULL);
  evfAFOff=1;
  //move invisible lifeview window to edge
  LifeViewDlg->MoveWindow(20+380+5,20,500,500,1);

  if(!mode_offline)
  {
	  setupListener(_controller);
	  setupObserver(getCameraModel());
    LifeViewDlg->setCameraController(this->_controller);

	  //Execute controller
	  _controller->run();
  }

	return TRUE;
}


void CCameraControlDlg::setupListener(ActionListener* listener)
{
	addActionListener(listener);
	
	_comboAEMode.setActionCommand("set_AEMode");
	_comboAEMode.addActionListener(listener);
	_comboTv.setActionCommand("set_Tv");
	_comboTv.addActionListener(listener);
	_comboAv.setActionCommand("set_Av");
	_comboAv.addActionListener(listener);
	_comboIso.setActionCommand("set_ISOSpeed");
	_comboIso.addActionListener(listener);
	_comboMeteringMode.addActionListener(listener);
	_comboExposureComp.setActionCommand("set_ExposureCompensation");
	_comboExposureComp.addActionListener(listener);
	_comboImageQuality.setActionCommand("set_ImageQuality");
	_comboImageQuality.addActionListener(listener);
	_comboEvfAFMode.setActionCommand("set_EvfAFMode");
	_comboEvfAFMode.addActionListener(listener);

	_btnTakePicture.setActionCommand("TakePicture");
	_btnTakePicture.addActionListener(listener);
	_btnStartEVF.setActionCommand("startEVF");
	_btnStartEVF.addActionListener(listener);
	_btnEndEVF.setActionCommand("endEVF");
	_btnEndEVF.addActionListener(listener);
	_btnFocusNear3.setActionCommand("focus_Near3");
	_btnFocusNear3.addActionListener(listener);
	_btnFocusNear2.setActionCommand("focus_Near2");
	_btnFocusNear2.addActionListener(listener);
	_btnFocusNear1.setActionCommand("focus_Near1");
	_btnFocusNear1.addActionListener(listener);
	_btnFocusFar3.setActionCommand("focus_Far3");
	_btnFocusFar3.addActionListener(listener);
	_btnFocusFar2.setActionCommand("focus_Far2");
	_btnFocusFar2.addActionListener(listener);
	_btnFocusFar1.setActionCommand("focus_Far1");
	_btnFocusFar1.addActionListener(listener);
	_btnFocusUp.setActionCommand("focus_Up");
	_btnFocusUp.addActionListener(listener);
	_btnFocusLeft.setActionCommand("focus_Left");
	_btnFocusLeft.addActionListener(listener);
	_btnFocusRight.setActionCommand("focus_Right");
	_btnFocusRight.addActionListener(listener);
	_btnFocusDown.setActionCommand("focus_Down");
	_btnFocusDown.addActionListener(listener);
	_btnZoomFit.setActionCommand("zoom_Fit");
	_btnZoomFit.addActionListener(listener);
	_btnZoomZoom.setActionCommand("zoom_Zoom");
	_btnZoomZoom.addActionListener(listener);
	_btnPressingHalfway.setActionCommand("pressingHalfway");
	_btnPressingHalfway.addActionListener(listener);
	_btnPressingCompletely.setActionCommand("pressingCompletely");
	_btnPressingCompletely.addActionListener(listener);
	_btnPressingOff.setActionCommand("pressingOff");
	_btnPressingOff.addActionListener(listener);
	_btnEvfAfON.setActionCommand("evfAFOn");
	_btnEvfAfON.addActionListener(listener);
	_btnEvfAfOFF.setActionCommand("evfAFOff");
	_btnEvfAfOFF.addActionListener(listener);

	LifeViewDlg->_pictureBox.setActionCommand("downloadEVF");
	LifeViewDlg->_pictureBox.addActionListener(listener);
}


void CCameraControlDlg::setupObserver(Observable* ob)
{
	ob->addObserver(static_cast<Observer*>(&_comboAEMode));
	ob->addObserver(static_cast<Observer*>(&_comboTv));
	ob->addObserver(static_cast<Observer*>(&_comboAv));
	ob->addObserver(static_cast<Observer*>(&_comboIso));
	ob->addObserver(static_cast<Observer*>(&_comboMeteringMode));
	ob->addObserver(static_cast<Observer*>(&_comboExposureComp));
	ob->addObserver(static_cast<Observer*>(&_comboImageQuality));
	ob->addObserver(static_cast<Observer*>(&LifeViewDlg->_pictureBox));
	ob->addObserver(static_cast<Observer*>(&_comboEvfAFMode));
	ob->addObserver(static_cast<Observer*>(&_btnZoomZoom));
}


void CCameraControlDlg::OnBnClickedOk()
{
  //SetNextFocus();
  //this means, "enter" button was pressed
}

void CCameraControlDlg::SetNextFocus()
{
  //navigate like "tab" key
   ::keybd_event(VK_TAB,MapVirtualKey(VK_TAB,0),0,0);
   ::keybd_event(VK_TAB,MapVirtualKey(VK_TAB,0),KEYEVENTF_KEYUP,0);
}

void CCameraControlDlg::OnBnClickedCancel()
{
  //OnCancel();
}

void CCameraControlDlg::OnClose()
{
	int z=MessageBox("Хотите ли вы сохранить текущие настройки перед выходом?","Сообщение",MB_YESNO);
  if(z==IDYES)
    OnBnClickedButton23();

  triggers.clear();
  hotkeys.clear();
  fireEvent("endEVF");
	fireEvent("closing");
	Lifeview.EnableWindow(FALSE);
	_btnTakePicture.EnableWindow(FALSE);	
	_progress.EnableWindow(FALSE);
	//_edit.EnableWindow(FALSE);
	_comboAEMode.EnableWindow(FALSE);
	_comboTv.EnableWindow(FALSE);
	_comboAv.EnableWindow(FALSE);
	_comboIso.EnableWindow(FALSE);	
	_comboImageQuality.EnableWindow(FALSE);	
	_btnPressingHalfway.EnableWindow(FALSE);	
	_btnPressingCompletely.EnableWindow(FALSE);	
	_btnPressingOff.EnableWindow(FALSE);	
	_comboEvfAFMode.EnableWindow(FALSE);	
	_btnEvfAfON.EnableWindow(FALSE);
	_btnEvfAfOFF.EnableWindow(FALSE);

  LifeViewDlg->CloseWindow();
  LifeViewDlg->DestroyWindow();
  delete(LifeViewDlg);
	//CWnd::OnClose();
  this->DestroyWindow();
  //exit(0);
}

void CCameraControlDlg::CheckFocusEnabled(Observable* from, CameraEvent *e)
{

  if(e->getArg()==NULL)
  {
    return;
  }
  EdsPropertyID propertyID=*(EdsPropertyID*)e->getArg();
  CameraModel* _model=getCameraModel();
  
	if(propertyID == kEdsPropID_Unknown)
  {
    return;
  }
		EdsDataType	dataType = kEdsDataType_Unknown;
		EdsUInt32   dataSize = 0;
		EdsError	err = EdsGetPropertySize(_model->getCameraObject(),
        propertyID,0,&dataType,&dataSize );
      
		if(err == EDS_ERR_OK)
		{
			if(dataType == kEdsDataType_FocusInfo)
      {
        
				EdsFocusInfo focusInfo;
				//Acquisition of the property
				err = EdsGetPropertyData( _model->getCameraObject(),
		propertyID,0,dataSize,&focusInfo );

				//Acquired property value is set
				if(err == EDS_ERR_OK)
				{
	        for(EdsUInt32 i = 0; i < focusInfo.pointNumber; i++)
	        {
		        if(focusInfo.focusPoint[i].valid==1)
            {
			        // Selecte Just Focus Pen
			        if(focusInfo.focusPoint[i].justFocus&1)
              {
                //focused=1;
                if(evfAFOff)
                  return;
                evfAFOff=1;
	              fireEvent("evfAFOff");
                shootbtn.EnableWindow(1);
                focusbtn.EnableWindow(1);
                return;
              }
            }
          }
        }
      }
      else
      {
        //MessageBox(NULL,"not focused",MB_OK);
      }
    }
return;
}


void CCameraControlDlg::update(Observable* from, CameraEvent *e)
{
  this->CheckFocusEnabled(from,e);
	std::string event = e->getEvent();
  
	if(event == "DownloadComplete")
	{
		//The update processing can be executed from another thread. 
		::PostMessage(this->m_hWnd, WM_USER_DOWNLOAD_COMPLETE, NULL, NULL);
	}

	//Progress of download of image
	if(event == "ProgressReport")
	{
		EdsInt32 percent = *static_cast<EdsInt32 *>(e->getArg());
		
		//The update processing can be executed from another thread. 
		::PostMessage(this->m_hWnd, WM_USER_PROGRESS_REPORT, percent, NULL);
	}

	//shutdown event
	if(event == "shutDown")
	{
		::PostMessage(this->m_hWnd, WM_CLOSE, 0, NULL);
	}
}


LRESULT CCameraControlDlg::OnDownloadComplete(WPARAM wParam, LPARAM lParam)
{
  CString data="";
  //AppendFormatedFileName(&data,"%projectdir%filedir %prefix%number");
  AppendFormatedFileName(&data,"%projectdir%filedir %prefix%number%prefix2%counter");
  
  /*
  tmp.Format(" %d %d",LifeViewDlg->_pictureBox.data.sizeJpegLarge.width,LifeViewDlg->_pictureBox.data.sizeJpegLarge.height);
  data.Append(tmp);*/
  data.Append(" ");
  CString tmp;
  PictureWidthT.GetWindowTextA(tmp);
  data.Append(tmp);
  data.Append(" ");
  PictureHeightT.GetWindowTextA(tmp);
  data.Append(tmp);
  CString filename="log.txt";
	FILE *stream;
	size_t  numwritten;
	if( fopen_s( &stream, filename, "a+t" ) == 0 )
	{
    unsigned int s=(unsigned int)data.GetLength();
	  numwritten = fwrite(data, sizeof(char),s, stream );
    s=1;
	  numwritten = fwrite("\n", sizeof(char),s, stream );
	  fclose( stream );
	}
	else
	  ShowError( "Problem opening the log file\n" );


	//End of download of image
	_progress.SetPos(0);

	
	//increment curent page
  if(AutoStepEnabled.GetCheck())
  {
	  current_page.GetWindowTextA(tmp);
	  int p=atoi(tmp.GetBuffer());

    CString tmp2;
    AutoStepT.GetWindowTextA(tmp2);
    p+=atoi(tmp2);
    tmp.Format("%d",p);
	  current_page.SetWindowTextA(tmp);
  }
  shootbtn.EnableWindow(1);
  shootbtn.SetFocus();

	return 0;
}

LRESULT CCameraControlDlg::OnProgressReport(WPARAM wParam, LPARAM lParam)
{
	_progress.SetPos((int)wParam);
	return 0;
}

void CCameraControlDlg::OnBnClickedCheck1()
{
  //enable / disable lifeview
	if(Lifeview.GetCheck())
  {
	  fireEvent("startEVF");
    LifeViewDlg->ShowWindow(SW_SHOW);
  }
	else
  {    
	  fireEvent("endEVF");
    LifeViewDlg->ShowWindow(SW_HIDE);
  }
}

void CCameraControlDlg::OnBnClickedButton19()
{
	//load settings
	CFileDialog dlg(TRUE/*Open=TRUE Save=False*/,NULL/*Filename Extension*/,""/*Initial Filename*/,OFN_ENABLESIZING|OFN_EXPLORER|OFN_FILEMUSTEXIST/*Flags*/,"XML(*.xml)|*.xml||"/*Filetype Filter*/,this/*parent Window*/);
	if (dlg.DoModal() == IDOK)
	{
		CString path=dlg.GetPathName();
		settings_file.SetWindowText(path.GetBuffer());
		this->InitPhotoSett();
	}
}

void CCameraControlDlg::OnBnClickedButton23()
{//save settings file
	
	CFileDialog dlg(FALSE/*Open=TRUE Save=False*/,NULL/*Filename Extension*/,"settings.xml"/*Initial Filename*/,OFN_ENABLESIZING|OFN_EXPLORER|OFN_FILEMUSTEXIST/*Flags*/,"XML(*.xml)|*.xml||"/*Filetype Filter*/,this/*parent Window*/);
	if (dlg.DoModal() == IDOK)
	{
		CString path=dlg.GetPathName();
		if(strcmp(path.Right(4).GetBuffer(),".xml"))
			path.Append(".xml");
		settings_file.SetWindowText(path.GetBuffer());
		this->SavePhotoSett(path.GetBuffer());
}
}



void CCameraControlDlg::InitPhotoSett()
{
  triggers.clear();
  hotkeys.clear();
	CString path;
	settings_file.GetWindowTextA(path);
	char* f=file_get_contents(path.GetBuffer(),0);
	if(f==NULL)
	{
		MessageBox("Файл настроек не найден, используются настройки по умолчанию!");
		return;
	}
	
	AllXml* xmlvec=new AllXml();
	xmlvec->Parse(f,"xml");
	delete[]f;
	xml* child=xmlvec->GetItemOnlyChild(xmlvec->MainElement,"xml",1);
  xml* trig=xmlvec->GetItemOnlyChild(child,"triggers",0);
  if(trig!=NULL)
  {
    int c=xmlvec->GetItemChildCount(trig);
    for(int i=0;i<c;i++)
    {
      xml* tr=xmlvec->GetItemChild(trig,i);
      xml* name=xmlvec->GetItemOnlyChild(tr,"name",1);
      xml* type=xmlvec->GetItemOnlyChild(tr,"type",1);
      xml* action=xmlvec->GetItemOnlyChild(tr,"action",1);
      trigger* NewTrigger=new trigger();
      NewTrigger->action=new char[strlen(action->subtext)+1];
      NewTrigger->name=new char[strlen(name->subtext)+1];
      strcpy_s(NewTrigger->action,strlen(action->subtext)+1,action->subtext);
      strcpy_s(NewTrigger->name,strlen(name->subtext)+1,name->subtext);
      NewTrigger->type=atoi(type->subtext);
      triggers.Add(NewTrigger);
    }
  }


  xml* hotk=xmlvec->GetItemOnlyChild(child,"hotkeys",0);
  if(hotk!=NULL)
  {
    int c=xmlvec->GetItemChildCount(hotk);
    for(int i=0;i<c;i++)
    {
      xml* h=xmlvec->GetItemChild(hotk,i);
      xml* KeyCode=xmlvec->GetItemOnlyChild(h,"keycode",1);
      xml* action=xmlvec->GetItemOnlyChild(h,"action",1);
      hotkey* NewHotkey=new hotkey();
      NewHotkey->action=new char[strlen(action->subtext)+1];
      strcpy_s(NewHotkey->action,strlen(action->subtext)+1,action->subtext);
      NewHotkey->KeyCode=atoi(KeyCode->subtext);
      hotkeys.Add(NewHotkey);
    }
  }

	child=xmlvec->GetItemOnlyChild(child,"settings",1);
	
	//Loading to select lists
  SetComboSett(&_comboAEMode,xmlvec->GetItemOnlyChild(child,"_comboAEMode",0)->subtext);
  _comboAEMode.OnSelChange();
  SetComboSett(&_comboTv,xmlvec->GetItemOnlyChild(child,"_comboTv",0)->subtext);
  _comboTv.OnSelChange();
  SetComboSett(&_comboAv,xmlvec->GetItemOnlyChild(child,"_comboAv",0)->subtext);
  _comboAv.OnSelChange();
  SetComboSett(&_comboIso,xmlvec->GetItemOnlyChild(child,"_comboIso",0)->subtext);
  _comboIso.OnSelChange();
  SetComboSett(&_comboMeteringMode,xmlvec->GetItemOnlyChild(child,"_comboMeteringMode",0)->subtext);
  _comboMeteringMode.OnSelChange();
  SetComboSett(&_comboExposureComp,xmlvec->GetItemOnlyChild(child,"_comboExposureComp",0)->subtext);
  _comboExposureComp.OnSelChange();
  SetComboSett(&_comboEvfAFMode,xmlvec->GetItemOnlyChild(child,"_comboEvfAFMode",0)->subtext);
  _comboEvfAFMode.OnSelChange();
  SetComboSett(&_comboImageQuality,xmlvec->GetItemOnlyChild(child,"_comboImageQuality",0)->subtext);
  _comboImageQuality.OnSelChange();

	Lifeview.SetCheck(atoi(xmlvec->GetItemOnlyChild(child,"Lifeview",0)->subtext));
	AutoStepEnabled.SetCheck(atoi(xmlvec->GetItemOnlyChild(child,"AutoStepEnabled",0)->subtext));
  CheckAutoStep();
//set drive if mapped
  SetComboSett(&drivebox,xmlvec->GetItemOnlyChild(child,"drivebox",0)->subtext);

	//set text values
	filedir.SetWindowTextA(xmlvec->GetItemOnlyChild(child,"filedir",0)->subtext);
	NumberT.SetWindowTextA(xmlvec->GetItemOnlyChild(child,"Number",0)->subtext);
	AutoStepT.SetWindowTextA(xmlvec->GetItemOnlyChild(child,"AutoStep",0)->subtext);
	prefix.SetWindowTextA(xmlvec->GetItemOnlyChild(child,"prefix",0)->subtext);
	prefix2T.SetWindowTextA(xmlvec->GetItemOnlyChild(child,"prefix2",0)->subtext);
	current_page.SetWindowTextA(xmlvec->GetItemOnlyChild(child,"current_page",0)->subtext);
	number_signs.SetWindowTextA(xmlvec->GetItemOnlyChild(child,"number_signs",0)->subtext);

	
	//Settings loaded. Now - update program settings
	CString SettText="<xml><program><DefaultSettFile>";
	SettText.Append(path);
	SettText.Append("</DefaultSettFile></program></xml>");
	file_put_contents("program_sett.xml",SettText.GetBuffer());

	//delete temporary objects
	delete(xmlvec);

	//update system events
	this->OnBnClickedCheck1();//enable or disable lifeview, according to options loaded
	
	
}
void CCameraControlDlg::InitProgramSett()
{
	char* z=GetApplicationDir();
	CString AppPath=z;
	delete []z;
	CString SettPath;
	SettPath=AppPath;
	SettPath.Append("program_sett.xml");
	char *f=file_get_contents(SettPath.GetBuffer(),0);
	if(f==NULL)//default program settings not found, making file...
	{
		CString sett="<xml><program><DefaultSettFile>";
		sett.Append(AppPath);
		sett.Append("default.xml");
		sett.Append("</DefaultSettFile></program></xml>");
		file_put_contents(SettPath.GetBuffer(),sett.GetBuffer());
		int l=sett.GetLength()+1;
		f=new char[l];
		strcpy_s(f,l,sett.GetBuffer());
		//SaveSett(SettPath.GetBuffer());
	}
	AllXml* xmlvec=new(AllXml);
	xmlvec->Parse(f,"xml");
	delete[] f;
	xml* child=xmlvec->GetItemOnlyChild(xmlvec->MainElement,"xml",1);
	child=xmlvec->GetItemOnlyChild(child,"program",1);
	child=xmlvec->GetItemOnlyChild(child,"DefaultSettFile",1);
	settings_file.SetWindowTextA(child->subtext);
	//this->SaveSett(child->subtext);
	delete(xmlvec);
}




void CCameraControlDlg::SavePhotoSett(char* path)
{
	//update photo settings
	CString SettText;
	SettText="<xml>";
	CString temp="";
  SettText.Append("<hotkeys>");
  for(int i=0;i<hotkeys.Count();i++)
  {
    temp.Format("<hotkey><action>%s</action><keycode>%d</keycode></hotkey>",hotkeys.GetAt(i)->action,hotkeys.GetAt(i)->KeyCode);
    SettText.Append(temp);
  }  
  SettText.Append("</hotkeys>");
  
  SettText.Append("<triggers>");
  for(int i=0;i<triggers.Count();i++)
  {
    temp.Format("<trigger><action>%s</action><name>%s</name><type>%d</type></trigger>",triggers.GetAt(i)->action,triggers.GetAt(i)->name,triggers.GetAt(i)->type);
    SettText.Append(temp);
  }  
  SettText.Append("</triggers>");

  SettText.Append("<settings>");
  GetComboSett(&_comboAEMode,"_comboAEMode",&SettText);
  GetComboSett(&_comboTv,"_comboTv",&SettText);
  GetComboSett(&_comboAv,"_comboAv",&SettText);
  GetComboSett(&_comboIso,"_comboIso",&SettText);
  GetComboSett(&_comboMeteringMode,"_comboMeteringMode",&SettText);
  GetComboSett(&_comboExposureComp,"_comboExposureComp",&SettText);
  GetComboSett(&_comboImageQuality,"_comboImageQuality",&SettText);
  GetComboSett(&_comboEvfAFMode,"_comboEvfAFMode",&SettText);
  if(Lifeview.GetCheck())
    SettText.Append("<Lifeview>1</Lifeview>");
  else
    SettText.Append("<Lifeview>0</Lifeview>");

  if(AutoStepEnabled.GetCheck())
    SettText.Append("<AutoStepEnabled>1</AutoStepEnabled>");
  else
    SettText.Append("<AutoStepEnabled>0</AutoStepEnabled>");
  GetComboSett(&drivebox,"drivebox",&SettText);
	
	SettText.Append("<filedir>");
	filedir.GetWindowTextA(temp);
	SettText.Append(temp);
	SettText.Append("</filedir>");
	
	SettText.Append("<AutoStep>");
	AutoStepT.GetWindowTextA(temp);
	SettText.Append(temp);
	SettText.Append("</AutoStep>");

	SettText.Append("<prefix>");
	prefix.GetWindowTextA(temp);
	SettText.Append(temp);
	SettText.Append("</prefix>");
	
	SettText.Append("<prefix2>");
	prefix2T.GetWindowTextA(temp);
	SettText.Append(temp);
	SettText.Append("</prefix2>");

	SettText.Append("<Number>");
	NumberT.GetWindowTextA(temp);
	SettText.Append(temp);
	SettText.Append("</Number>");
	
	SettText.Append("<current_page>");
	current_page.GetWindowTextA(temp);
	SettText.Append(temp);
	SettText.Append("</current_page>");

	SettText.Append("<number_signs>");
	number_signs.GetWindowTextA(temp);
	SettText.Append(temp);
	SettText.Append("</number_signs>");

	SettText.Append("</settings></xml>");
	file_put_contents(path,SettText.GetBuffer());

	//Settings saved. Now - update program settings
	
	SettText="<xml><program><DefaultSettFile>";
	SettText.Append(path);
	SettText.Append("</DefaultSettFile></program></xml>");
	char* p=GetApplicationDir();
	CString z=p;
	z.Append("program_sett.xml");
	delete(p);
	file_put_contents(z.GetBuffer(),SettText.GetBuffer());
}




void CCameraControlDlg::SelectFileDir()
{
	if(drivebox.GetCurSel()==-1)
	{
		MessageBox("Пожалуйста, выберите сначала диск для работы","Ошибка",MB_OK);
		return;
	}
  //set root folder you can't go up
	LPITEMIDLIST pidlRoot = NULL;
	PCWSTR temp;
	CString tmp;
  AppendFileNamePart(&tmp,"drive");
	#ifdef _UNICODE
		temp = LPCTSTR(tmp);
	#else
		USES_CONVERSION;
		temp = A2CW(LPCTSTR(tmp));
	#endif
	HRESULT hR= SHParseDisplayName(temp,0, &pidlRoot, 0, 0);


	TCHAR path[600];//more then MAX_path, just in case...
  //set begining path
  tmp="";
  AppendFormatedFileName(&tmp,"%drive%projectdir%filedir");
  BROWSEINFO bi;
	bi.hwndOwner = NULL;
	bi.pidlRoot = pidlRoot;
	bi.pszDisplayName = path;
	bi.lpszTitle = _T("Пожалуйста, выберите папку для сохранения фотографий");
	bi.ulFlags = BIF_USENEWUI+BIF_SHAREABLE; 
	bi.lpfn = BrowseForFolderCallback;
  bi.lParam = (LPARAM)tmp.GetBuffer();


  LPITEMIDLIST pidl = SHBrowseForFolder ( &bi );
  if ( pidl != 0 )//if folder selected
  {
    if ( SHGetPathFromIDList ( pidl, path ) )
    {
      tmp=path;
      tmp=tmp.Right(tmp.GetLength()-3);
	    filedir.SetWindowTextA(tmp);
    }
    else
	    MessageBox("Не получается получить путь к директории","Ошибка!",MB_OK);

        // free memory used
    IMalloc * imalloc = 0;
    if ( SUCCEEDED( SHGetMalloc ( &imalloc )) )
    {
      imalloc->Free ( pidl );
      imalloc->Release ( );
    }
  }
}


void CCameraControlDlg::AppendFormatedFileName(CString* to, char* format)
{
  CString tmp,tmp2;
  tmp=format;
	  AppendFileNamePart(&tmp2,"drive");
    tmp.Replace("%drive",tmp2);
    tmp2="";
	  AppendFileNamePart(&tmp2,"projectdir");
    tmp.Replace("%projectdir",tmp2);
    tmp2="";
	  AppendFileNamePart(&tmp2,"filedir");
    tmp.Replace("%filedir",tmp2);
    tmp2="";
	  AppendFileNamePart(&tmp2,"prefix2");
    tmp.Replace("%prefix2",tmp2);
    tmp2="";
	  AppendFileNamePart(&tmp2,"prefix");
    tmp.Replace("%prefix",tmp2);
    tmp2="";
	  AppendFileNamePart(&tmp2,"number");
    tmp.Replace("%number",tmp2);
    tmp2="";
	  AppendFileNamePart(&tmp2,"counter");
    tmp.Replace("%counter",tmp2);
    tmp2="";
	  AppendFileNamePart(&tmp2,"ext");
    tmp.Replace("%ext",tmp2);
    to->Append(tmp);
}

void CCameraControlDlg::AppendFileNamePart(CString * to,char* mode)
{
	//1 by default
	CString temp;
  if(!strcmp(mode,"drive"))
  {
	  drivebox.GetWindowTextA(temp);
	  temp=temp.GetAt(2);
	  temp.Append(":\\");
    to->Append(temp);
  }
  else if(!strcmp(mode,"projectdir"))
  {
	  projectdir.GetWindowTextA(temp);
	  if(temp.GetLength())
	  {
		  to->Append(temp);
		  to->Append("\\");
	  }
  }
  else if(!strcmp(mode,"filedir"))
	{
		filedir.GetWindowTextA(temp);
		if(temp.GetLength())
		{
			to->Append(temp);
			to->Append("\\");
		}
	}
  else if(!strcmp(mode,"prefix"))
	{
		prefix.GetWindowTextA(temp);
		to->Append(temp);
  }
  else if(!strcmp(mode,"prefix2"))
	{
		prefix2T.GetWindowTextA(temp);
		to->Append(temp);
  }
  else if(!strcmp(mode,"counter"))
  {
		current_page.GetWindowTextA(temp);
		if(temp.GetLength())
		{
			CString temp2;
			number_signs.GetWindowTextA(temp2);
			int nulls=atoi(temp2.GetBuffer());
			while(temp.GetLength()<nulls)
				temp.Insert(0,'0');
			to->Append(temp);
		}
  }
  else if(!strcmp(mode,"number"))
  {
		NumberT.GetWindowTextA(temp);
		to->Append(temp);
	}
  else if(!strcmp(mode,"ext"))
  {
    _comboImageQuality.GetWindowText(temp);
	  if(temp.Find("Jpeg")!=-1)
		  to->Append(".JPG");
	  else if(temp.Find("RAW")!=-1)
		  to->Append(".CR2");
	  else if(temp.Find("Raw")!=-1)
		  to->Append(".CR2");
  }
	return;
}


void CCameraControlDlg::Shoot()
{
	
	CString test;
  CString temp3;
	if(drivebox.GetCurSel()==-1)
	{
		MessageBox("Пожалуйста, выберите сначала диск для работы","Ошибка",MB_OK);
		return;
	}
	
  CString dir;
  AppendFormatedFileName(&dir,"%drive%projectdir%filedir");
	
  if(!DirectoryExists(dir.GetBuffer()))
	{
		CString msg;
		msg.Append("Директория '");
		msg.Append(dir);
		msg.Append("' не существует. Создать?");
		int n=MessageBox(msg,"Предупреждение",MB_OKCANCEL);
		if(n==IDCANCEL)
			return;
		else
		{
		int r=SHCreateDirectoryEx(NULL,dir,NULL);
		if(r==ERROR_SUCCESS)
			MessageBox("Директория успешно содана","Сообщение",MB_OK);
		else
		{
			MessageBox("Директорию создать не удалось. Проверьте доступность диска и права на запись","Сообщение",MB_OK);
			return;
		}
		}
	}
	CString fname;
  if(AutoStepEnabled.GetCheck())
    AppendFormatedFileName(&fname,"%drive%projectdir%filedir%prefix%number%prefix2%counter%ext");
  else
    AppendFormatedFileName(&fname,"%drive%projectdir%filedir%prefix%number%ext");
  filedir.SetFocus();

	if(FileExists(fname.GetBuffer()))
	{
		int n=MessageBox("Такой файл уже существует. Вы уверены, что хотите его перезаписать?","Предупреждение",MB_OKCANCEL);
		if(n==IDCANCEL)
			return;
	}
  PhotoSavePath="";//save here
  if(AutoStepEnabled.GetCheck())
    AppendFormatedFileName(&PhotoSavePath,"%drive%projectdir%filedir%prefix%number%prefix2%counter");//without ext
  else
    AppendFormatedFileName(&PhotoSavePath,"%drive%projectdir%filedir%prefix%number");//without ext
  shootbtn.EnableWindow(0);
	fireEvent("TakePicture");
  return;//trigger in beta mode

  trigger* tr=triggers.Find("OnShoot");
  if(tr!=NULL)
  {
    CString tmp;
    tmp=tr->action;
    this->AppendFormatedFileName(&tmp,tr->action);
    tr->run(tmp.GetBuffer());
  }
}



void CCameraControlDlg::FocusPhoto()
{
  if(evfAFOff==1)
  {
    shootbtn.EnableWindow(0);
    focusbtn.EnableWindow(0);
    fireEvent("evfAFOn");
    evfAFOff=0;
  }
}

void CCameraControlDlg::OpenFileDir()
{
    CString tmp;
    AppendFormatedFileName(&tmp,"%drive%projectdir%filedir");
    ShellExecute (NULL,"explore",tmp,NULL,NULL,SW_SHOWNORMAL);
}

void CCameraControlDlg::OnEnChangeEdit1()
{
  // prefix changed. set current page to 1
  current_page.SetWindowTextA("1");
}

void CCameraControlDlg::OnEnSetfocusEdit8()
{
 PictureWidthT.PostMessage(EM_SETSEL, 0, -1);
}

void CCameraControlDlg::OnEnSetfocusEdit9()
{
  PictureHeightT.PostMessage(EM_SETSEL, 0, -1);
}

void CCameraControlDlg::OnEnSetfocusEdit11()
{
  NumberT.PostMessage(EM_SETSEL, 0, -1);
}

void CCameraControlDlg::IncrementNumber()
{
  CString tmp;
  NumberT.GetWindowTextA(tmp);
  int l=tmp.GetLength();
  tmp.Format("%d",atoi(tmp)+1);
  while(tmp.GetLength()<l)
    tmp.Insert(0,"0");
  NumberT.SetWindowTextA(tmp);
  current_page.SetWindowTextA("1");
  PictureWidthT.SetFocus();
}

void CCameraControlDlg::DecrementNumber()
{
  CString tmp;
  NumberT.GetWindowTextA(tmp);
  int l=tmp.GetLength();
  tmp.Format("%d",atoi(tmp)-1);
  while(tmp.GetLength()<l)
    tmp.Insert(0,"0");
  NumberT.SetWindowTextA(tmp);
  current_page.SetWindowTextA("1");
  PictureWidthT.SetFocus();
}


void CCameraControlDlg::OnEnChangeNumber()
{
  current_page.SetWindowTextA("1");
}

void CCameraControlDlg::CheckAutoStep()
{
  //disable / enable auto step
  if(AutoStepEnabled.GetCheck())
  {
    current_page.EnableWindow(1);
    prefix2T.EnableWindow(1);
  }
  else
  {
    current_page.EnableWindow(0);
    prefix2T.EnableWindow(0);
  }
}

