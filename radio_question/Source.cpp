#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	double frequency;
	char name[20];
	int hits;
} radio_t;

void read(FILE* inp, int size, radio_t* arr) {
	int i = 0;
	while (i != size)
	{
		fscanf(inp, "%lf %s %d", &arr[i].frequency, &arr[i].name, &arr[i].hits);
		i++;
	}
}

void display(radio_t* arr, int size) {
	int i;
	printf("Frequency  Name         #of Hits\n");
	printf("*********  ************ ********\n");
	for (i = 0; i < size; i++)
		printf("%9.1f  %-12s %7d\n", arr[i].frequency, arr[i].name, arr[i].hits);
}

int findMaxHits(radio_t* arr, int size) {
	int max = arr[0].hits, i, indexMax = 0;;
	for (i = 1; i < size; i++)
		if (arr[i].hits > max)
		{
			max = arr[i].hits;
			indexMax = i;
		}
	return (indexMax);
}

int findRadio(radio_t* arr, int size, double frequencyFind) {
	int i;
	for (i = 0; i < size; i++)
		if (arr[i].frequency == frequencyFind)
			return (i);
	return (-1);
}

int main(void)
{
	FILE* inp;
	inp = fopen("radio.txt", "r");
	if (inp == NULL)
		printf("error");
	else
	{
		radio_t* arr;
		int size;
		do {
			printf("\nHow many radio information will you read? ");
			scanf("%d", &size);
			if (size < 1 || size > 20)
				printf("Error!!! Please enter a number 1-20\n");
		} while (size < 1 || size > 20);
		printf("\n");

		arr = (radio_t*)malloc(sizeof(radio_t) * size);
		read(inp, size, arr);
		fclose(inp);
		display(arr, size);
		printf("\n");

		int maxHitsIndex = findMaxHits(arr, size);
		printf("The radio <%s> has the maximum number of hits\n", arr[maxHitsIndex].name);
		printf("Frequency: %.1f\n", arr[maxHitsIndex].frequency);
		printf("Hits: %d\n", arr[maxHitsIndex].hits);
		printf("\n");

		double search_F;
		printf("Enter a radio frequency to be searched: ");
		scanf("%lf", &search_F);
		int index_F = findRadio(arr, size, search_F);
		if (index_F == -1)
			printf("\nSorry! There is no radio on the given frequency :(\n");
		else
			printf("\nRadio <%s> is on the %.1f frequency\n", arr[index_F].name, search_F);
	}
	return 0;
}