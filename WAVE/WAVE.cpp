// WAVE.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "WaveClass.h"
#include "SpeechClass.h"
#include <typeinfo>
int main()
{
	WaveClass wC;
	/*wC.ReadFile("G:\\Resource\\wav\\D1048\\ID1048W0001.wav");*/
	wC.ReadFile("G:\\Resource\\ID1048W0001.wav");
	//wC.ReadFile("G:\\Resource\\F001_T4_M.wav");
	cout << "Read Success" << endl;

	SpeechClass speech;
	/*
		frameWidth:帧长，ms
		frameStep:帧移,ms
	*/
	int frameWidth = 25;
	int frameStep = 10;
	speech = wC.EnFrame(frameWidth,frameStep,"hanning");
	cout << "enframe success" << endl;
	/*vector<long double> En = speech.shortEnergy();
	vector<int>	Zn = speech.shortCrossZero();*/
	/*cout << En[0] << endl;
	cout << Zn[0] << endl;*/
	vector<vector<long double>> pRealOut, pImageOut;
	speech.ConvertToFFT(pRealOut,pImageOut);
	system("pause");
    return 0;
}

