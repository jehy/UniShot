/******************************************************************************
*                                                                             *
*   PROJECT : EOS Digital Software Development Kit EDSDK                      *
*      NAME : Av.h      	                                                  *
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

#include "PropertyComboBox.h"
#include "Observer.h"
#include "ActionSource.h"
// CAv

class CAv : public CPropertyComboBox, public ActionSource , public Observer  
{
	DECLARE_DYNAMIC(CAv)

public:
	CAv();
	virtual ~CAv();

	//observer
	virtual void update(Observable* from, CameraEvent *e);
	void OnSelChange();

protected:
	afx_msg LRESULT OnPropertyChanged(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnPropertyDescChanged(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};


