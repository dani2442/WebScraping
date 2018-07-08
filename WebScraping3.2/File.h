#pragma once

#include <rapidjson/filereadstream.h>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <rapidjson/filewritestream.h>
#include <filesystem>
#include <sys/stat.h>
#include <sys/types.h>
using namespace rapidjson;

#if __cplusplus < 201703L
    namespace fs = std::experimental::filesystem;
#else
    namespace fs = std::filesystem;
#endif

class File
{
public:
	File();
	~File();

	static void mkdir(std::string& path);
	static void rmdir(std::string& path,bool remove_all);

	static bool isFile(std::string& path);
	static bool isDir(std::string& path);

	static bool read(std::string path, char *&content);
	static bool write(std::string path, char *&content,bool overwrite);

	static bool FReadStream(std::string path,Document& content);
	static bool FWriteStream(std::string path, Document& d);

	static std::string StringStream();
	static bool FStringBuffer(std::string path, Document& d);

private:
	static struct stat info;
};

struct stat File::info;

File::File()
{
}

File::~File()
{
}

inline void File::mkdir(std::string& path)
{
	if (isDir(path))
		return;
	if (std::count(path.begin(), path.end(), '/') > 0)
		fs::create_directories(path);
	else
		fs::create_directory(path);
}

inline void File::rmdir(std::string& path, bool remove_all)
{
	if (remove_all)
		fs::remove_all(path);
	else
		fs::remove(path);
}

inline bool File::isFile(std::string& path)
{
	struct stat buffer;   
	return (stat (path.c_str(), &buffer) == 0);
}

inline bool File::isDir(std::string& path)
{
	if (stat(path.c_str(), &info) != 0) {
		std::cout << "cannot access: "<<path <<std::endl;
		return false;
	}
	else if (info.st_mode & S_IFDIR)
		return false;
	else
		return true;
}

inline bool File::read(std::string path, char *& source)
{
	FILE *fp = fopen(path.c_str(), "r");
	if (fp != NULL) {
		source = NULL;
		if (fseek(fp, 0L, SEEK_END) == 0) {
			long bufsize = ftell(fp);
			if (bufsize == -1) {}
			source = new char[bufsize + 1];
			if (fseek(fp, 0L, SEEK_SET) != 0) {}
			size_t newLen = fread(source, sizeof(char), bufsize, fp);
			if (ferror(fp) != 0) {
				fputs("Error reading file", stderr);
			}
			else {
				source[newLen++] = '\0';
			}
		}
		fclose(fp);
		return true;
	}
	else
		return false;
}

inline bool File::write(std::string path, char *& content, bool overwrite=true)
{
	FILE* fp;
	if (overwrite)
		fp = fopen(path.c_str(), "w");
	else
		fp = fopen(path.c_str(), "a");
    fwrite(content, sizeof(char),strlen(content), fp);
    fclose(fp);
    return 0;
}
inline bool File::FReadStream(std::string path,Document& d)
{
	FILE *fp = fopen(path.c_str(), "r");
	if (fp != NULL) {
		char* content = NULL;
		if (fseek(fp, 0L, SEEK_END) == 0) {
			long bufsize = ftell(fp);
			if (bufsize == -1) {}
			content = new char[bufsize];
			FileReadStream is(fp, content, strlen(content));
			d.ParseStream(is);
		}
		fclose(fp);
		return true;
	}
	else
		return false;
}

inline bool File::FWriteStream(std::string path, Document& d)
{
	FILE* fp;
	if (true)
		fp = fopen(path.c_str(), "w");
	else
		fp = fopen(path.c_str(), "a");
	char *writeBuff = new char[10000];
	FileWriteStream os(fp, writeBuff, sizeof(writeBuff));
	Writer<FileWriteStream>writer(os);
	d.Accept(writer);
    fclose(fp);
	delete[] writeBuff;
    return true;
}

inline bool File::FStringBuffer(std::string path, Document& d)
{
	FILE* fp;
	if (true)
		fp = fopen(path.c_str(), "w");
	else
		fp = fopen(path.c_str(), "a");
	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	d.Accept(writer);
	const char* output=buffer.GetString();
	fwrite(output, sizeof(char),strlen(output)+1, fp);
    fclose(fp);
    return true;

}
