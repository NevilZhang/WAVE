// WAVE.cpp : �������̨Ӧ�ó������ڵ㡣
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

