// AppFrame.cpp : main project file.

#include "stdafx.h"
#include "Form1.h"

using namespace AppFrame;

[STAThreadAttribute]
int main(cli::array<System::String ^> ^args)
{
	srand(1);
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 
	
	// Create the main window and run it
	Application::Run(gcnew Form1());
	return 0;
}
