#include "Parser.hpp"
#include "Value.hpp"
#include <vector>

struct pairs
{
	std::vector<std::pair<std::string, std::function<void(void)>>> m_voidmap;
	std::vector<std::pair<std::string, std::function<void(int)>>> m_intmap;
	std::vector<std::pair<std::string, std::function<void(float)>>> m_floatmap;
	std::vector<std::pair<std::string, std::function<void(std::string)>>> m_stringmap;
};

void Parser::setToken(std::string str, std::function<void(void)> func)
{
	//func("1440");
	m_tokens->m_voidmap.push_back(std::make_pair(str, func));
}

void Parser::setToken(std::string str, std::function<void(int)> func)
{
	//func(1440);
	m_tokens->m_intmap.push_back(std::make_pair(str, func));
}

void Parser::setToken(std::string str, std::function<void(float)> func)
{
	//func(1440.f);
	m_tokens->m_floatmap.push_back(std::make_pair(str, func));
}

void Parser::setToken(std::string str, std::function<void(std::string)> func)
{
	//func("1440");
	m_tokens->m_stringmap.push_back(std::make_pair(str, func));
}

bool Parser::parse(int argc, char* argv[])
{
	std::vector<std::string> vec(argv, argv + argc);

	if (!m_tokens->m_voidmap.empty())
	{
		for (size_t i = 0; i < m_tokens->m_voidmap.size(); i++)
		{
			auto it = std::find(vec.begin(), vec.end(), m_tokens->m_voidmap[i].first);
			if (it != vec.end())
			{
				m_tokens->m_voidmap[i].second();
			}
		}
	}
#pragma message("Finish this - parser.cpp @ line 52")
	if (!m_tokens->m_voidmap.empty())
	{
		for (size_t i = 0; i < m_tokens->m_voidmap.size(); i++)
		{
			auto it = std::find(vec.begin(), vec.end(), m_tokens->m_voidmap[i].first);
			if (it != vec.end())
			{
				m_tokens->m_voidmap[i].second();
			}
		}
	}

	if (!m_tokens->m_voidmap.empty())
	{
		for (size_t i = 0; i < m_tokens->m_voidmap.size(); i++)
		{
			auto it = std::find(vec.begin(), vec.end(), m_tokens->m_voidmap[i].first);
			if (it != vec.end())
			{
				m_tokens->m_voidmap[i].second();
			}
		}
	}

	if (!m_tokens->m_stringmap.empty())
	{
		for (size_t i = 0; i < m_tokens->m_stringmap.size(); i++)
		{
			auto it = std::find(vec.begin(), vec.end(), m_tokens->m_stringmap[i].first);
			if (it != vec.end())
			{
				size_t index = it - vec.begin();
				if (index < vec.size());
				{
					m_tokens->m_stringmap[i].second(vec[index + 1]);
				}
			}
		}
	}
}
