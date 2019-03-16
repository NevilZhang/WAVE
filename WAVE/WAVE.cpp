// WAVE.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "WaveClass.h"
#include "WAVEOperater.h"
int main()
{
	WaveClass wC;
	ReadFile("D:\\Media\\F001_T4_M.wav",wC.wHC,wC.wDC);
	system("pause");
    return 0;
}

