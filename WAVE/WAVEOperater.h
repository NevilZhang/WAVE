#pragma once
#include"WaveClass.h"
//////////////////////////////////////////////////////////////
//文件操作函数
bool ReadFile(char *wavePath, WaveHeaderClass wHC,WaveDataClass wDC) {
	//cout << wavePath << endl;

	FILE* pf = fopen(wavePath, "r");				//打开文件
	if (pf == NULL) {
		cout << "Can not able to open wave file" << endl;
		return false;								//文件打开失败
	}

	fread(&wHC, sizeof(wHC), 1, pf);					//读取头文件数据
	wHC.ShowInfo();

	short *tmpData = (short *)malloc(sizeof(short)*wHC.dataInfoChunk.subChunk2Size);//新建short类型临时数组，用于接收文件数据
	wDC.dataChunk = (int *)malloc(sizeof(int) *wHC.dataInfoChunk.subChunk2Size);	//数据类对象分配内存空间
	

	fread(tmpData, wHC.dataInfoChunk.subChunk2Size, 1, pf);	//读取数据文件
	
	//文件数据存储至WaveClass中
	for (int i = 0; i < wHC.dataInfoChunk.subChunk2Size; i++) {
		wDC.dataChunk[i] = tmpData[i];
	}
	
	//cout << wDC.dataChunk[wHC.dataInfoChunk.subChunk2Size-1] << "	" << tmpData[wHC.dataInfoChunk.subChunk2Size-1] << endl;

	fclose(pf);										//关闭文件
	delete tmpData;									//释放内存
	return true;									//ReadFile结束
}


