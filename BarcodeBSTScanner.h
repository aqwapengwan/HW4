class BarcodeBSTScanner {
public:
	typedef bool ReadFunc(UPC *);
	BarcodeBSTScanner(ReadFunc reader) { DatabaseLineReader = reader; }
	int ReadDatabase();
	UPC FindItem(int64_t upc);

private:
	ReadFunc *DatabaseLineReader;
	BST<UPC> tree;
};
