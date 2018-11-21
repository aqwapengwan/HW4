class UPC {
public:
	UPC() { Init(); }
	UPC(int64_t code) { upc = code; description = NULL; }
	UPC(int64_t code, char *desc);
	UPC(const UPC&);
	~UPC() { delete description; }

	void Init() { description = NULL; upc = 0; }
	void SetUpc(int64_t c) { upc = c; }
	void SetDescription(const char *desc);
	int64_t GetUpcCode() { return upc; }
	const char *GetDescription() { return description; }
	void operator=(const UPC& o);
	bool operator==(UPC& o) { return upc == o.upc; }
	bool operator<(UPC& o) { return upc < o.upc; }
	bool operator>(UPC& o) { return upc > o.upc; }
	friend ostream& operator<<(ostream& ob, UPC&);

private:
	int64_t upc;
	char *description;
};
