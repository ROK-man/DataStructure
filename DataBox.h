// Example header file 
#pragma once
typedef struct{
	int carNo;
	int parkingNo;
	int i;
}DataBox;

DataBox* MakeData(int a)
{
	DataBox* newData = (DataBox*)malloc(sizeof(DataBox));
	newData->i = a;

	return newData;
}

void DestroyData(DataBox* data)
{
	free(data);
}