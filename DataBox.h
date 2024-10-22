// Example header file 
typedef struct {
	int i;
}DataBox;

DataBox* MakeData(int data)
{
	DataBox* newData = (DataBox*)malloc(sizeof(DataBox));
	newData->i = data;

	return newData;
}

void DestroyData(DataBox* data)
{
	free(data);
}