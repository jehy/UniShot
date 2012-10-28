#pragma once
#include "afxwin.h"
#include "resource.h"


#include "CameraControl.h"
#include "CameraControlDlg.h"
#include "EDSDK.h"
#include "EDSDKTypes.h"

// LifeViewDlg dialog

class CLifeViewDlg : public CDialog
{
	DECLARE_DYNAMIC(CLifeViewDlg)

public:
	CLifeViewDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLifeViewDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
  CEVFPictureBox _pictureBox;
  afx_msg void OnBnClickedOk();
  afx_msg void OnBnClickedCancel();
  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	void setCameraController(CameraController* controller){_controller = controller;}
protected:
	CameraController* _controller;
  CPoint PrevSize;
  int MouseState;
  CPoint FromPoint;
public:
  void SetControl(CCameraControlDlg* Control);
  CCameraControlDlg* Control;
  BOOL PreTranslateMessage(MSG* pMsg);
  //afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
