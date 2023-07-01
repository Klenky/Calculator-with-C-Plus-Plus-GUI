#include "MainFrame.h"
#include <wx/wx.h>
#include <string>
#include <sstream>

using namespace std;

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
	// panel to fit buttons and text to
	wxPanel* panel = new wxPanel(this);

	//Text to display user's input and results
	inputText = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxPoint(10, 10), wxSize(270, 40), wxTE_READONLY | wxTE_RIGHT);
	inputText->SetFont(wxFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

	//Create number buttons
	//Buttons listed in array as they are on a num pad
	const wxString numbers[] = { "7", "8", "9", "4", "5", "6", "1", "2", "3", "0" };
	wxButton* numberButtons[10];
	int xPos = 10;
	int yPos = 60;
	for (int i = 0; i < 10; i++)
	{
		numberButtons[i] = new wxButton(panel, 1000 + i, numbers[i], wxPoint(xPos, yPos), wxSize(50, 50));
		xPos += 60;
		if (i % 3 == 2)
		{
			xPos = 10;
			yPos += 60;
		}
		numberButtons[i]->Bind(wxEVT_BUTTON, &MainFrame::OnNumberButton, this);
	}

	//Create the operations buttons
	const wxString operations[] = { "+", "-", "*", "/" };
	wxButton* operationButtons[4];
	xPos = 190;
	yPos = 60;
	for (int i = 0; i < 4; i++)
	{
		operationButtons[i] = new wxButton(panel, 1100 + i, operations[i], wxPoint(xPos, yPos), wxSize(50, 50));
		yPos += 60;
		operationButtons[i]->Bind(wxEVT_BUTTON, &MainFrame::OnOperationsButton, this);
	}

	//Create the equal button
	wxButton* equalButton = new wxButton(panel, wxID_ANY, "=", wxPoint(250, 180), wxSize(50, 110));
	equalButton->SetFont(wxFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	equalButton->Bind(wxEVT_BUTTON, &MainFrame::OnEqualButton, this);

	//Create a clear button
	wxButton* clearButton = new wxButton(panel, wxID_ANY, "C", wxPoint(250, 60), wxSize(50, 110));
	clearButton->SetFont(wxFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	clearButton->Bind(wxEVT_BUTTON, &MainFrame::OnClearButton, this);

	
}

void MainFrame::OnNumberButton(wxCommandEvent& event)
{
	wxButton* button = static_cast<wxButton*>(event.GetEventObject());
	wxString buttonText = button->GetLabel();
	inputText->SetValue(inputText->GetValue() + buttonText);
}

void MainFrame::OnOperationsButton(wxCommandEvent& event)
{
	wxButton* button = static_cast<wxButton*>(event.GetEventObject());
	wxString buttonText = button->GetLabel();
	inputText->SetValue(inputText->GetValue() + buttonText);
}

void MainFrame::OnEqualButton(wxCommandEvent& event)
{
	wxString expression = inputText->GetValue();
	
	//Removes any empty spaces from expression
	expression.Replace(" ", "");

	//Evals the expression
	double result;
	if (EvaluateExpression(expression, result))
	{
		inputText->SetValue(wxString::FromDouble(result));
	}
	else
	{
		wxMessageBox("Invalid expression!", "Error", wxOK | wxICON_ERROR);
	}
}

bool MainFrame::EvaluateExpression(const wxString& expression, double& result)
{
	string expr = expression.ToStdString();

	//Create stringstream to tokenize expression
	istringstream iss(expr);

	//var to store parsed tokens and operators
	double num1, num2;
	char op;

	//parse first number
	if (!(iss >> num1))
	{
		return false; // Invalid expression
	}

	//parse operator
	if (!(iss >> op))
	{
		return false;
	}

	// Parse the second number
	if (!(iss >> num2))
	{
		return false; // Invalid expression
	}

	// Perform the arithmetic operation
	switch (op)
	{
	case '+':
		result = num1 + num2;
		break;
	case '-':
		result = num1 - num2;
		break;
	case '*':
		result = num1 * num2;
		break;
	case '/':
		if (num2 == 0)
		{
			return false; // Division by zero
		}
		result = num1 / num2;
		break;
	default:
		return false; // Invalid operator
	}

	return true;
}

void MainFrame::OnClearButton(wxCommandEvent& event)
{
	inputText->Clear();
}
