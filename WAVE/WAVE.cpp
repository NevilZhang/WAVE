// WAVE.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "WaveClass.h"
#include "SpeechClass.h"
#include <typeinfo>
int main()
{
	WaveClass wC;
	wC.ReadFile("G:\\Resource\\wav\\D1048\\ID1048W0001.wav");
	//wC.ReadFile("G:\\Resource\\F001_T4_M.wav");
	cout << "Read Success" << endl;
	SpeechClass speech;
	
	/*
		frameWidth:֡����ms
		frameStep:֡��,ms
	*/
	int frameWidth = 25;
	int frameStep = 10;
	speech = wC.EnFrame(frameWidth,frameStep,"hanning");
	
	system("pause");
    return 0;
}

