#include "TradingData.h"

#include "iostream"
#include "string"


int main(int argc, wchar_t* argv[]) {
	TradingData TD("aapl");
	TD.Charts();
	getchar();
	return 1;
}