class BarcodeArrayScanner {
public:
	typedef bool ReadFunc(UPC *);
	BarcodeArrayScanner(ReadFunc reader);
	int ReadDatabase();
	UPC FindItem(int64_t upc);

private:
	ReadFunc *DatabaseLineReader;
	UPC *array;
	int count;
};
