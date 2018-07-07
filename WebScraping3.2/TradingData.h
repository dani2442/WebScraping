#pragma once
#include "ConnectHttp.h"
#include "Macros.h"
#include "File.h"
#include "Date.h"
#include <iostream>
#include <iomanip>
#include <sstream>
class TradingData
{
public:
	//TradingData(std::vector<std::string> name);
	TradingData(std::string name);
	~TradingData();

	//void BatchRequests();
	void Book();
	void Charts();
	void Company();
	//void DelayedQuote();
	void Dividends();
	void Earnings();
	void EffectiveSpread();
	void Financials();
	//void HistoricalPrices();
	void KeyStats();
	void LargestTrades();
	void List();
	void Logo();
	void News();
	void OHLC();
	void OpenClose();
	void Peers();
	void Previous();
	void Price();
	void Quote();
	void Relevant();
	void Splits();
	void TimeSeries();
	void VolumeByVenue();

	std::string name;
	const static std::string extension;
private:
	static ConnectHttp connect;
	Date date;	
};

ConnectHttp TradingData::connect;
const std::string TradingData::extension = ".24d";

TradingData::TradingData(std::string name):
	name(name),
	date()
{
	//BatchRequests();
	Book();
	Charts();
	Company();
	//DelayedQuote();
	Dividends();
	Earnings();
	EffectiveSpread();
	Financials();
	//HistoricalPrices();
	KeyStats();
	LargestTrades();
	List();
	Logo();
	News();
	OHLC();
	OpenClose();
	Peers();
	Previous();
	Price();
	Quote();
	Relevant();
	Splits();
	TimeSeries();
	VolumeByVenue();
}
/*
TradingData::TradingData(std::vector<std::string> name) :
	name(std::vector<std::string>{name}),
	date()
{
	ConnectHttp::Init();
}
*/
TradingData::~TradingData()
{
}

void TradingData::Book()
{
	std::string c_path = ConnectHttp::path + name + "Book/Book" + TradingData::extension;
	std::string c_url = ConnectHttp::URL + name + "/book";

	connect.RequestWriteJson(c_url, c_path);

}

void TradingData::Charts()
{
	std::string c_path = ConnectHttp::path + name;
	File::mkdir(c_path);
	//std::string c_url = ConnectHttp::URL + "chart?" + _Parameters[Parameters::SYMBOLS] + "=" + _name + "&" + _Parameters[Parameters::RANGE] + "=" + _Range[Date::__range];
	std::string c_url = ConnectHttp::URL + name + "/chart/" + _Range[Date::__range];
	c_path=c_path+"/Chart/chart"+TradingData::extension;
	connect.RequestAddJson(c_url, c_path,"date");
	time_t tempdate = Date::t_date30;
	while (Date::t_date >tempdate) {
		tm* temp = localtime(&tempdate);
		std::stringstream mon;mon << std::setfill('0') << std::setw(2) << temp->tm_mon;
		std::stringstream day;day << std::setfill('0') << std::setw(2) << temp->tm_mday;
		std::string s_date(std::to_string(temp->tm_year + 1900) + mon.str() + day.str());
		std::string c_url = ConnectHttp::URL + name + "/chart/date/" + s_date;
		std::string c_path = ConnectHttp::path + name +"/Chart_1d/" +s_date+TradingData::extension;
		connect.RequestAddJson(c_url, c_path, "minute");
		tempdate += i_Range2;
	}
}

inline void TradingData::Company()
{
	std::string c_path = ConnectHttp::path + name + "/Company/";
	File::mkdir(c_path);
	c_path+="Company" + TradingData::extension;
	std::string c_url = ConnectHttp::URL + name + "/company";

	connect.RequestWriteJson(c_url, c_path);
}

inline void TradingData::Dividends()
{
	std::string c_path = ConnectHttp::path + name + "/Dividends/Dividends" + TradingData::extension;
	std::string c_url = ConnectHttp::URL + name + "/dividends/5y";

	connect.RequestWriteJson(c_url, c_path);
}

void TradingData::Earnings()
{
	std::string c_path = ConnectHttp::path + name + "/Earnings/Earnings" + TradingData::extension;
	std::string c_url = ConnectHttp::URL + name + "/earnings";

	connect.RequestWriteJson(c_url, c_path);
}

void TradingData::EffectiveSpread()
{
	std::string c_path = ConnectHttp::path + name + "/EffectiveSpread";
	File::mkdir(c_path);
	c_path+="/EffectiveSpread" + TradingData::extension;
	std::string c_url = ConnectHttp::URL + name + "/effective-spread";

	connect.RequestWriteJson(c_url, c_path);
}

inline void TradingData::Financials()
{
	std::string c_path = ConnectHttp::path + name + "/Financials";
	File::mkdir(c_path);
	c_path+="/Financials" + TradingData::extension;
	std::string c_url = ConnectHttp::URL + name + "/finacials";

	connect.RequestWriteJson(c_url, c_path);
}

inline void TradingData::KeyStats()
{
	std::string c_path = ConnectHttp::path + name + "/Stats/";
	File::mkdir(c_path);
	c_path+="Stats" + TradingData::extension;
	std::string c_url = ConnectHttp::URL + name + "/stats";

	connect.RequestWriteJson(c_url, c_path);
}

inline void TradingData::LargestTrades()
{
	std::string c_path = ConnectHttp::path + name + "/LargestTrades/";
	File::mkdir(c_path);
	c_path+="LargestTrades" + TradingData::extension;
	std::string c_url = ConnectHttp::URL + name + "/largest-trades";

	connect.RequestWriteJson(c_url, c_path);
}

inline void TradingData::List()
{
	std::string c_path = ConnectHttp::path + name + "/List/";
	std::string c_url = ConnectHttp::URL + name;
	File::mkdir(c_path);

	connect.RequestWriteJson(c_url + "/mostactive", c_path+"MostActive" + TradingData::extension);

	connect.RequestWriteJson(c_url + "/gainers", c_path + "Gainers" + TradingData::extension);

	connect.RequestWriteJson(c_url + "/losers", c_path + "Losers" + TradingData::extension);

	connect.RequestWriteJson(c_url + "/iexvolume", c_path + "iexVolume" + TradingData::extension);

	connect.RequestWriteJson(c_url+"/iexpercent", c_path+"iexpercent" + TradingData::extension);
}

inline void TradingData::Logo()
{
	std::string c_path = ConnectHttp::path + name + "/Logo";
	File::mkdir(c_path);
	c_path+="/Logo" + TradingData::extension;
	std::string c_url = ConnectHttp::URL + name + "/logo";

	connect.RequestWriteJson(c_url, c_path);
}

inline void TradingData::News()
{
	std::string c_path = ConnectHttp::path + name + "/News/News" + TradingData::extension;
	std::string c_url = ConnectHttp::URL + name + "/news/last/500";

	connect.RequestWriteJson(c_url, c_path);
}

inline void TradingData::OHLC()
{
	std::string c_path = ConnectHttp::path + name + "/OHLC/OHLC" + TradingData::extension;
	std::string c_url = ConnectHttp::URL + name + "/ohcl";

	connect.RequestWriteJson(c_url, c_path);
}

inline void TradingData::OpenClose()
{
}

inline void TradingData::Peers()
{
}

inline void TradingData::Previous()
{
	ConnectHttp connect;

	std::string c_path = ConnectHttp::path + "Market/Previous" + TradingData::extension;
	std::string c_url = ConnectHttp::URL + "market/previous";
	connect.RequestWriteJson(c_url, c_path);

	c_path = ConnectHttp::path + name + "/Previous/Previous" + TradingData::extension;
	c_url = ConnectHttp::URL + name + "/previous";
	connect.RequestWriteJson(c_url, c_path);
}

inline void TradingData::Price()
{
	ConnectHttp connect;
	std::string c_path = ConnectHttp::path + name + "/Price/Price" + TradingData::extension;
	std::string c_url = ConnectHttp::URL + name + "/price";

	connect.RequestWriteJson(c_url, c_path);
}

inline void TradingData::Quote()
{
	ConnectHttp connect;
	std::string c_path = ConnectHttp::path + name + "/Quote/Quote" + TradingData::extension;
	std::string c_url = ConnectHttp::URL + name + "/quote";

	connect.RequestWriteJson(c_url, c_path);
}

inline void TradingData::Relevant()
{
	ConnectHttp connect;
	std::string c_path = ConnectHttp::path + name + "/Relevant/Relevant" + TradingData::extension;
	std::string c_url = ConnectHttp::URL + name + "/relevant";

	connect.RequestWriteJson(c_url, c_path);
}

inline void TradingData::Splits()
{
	ConnectHttp connect;
	std::string c_path = ConnectHttp::path + name + "/Splits/Splits" + TradingData::extension;
	std::string c_url = ConnectHttp::URL + name + "/splits/5y";

	connect.RequestWriteJson(c_url, c_path);
}

inline void TradingData::TimeSeries()
{
	ConnectHttp connect;
	std::string c_path = ConnectHttp::path + name + "/TimeSeries/TimeSeries" + TradingData::extension;
	std::string c_url = ConnectHttp::URL + name + "/time-series";

	connect.RequestWriteJson(c_url, c_path);
}

inline void TradingData::VolumeByVenue()
{
	ConnectHttp connect;
	std::string c_path = ConnectHttp::path + name + "/VolumeByVenue/VolumeByVenue" + TradingData::extension;
	std::string c_url = ConnectHttp::URL + name + "/volume-by-venue";

	connect.RequestWriteJson(c_url, c_path);
}
