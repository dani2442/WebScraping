#include "TradingData.h"
#include "iostream"
#include "string"


int main(int argc, wchar_t* argv[]) {
	TradingData TD("aapl");
	TD.EXECUTE();
	std::cout << "###_FINISHED_###";
	getchar();
	return 0;
}