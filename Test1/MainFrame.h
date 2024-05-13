#pragma once
#include <wx/wx.h>

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);

	//void OnInsertButtonClicked(wxCommandEvent& evt);
	//void OnDeleteButtonClicked(wxCommandEvent& evt);
	void OnModifyButtonClicked(wxCommandEvent& evt);
	void OnInsertTextChanged(wxCommandEvent& evt);
	void OnLineNumberChanged(wxCommandEvent& evt);
};