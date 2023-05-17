#include "stdafx.h"
#include "threadedLoadingForm.h"
#include <chrono>
#include <thread>
#include "loadingForm.h"
#include <string>


using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds
using namespace std;

//calls the thread for the loading form
void threadedLoadingForm::loadLoadingForm()
{
	thread_obj = std::thread(&threadedLoadingForm::threadedLoading, this);
}

//the code which initiates the loading form and closes the loading form when ready
void threadedLoadingForm::threadedLoading()
{
	VisCanvas::loadingForm^ form = gcnew VisCanvas::loadingForm();
	form->Show();
	form->Update();
	int n = 0; // keeps track of the count of the loop
	while (loading)//loading is a global variable
	{
		//the following if statements create a sort of animation. This way something is moving for the user
		string formText = "loading ";
		if (n == 0)
		{
			formText += loadInfo;
		}
		else if (n == 1)
		{
			formText += loadInfo + ".";
		}
		else if (n == 2)
		{
			formText += loadInfo + "..";
		}
		else if (n == 3)
		{
			formText += loadInfo + "...";
			n = -1;//this way n = 0 upon n++ below
		}
		String^ forFunc = gcnew String(formText.c_str());
		form->updateLabel(forFunc);
		n++;

		form->Update();
		sleep_until(system_clock::now() + milliseconds(500));//half a second between every update
	}
	form->Close();
	loadInfo = "";//resets loadInfo for the next Loading form
}

//the code which closes the the loading form thread
void threadedLoadingForm::terminateLoadingForm()
{
	loading = false; //set to false, and thus the form is closed and the threaded method is complete
	thread_obj.join();
	loading = true; //sets loading to true again when the loading form is again used
}

void threadedLoadingForm::updateLoadingText(string loadInf)
{
	loadInfo = loadInf;
}
