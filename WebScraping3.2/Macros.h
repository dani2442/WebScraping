#pragma once
const static std::string EXT = ".24d";

// Batch Requests
const char *Types[]= { 
	"quote", 
	"news", 
	"chart" 
};
double QUOTE = 5;

#define QUOTE		0
#define NEWS		1
#define CHART		2

// Chart

const char *_Range[]{ "5y","2y","1y","6m","3m","1m","1d","ytd","date","dynamic" };
const size_t i_Range1[]{ 157784630,63113852,31556926,15778463,7889232,2629744 };
const size_t i_Range2 = 86400;
enum Range { _5Y, _2Y, _1Y, _6M, _3M, _1M, _1D, _YTD, _DATE, _DYNAMIC };

const char *_Parameters[]{
	"symbols",
	"range"
};

enum Parameters {
	SYMBOLS,
	RANGE
};


/*
const char *Parameters[] { 
	"chartReset", 
	"chartSimplify", 
	"chartInterval", 
	"changeFromClose", 
	"chartLast" 
};
#define CHART_RESET			0
#define CHART_SIMPLIFY		1
#define CHART_INTERVAL		2
#define CHANGE_FROM_CLOSE	3
#define CHART_LAST			4
*/

const char *Key[] { 
	"minute", 
	"marketAverage", 
	"marketNotonal", 
	"marketNumberOfTrades", 
	"marketOpen",
	"marketClose", 
	"marketHigh", 
	"marketLow", 
	"marketVolume", 
	"marketChageOverTime", 
	"avarage", 
	"notional", 
	"numberOfTrades", 
	"simplifyFactor", 
	"high",
	"low", 
	"volume", 
	"label", 
	"chageOverTime", 
	"date", 
	"open", 
	"close", 
	"unadjustedVolume", 
	"change", 
	"changePercent",
	"vwap"
};
#define MINUTE					0
#define MARKET_AVARAGE			1
#define MARKET_NOTIONAL			2
#define MARKET_NUMBER_OF_TRADES	3
#define MARKET_OPEN				4
#define MARKET_CLOSE			5
#define MARKET_HIGH				6
#define MARKET_LOW				7
#define MARKET_VOLUME			8
#define MARKET_CHANGE_OVER_TIME	9
#define AVARAGE					10
#define NOTIONAL				11
#define NUMNER_OF_TRADES		12
#define SIMPLIFY_FACTOR			13
#define HIGH					14
#define LOW						15
#define VOLUME					16
#define LABEL					17
#define CHAGE_OVER_TIME			18
#define DATE					19
#define OPEN					20
#define CLOSE					21
#define UNADJUSTED_VOLUME		22
#define CHANGE					23
#define CHANGE_PERCENT			24
#define VWAP					25

// Company
const char *Company[] {
	"symbol",
	"compnyName",
	"exchange",
	"industry",
	"website",
	"description",
	"CEO",
	"issueType",
	"sector"
};
#define SYMBOL			0
#define COMPANY_NAME	1
#define EXCHANGE		2
#define INDUSTRY		3
#define WEBSITE			4
#define DESCRIPTION		5
#define CEO				6
#define ISSUE_TYPE		7
#define SECTOR			8

const char *Dividends[] = {
	"5y",
	"2y",
	"1y",
	"ytd",
	"6m",
	"3m",
	"1m"
};

const char *DelayedQuote[] = {
	"symbol",
	"delayedPrice",
	"delayerSize",
	"delayerPriceTime",
	"processedTime"
};

#define SYMBOL				0
#define DELAYED_PRICE		1
#define DELAYED_SIZE		2
#define DELAYED_PRICE_TIME	3
#define DELAYED_TIME		4
