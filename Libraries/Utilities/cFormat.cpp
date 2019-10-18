#include "cFormat.h"
#include <sstream>
#include <algorithm>

glm::vec4 cFormat::LoadVec4(const std::string& in)
{
	std::vector<std::string> tokens;
	Tokens(in, tokens, " ,");
	assert(tokens.size() == 4);
	glm::vec4 ret(
		std::stof(tokens[0]),
		std::stof(tokens[1]),
		std::stof(tokens[2]),
		std::stof(tokens[3]));
	return ret;
}

std::string cFormat::PackVec4(const glm::vec4& in)
{
	std::string ret;
	std::stringstream  ss(ret);
	ss << in.x << " "
		<< in.y << " "
		<< in.z << " "
		<< in.w;
	return ss.str();
}

glm::vec3 cFormat::LoadVec3(const std::string& in)
{
	std::vector<std::string> tokens;
	Tokens(in, tokens, " ,");
	assert(tokens.size() == 3);
	glm::vec3 ret(
		std::stof(tokens[0]),
		std::stof(tokens[1]),
		std::stof(tokens[2]));
	return ret;
}


std::string cFormat::PackVec3(const glm::vec3& in)
{
	std::string ret;
	std::stringstream  ss(ret);
	ss << in.x << " "
		<< in.y << " "
		<< in.z;
	return ss.str();
}

bool cFormat::LoadBool(const std::string& in)
{
	if (in == "1")
		return true;
	else if (in == "true")
		return true;
	else if (in == "false")
		return false;
	else if (in == "0")
		return false;
	assert(false);
	return false;

}
std::string cFormat::PackBool(bool in)
{
	return (in) ? "true" : "false";
}

float cFormat::LoadFloat(const std::string& in)
{
	if (in.size() == 0)
		return 0.0f;
	return std::stof(in);
}

std::string cFormat::PackFloat(float in)
{
	return std::to_string(in);
}

int cFormat::LoadInt(const std::string& in)
{
	return std::stoi(in);
}

std::string cFormat::PackInt(int in)
{
	return std::to_string(in);
}

void cFormat::Tokens(const std::string& in, std::vector<std::string>& out, const std::string& separators)
{
	std::string temp = in;
	for (size_t i = 1; i < separators.size(); ++i)
	{
		std::replace(temp.begin(), temp.end(), separators[i], separators[0]);
	}

	std::stringstream check(temp);

	std::string intermediate;

	// Tokenizing w.r.t. space ' ' 
	while (getline(check, intermediate, separators[0]))
	{
		if (intermediate.size() != 0)
			out.push_back(intermediate);
	}
}
