#pragma once
#include<iostream>
#include<windows.h>
#include<ctime>
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
	unsigned long subChunk2Size;			//�����ݿ�Ĵ�С��������ID��Size�ֶα���
	
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
	cout	<< "�������� Data ��С��" 
			<< dataInfoChunk.subChunk2Size
			<<"�ֽ�"<< endl;
	

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
	wHC.ShowInfo();

	short *tmpData = new short [wHC.dataInfoChunk.subChunk2Size / 2];//�½�short������ʱ���飬���ڽ����ļ�����
	wDC.dataChunk = new int[wHC.dataInfoChunk.subChunk2Size / 2];	//�������������ڴ�ռ�
	//short tmpData;

	
	fread(tmpData, wHC.dataInfoChunk.subChunk2Size, 1, pf);	//��ȡ�����ļ�

	//�ļ����ݴ洢��WaveClass��
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
	//endTime = clock();//��ʱ����
	//cout << wDC.dataChunk[wHC.dataInfoChunk.subChunk2Size-1] << "	" << tmpData[wHC.dataInfoChunk.subChunk2Size-1] << endl;
	//cout << "The run time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	fclose(pf);										//�ر��ļ�
	//delete tmpData;								//�ͷ��ڴ�
	return true;									//ReadFile����
}
































