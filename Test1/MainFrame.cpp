#include "MainFrame.h"
#include <wx/wx.h>

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
	wxPanel* panel = new wxPanel(this); // Make sure to update the IDs to something recognizable for ease of use later

	//wxButton* insert_button = new wxButton(panel, wxID_ANY, "Insert", wxPoint(306, 30), wxSize(40, 20));
	//wxButton* delete_button = new wxButton(panel, wxID_ANY, "Delete", wxPoint(352, 30), wxSize(40, 20));
	wxButton* modify_button = new wxButton(panel, wxID_ANY, "Modify", wxPoint(306, 29), wxSize(86, 22));

	//insert_button->Bind(wxEVT_BUTTON, &MainFrame::OnInsertButtonClicked, this);
	//delete_button->Bind(wxEVT_BUTTON, &MainFrame::OnDeleteButtonClicked, this);
	modify_button->Bind(wxEVT_BUTTON, &MainFrame::OnModifyButtonClicked, this);

	wxStaticText* SimpleCstatement = new wxStaticText(panel, wxID_ANY, "Simple C Statement", wxPoint(17, 10));
	wxTextCtrl* inputSimpleCstatement = new wxTextCtrl(panel, wxID_ANY, "string", wxPoint(17, 30), wxSize(200, 20));

	inputSimpleCstatement->Bind(wxEVT_TEXT, &MainFrame::OnInsertTextChanged, this);

	wxStaticText* LineNumber = new wxStaticText(panel, wxID_ANY, "Line Number", wxPoint(227, 10));
	wxTextCtrl* inputLineNumber = new wxTextCtrl(panel, wxID_ANY, "int", wxPoint(227, 30), wxSize(70, 20));

	inputLineNumber->Bind(wxEVT_TEXT, &MainFrame::OnLineNumberChanged, this);

	wxTextCtrl* outputCode = new wxTextCtrl(panel, wxID_ANY, "int main{\n\n\n\n}", wxPoint(17, 60), wxSize(375, 500));
	wxTextCtrl* outputAnomaly = new wxTextCtrl(panel, wxID_ANY, "No Anomalies detected.", wxPoint(17, 570), wxSize(375,100));

	CreateStatusBar();
}

/*void MainFrame::OnInsertButtonClicked(wxCommandEvent& evt) {
	wxLogStatus("Insert Button Clicked!");
}*/

/*void MainFrame::OnDeleteButtonClicked(wxCommandEvent& evt) {
	wxLogStatus("Delete Button Clicked!");
}*/

void MainFrame::OnModifyButtonClicked(wxCommandEvent& evt) {
	wxLogStatus("Modify Button Clicked!");
}

void MainFrame::OnInsertTextChanged(wxCommandEvent& evt) {
	wxLogStatus("Simple C Statement Inserted!");
}

void MainFrame::OnLineNumberChanged(wxCommandEvent& evt) {
	wxLogStatus("Line Number Inserted!");
}