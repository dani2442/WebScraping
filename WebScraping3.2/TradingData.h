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

	static void BatchRequests();
	static void Book();
	void Charts();
	static void Company();
	static void DelayedQuote();
	static void Dividends();
	static void Earnings();
	static void EffectiveSpread();
	static void Financials();
	static void HistoricalPrices();
	static void KeyStats();
	static void LargestTrades();
	static void List();
	static void Logo();
	static void News();
	static void OHLC();
	static void OpenClose();
	static void Peers();
	static void Previous();
	static void Price();
	static void Quote();
	static void Relevant();
	static void Splits();
	static void TimeSeries();
	static void VolumeByVenue();

	std::string name;
	const static std::string extension;
private:
	Date date;	
};

const std::string TradingData::extension = ".24d";

TradingData::TradingData(std::string name):
	name(name),
	date()
{
	ConnectHttp::Init();
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

void TradingData::Charts()
{
	ConnectHttp connect;
	std::string c_path = ConnectHttp::path + name;
	File::mkdir(c_path);
	c_path+= "/chart_1d"+TradingData::extension;
	//std::string c_url = ConnectHttp::URL + "chart?" + _Parameters[Parameters::SYMBOLS] + "=" + _name + "&" + _Parameters[Parameters::RANGE] + "=" + _Range[Date::__range];
	std::string c_url = ConnectHttp::URL + name + "/chart/" + _Range[Date::__range];
	c_path=ConnectHttp::path + name+"/chart_1d"+TradingData::extension;
	connect.RequestAddJson(c_url, c_path,"date");
time_t tempdate = Date::t_date30;
	while (Date::t_date >tempdate) {
		tm* temp = localtime(&tempdate);
		std::stringstream mon;mon << std::setfill('0') << std::setw(2) << temp->tm_mon;
		std::stringstream day;day << std::setfill('0') << std::setw(2) << temp->tm_mday;
		std::string s_date(std::to_string(temp->tm_year + 1900) + mon.str() + day.str());
		std::string c_url = ConnectHttp::URL + name + "/chart/date/" + s_date;
		std::string c_path = ConnectHttp::path + name +"/" +s_date+TradingData::extension;
		connect.RequestAddJson(c_url, c_path, "minute");
		tempdate += i_Range2;
	}
}
