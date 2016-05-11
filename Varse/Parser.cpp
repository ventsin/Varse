#include "Parser.hpp"
#include <algorithm>
#include <sstream>
using namespace va;

std::vector<std::string> split(std::string str, char delimiter)
{
	std::vector<std::string> internal;
	std::stringstream ss(str); // Turn the string into a stream.
	std::string tok;

	while (getline(ss, tok, delimiter)) {
		internal.push_back(tok);
	}

	return internal;
}

bool isInteger(const std::string & s)
{
	if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;

	char * p;
	strtol(s.c_str(), &p, 10);

	return (*p == 0);
}

bool isFloat(const std::string& myString)
{
	std::istringstream iss(myString);
	float f;
	iss >> std::noskipws >> f; // noskipws considers leading whitespace invalid
							   // Check the entire string was consumed and if either failbit or badbit is set
	return iss.eof() && !iss.fail();
}

void Parser::setToken(std::string str, std::function<void(int)> func)
{
	//func(1440);
	m_tokens.m_intmap.push_back(std::make_pair(str, func));
}

void Parser::setToken(std::string str, std::function<void(float)> func)
{
	//func(1440.f);
	m_tokens.m_floatmap.push_back(std::make_pair(str, func));
}

void Parser::setToken(std::string str, std::function<void(std::string)> func)
{
	//func("1440");
	m_tokens.m_stringmap.push_back(std::make_pair(str, func));
}

bool Parser::parse(int argc, char* argv[])
{
	if (m_ignore)
	{
		if (argc > 1)
		{
			for (int i = 0; i < argc; i++)
			{
				auto it = std::find_if(m_tokens.m_stringmap.begin(), m_tokens.m_stringmap.end(),
					[&](std::pair<std::string, std::function<void(std::string)>> fd)
				{
					return fd.first == argv[i];
				});

				if (it != m_tokens.m_stringmap.end())
				{
					std::string str(argv[i + 1]);
					if(it->second)
						it->second(str);
				}
			}

			for (int i = 0; i < argc; i++)
			{
				auto it = std::find_if(m_tokens.m_intmap.begin(), m_tokens.m_intmap.end(),
					[&](std::pair<std::string, std::function<void(int)>> fd)
				{
					return fd.first == argv[i];
				});

				if (it != m_tokens.m_intmap.end())
				{
					std::string str(argv[i + 1]);
					if (isInteger(str) && it->second)
						it->second(std::stoi(str));
				}
			}

			for (int i = 0; i < argc; i++)
			{
				auto it = std::find_if(m_tokens.m_floatmap.begin(), m_tokens.m_floatmap.end(),
					[&](std::pair<std::string, std::function<void(float)>> fd)
				{
					return fd.first == argv[i];
				});

				if (it != m_tokens.m_floatmap.end())
				{
					std::string str(argv[i + 1]);
					if (isFloat(str) && it->second)
						it->second(std::stof(str));
				}
			}
		}
		else
			return false;
	}
	else
	{
		for (int i = 0; i < argc; i++)
		{
			auto it = std::find_if(m_tokens.m_stringmap.begin(), m_tokens.m_stringmap.end(),
				[&](std::pair<std::string, std::function<void(std::string)>> fd)
			{
				return fd.first == argv[i];
			});

			if (it != m_tokens.m_stringmap.end())
			{
				std::string str(argv[i + 1]);
				if (it->second)
					it->second(str);
			}
		}

		for (int i = 0; i < argc; i++)
		{
			auto it = std::find_if(m_tokens.m_intmap.begin(), m_tokens.m_intmap.end(),
				[&](std::pair<std::string, std::function<void(int)>> fd)
			{
				return fd.first == argv[i];
			});

			if (it != m_tokens.m_intmap.end())
			{
				std::string str(argv[i + 1]);
				if (isInteger(str) && it->second)
					it->second(std::stoi(str));
			}
		}

		for (int i = 0; i < argc; i++)
		{
			auto it = std::find_if(m_tokens.m_floatmap.begin(), m_tokens.m_floatmap.end(),
				[&](std::pair<std::string, std::function<void(float)>> fd)
			{
				return fd.first == argv[i];
			});

			if (it != m_tokens.m_floatmap.end())
			{
				std::string str(argv[i + 1]);
				if (isFloat(str) && it->second)
					it->second(std::stof(str));
			}
		}
	}
	return true;
}

bool Parser::parse(std::string str, char delimiter)
{
	return parse(split(str, delimiter));
}

bool Parser::parse(std::vector<std::string> vec)
{
	std::vector<char*> v;
	for (auto &e : vec)
		v.push_back(const_cast<char*>(e.c_str()));

	return parse(v);
}

bool Parser::parse(std::vector<char*> vec)
{
	return parse(vec.size(), vec.data());
}