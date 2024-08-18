#include "MainFrame.h"
#include <wx/wx.h>
#include <vector>
#include <filesystem>
#include <string>
#include <sstream>
#include "Task.h"

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
	CreateControls();
	BindEventHandlers();
	//AddSavedTasks();
	wxMessageDialog dialog1(this, "Things to note when using the application:\n1. Please check for any syntax errors\n2. Press SAVE before you press the CHECK button\n3. Use the CLEAR button to clear all codes\n4. Have Fun!",
		"Simple C Anomaly Detector", wxOK);
	dialog1.ShowModal();
}

void MainFrame::CreateControls()
{
	panel = new wxPanel(this);

	inputTextHeader = new wxStaticText(panel, wxID_ANY, "Anomaly Detector", wxPoint(220, 32));
	//inputTextField = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(17, 30), wxSize(280, 20), wxTE_PROCESS_ENTER);
	clearButton = new wxButton(panel, wxID_ANY, "Clear", wxPoint(17, 675), wxSize(86, 22));
	modifyButton = new wxButton(panel, wxID_ANY, "Check", wxPoint(110, 29), wxSize(86, 22)); //changing modifyButton to saving function
	saveButton = new wxButton(panel, wxID_ANY, "Save", wxPoint(17, 29), wxSize(86, 22)); //changing modifyButton to saving function

	outputAnomaly = new wxTextCtrl(panel, wxID_ANY, "No Anomalies detected.", wxPoint(17, 569), wxSize(375, 100), wxTE_READONLY | wxTE_MULTILINE);
	outputBox = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(17, 60), wxSize(375, 500), wxTE_MULTILINE);
}

void MainFrame::BindEventHandlers()
{
	
	//inputTextField->Bind(wxEVT_TEXT_ENTER, &MainFrame::OnInputEnter, this);
	//outputBox->Bind(wxEVT_KEY_DOWN, &MainFrame::OnListKeyDown, this);
	modifyButton->Bind(wxEVT_BUTTON, &MainFrame::OnModifyButtonClicked, this); 
	clearButton->Bind(wxEVT_BUTTON, &MainFrame::OnClearButtonClicked, this); //no problems
	saveButton->Bind(wxEVT_BUTTON, &MainFrame::OnSaveButtonClicked, this); //need fix
}

/*void MainFrame::AddSavedTasks()
{
	std::vector<Code> codes = loadCodeFromFile("codes.txt");

	for (const Code& code : codes) {
		//int index = outputBox->GetCount();
		//outputBox->Insert(code.description, index);
		//outputBox->Check(index, 0); //all check_boxes should be empty since they will only be used to check for anomaly
	}
}*/

void MainFrame::OnModifyButtonClicked(wxCommandEvent& evt) //update modify button to call Koko's function											  
{	
	std::string errorMessage = loadCodeFromFile("error.txt", "lineNumbers.txt");
	outputAnomaly->Clear();
	outputAnomaly->WriteText(errorMessage);
}

/*void MainFrame::OnInputEnter(wxCommandEvent& evt)
{
	AddCodeFromInput();
	AddCodeToFile(); //so when user presses "enter" it also saves and adds the parsed function
}*/

/*void MainFrame::OnListKeyDown(wxKeyEvent& evt)
{
	switch (evt.GetKeyCode()) {
		case WXK_DELETE:
			DeleteSelectedTask();
			AddCodeToFile();
			break;
		case WXK_UP:
			MoveSelectedCode(-1);
			AddCodeToFile();
			break;
		case WXK_DOWN:
			MoveSelectedCode(1);
			AddCodeToFile();
			break;
	}
}*/

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
		outputAnomaly->Clear();
	}

	AddCodeToFile();
}

void MainFrame::OnSaveButtonClicked(wxCommandEvent& evt)
{
	AddCodeToFile();
}

/*void MainFrame::DeleteSelectedTask()
{
	int selectedIndex = outputBox->GetSelection();

	if (selectedIndex == wxNOT_FOUND) {
		return;
	}

	outputBox->Delete(selectedIndex);
}*/

/*void MainFrame::AddCodeFromInput()
{
	wxString code = inputTextField->GetValue();

	if (!code.IsEmpty()) {
		//outputBox->Insert(code, outputBox->GetCount());
		inputTextField->Clear();
	}

	//inputTextField->SetFocus();
}*/

void MainFrame::AddCodeToFile()
{
	wxString codes = outputBox->GetValue();
	std::string code = std::string(codes.mb_str());

	saveCodeToFile(code, "codes.txt", "test.txt", "lineNumbers.txt");
}

/*void MainFrame::MoveSelectedCode(int offset)
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
}*/

/*void MainFrame::SwapCode(int i, int j)
{
	Code codeI{ outputBox->GetString(i).ToStdString(), outputBox->IsChecked(i) };
	Code codeJ{ outputBox->GetString(j).ToStdString(), outputBox->IsChecked(j) };

	outputBox->SetString(i, codeJ.description);
	outputBox->Check(i, codeJ.done);

	outputBox->SetString(j, codeI.description);
	outputBox->Check(j, codeI.done);
}*/