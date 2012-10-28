// LifeViewDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CLifeViewDlg.h"


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
  ON_BN_CLICKED(IDOK, &CLifeViewDlg::OnBnClickedOk)
  ON_BN_CLICKED(IDCANCEL, &CLifeViewDlg::OnBnClickedCancel)
  ON_WM_SIZE()
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
  CDialog::OnSize(nType, cx, cy);

  CRect rect;
  GetWindowRect(&rect);
  _pictureBox.MoveWindow(0,0,rect.right,rect.bottom,1);
}
