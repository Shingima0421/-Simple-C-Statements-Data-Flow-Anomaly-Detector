#pragma once
#include <wx/wx.h>

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);
private:
	void CreateControls();
	void BindEventHandlers();
	//void AddSavedTasks();

	void OnModifyButtonClicked(wxCommandEvent& evt);
	//void OnInputEnter(wxCommandEvent& evt);
	//void OnListKeyDown(wxKeyEvent& evt);
	void OnClearButtonClicked(wxCommandEvent& evt);
	void OnSaveButtonClicked(wxCommandEvent& evt);

	//void DeleteSelectedTask();
	//void AddCodeFromInput();
	void AddCodeToFile();
	//void MoveSelectedCode(int offset);
	//void SwapCode(int i, int j);

	wxPanel* panel;
	wxStaticText* inputTextHeader;
	wxTextCtrl* inputTextField;
	wxTextCtrl* outputAnomaly;
	wxTextCtrl* outputBox;
	wxButton* modifyButton;
	wxButton* saveButton;
	wxButton* clearButton;
};