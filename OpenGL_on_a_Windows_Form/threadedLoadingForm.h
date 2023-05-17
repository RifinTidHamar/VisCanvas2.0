#pragma once
#ifndef _THREADEDLOADINGFORM
#define _THREADEDLOADINGFORM
#include "stdafx.h"
#include <thread>
#include "loadingForm.h"
#include <string>

//the purpose of the loading form is to indicate to the user that the program is still running during computationally intesive parts 
//of the code

using namespace std::this_thread; // sleep_for, sleep_until
using namespace std;
using namespace System;

class threadedLoadingForm
{
	public: void loadLoadingForm(); //calls the thread for the loading form
	private: void threadedLoading(); //the code which initiates the loading form and closes the loading form when ready
	public: void terminateLoadingForm(); //the code which closes the the loading form thread
	public: void updateLoadingText(string loadInf); //This text is added between "loading" and "..." so if you set the param as "cake", then the form would say "loading cake ..." 
	private: bool loading = true; //when set to false, the loading form closes
	private: std::thread thread_obj; //gloabl thread_obj
	private: string loadInfo = "";
};

#endif