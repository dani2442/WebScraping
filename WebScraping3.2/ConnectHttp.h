#pragma once

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <iostream>
#include <string>
#include <vector>
#include "File.h"

#define CURL_STATICLIB
#include "curl/curl.h"

#ifdef _DEBUG
# pragma comment(lib,"curl/libcurl_a_debug.lib")
#else
# pragma comment(lib,"curl/libcurl_a.lib")
#endif
using namespace rapidjson;
#undef GetObject 
class ConnectHttp
{
public:
	ConnectHttp();
	~ConnectHttp();

	static void Init();

	std::string _Request(std::string url);
	void RequestReadJson(std::string url, std::string &content);
	void CRequestReadJson(std::string url, char *&content);
	void RequestWriteJson(std::string url, std::string path);
	void RequestAddJson(std::string url, std::string path,std::string key);

	std::string name;
	static const std::string path;
	static const std::string URL;

private:
	static bool b_init;

	static size_t Swriter(char*data, size_t size, size_t nmemb, std::string *writerData);
	static size_t Fwriter(void*ptr, size_t size, size_t nmemb, FILE* stream);
	static size_t Cwriter(char * data, size_t size, size_t nmemb, char *&writerData);
};

const std::string ConnectHttp::URL = "https://api.iextrading.com/1.0/stock/";
const std::string ConnectHttp::path = "Data/";
bool ConnectHttp::b_init = false;

ConnectHttp::ConnectHttp()
{
	ConnectHttp::Init();
}

ConnectHttp::~ConnectHttp()
{
	//curl_global_cleanup();
	//ConnectHttp::b_init = true;
}

inline std::string ConnectHttp::_Request(std::string url)
{
	std::string content;
	CURL *curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Swriter);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content);
		curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}
	return content;
}

inline void ConnectHttp::RequestReadJson(std::string url, std::string &content)
{
	CURL *curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Swriter);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content);
		curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}
}

inline void ConnectHttp::CRequestReadJson(std::string url, char *&content)
{
	CURL *curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Cwriter);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content);
		curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}
}

inline void ConnectHttp::RequestWriteJson(std::string url, std::string path)
{
	FILE *fp;
	CURL *curl = curl_easy_init();
	if (curl) {
		fp = fopen(path.c_str(), "w");
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Fwriter);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
		curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		fclose(fp);
	}
}

inline void ConnectHttp::RequestAddJson(std::string url, std::string path,std::string key)
{
	std::string snewsource;
	RequestReadJson(url, snewsource);
	if (snewsource.size() < 5)
		return;
	char *newsource = &newsource[0u];
	Document old,newdoc;
	newdoc.Parse(newsource);
	char* data = NULL;
	if (File::read(path, data)){
		old.Parse(data);

		std::string old_elem = old[old.Size() - 1][old[0][key.c_str()].GetInt()].GetString(); //////////////////////////// getstring() correct
		for (Value::ConstValueIterator itr = newdoc.Begin(); itr != newdoc.End(); ++itr) {
			std::string name = (*itr)[key.c_str()].GetString();
			if (name.compare(old_elem)==0){
				newdoc.Erase(newdoc.Begin(), itr+1);
				break;
			}
		}

		Document temp(&old.GetAllocator());
		for (Value::ConstValueIterator itr = newdoc.Begin(); itr != newdoc.End(); ++itr) {
			temp.SetArray();
			std::cout << (*itr)["date"].GetString()<<  std::endl;
			for (Value::ConstMemberIterator itr2 = itr->MemberBegin(); itr->MemberEnd() != itr2; ++itr2) {
				Value d;
				d =(Value&) (itr2->value);                             
				temp.PushBack(d, temp.GetAllocator());
			}
			old.PushBack(temp, old.GetAllocator());
		}
		if(temp.IsArray())temp.Clear();


		StringBuffer buffer;
		Writer<StringBuffer> writer(buffer);
		old.Accept(writer);
		newsource=_strdup( buffer.GetString() );
	}
	else {
		Document translated;
		translated.SetArray();
		Document temp(&translated.GetAllocator());
		temp.SetObject();
		int i = 0;
		for (Value::ConstMemberIterator itr2 = newdoc[0].MemberBegin(); newdoc[0].MemberEnd() != itr2; ++itr2) {
			Document::StringRefType d(itr2->name.GetString());
			temp.AddMember(d,i, temp.GetAllocator());
			i++;
		}

		translated.PushBack(temp, translated.GetAllocator());

		
		for (Value::ConstValueIterator itr = newdoc.Begin(); itr != newdoc.End(); ++itr) {
			temp.SetArray();
			for (Value::ConstMemberIterator itr2 = itr->MemberBegin(); itr->MemberEnd() != itr2; ++itr2) {
				Value d;
				d =(Value&) (itr2->value);                             
				temp.PushBack(d, temp.GetAllocator());
			}
			translated.PushBack(temp, translated.GetAllocator());
		}
		if(temp.IsArray())temp.Clear();
		StringBuffer buffer;
		Writer<StringBuffer> writer(buffer);
		translated.Accept(writer);
		newsource=_strdup( buffer.GetString() );

	}
	File::write(path,newsource);
	delete[] newsource;
	delete[] data; 
}

inline void ConnectHttp::Init()
{
	if (!ConnectHttp::b_init) {
		curl_global_init(CURL_GLOBAL_ALL);
		ConnectHttp::b_init = true;
	}
}

inline size_t ConnectHttp::Swriter(char * data, size_t size, size_t nmemb, std::string *writerData)
{
	if (writerData == NULL)
		return 0;
	writerData->append(data, size*nmemb);
	return size * nmemb;
}
inline size_t Cwriter(char *ptr, size_t size, size_t nmemb, void *userdata) {
	
}

inline size_t ConnectHttp::Fwriter(void *ptr, size_t size, size_t nmemb, FILE * stream)
{
	size_t written;
    written = fwrite(ptr, size, nmemb, stream);
	fclose(stream);
    return written;
}

inline size_t ConnectHttp::Cwriter(char * data, size_t size, size_t nmemb, char *& writerData)
{
	writerData = new char[strlen(data)];
	strcpy(writerData, data);
	return strlen(writerData);
}



