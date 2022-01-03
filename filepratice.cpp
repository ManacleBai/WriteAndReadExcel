// filepratice.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>
#include <math.h>
#include<string>
#include <fstream>
#include <vector>
#include <cstring>
using namespace std;
#define AR_SIZE(a) sizeof(a) / sizeof(a[0])

void AutoReadExcel(ifstream& in, string FilePath, char(*data)[100][100]); // Read char[] format;
void AutoReadExcel(ifstream& in, string FilePath, vector<vector<string> >* data); //Read vector format;
void WriteToExcel(string FilePath, vector<string>* data, uint8_t Terminal);
void WriteToExcel(string FilePath, int *data, uint8_t Terminal, int length);



int main(int argc)
{
	char TxBuff[50][50][50] = {0};
	vector <vector<string> > DataIn;
	ifstream DataFile;
	char InPut[] = "C:\\Users\\Alfred\\Desktop\\fortest\\testdata.csv";
	char OutPut[] = "C:\\Users\\Alfred\\Desktop\\fortest\\dataOutput.csv";
	AutoReadExcel(DataFile, InPut, &DataIn);
	//AutoReadExcel(DataFile, InPut, &TxBuff);

	vector<string> Temp[5];  // Tmp for each row of Data
	for (uint8_t Row =0; Row < DataIn.size(); Row++)
	{
		for (uint8_t j = 0; j < DataIn[Row].size(); j++)
		{
			Temp[Row].push_back(DataIn[Row][j]);
			
		}
	}
	 
	//process some data
	
	int TmpNum[10];
	for (uint8_t i = 0; i < DataIn[2].size(); i++)
	{
		TmpNum[i] = atoi(DataIn[2][i].c_str())*2;
	}



	WriteToExcel(OutPut, &Temp[0], 1);  // write data for 
	WriteToExcel(OutPut, &Temp[3], 1);
	int length = DataIn[2].size();
	WriteToExcel(OutPut, TmpNum, 1, length);
	WriteToExcel(OutPut, &Temp[0], 0); // saving data
	

    std::cout << "Hello World!\n";
	return 0;
}


void AutoReadExcel(ifstream& in, string FilePath, char (*data)[100][100])
{
	int col = 0, row = 0;
	char buff[100] = { 0 };
	char cc;  const char* split = ",\0";
	string firstRow;
	char* ptr = NULL;
	char* input;

	in.open(FilePath, ios::in);//開

	for (int i = 0; i < 3; i++)
	{
		cc = in.get(); // clear Excel header
	}

	while (getline(in, firstRow))
	{
		strcpy_s(buff, firstRow.c_str());
		input = strtok_s(buff, split, &ptr);
		while (input != NULL)
		{
			strcpy_s(data[row][col++], input);
			input = strtok_s(NULL, split, &ptr);
		}
		row++; col = 0;
	}
	in.close();
}

void AutoReadExcel(ifstream& in, string FilePath, vector<vector<string> > *data)
{
	char buff[100] = { 0 };
	char cc;  const char* split = ",\0";
	string firstRow;
	char* ptr = NULL;
	char* input;

	in.open(FilePath, ios::in);//開

	for (int i = 0; i < 3; i++)
	{
		cc = in.get(); // clear Excel header
	}

	while (getline(in, firstRow))
	{
		vector<string> tmp;
		strcpy_s(buff, firstRow.c_str());
		input = strtok_s(buff, split, &ptr);
		while (input != NULL)
		{
			tmp.push_back(input);	
			input = strtok_s(NULL, split, &ptr);
		}
		data->push_back(tmp);
	}
	in.close();
}

void WriteToExcel(string FilePath, vector<string> *data, uint8_t Terminal)
{
	static ofstream OutData;
	static uint8_t IsOpenBefore = 0;
	vector<string> Temp;
	string stringTemp;
	Temp.assign(data->begin(),data->end());
	if (!IsOpenBefore)
	{
		OutData.open(FilePath, ios::app);
		IsOpenBefore = 1;
	}
	switch (Terminal)
	{
	case 0 :
			OutData.close();
			break;
	case 1:
		
			for (int i = 0; i < data->size(); i++)
			{
				stringTemp = Temp[i];
				OutData << stringTemp.c_str() << ',';
			}
			OutData << endl;
			break;
	}

	
};

void WriteToExcel(string FilePath, int* data, uint8_t Terminal, int length)
{
	static ofstream OutData;
	static uint8_t IsOpenBefore = 0;
	vector<string> Temp;
	string stringTemp;
	int c  = data[2];
	if (!IsOpenBefore)
	{
		OutData.open(FilePath, ios::app);
		IsOpenBefore = 1;
	}
	switch (Terminal)
	{
	case 0:
		OutData.close();
		break;
	case 1:
		//int length = AR_SIZE(data); // getArrayLen(data);
		for (int i = 0; i < length; i++)
		{
			OutData << data[i] << ',';
		}
		OutData << endl;
		break;
	}


};