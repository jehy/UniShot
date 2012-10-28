/******************************************************************************
*                                                                             *
*   PROJECT : EOS Digital Software Development Kit EDSDK                      *
*      NAME : CameraControlDlg.h                                              *
*                                                                             *
*   Description: This is the Sample code to show the usage of EDSDK.          *
*                                                                             *
*                                                                             *
*******************************************************************************
*                                                                             *
*   Written and developed by Camera Design Dept.53                            *
*   Copyright Canon Inc. 2006-2008 All Rights Reserved                        *
*                                                                             *
*******************************************************************************/

#pragma once

#include <map>
#include "Observer.h"
#include "CameraController.h"


#include "AEMode.h"
#include "Tv.h"
#include "Av.h"
#include "Iso.h"
#include "MeteringMode.h"
#include "ExposureComp.h"
#include "ImageQuality.h"
#include "EVFPictureBox.h"
#include "EvfAFMode.h"

#include "ActionButton.h"
#include "EvfZoomButton.h"
#include "afxwin.h"
#include "trigger.h"

// CCameraControlDlg Dialog
class CCameraControlDlg : public CDialog, public ActionSource, public Observer
{
public://jehy
	void SavePhotoSett(char* path);
  void AppendFormatedFileName(CString* to, char* format);
	void InitProgramSett();
	void InitPhotoSett();
  trigger* OnShoot;
	
// Construction
private:
	void setupListener(ActionListener* listener);
	void setupObserver(Observable* ob);
	void changeEnableWindow();

public:
	CCameraControlDlg(CWnd* pParent = NULL);	// standard constructor
	void setCameraController(CameraController* controller){_controller = controller;}


public:
	// Observer 
	virtual void update(Observable* from, CameraEvent *e);

	//Dialog data
	enum { IDD = IDD_CAMERACONTROL_DIALOG };
	
	CActionButton	_btnTakePicture;
	CActionButton	_btnStartEVF;
	CActionButton	_btnEndEVF;
	CActionButton	_btnFocusNear3;
	CActionButton	_btnFocusNear2;
	CActionButton	_btnFocusNear1;
	CActionButton	_btnFocusFar3;
	CActionButton	_btnFocusFar2;
	CActionButton	_btnFocusFar1;
	CActionButton	_btnFocusUp;
	CActionButton	_btnFocusDown;
	CActionButton	_btnFocusLeft;
	CActionButton	_btnFocusRight;
	CActionButton	_btnZoomFit;
	CEvfZoomButton	_btnZoomZoom;
	CProgressCtrl	_progress;
	CEdit			_edit;
	//CEVFPictureBox	_pictureBox;
	CAEMode			_comboAEMode;
	CTv				_comboTv;
	CAv				_comboAv;
	CIso			_comboIso;
	CMeteringMode	_comboMeteringMode;
	CExposureComp	_comboExposureComp;
	CImageQuality	_comboImageQuality;
	CActionButton	_btnPressingHalfway;
	CActionButton	_btnPressingCompletely;
	CActionButton	_btnPressingOff;
	CEvfAFMode		_comboEvfAFMode;
	CActionButton	_btnEvfAfON;
	CActionButton	_btnEvfAfOFF;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnDownloadComplete(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnProgressReport(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

protected:
	CameraController* _controller;

public:
	afx_msg void OnClose();
	CButton Lifeview;
	afx_msg void OnBnClickedCheck1();
	CComboBox drivebox;
	afx_msg void OnBnClickedButton19();
	afx_msg void OnBnClickedButton23();
	CEdit settings_file;
	CEdit filedir;
	afx_msg void OnBnClickedButton24();
//	afx_msg void OnBnClickedButton1();
  void AppendFileNamePart(CString * to,char* mode);

	CEdit projectdir;
	afx_msg void OnBnClickedButton26();
	CButton shootbtn;
	CEdit prefix;
	CEdit current_page;
	CEdit number_signs;
	//afx_msg void OnBnClickedButton27();  
  void CheckFocusEnabled(Observable* from, CameraEvent *e);
  void GetComboSett(CComboBox* combo,char*name,CString* SettText);
  void SetComboSett(CComboBox* combo,char* val);
	//CEdit state;
//  afx_msg void OnBnClickedButton22();
  //afx_msg void OnSize(UINT nType, int cx, int cy);
  //CEdit _edit;
//  afx_msg void OnBnClickedButton21();
  afx_msg void OnBnClickedButton27();
  CButton focusbtn;
  bool evfAFOff;
  afx_msg void OnBnClickedButton28();
  afx_msg void OnEnChangeEdit1();
  CEdit PictureWidthT;
  CEdit PictureHeightT;
};
