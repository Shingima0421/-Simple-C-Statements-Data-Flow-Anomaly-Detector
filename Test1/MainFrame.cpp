#include "MainFrame.h"
#include <wx/wx.h>
#include <vector>
#include <string>
#include "Task.h"

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
	CreateControls();
	BindEventHandlers();
	AddSavedTasks();
	wxMessageDialog dialog1(this, "Things to note when using the application:\n1. Please do not interact with the checkboxes\n2. Don't forget to press Save\n3. Have Fun!",
		"Simple C Anomaly Detector", wxOK);
	dialog1.ShowModal();
}

void MainFrame::CreateControls()
{
	panel = new wxPanel(this);

	inputTextHeader = new wxStaticText(panel, wxID_ANY, "Simple C Statement", wxPoint(17, 10));
	inputTextField = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(17, 30), wxSize(280, 20), wxTE_PROCESS_ENTER);
	clearButton = new wxButton(panel, wxID_ANY, "Clear", wxPoint(17, 675), wxSize(86, 22));
	modifyButton = new wxButton(panel, wxID_ANY, "Save", wxPoint(306, 29), wxSize(86, 22)); //changing modifyButton to saving function

	outputAnomaly = new wxTextCtrl(panel, wxID_ANY, "No Anomalies detected.", wxPoint(17, 570), wxSize(375, 100));
	outputBox = new wxCheckListBox(panel, wxID_ANY, wxPoint(17, 60), wxSize(375, 500));
}

void MainFrame::BindEventHandlers()
{
	modifyButton->Bind(wxEVT_BUTTON, &MainFrame::OnModifyButtonClicked, this);
	inputTextField->Bind(wxEVT_TEXT_ENTER, &MainFrame::OnInputEnter, this);
	outputBox->Bind(wxEVT_KEY_DOWN, &MainFrame::OnListKeyDown, this);
	clearButton->Bind(wxEVT_BUTTON, &MainFrame::OnClearButtonClicked, this);
}

void MainFrame::AddSavedTasks()
{
	std::vector<Code> codes = loadCodeFromFile("codes.txt");

	wxMessageDialog dialog(this, "Hi?",
		"Hi!", wxOK);

	for (const Code& code : codes) {
		int index = outputBox->GetCount();
		outputBox->Insert(code.description, index);
		outputBox->Check(index, 0); //all check_boxes should be empty since they will only be used to check for anomaly
	}
}

void MainFrame::OnModifyButtonClicked(wxCommandEvent& evt) //change modify button to save button so that when pressed, 												  
{														   //it will save all the code to the text file, rather than only when it closes
	AddCodeToFile();
}

void MainFrame::OnInputEnter(wxCommandEvent& evt)
{
	AddCodeFromInput();
	AddCodeToFile(); //so when user presses "enter" it also saves and adds the parsed function
}

void MainFrame::OnListKeyDown(wxKeyEvent& evt)
{
	switch (evt.GetKeyCode()) {
		case WXK_DELETE:
			DeleteSelectedTask();
			break;
		case WXK_UP:
			MoveSelectedCode(-1);
			break;
		case WXK_DOWN:
			MoveSelectedCode(1);
			break;
	}
}

void MainFrame::OnClearButtonClicked(wxCommandEvent& evt)
{
	if (outputBox->IsEmpty()) {
		return;
	}

	wxMessageDialog dialog(this, "Do you want to clear all code?", 
		"Clear", wxYES_NO | wxCANCEL);

	int result = dialog.ShowModal();

	if (result == wxID_YES) {
		outputBox->Clear();
	}
}

void MainFrame::DeleteSelectedTask()
{
	int selectedIndex = outputBox->GetSelection();

	if (selectedIndex == wxNOT_FOUND) {
		return;
	}

	outputBox->Delete(selectedIndex);
}

void MainFrame::AddCodeFromInput()
{
	wxString code = inputTextField->GetValue();

	if (!code.IsEmpty()) {
		outputBox->Insert(code, outputBox->GetCount());
		inputTextField->Clear();
	}

	inputTextField->SetFocus();
}

void MainFrame::AddCodeToFile()
{
	std::vector<Code> codes;

	for (int i = 0; i < outputBox->GetCount(); i++) {
		Code code;
		code.description = outputBox->GetString(i);
		code.done = outputBox->IsChecked(i);
		codes.push_back(code);
	}

	saveCodeToFile(codes, "codes.txt", "test.txt"); //add extra file here
}

void MainFrame::MoveSelectedCode(int offset)
{
	int selectedIndex = outputBox->GetSelection();
	if (selectedIndex == wxNOT_FOUND) {
		return;
	}

	int newIndex = selectedIndex + offset;

	if (newIndex >= 0 && newIndex < outputBox->GetCount()) {
		SwapCode(selectedIndex, newIndex);
		outputBox->SetSelection(newIndex, true);
	}
}

void MainFrame::SwapCode(int i, int j)
{
	Code codeI{ outputBox->GetString(i).ToStdString(), outputBox->IsChecked(i) };
	Code codeJ{ outputBox->GetString(j).ToStdString(), outputBox->IsChecked(j) };

	outputBox->SetString(i, codeJ.description);
	outputBox->Check(i, codeJ.done);

	outputBox->SetString(j, codeI.description);
	outputBox->Check(j, codeI.done);
}