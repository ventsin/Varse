#include "Parser.hpp"
#include "Value.hpp"
#include <map>

struct map
{
	std::map<std::string, std::function<void(int)>> m_intmap;
	std::map<std::string, std::function<void(float)>> m_floatmap;
	std::map<std::string, std::function<void(std::string)>> m_stringmap;
};

void Parser::setToken(std::string str, std::function<void(int)> func)
{
	//func(1440);
	m_tokens->m_intmap[str] = func;
}

void Parser::setToken(std::string str, std::function<void(float)> func)
{
	//func(1440.f);
	m_tokens->m_floatmap[str] = func;
}

void Parser::setToken(std::string str, std::function<void(std::string)> func)
{
	//func("1440");
	m_tokens->m_stringmap[str] = func;
}

bool Parser::parse(int argc, char* argv[])
{
	if (m_ignore)
	{
		if (argc > 1)
		{
			for (int i = 0; i < argc; i++)
			{
				auto it = m_tokens->m_stringmap.find(argv[i]);
				if (it != m_tokens->m_stringmap.end())
				{
					std::string str(argv[i + 1]);
					if(it->second)
						it->second(str);
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
			auto it = m_tokens->m_stringmap.find(argv[i]);
			if (it != m_tokens->m_stringmap.end())
			{
				std::string str(argv[i + 1]);
				if(it->second)
					it->second(str);
			}
		}
	}
	return true;
}