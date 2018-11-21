using namespace std;

#include <stdint.h>
#include <string.h>
#include <iostream>

#include "UPC.h"

//constructor
UPC::UPC(int64_t code, char *desc) {
	upc = code;
	int n = strlen(desc) + 1;
	description = new char[n];
	memcpy(description, desc, n);
}

//copy constructor
UPC::UPC(const UPC &o) {
	description = NULL;
	*this = o;
}

//sets description of product
void UPC::SetDescription(const char *desc) {
	int n = strlen(desc) + 1;
	description = new char[n];
	memcpy(description, desc, n);
}

//assignment operator
void UPC::operator=(const UPC& o) {
	delete description;

	upc = o.upc;
	if(o.description == NULL) {
		description = NULL;
		return;
	}

	SetDescription(o.description);
}

//print out operator
ostream& operator<<(ostream& ob, UPC& item) {
	ob << item.upc << ' ' << item.description << endl;
	return ob;
}
