#pragma once
#include<iostream>
#include<windows.h>
#include<string>
#include<ctime>
#include <stdio.h>
#include "math.h"
#include"SpeechClass.h"
#define M_PI 3.14159265358979323846
using namespace std;

//////////////////////////////////////————WAVE文件类和结构体————/////////////////////////////////////////////////
//////////////——类和结构体定义——////////////////

//wave文件头信息块的结构体
struct RIFFChunk{
	char chunkID[4];			//文件头标识一般是RIFF四个字母
	unsigned long chunkSize;	//整个文件大小，不包含ID和Size这八个字节
	char format[4];				//文件格式，一般是WAVE四个字母
};
//wave文件格式信息块的结构体
struct FmtChunk {
	char subChunkID[4];			//格式说明块，一般是fmt字段
	unsigned long subChunkSize;	//本数据块的大小，不包括ID和Size字段
	unsigned short audioFormat;	//音频格式说明，PCM = 1 （比如，线性采样），如果是其它值的话，则可能是一些压缩形式
	unsigned short numChannels;	//1 => 单声道  |  2 => 双声道
	unsigned long sampleRate;	//采样率
	unsigned long byteRate;		//比特率，每秒所需要的字节数， = SampleRate * numChannels * BitsPerSample / 8
	unsigned short blockAlign;	//数据块对齐单元，NumChannels * BitsPerSample / 8
	unsigned short bitsPerSample;//采样分辨率（采样时模数转换的分辨率），也就是每个样本用几位来表示，一般是 8bits 或是 16bits
};
//wave文件数据信息块的结构体
struct DataInfoChunk {
	char subChunkID[4];			//真正的声音数据块，本字段一般是"data"
	unsigned long subChunk2Size;//本数据块的大小，不包括ID和Size字段本身
	
};

//——wave文件数据存储块的类
class WaveDataClass {
	//数据类属性
public:
	int *dataChunk;
};
//——wave文件头类
class WaveHeaderClass
{
//wave文件的属性
public:
	RIFFChunk	riffChunk;
	FmtChunk	fmtChunk;
	DataInfoChunk	dataInfoChunk;
	
//
public:


//默认函数
public:
	WaveHeaderClass();
	~WaveHeaderClass();
//自定义函数
public:
	void ShowInfo();


};


//————wave类————//
class WaveClass {
public:
	WaveHeaderClass wHC;
	WaveDataClass	wDC;
public:
	bool ReadFile(char *wavePath);
	SpeechClass EnFrame(int nw, int inc, string windows_function_name);
};












///////////////////——类函数实现——/////////////////////////
//默认函数

WaveHeaderClass::WaveHeaderClass()
{
}

WaveHeaderClass::~WaveHeaderClass()
{
}
void WaveHeaderClass::ShowInfo() {
	cout << "----Riff Chunk----" << endl;
	cout	<< "RIFF Header: "
			<< riffChunk.chunkID[0]
			<< riffChunk.chunkID[1]
			<< riffChunk.chunkID[2]
			<< riffChunk.chunkID[3] << endl;
	cout	<< "文件大小："
			<< riffChunk.chunkSize << endl;
	cout	<< "文件类型："
			<< riffChunk.format[0]
			<< riffChunk.format[1]
			<< riffChunk.format[2]
			<< riffChunk.format[3] << endl;
	cout << endl;

	cout << "----FORMAT Chunk----" << endl;
	cout	<< "FORMAT Header:"
			<< fmtChunk.subChunkID[0]
			<< fmtChunk.subChunkID[1]
			<< fmtChunk.subChunkID[2]
			<< fmtChunk.subChunkID[3] << endl;
	cout	<< "FMTChunk的大小："
			<< fmtChunk.subChunkSize << endl;
	cout	<< "压缩形式 Audio Format： "
			<< fmtChunk.audioFormat << endl;
	cout	<< "通道数："
			<< fmtChunk.numChannels << endl;
	cout	<< "采样频率："
			<< fmtChunk.sampleRate << endl;
	cout	<< "比特率："
			<< fmtChunk.byteRate << endl;
	cout << fmtChunk.blockAlign << endl;;   // 2=16-bit mono, 4=16-bit stereo 
	cout << fmtChunk.bitsPerSample << endl; // Number of bits per sample  
	cout << endl;

	cout << "----Data Chunk----" << endl;
	cout	<< "DataChunk Header:"
			<< dataInfoChunk.subChunkID[0]
			<< dataInfoChunk.subChunkID[1]
			<< dataInfoChunk.subChunkID[2]
			<< dataInfoChunk.subChunkID[3] << endl;
	cout << "采样数据 Data 大小："
			<< dataInfoChunk.subChunk2Size
			<< "个字节;"
			<< dataInfoChunk.subChunk2Size/2
			<< "个采样点"
			<< endl;
	

}

//文件操作函数
bool WaveClass::ReadFile(char *wavePath) {
	
	//clock_t startTime, endTime;
	//startTime = clock();//计时开始

	FILE* pf = fopen(wavePath, "rb");				//打开文件
	if (pf == NULL) {
		cout << "Can not able to open wave file" << endl;
		return false;								//文件打开失败
	}

	fread(&wHC, sizeof(wHC), 1, pf);					//读取头文件数据
	wHC.dataInfoChunk.subChunk2Size = wHC.riffChunk.chunkSize - 42;
	wHC.ShowInfo();
	short *tmpData = new short [wHC.dataInfoChunk.subChunk2Size / 2];//新建short类型临时数组，用于接收文件数据
	wDC.dataChunk = new int[wHC.dataInfoChunk.subChunk2Size / 2];	//数据类对象分配内存空间
	//short tmpData;

	
	fread(tmpData, wHC.dataInfoChunk.subChunk2Size, 1, pf);	//读取数据文件

	//文件数据存储至WaveClass中
	for (int i = 0; i < wHC.dataInfoChunk.subChunk2Size / 2; i++) {
		
		//fread(&tmpData, 2, 1, pf);
		wDC.dataChunk[i] = tmpData[i];
		//cout << wDC.dataChunk[i] << endl;
		/*
		cout <<i<<"	:"<< tmpData[i] << "	:"<< wDC.dataChunk[i] <<endl;
		if (i == 1160) {

			//cout << i << endl;
			break;
		}
		*/
		
	}
	//endTime = clock();//计时结束
	//cout << wDC.dataChunk[wHC.dataInfoChunk.subChunk2Size-1] << "	" << tmpData[wHC.dataInfoChunk.subChunk2Size-1] << endl;
	//cout << "The run time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	fclose(pf);										//关闭文件
	//delete tmpData;								//释放内存
	return true;									//ReadFile结束
}
SpeechClass hanning(SpeechClass speech_data, int nw, int nf) {
	SpeechClass pre_hanning_data = SpeechClass(speech_data.frame_data);
	long double* winfun = new long double[nw];
	for (int i = 0; i < nw; i++) {
		winfun[i] = 0.5 * (1.0 - cos(2.0 * M_PI *(i - 1) / nw));
	}
	for (int i = 0; i < nf; i++) {
		for (int j = 0; j < nw; j++) {
			pre_hanning_data.frame_data[i][j] *= winfun[j];
		}
	}
	return pre_hanning_data;
}
SpeechClass WaveClass::EnFrame(int nw, int inc, string windows_function_name) {
	/*
		将音频信号转化为帧。
        参数含义：
        nw:每一帧的长度(这里指采样点的长度，即采样频率乘以时间间隔)
        inc:相邻帧的间隔（同上定义）
		windows_function_name:窗函数
	*/
	nw *= 16; inc *= 16;	//帧长和帧移从毫秒转移到采样点数量
	SpeechClass speech_data;
	int signal_length = wHC.dataInfoChunk.subChunk2Size/2;	//数据采样点总数
	int nf = 0;	//帧数

	if (signal_length <= nw) { // 若信号长度小于一个帧的长度，则帧数定义为1
		nf = 1;
	}
	else {	//否则，计算帧的总数量
		nf = int(ceil((1.0 * signal_length - nw + inc) / inc));
	}

	int pad_length = int((nf - 1) * inc + nw);	//所有帧加起来总的铺平后的长度
	int zero_length = pad_length - signal_length;	//不够的长度使用0填补，类似于FFT中的扩充数组操作
	for (int i = 0; i < nf; i++) {				//分帧
		vector<long double>tmpVector;
		for (int k = 0; k < nw; k++) {			//尾部补零
			tmpVector.push_back((i == nf - 1 && zero_length != 0 && i*nw + k > signal_length) ? 0.0 : long double(wDC.dataChunk[i*nw + k]));
		}
		speech_data.frame_data.push_back(tmpVector);
	}
	return (windows_function_name == "hanning") ? hanning(speech_data, nw, nf) : speech_data;
}

































