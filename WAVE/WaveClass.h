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

//////////////////////////////////////��������WAVE�ļ���ͽṹ�塪������/////////////////////////////////////////////////
//////////////������ͽṹ�嶨�塪��////////////////

//wave�ļ�ͷ��Ϣ��Ľṹ��
struct RIFFChunk{
	char chunkID[4];			//�ļ�ͷ��ʶһ����RIFF�ĸ���ĸ
	unsigned long chunkSize;	//�����ļ���С��������ID��Size��˸��ֽ�
	char format[4];				//�ļ���ʽ��һ����WAVE�ĸ���ĸ
};
//wave�ļ���ʽ��Ϣ��Ľṹ��
struct FmtChunk {
	char subChunkID[4];			//��ʽ˵���飬һ����fmt�ֶ�
	unsigned long subChunkSize;	//�����ݿ�Ĵ�С��������ID��Size�ֶ�
	unsigned short audioFormat;	//��Ƶ��ʽ˵����PCM = 1 �����磬���Բ����������������ֵ�Ļ����������һЩѹ����ʽ
	unsigned short numChannels;	//1 => ������  |  2 => ˫����
	unsigned long sampleRate;	//������
	unsigned long byteRate;		//�����ʣ�ÿ������Ҫ���ֽ����� = SampleRate * numChannels * BitsPerSample / 8
	unsigned short blockAlign;	//���ݿ���뵥Ԫ��NumChannels * BitsPerSample / 8
	unsigned short bitsPerSample;//�����ֱ��ʣ�����ʱģ��ת���ķֱ��ʣ���Ҳ����ÿ�������ü�λ����ʾ��һ���� 8bits ���� 16bits
};
//wave�ļ�������Ϣ��Ľṹ��
struct DataInfoChunk {
	char subChunkID[4];			//�������������ݿ飬���ֶ�һ����"data"
	unsigned long subChunk2Size;//�����ݿ�Ĵ�С��������ID��Size�ֶα���
	
};

//����wave�ļ����ݴ洢�����
class WaveDataClass {
	//����������
public:
	int *dataChunk;
};
//����wave�ļ�ͷ��
class WaveHeaderClass
{
//wave�ļ�������
public:
	RIFFChunk	riffChunk;
	FmtChunk	fmtChunk;
	DataInfoChunk	dataInfoChunk;
	
//
public:


//Ĭ�Ϻ���
public:
	WaveHeaderClass();
	~WaveHeaderClass();
//�Զ��庯��
public:
	void ShowInfo();


};


//��������wave�ࡪ������//
class WaveClass {
public:
	WaveHeaderClass wHC;
	WaveDataClass	wDC;
public:
	bool ReadFile(char *wavePath);
	SpeechClass EnFrame(int nw, int inc, string windows_function_name);
};












///////////////////�����ຯ��ʵ�֡���/////////////////////////
//Ĭ�Ϻ���

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
	cout	<< "�ļ���С��"
			<< riffChunk.chunkSize << endl;
	cout	<< "�ļ����ͣ�"
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
	cout	<< "FMTChunk�Ĵ�С��"
			<< fmtChunk.subChunkSize << endl;
	cout	<< "ѹ����ʽ Audio Format�� "
			<< fmtChunk.audioFormat << endl;
	cout	<< "ͨ������"
			<< fmtChunk.numChannels << endl;
	cout	<< "����Ƶ�ʣ�"
			<< fmtChunk.sampleRate << endl;
	cout	<< "�����ʣ�"
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
	cout << "�������� Data ��С��"
			<< dataInfoChunk.subChunk2Size
			<< "���ֽ�;"
			<< dataInfoChunk.subChunk2Size/2
			<< "��������"
			<< endl;
	

}

//�ļ���������
bool WaveClass::ReadFile(char *wavePath) {
	
	//clock_t startTime, endTime;
	//startTime = clock();//��ʱ��ʼ

	FILE* pf = fopen(wavePath, "rb");				//���ļ�
	if (pf == NULL) {
		cout << "Can not able to open wave file" << endl;
		return false;								//�ļ���ʧ��
	}

	fread(&wHC, sizeof(wHC), 1, pf);					//��ȡͷ�ļ�����
	wHC.dataInfoChunk.subChunk2Size = wHC.riffChunk.chunkSize - 42;
	wHC.ShowInfo();
	short *tmpData = new short [wHC.dataInfoChunk.subChunk2Size / 2];//�½�short������ʱ���飬���ڽ����ļ�����
	wDC.dataChunk = new int[wHC.dataInfoChunk.subChunk2Size / 2];	//�������������ڴ�ռ�
	//short tmpData;

	
	fread(tmpData, wHC.dataInfoChunk.subChunk2Size, 1, pf);	//��ȡ�����ļ�

	//�ļ����ݴ洢��WaveClass��
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
	//endTime = clock();//��ʱ����
	//cout << wDC.dataChunk[wHC.dataInfoChunk.subChunk2Size-1] << "	" << tmpData[wHC.dataInfoChunk.subChunk2Size-1] << endl;
	//cout << "The run time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	fclose(pf);										//�ر��ļ�
	//delete tmpData;								//�ͷ��ڴ�
	return true;									//ReadFile����
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
		����Ƶ�ź�ת��Ϊ֡��
        �������壺
        nw:ÿһ֡�ĳ���(����ָ������ĳ��ȣ�������Ƶ�ʳ���ʱ����)
        inc:����֡�ļ����ͬ�϶��壩
		windows_function_name:������
	*/
	nw *= 16; inc *= 16;	//֡����֡�ƴӺ���ת�Ƶ�����������
	SpeechClass speech_data;
	int signal_length = wHC.dataInfoChunk.subChunk2Size/2;	//���ݲ���������
	int nf = 0;	//֡��

	if (signal_length <= nw) { // ���źų���С��һ��֡�ĳ��ȣ���֡������Ϊ1
		nf = 1;
	}
	else {	//���򣬼���֡��������
		nf = int(ceil((1.0 * signal_length - nw + inc) / inc));
	}

	int pad_length = int((nf - 1) * inc + nw);	//����֡�������ܵ���ƽ��ĳ���
	int zero_length = pad_length - signal_length;	//�����ĳ���ʹ��0���������FFT�е������������
	for (int i = 0; i < nf; i++) {				//��֡
		vector<long double>tmpVector;
		for (int k = 0; k < nw; k++) {			//β������
			tmpVector.push_back((i == nf - 1 && zero_length != 0 && i*nw + k > signal_length) ? 0.0 : long double(wDC.dataChunk[i*nw + k]));
		}
		speech_data.frame_data.push_back(tmpVector);
	}
	return (windows_function_name == "hanning") ? hanning(speech_data, nw, nf) : speech_data;
}

































