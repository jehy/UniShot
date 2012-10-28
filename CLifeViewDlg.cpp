// LifeViewDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CLifeViewDlg.h"



#include "EDSDK.h"
#include "CameraModel.h"
#include "Processor.h"

#include "ActionListener.h"
#include "ActionEvent.h"

int MouseState=0;
CPoint FromPoint;
// LifeViewDlg dialog

IMPLEMENT_DYNAMIC(CLifeViewDlg, CDialog)

CLifeViewDlg::CLifeViewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLifeViewDlg::IDD, pParent)
{

}

CLifeViewDlg::~CLifeViewDlg()
{
}

void CLifeViewDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_PICT, _pictureBox);
}


BEGIN_MESSAGE_MAP(CLifeViewDlg, CDialog)
  //ON_BN_CLICKED(IDOK, &CLifeViewDlg::OnBnClickedOk)
  //ON_BN_CLICKED(IDCANCEL, &CLifeViewDlg::OnBnClickedCancel)
  ON_WM_SIZE()
  ON_WM_LBUTTONDOWN()
  ON_WM_LBUTTONUP()
//  ON_WM_NCMOUSEMOVE()
END_MESSAGE_MAP()


// LifeViewDlg message handlers

/*void CLifeViewDlg::OnBnClickedOk()
{
  //OnOK();
}

void CLifeViewDlg::OnBnClickedCancel()
{
  //OnCancel();
}*/

void CLifeViewDlg::OnSize(UINT nType, int cx, int cy)
{
  CDialog::OnSize(nType, cx, cy);

  CRect rect;
  GetWindowRect(&rect);
  _pictureBox.MoveWindow(0,0,rect.right,rect.bottom,1);
}

void CLifeViewDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
  MouseState=1;
  FromPoint=point;
  CDialog::OnLButtonDown(nFlags, point);
}

void CLifeViewDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
  MouseState=0;
  FromPoint.x=point.x-FromPoint.x;
  FromPoint.y=point.y-FromPoint.y;
  
  CRect rect;
  GetWindowRect(&rect);
  FromPoint.x/=rect.right;
  FromPoint.y/=rect.bottom;
  

	const int stepY = 128;
	const int stepX = 128;
  CameraModel* _model=getCameraModel();
	EdsPoint newpoint = _model->getEvfZoomPosition();

  
	newpoint.x -= FromPoint.x;
	newpoint.y -= FromPoint.y;
	if(newpoint.y < 0) newpoint.y = 0;
  this->_controller->StoreAsync(new SetPropertyCommand<EdsPoint>(_model, kEdsPropID_Evf_ZoomPosition, newpoint));			


  //CString xx;
  //xx.Format("%d; %d",FromPoint.x,FromPoint.y);
  //MessageBox(xx);


  /*
  
  
		if ( command == "focus_Up" || command == "focus_Down")
		{
			const int stepY = 128;

			EdsPoint point = _model->getEvfZoomPosition();
			if ( command == "focus_Up")
			{
				point.y -= stepY;
				if(point.y < 0) point.y = 0;
			}
			if ( command == "focus_Down") point.y += stepY;
			StoreAsync(new SetPropertyCommand<EdsPoint>(_model, kEdsPropID_Evf_ZoomPosition, point));			
		}
		

		if ( command == "focus_Left" || command == "focus_Right")
		{
			const int stepX = 128;

			EdsPoint point = _model->getEvfZoomPosition();
			if(command == "focus_Left")
			{
				point.x -= stepX;
				if(point.x < 0) point.x = 0;
			}
			if(command == "focus_Right")point.x += stepX;
			StoreAsync(new SetPropertyCommand<EdsPoint>(_model, kEdsPropID_Evf_ZoomPosition, point));			
		}

  
  */




  CDialog::OnLButtonUp(nFlags, point);
}

