#pragma once

#include <functional>
#include <vector>
#include <string>

namespace va
{
	struct map
	{
		std::vector<std::pair<std::string, std::function<void(int)>>> m_intmap;
		std::vector<std::pair<std::string, std::function<void(float)>>> m_floatmap;
		std::vector<std::pair<std::string, std::function<void(std::string)>>> m_stringmap;
	};

	class Parser
	{
	public:
		void setToken(std::string, std::function<void(int)>);
		void setToken(std::string, std::function<void(float)>);
		void setToken(std::string, std::function<void(std::string)>);

		void setIgnoreMode(bool b) { m_ignore = b; };

		bool parse(int argc, char* argv[]);
		bool parse(std::string, char delimiter);
		bool parse(std::vector<std::string>);
		bool parse(std::vector<char*>);

	private:
		map m_tokens;
		bool m_ignore = true;
	};
};