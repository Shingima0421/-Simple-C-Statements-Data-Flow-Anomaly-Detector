#pragma once
#include <wx/wx.h>

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);
private:
	void CreateControls();
	void BindEventHandlers();

	void OnModifyButtonClicked(wxCommandEvent& evt);

	void AddCodeFromInput();

	wxPanel* panel;
	wxStaticText* inputTextHeader;
	wxStaticText* inputLineHeader;
	wxTextCtrl* inputTextField;
	wxTextCtrl* inputLineField;
	wxTextCtrl* outputAnomaly;
	wxTextCtrl* outputBox;
	wxButton* modifyButton;
	wxButton* clearButton;
};