#include "stdafx.h"
#include "CLifeViewDlg.h"
#include "CameraControlDlg.h"


// LifeViewDlg dialog

IMPLEMENT_DYNAMIC(CLifeViewDlg, CDialog)


BOOL CLifeViewDlg::PreTranslateMessage(MSG* pMsg) 
{
  //catch hotkeys
  if(pMsg->message==WM_KEYDOWN)
  {
    this->Control->SetFocus();
    this->Control->PreTranslateMessage(pMsg);
  }
  return CDialog::PreTranslateMessage(pMsg);
}

CLifeViewDlg::CLifeViewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLifeViewDlg::IDD, pParent)
{
  MouseState=0;
  PrevSize.x=0;
  PrevSize.y=0;
}

CLifeViewDlg::~CLifeViewDlg()
{
}

void CLifeViewDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_PICT, _pictureBox);
}

void CLifeViewDlg::SetControl(CCameraControlDlg* Control)
{
  this->Control=Control;
}

/*
BOOL CLifeViewDlg::OnInitDialog()
{
  this->OnSize(0,500,500);
  return 1;
}*/

BEGIN_MESSAGE_MAP(CLifeViewDlg, CDialog)
  ON_BN_CLICKED(IDOK, &CLifeViewDlg::OnBnClickedOk)
  ON_BN_CLICKED(IDCANCEL, &CLifeViewDlg::OnBnClickedCancel)
  ON_WM_SIZE()
  ON_WM_LBUTTONDOWN()
  ON_WM_RBUTTONDOWN()
  ON_WM_ACTIVATE()
  ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

// LifeViewDlg message handlers

void CLifeViewDlg::OnBnClickedOk()
{
  //OnOK();
}

void CLifeViewDlg::OnBnClickedCancel()
{
  //OnCancel();
}

void CLifeViewDlg::OnSize(UINT nType, int cx, int cy)
{
  if(nType!=SIZE_RESTORED)
    return;
  //we don't care about parameters - they are pretty fucked up in this callback. Scrollbars and everything else affects cx and cy. Better to take client area size.
  if((HWND)_pictureBox==(HWND)NULL)//not yet created
    return;
  CRect rect;
  //this->CalcWindowRect(&rect,CWnd::adjustBorder);
  //_pictureBox.GetWindowRect(&rect);
  this->GetWindowRect(&rect);
  cy=rect.Height();
  cx=rect.Width();

  if(cx<200 || cy<200)// if it was accidentially created or resized too little
  {
    cx=500;
    cy=500;
  }

  //see what dimension changed more
  //and change it to neccesary aspect ratio


  
  if(PrevSize.y!=cy || PrevSize.x!=cx)
  {

    if(abs(PrevSize.x-cx)>abs(PrevSize.y-cy))
      //if X changed more
      cy=(float)_pictureBox.data.sizeJpegLarge.height/(float)_pictureBox.data.sizeJpegLarge.width*(float)cx;
    else
      //if y changed more
      cx=(float)_pictureBox.data.sizeJpegLarge.width/(float)_pictureBox.data.sizeJpegLarge.height*(float)cy;


    CRect WndRect;
    WndRect.SetRect(0,0,cx,cy);
    this->CalcWindowRect(&WndRect,CWnd::adjustOutside);

    PrevSize.x=WndRect.Width();
    PrevSize.y=WndRect.Height();
    
    _pictureBox.SetWindowPos(NULL, 0, 0,cx,cy,SWP_NOZORDER);
    this->
SetWindowPos(NULL, rect.TopLeft().x,rect.TopLeft().y,WndRect.Width(),WndRect.Height(), SWP_NOMOVE | SWP_NOZORDER);
    //_pictureBox.MoveWindow(0,0,cx,cy,1);
    //this->MoveWindow(rect.TopLeft().x,rect.TopLeft().y,WndRect.Width(),WndRect.Height(),1);
    //this->SetWindowPos(NULL, rect.TopLeft().x, rect.TopLeft().y, cx, cy, SWP_NOMOVE | SWP_NOZORDER);
    //CDialog::OnSize(nType, cx, cy);
  }
}

void CLifeViewDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
  //MouseState=1;
  //FromPoint=point;

  float x,y;
  EdsPoint NewPoint;

  x=point.x;
  y=point.y;

  CRect rect;
  GetWindowRect(&rect);

  x/=rect.Width();
  y/=rect.Height();

  x*=_pictureBox.data.sizeJpegLarge.width;
  y*=_pictureBox.data.sizeJpegLarge.height;

  x-=_pictureBox.data.sizeJpegLarge.width/10.0;
  y-=_pictureBox.data.sizeJpegLarge.height/10.0;

  NewPoint.x=x;
  NewPoint.y=y;

  CameraModel* _model=getCameraModel();
  //EdsFocusInfo xxx = _model->getFocusInfo().;
  this->_controller->StoreAsync(new SetPropertyCommand<EdsPoint>(_model, kEdsPropID_Evf_ZoomPosition, NewPoint));

  
  if(this->Control->evfAFOff==1)
    this->Control->FocusPhoto();
  this->Control->SetFocus();
}

void CLifeViewDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
  this->Control->Shoot();
  this->Control->SetFocus();
}



void CLifeViewDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
  if(PrevSize.x==0 && PrevSize.y==0)
    this->OnSize(0,500,500);
  CDialog::OnShowWindow(bShow, nStatus);
}/*
void CLifeViewDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
  CDialog::OnActivate(nState, pWndOther, bMinimized);
}
*/