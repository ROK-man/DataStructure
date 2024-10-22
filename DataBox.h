// Example header file 
typedef struct {
	int carNo;
	int parkingNo;
}DataBox;

DataBox* MakeData(int car, int parking)
{
	DataBox* newData = (DataBox*)malloc(sizeof(DataBox));
	newData->carNo = car;
	newData->parkingNo = parking;

	return newData;
}

void DestroyData(DataBox* data)
{
	free(data);
}