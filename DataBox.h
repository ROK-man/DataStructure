#pragma once
typedef struct{
	int carNo;
	int parkingNo;
	int i;
	char s[10];
	char* key;
}DataBox;

DataBox* MakeData(int a)
{
	DataBox* newData = (DataBox*)malloc(sizeof(DataBox));
	if (newData == NULL)
	{
		return NULL;
	}
	newData->i = a;

	return newData;
}

void DestroyData(DataBox* data)
{
	free(data);
}