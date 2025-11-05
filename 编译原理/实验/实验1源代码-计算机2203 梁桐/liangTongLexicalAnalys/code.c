//注意！！！此程序是冒泡排序法，是被词法分析的程序
//词法分析程序的文件名为源.cpp
//注意！！！此程序是冒泡排序法，是被词法分析的程序
//词法分析程序的文件名为源.cpp
//注意！！！此程序是冒泡排序法，是被词法分析的程序
//词法分析程序的文件名为源.cpp
void Bubble_sort(int arr[], int size)
{
	int j,i,tem;
	for (i = 0; i < size-1;i ++)
		int count = 0;
		for (j = 0; j < size-1 - i; j++)
		{
			if (arr[j] > arr[j+1])
			{
				tem = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = tem;
				count = 1;

			}
		}
		if (count == 0)
				break;
	}

}

a=1+1;
b=1-1;
int main()
{
	int arr[10];
	int i;

	printf("\n");
	for (i = 0; i < 10; i++)
	{
		scanf("%d", &arr[i]);
	}
	printf("");
	for (i = 0; i < 10; i++)
	{
		printf("%d ", arr[i]);
	}

	printf("\n");
	Bubble_sort(arr, 10);
	for (i = 0; i < 10; i++)
	{
		printf("%d ", arr[i]);
	}

	return 0;
}
