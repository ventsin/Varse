#pragma once
#include <string>

class Value
{
public:
	enum type { Int, Float, String, None };

	Value();
	Value(int i);
	Value(float f);
	Value(std::string s);
	~Value();

	void setValue(int i);
	void setValue(float f);
	void setValue(std::string s);

	type getType();

	int getInt();
	float getFloat();
	std::string getString();

	Value & operator=(const Value &val);
	Value & operator=(int &val);
	Value & operator=(float &val);
	Value & operator=(std::string &val);

private:
	int m_int = 0;
	float m_float = 0.f;
	std::string* m_string;
	type currentType = None;
};