#pragma once
#include"WaveClass.h"
//////////////////////////////////////////////////////////////
//�ļ���������
bool ReadFile(char *wavePath, WaveHeaderClass wHC,WaveDataClass wDC) {
	//cout << wavePath << endl;

	FILE* pf = fopen(wavePath, "r");				//���ļ�
	if (pf == NULL) {
		cout << "Can not able to open wave file" << endl;
		return false;								//�ļ���ʧ��
	}

	fread(&wHC, sizeof(wHC), 1, pf);					//��ȡͷ�ļ�����
	wHC.ShowInfo();

	short *tmpData = (short *)malloc(sizeof(short)*wHC.dataInfoChunk.subChunk2Size);//�½�short������ʱ���飬���ڽ����ļ�����
	wDC.dataChunk = (int *)malloc(sizeof(int) *wHC.dataInfoChunk.subChunk2Size);	//�������������ڴ�ռ�
	

	fread(tmpData, wHC.dataInfoChunk.subChunk2Size, 1, pf);	//��ȡ�����ļ�
	
	//�ļ����ݴ洢��WaveClass��
	for (int i = 0; i < wHC.dataInfoChunk.subChunk2Size; i++) {
		wDC.dataChunk[i] = tmpData[i];
	}
	
	//cout << wDC.dataChunk[wHC.dataInfoChunk.subChunk2Size-1] << "	" << tmpData[wHC.dataInfoChunk.subChunk2Size-1] << endl;

	fclose(pf);										//�ر��ļ�
	delete tmpData;									//�ͷ��ڴ�
	return true;									//ReadFile����
}


