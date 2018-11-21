//Alanna Romao CS 300
//This program reads UPCs and their descriptions from a file given in the command line.
//The program stores these UPCs in both an array and a binary search tree (BST).
//The program then searches for five different UPCs
//and returns the time it took to find each one in miliseconds

using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <iostream>

#include "UPC.h"
#include "BST.h"
#include "BarcodeBSTScanner.h"
#include "BarcodeArrayScanner.h"

#ifdef _WIN32
#pragma warning(disable : 4996)
#define ITEMFORMAT "UPC code: %I64d\nDescription: %s\n"
#else
#define ITEMFORMAT "UPC code: %ld\nDescription: %s\n"
#endif

#define lenof(x) (sizeof(x) / sizeof(*x))

bool ReadUpcItem(UPC *item);
bool GetLine(char *buff, int size, FILE *f);
void PrintElapsedTime(clock_t start, clock_t end, const char *name);

static FILE *f;


int main(int argc, char *argv[])
{
	if(argc < 2) { //no file passed
		printf("Usage: HW4 <upcfile>\n");
		return -1;
	}

	f = fopen(argv[1], "r");
	if(f == NULL) { //can't open file
		printf("Can't open UPC file '%s'\n", argv[1]);
		return -1;
	}

	BarcodeBSTScanner bstScan(ReadUpcItem);
	printf("Reading UPC items into BST...\n");
	int n = bstScan.ReadDatabase();
	printf("%d UPC items read into BST\n", n);

	BarcodeArrayScanner arrayScan(ReadUpcItem);
	fseek(f, 0, SEEK_SET);
	printf("Reading UPC items into array...\n");
	n = arrayScan.ReadDatabase();
	printf("%d UPC items read into array\n", n);
	printf("\n\n");

	int64_t codes[] = { //UPCs to be found in array and BST
		87902811026, 6412500078115, 25700123729, 6417182605703, 4280000580
	};

	n = lenof(codes);
	int i;
	for(i = 0; i < n; i++) { //find and time UPCs
		clock_t t0 = clock();//BST search
		UPC upc = bstScan.FindItem(codes[i]); 
		clock_t t1 = clock();

		printf(ITEMFORMAT, upc.GetUpcCode(), upc.GetDescription());
		PrintElapsedTime(t0, t1, "BST");

		t0 = clock(); //array search
		upc = arrayScan.FindItem(codes[i]);
		t1 = clock();
		PrintElapsedTime(t0, t1, "Array");
		printf("\n");
	}

	return 0;
}

//read UPCs and descriptions into program
bool ReadUpcItem(UPC *item) {
	char buff[500];
	while(true) {
		if(!GetLine(buff, sizeof(buff), f))
			return false;

		const char *p = strchr(buff, ',');
		if(p == NULL)
			continue;

		int n = strlen(p) - 1;
		if(n < 1)
			p = "[No description]";
		else
			p++;

		int64_t u = atoll(buff);
		if(u == 0)
			continue;

		item->SetUpc(u);
		item->SetDescription(p);
		return true;
	}
}

//get line from file
bool GetLine(char *buff, int size, FILE *f) {
	do {
		buff[0] = 0;
		if(fgets(buff, size, f) == NULL)
			return false;
		char *p = strchr(buff, '\n');
		if(p != NULL)
			*p = 0;
	} while(buff[0] == 0);
	return true;
}

// Print elapsed time
void PrintElapsedTime(clock_t start, clock_t end, const char *name) {
	printf("%s elapsed time: %f ms\n", name, (end - start) * 1000.0 / CLOCKS_PER_SEC);
}
