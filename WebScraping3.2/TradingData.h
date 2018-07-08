#pragma once
#include "ConnectHttp.h"
#include "Macros.h"
#include "File.h"
#include "Date.h"
#include <thread>
#include <iostream>
#include <iomanip>
#include <sstream>

#define N_FUNCTIONS 23

class TradingData
{
public:
	//TradingData(std::vector<std::string> name);
	TradingData(std::string name);
	~TradingData();

	void EXECUTE();

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
	//void OpenClose(bool overwrite=true);
	void Peers();
	void Previous();
	void Price();
	void Quote();
	void Relevant();
	void Splits();
	void TimeSeries();
	void VolumeByVenue();

	void S_Previous();
	void S_Symbols();

	std::string name;
	
private:

	typedef void (TradingData::*overall)();
	overall p_overall[N_FUNCTIONS] = {
		&TradingData::Book,
		&TradingData::Charts,
		&TradingData::Company,
		&TradingData::Dividends,
		&TradingData::Earnings,
		&TradingData::EffectiveSpread,
		&TradingData::Financials,
		&TradingData::KeyStats,
		&TradingData::LargestTrades,
		&TradingData::List,
		&TradingData::Logo,
		&TradingData::News,
		&TradingData::OHLC,
		&TradingData::Peers,
		&TradingData::Previous,
		&TradingData::Price,
		&TradingData::Quote,
		&TradingData::Relevant,
		&TradingData::Splits,
		&TradingData::TimeSeries,
		&TradingData::VolumeByVenue,
		&TradingData::S_Symbols,
		&TradingData::S_Previous
	};
	
	
	std::thread p_thread[N_FUNCTIONS];
	static ConnectHttp connect;
	Date date;	
};

ConnectHttp TradingData::connect;

TradingData::TradingData(std::string name):
	name(name),
	date()
{
	std::string Company_path = ConnectHttp::path + name;
	File::mkdir(Company_path);
}


TradingData::~TradingData()
{
}

void TradingData::Book()
{
	bool overwrite = true;
	std::string c_path = ConnectHttp::path + name + "/Book";
	File::mkdir(c_path);
	c_path+="/Book" + EXT;
	std::string c_url = ConnectHttp::URL + name + "/book";
	if(overwrite||!File::isFile(c_path))
	connect.RequestWriteJson(c_url, c_path);

}

void TradingData::Charts()
{
	bool overwrite = true;
	std::string c_path = ConnectHttp::path + name;
	File::mkdir(c_path);
	//std::string c_url = ConnectHttp::URL + "chart?" + _Parameters[Parameters::SYMBOLS] + "=" + _name + "&" + _Parameters[Parameters::RANGE] + "=" + _Range[Date::__range];
	std::string c_url = ConnectHttp::URL + name + "/chart/" + _Range[Date::__range];
	c_path=c_path+"/Chart/chart"+EXT;
	connect.RequestAddJson(c_url, c_path,"date");
	time_t tempdate = Date::t_date30;
	while (Date::t_date >tempdate) {
		tm* temp = localtime(&tempdate);
		std::stringstream mon;mon << std::setfill('0') << std::setw(2) << temp->tm_mon;
		std::stringstream day;day << std::setfill('0') << std::setw(2) << temp->tm_mday;
		std::string s_date(std::to_string(temp->tm_year + 1900) + mon.str() + day.str());
		std::string c_url = ConnectHttp::URL + name + "/chart/date/" + s_date;
		std::string c_path = ConnectHttp::path + name +"/Chart_1d/" +s_date+EXT;
		connect.RequestAddJson(c_url, c_path, "minute");
		tempdate += i_Range2;
	}
}

inline void TradingData::Company()
{
	bool overwrite = false;
	std::string c_path = ConnectHttp::path + name + "/Company/";
	File::mkdir(c_path);
	c_path+="Company" + EXT;
	std::string c_url = ConnectHttp::URL + name + "/company";
	if(overwrite||!File::isFile(c_path))
	connect.RequestWriteJson(c_url, c_path);
}

inline void TradingData::Dividends()
{
	bool overwrite = true;
	std::string c_path = ConnectHttp::path + name + "/Dividends";
	File::mkdir(c_path);
	c_path+="/Dividends" + EXT;
	std::string c_url = ConnectHttp::URL + name + "/dividends/5y";
	if(overwrite||!File::isFile(c_path))
	connect.RequestWriteJson(c_url, c_path);
}

void TradingData::Earnings()
{
	bool overwrite = true;
	std::string c_path = ConnectHttp::path + name + "/Earnings";
	File::mkdir(c_path);
	c_path+="/Earnings" + EXT;
	std::string c_url = ConnectHttp::URL + name + "/earnings";
	if(overwrite||!File::isFile(c_path))
	connect.RequestWriteJson(c_url, c_path);
}

void TradingData::EffectiveSpread()
{
	bool overwrite = true;
	std::string c_path = ConnectHttp::path + name + "/EffectiveSpread";
	File::mkdir(c_path);
	c_path+="/EffectiveSpread" + EXT;
	std::string c_url = ConnectHttp::URL + name + "/effective-spread";
	if(overwrite||!File::isFile(c_path))
	connect.RequestWriteJson(c_url, c_path);
}

inline void TradingData::Financials()
{
	bool overwrite = true;
	std::string c_path = ConnectHttp::path + name + "/Financials";
	File::mkdir(c_path);
	c_path+="/Financials" + EXT;
	std::string c_url = ConnectHttp::URL + name + "/finacials";
	if(overwrite||!File::isFile(c_path))
	connect.RequestWriteJson(c_url, c_path);
}

inline void TradingData::KeyStats()
{
	bool overwrite = true;
	std::string c_path = ConnectHttp::path + name + "/Stats/";
	File::mkdir(c_path);
	c_path+="Stats" + EXT;
	std::string c_url = ConnectHttp::URL + name + "/stats";
	if(overwrite||!File::isFile(c_path))
	connect.RequestWriteJson(c_url, c_path);
}

inline void TradingData::LargestTrades()
{
	bool overwrite = true;
	std::string c_path = ConnectHttp::path + name + "/LargestTrades/";
	File::mkdir(c_path);
	c_path+="LargestTrades" + EXT;
	std::string c_url = ConnectHttp::URL + name + "/largest-trades";
	if(overwrite||!File::isFile(c_path))
	connect.RequestWriteJson(c_url, c_path);
}

inline void TradingData::List()
{
	bool overwrite = true;
	std::string c_path = ConnectHttp::path + name + "/List/";
	std::string c_url = ConnectHttp::URL + name;
	File::mkdir(c_path);
	
	connect.RequestWriteJson(c_url + "/mostactive", c_path+"MostActive" + EXT);

	connect.RequestWriteJson(c_url + "/gainers", c_path + "Gainers" + EXT);

	connect.RequestWriteJson(c_url + "/losers", c_path + "Losers" + EXT);

	connect.RequestWriteJson(c_url + "/iexvolume", c_path + "iexVolume" + EXT);

	connect.RequestWriteJson(c_url + "/iexpercent", c_path + "iexpercent" + EXT);
}

inline void TradingData::Logo()
{
	bool overwrite = false;
	std::string c_path = ConnectHttp::path + name + "/Logo";
	File::mkdir(c_path);
	c_path+="/Logo" + EXT;
	std::string c_url = ConnectHttp::URL + name + "/logo";
	if(overwrite||!File::isFile(c_path))
	connect.RequestWriteJson(c_url, c_path);
}

inline void TradingData::News()
{
	bool overwrite = true;
	std::string c_path = ConnectHttp::path + name + "/News";
	File::mkdir(c_path);
	c_path+="/News" + EXT;
	std::string c_url = ConnectHttp::URL + name + "/news/last/500";
	if(overwrite||!File::isFile(c_path))
	connect.RequestWriteJson(c_url, c_path);
}

inline void TradingData::OHLC()
{
	bool overwrite = true;
	std::string c_path = ConnectHttp::path + name + "/OHLC"; 
	File::mkdir(c_path);
	c_path+="/OHLC" + EXT;
	std::string c_url = ConnectHttp::URL + name + "/ohcl";
	if(overwrite||!File::isFile(c_path))
	connect.RequestWriteJson(c_url, c_path);
}

inline void TradingData::Peers()
{
	bool overwrite = true;
	std::string c_path = ConnectHttp::path + name + "/Peers";
	File::mkdir(c_path);
	c_path+= "/Peers" + EXT;
	std::string c_url = ConnectHttp::URL + name + "/peers";
	if(overwrite||!File::isFile(c_path))
	connect.RequestWriteJson(c_url, c_path);
}

inline void TradingData::Previous()
{
	bool overwrite = true;
	std::string c_path = ConnectHttp::path + name + "/Previous";
	File::mkdir(c_path);
	c_path+= "/Previous" + EXT;
	std::string c_url = ConnectHttp::URL + name + "/previous";
	if(overwrite||!File::isFile(c_path))
	connect.RequestWriteJson(c_url, c_path);
}

inline void TradingData::Price()
{
	bool overwrite = true;
	std::string c_path = ConnectHttp::path + name + "/Price";
	File::mkdir(c_path);
	c_path+="/Price" + EXT;
	std::string c_url = ConnectHttp::URL + name + "/price";
	if(overwrite||!File::isFile(c_path))
	connect.RequestWriteJson(c_url, c_path);
}

inline void TradingData::Quote()
{
	bool overwrite = true;
	std::string c_path = ConnectHttp::path + name + "/Quote";
	File::mkdir(c_path);
	c_path+="/Quote" + EXT;
	std::string c_url = ConnectHttp::URL + name + "/quote";
	if(overwrite||!File::isFile(c_path))
	connect.RequestWriteJson(c_url, c_path);
}

inline void TradingData::Relevant()
{
	bool overwrite = true;
	std::string c_path = ConnectHttp::path + name + "/Relevant";
	File::mkdir(c_path);
	c_path+="/Relevant" + EXT;
	std::string c_url = ConnectHttp::URL + name + "/relevant";
	if(overwrite||!File::isFile(c_path))
	connect.RequestWriteJson(c_url, c_path);
}

inline void TradingData::Splits()
{
	bool overwrite = true;
	std::string c_path = ConnectHttp::path + name + "/Splits";
	File::mkdir(c_path);
	c_path+="/Splits" + EXT;
	std::string c_url = ConnectHttp::URL + name + "/splits/5y";
	if(overwrite||!File::isFile(c_path))
	connect.RequestWriteJson(c_url, c_path);
}

inline void TradingData::TimeSeries()
{
	bool overwrite = true;
	std::string c_path = ConnectHttp::path + name + "/TimeSeries";
	File::mkdir(c_path);
	c_path+="/TimeSeries" + EXT;
	std::string c_url = ConnectHttp::URL + name + "/time-series";
	if(overwrite||!File::isFile(c_path))
	connect.RequestWriteJson(c_url, c_path);
}

inline void TradingData::VolumeByVenue()
{
	bool overwrite = true;
	std::string c_path = ConnectHttp::path + name + "/VolumeByVenue";
	File::mkdir(c_path);
	c_path+="/VolumeByVenue" + EXT;
	std::string c_url = ConnectHttp::URL + name + "/volume-by-venue";
	if(overwrite||!File::isFile(c_path))
	connect.RequestWriteJson(c_url, c_path);
}

inline void TradingData::S_Previous()
{
	bool overwrite = true;
	std::string c_path = ConnectHttp::path + "Market/";
	File::mkdir(c_path);
	c_path+="Previous" + EXT;
	std::string c_url = ConnectHttp::URL + "market/previous";
	if(overwrite||!File::isFile(c_path))
	connect.RequestWriteJson(c_url, c_path);
}

inline void TradingData::S_Symbols()
{
	bool overwrite = false;
	std::string c_path = ConnectHttp::path + "Symbols";
	File::mkdir(c_path);
	c_path+="/Symbols" + EXT;
	std::string c_url = ConnectHttp::URL + "ref-data/symbols";
	if(overwrite||!File::isFile(c_path))
	connect.RequestWriteJson(c_url, c_path);
}

inline void TradingData::EXECUTE()
{
	for (int i = 0; i < N_FUNCTIONS; i++) {
		p_thread[i] = std::thread(p_overall[i],this);
	}
	for (int i = 0; i < N_FUNCTIONS; i++) {
		p_thread[i].join();
	}
	std::cout << "finished successfully" <<std::endl;
}
