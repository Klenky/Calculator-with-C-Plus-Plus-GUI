#pragma once
#include <wx/wx.h>


class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);

private:
	wxTextCtrl* inputText;

	void OnNumberButton(wxCommandEvent& event);
	void OnOperationsButton(wxCommandEvent& event);
	void OnEqualButton(wxCommandEvent& event);
	bool EvaluateExpression(const wxString& expression, double& result);
	void OnClearButton(wxCommandEvent& event);
};

