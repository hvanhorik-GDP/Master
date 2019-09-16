#include <iostream>
#include <ostream>
#include <typeinfo>
#include <locale>
#include <cctype>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstring>
#include <memory>
#include <algorithm>

#include "CreateGLHeaders.h"

enum {
	one = 1,
	two = 2,
};

 
//#include "glmLib.h"

using namespace std;

void Tokens(const std::string& in, std::vector<std::string>& out, const string& separators)
{
	std::string temp = in;
	for (size_t i = 1; i < separators.size(); ++i)
	{
		std::replace(temp.begin(), temp.end(), separators[i], separators[0]);
	}

	stringstream check(temp);

	string intermediate;

	// Tokenizing w.r.t. space ' ' 
	while (getline(check, intermediate, separators[0]))
	{
		if (intermediate.size() != 0)
			out.push_back(intermediate);
	}
}

std::string FirstToUpper(const std::string& in)
{
	std::string out = in;
	for (auto& c : out)
	{
		c = tolower(c);
	}
	if (out.size() > 0)
	{
		out[0] = toupper(out[0]);
	}
	return out;
}

template<class T>
void TestVec(const T &in)
{
	auto i = in.length();
	auto j = sizeof(in);
	std::cout << typeid(T[0]).name() << std::endl;
//	type_info k = typeid(T);
}

//template <class T>
//T GetMax(T a, T b) {
//	T result;
//	result = (a > b) ? a : b;
//	return (result);
//}

//void TestVec4(const glm::vec4 &in)
//{
//	int i = in.length();
//	int j = sizeof(in);
//}

int main(int argc, char** argv)
{
	std::string inputFile("input.txt");
	ifstream in(inputFile);
	if (!in)
	{
		cout << "error opening file:" << inputFile << endl;
		return 0;
	}
	ofstream out1("defines.txt", std::ios::out);
	ofstream out2("prototypes.txt", std::ios::out);
	ofstream out_pname("prototypes pname.txt", std::ios::out);
	ofstream out_program("prototypes program.txt", std::ios::out);
	ofstream out_shader("prototypes shader.txt", std::ios::out);
	// pipeline
	// texture
	// buffer
	// framebuffer
	// vaobj
	// attribindex


	while (!in.eof())
	{
		
		std::string line;
		getline(in, line);
		vector <string> tokens;
		std::string delimiters = " \t();";
		Tokens(line, tokens, delimiters);
		std::string newline;
		if (tokens.size() >= 3)
		{
			if (tokens[0] == "#define")
			{
				vector<string> wordTokens;
				Tokens(tokens[1], wordTokens, "_");
				if (wordTokens[0] == "GL")
				{
					wordTokens[0].clear();
					std::string newWord;
					for (auto item : wordTokens)
					{
						newWord += (isdigit(item[0])) ? "_" + item : FirstToUpper(item);
					}
					line = newWord + " = " + tokens[2]  + ",\t\t// " + tokens[1] + "\n";
					out1 << line;
				}
			}
			else
			{
				if (tokens[0] == "typedef" && tokens[2] == "APIENTRYP")
				{
					std::string line2;
					getline(in, line2);
					getline(in, line2);
					vector <string> tokens2;
					Tokens(line2, tokens2, delimiters);
					line = tokens[1] + " " + tokens2[1] + "(";
					for (auto i = 4; i < tokens.size(); ++i)
						line += " " + tokens[i];
					line += ");\n";
					out2 << line;
					if (tokens.size() > 5)
					{
						if (tokens[5] == "pname,")
							out_pname << line;
						if (tokens[5] == "program,")
							out_program << line;
						if (tokens[5] == "shader,")
							out_shader << line;
					}
				}
			}
		}
	}


	//glm::vec3 test = { 1, 2, 3 };
	//TestVec(test);

	//glm::vec4 test2 = { 1,2,3,4 };
	//TestVec(test2);


	std::system("pause");
	return 0;
}