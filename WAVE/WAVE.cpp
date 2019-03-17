// WAVE.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "WaveClass.h"

int main()
{
	WaveClass wC;
	wC.ReadFile("D:\\Media\\F001_T4_M.wav");
	system("pause");
    return 0;
}

