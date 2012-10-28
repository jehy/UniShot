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
  //if(cx==0 && cy==0)
  //  return;
  if(nType!=SIZE_RESTORED)
    return;
  //we don't care about parameters - they are pretty fucked up in this callback
  if((HWND)_pictureBox==(HWND)NULL)//not yet created
    return;
  CRect rect;
  GetWindowRect(&rect);
  cy=rect.Height();
  cx=rect.Width();
  if(cx<200 || cy<200)
  {
    cx=500;
    cy=500;
  }
  //if(PrevSize.x==cx&& PrevSize.y==cy)
 //   return;


  //see what dimension changed more
  //and change it to neccesary aspect ratio

  if(abs(PrevSize.x-cx)>abs(PrevSize.y-cy))
    //if X changed more
    cy=(float)_pictureBox.data.sizeJpegLarge.height/(float)_pictureBox.data.sizeJpegLarge.width*(float)cx;
  else
    //if y changed more
    cx=(float)_pictureBox.data.sizeJpegLarge.width/(float)_pictureBox.data.sizeJpegLarge.height*(float)cy;

  
  if(PrevSize.y!=cy || PrevSize.x!=cx)
  {
    this->MoveWindow(rect.TopLeft().x,rect.TopLeft().y,cx,cy,1);
    _pictureBox.MoveWindow(0,0,cx,cy,1);
    //CDialog::OnSize(nType, cx, cy);
  }
  PrevSize.x=cx;
  PrevSize.y=cy;
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