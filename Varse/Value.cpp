#include "Value.hpp"
#include <string>
#include <sstream>
#include <algorithm>

bool isNumber(const std::string& s)
{
	return !s.empty() && std::find_if(s.begin(),
		s.end(), [](char c) { return !isdigit(c); }) == s.end();
}

bool isFloat(const std::string& myString)
{
	std::istringstream iss(myString);
	float f;
	iss >> std::noskipws >> f; // noskipws considers leading whitespace invalid
						  // Check the entire string was consumed and if either failbit or badbit is set
	return iss.eof() && !iss.fail();
}

Value::Value()
{
	if (m_string)
		delete m_string;
	m_string = new std::string("");
	
	currentType = None;
}

Value::Value(int i)
{
	m_int = i;
	if (m_string)
		delete m_string;
	m_string = new std::string("");

	currentType = Int;
}

Value::Value(float f)
{
	m_float = f;
	if (m_string)
		delete m_string;
	m_string = new std::string("");

	currentType = Float;
}

Value::Value(std::string s)
{
	if (isNumber(s))
		setValue(stoi(s));
	else if (isFloat(s))
		setValue(stof(s));
	else
		setValue(s);
}

Value::~Value()
{
	if (m_string)
		delete m_string;
}

void Value::setValue(int i)
{
	m_int = i;
	m_float = 0.f;
	
	if (m_string)
		delete m_string;
	m_string = new std::string("");

	currentType = Int;
};

void Value::setValue(float f)
{
	m_int = 0;
	m_float = f;

	if (m_string)
		delete m_string;
	m_string = new std::string("");


	currentType = Float;
}

void Value::setValue(std::string s)
{
	m_int = 0;
	m_float = 0.f;

	if (m_string)
		delete m_string;
	m_string = new std::string(s);


	currentType = String;
};

Value::type Value::getType()
{
	return currentType;
};
	
int Value::getInt()
{ 
	return m_int;
};

float Value::getFloat()
{
	return m_float;
}

std::string Value::getString()
{
	return *m_string;
}

Value & Value::operator=(const Value & val)
{
	m_int = val.m_int;
	m_float = val.m_float;
	m_string = val.m_string;
	currentType = val.currentType;
	return *this;
}

Value & Value::operator=(int & val)
{
	setValue(val);
	return *this;
}

Value & Value::operator=(float & val)
{
	setValue(val);
	return *this;
}

Value & Value::operator=(std::string & val)
{
	setValue(val);
	return *this;
}
