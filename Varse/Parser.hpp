#pragma once

#include <functional>
#include <string>

class Value;

struct map;

class Parser
{
public:
	//void f(std::function< int(int) >& lambda);
	void setToken(std::string, std::function<void(int)>);
	void setToken(std::string, std::function<void(float)>);
	void setToken(std::string, std::function<void(std::string)>);
	//void setToken(std::wstring, function);
	bool parse(int argc, char* argv[]);
	void setIgnoreMode(bool b) { m_ignore = b; };

	//int parse(std::string); //provided with a \
	void setDelimiter(char);

private:
	map* m_tokens = {};
	//char m_delimiter = ' ';
	bool m_ignore = true;
};