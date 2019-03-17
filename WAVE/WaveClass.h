#pragma once
#include<iostream>
#include<windows.h>
#include<ctime>
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
	unsigned long subChunk2Size;			//本数据块的大小，不包括ID和Size字段本身
	
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
	cout	<< "采样数据 Data 大小：" 
			<< dataInfoChunk.subChunk2Size
			<<"字节"<< endl;
	

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
	wHC.ShowInfo();

	short *tmpData = new short [wHC.dataInfoChunk.subChunk2Size / 2];//新建short类型临时数组，用于接收文件数据
	wDC.dataChunk = new int[wHC.dataInfoChunk.subChunk2Size / 2];	//数据类对象分配内存空间
	//short tmpData;

	
	fread(tmpData, wHC.dataInfoChunk.subChunk2Size, 1, pf);	//读取数据文件

	//文件数据存储至WaveClass中
	for (int i = 0; i < wHC.dataInfoChunk.subChunk2Size / 2; i++) {
		
		//fread(&tmpData, 2, 1, pf);
		wDC.dataChunk[i] = tmpData[i];
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
































