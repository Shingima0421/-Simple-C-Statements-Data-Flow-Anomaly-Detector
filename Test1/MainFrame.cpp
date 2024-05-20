#include "MainFrame.h"
#include <wx/wx.h>
#include <vector>
#include <string>
#include "Task.h"

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
	CreateControls();
	BindEventHandlers();
}

void MainFrame::CreateControls()
{
	panel = new wxPanel(this);

	inputTextHeader = new wxStaticText(panel, wxID_ANY, "Simple C Statement", wxPoint(17, 10));
	inputLineHeader = new wxStaticText(panel, wxID_ANY, "Line Number", wxPoint(227, 10));

	inputTextField = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(17, 30), wxSize(200, 20));
	inputLineField = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(227, 30), wxSize(70, 20));
	clearButton = new wxButton(panel, wxID_ANY, "Clear", wxPoint(17, 675), wxSize(86, 22));
	modifyButton = new wxButton(panel, wxID_ANY, "Modify", wxPoint(306, 29), wxSize(86, 22));

	outputAnomaly = new wxTextCtrl(panel, wxID_ANY, "No Anomalies detected.", wxPoint(17, 570), wxSize(375, 100));
	outputBox = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(17, 60), wxSize(375, 500), wxTE_READONLY | wxTE_MULTILINE);


}

void MainFrame::BindEventHandlers()
{
	modifyButton->Bind(wxEVT_BUTTON, &MainFrame::OnModifyButtonClicked, this);
}

void MainFrame::OnModifyButtonClicked(wxCommandEvent& evt)
{
	AddCodeFromInput();
}

void MainFrame::AddCodeFromInput()
{
	wxString code = inputTextField->GetValue();
	wxString line = inputLineField->GetValue();
	int lineNumber = wxAtoi(line);

	if (!code.IsEmpty()) {

		//how to get position of insertion, so that write text can write there!
		outputBox->WriteText(code);
		outputBox->WriteText('\n');
		inputTextField->Clear();
		inputLineField->Clear();
	}

	inputTextField->SetFocus();
}
