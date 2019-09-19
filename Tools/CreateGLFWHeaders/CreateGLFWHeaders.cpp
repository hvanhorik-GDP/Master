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

#ifdef __WIN32__
#include <winsock2.h>
#else
#include <winsock2.h>
#endif

#include <map>

#include "CreateGLFWHeaders.h"

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

string replace_str(string& str, const string& from, const string& to)
{
	while (str.find(from) != string::npos)
		str.replace(str.find(from), from.length(), to);
	return str;
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
	typedef vector<string> lines;

	map<string, lines> search_defines;
	lines other_gl_defines;

	//search_defines["MOUSE"] = lines();
	//search_defines["CONTEXT"] = lines();
	//search_defines["DEPTH"] = lines();
	//search_defines["INVALID"] = lines();
	//search_defines["STENCIL"] = lines();
	//search_defines["VERSION"] = lines();
	//search_defines["ACCUM"] = lines();
	//search_defines["CURSOR"] = lines();
	//search_defines["JOYSTICK"] = lines();
	//search_defines["KEY"] = lines();
	//search_defines["MOD"] = lines();	
	//search_defines["MOUSE"] = lines();
	//search_defines["OPENGL"] = lines();
	//search_defines["RELEASE"] = lines();

	map<string, lines> search_names;
	lines other_names;
	lines typedefs;

	/*search_names["program"] = lines();
	search_names["pname"] = lines();
	search_names["shader"] = lines();
	search_names["light"] = lines();
	search_names["buf"] = lines();
	search_names["face"] = lines();
	search_names["mode"] = lines();
	search_names["coord"] = lines();
	search_names["name"] = lines();
	search_names["target"] = lines();
	search_names["plane"] = lines();
	search_names["mask"] = lines();
	search_names["mode"] = lines();
	search_names["face"] = lines();
	search_names["index"] = lines();
	search_names["location"] = lines();
	search_names["index"] = lines();
	search_names["target"] = lines();
	search_names["sampler"] = lines();
	search_names["pipeline"] = lines();
	search_names["attribindex"] = lines();
	search_names["framebuffer"] = lines();
	search_names["renderbuffer"] = lines();
	search_names["vaobj"] = lines();
	search_names["map"] = lines();
	search_names["attribindex"] = lines();
	search_names["bindingindex"] = lines();
	search_names["identifier"] = lines();
	search_names["texture"] = lines();
	search_names["id"] = lines();
	search_names["buffer"] = lines();
	search_names["xfb"] = lines();
	search_names["readFramebuffer"] = lines();
	search_names["shadertype"] = lines();*/

	while (!in.eof())
	{
		std::string line;
		getline(in, line);
		vector <string> tokens;
		std::string delimiters = " \t;";
		Tokens(line, tokens, delimiters);
		if (tokens.size() >= 3)
		{
		
			if (tokens[0] == "#define")
			{
				// Search for all of the #defines, order them and create new strings
				// From:
				//      #define GL_NAME_NAME1_NAME2 0xNNNN
				// to:
				//      Name_Name1_Name2 = 0xNNNNN			// GL_NAME_NAME1_NAME2
				// Place in a namespace if found in the search words
				// Sort them into groups
				// and sort all of the defines

				vector<string> wordTokens;
				Tokens(tokens[1], wordTokens, "_");
				if (wordTokens[0] == "GLFW")
				{
					wordTokens[0].clear();
					std::string newWord;
					std::string found;
					for (auto item : wordTokens)
					{
						newWord += (isdigit(item[0])) ? "_" + item : FirstToUpper(item);
						if (found.size() == 0 && search_defines.find(item) != search_defines.end())
							found = item;
					}
					string newline = "\t" + newWord + " = " + tokens[2] + ",\t\t\t\t// " + tokens[1] + "\n";
					
					if (found.size() != 0)
					{
						search_defines[found].push_back(newline);
					}
					else
						other_gl_defines.push_back(newline);
				}
			}
			else
			{
				if (tokens[0] == "GLFWAPI" )
				{
					// Grab the function prototypes from
					//	 GLFWAPI GLFWdropfun glfwSetDropCallback(GLFWwindow* window, GLFWdropfun cbfun);
					// to
					//	 glfwSetDropCallback(GLFWwindow* window, GLFWdropfun cbfun);
					// Sort them into groups
					// and Sort all of the functions within each group

					string newline;
					for (auto i = 1; i < tokens.size(); ++i)
					{
						std::string temp = replace_str(tokens[i], "glfw", "");
						temp = replace_str(temp, "GLFW", "");
						newline += " " + temp;
					}
					
					newline += ";\n";
					other_names.push_back(newline);
				}
				else if (tokens[0] == "typedef")
				{
					std::string newline = replace_str(line, "GLFW", "");
					typedefs.push_back(newline);
				}
			}
		}
	}

	{
		// Place all of the defines into a new file in the form
		//      // name
		//      namespace  name
		//		{
		//             list of lines containing name (sorted)
		//      }} // name

		ofstream out1("defines.txt", std::ios::out);
		for (auto i : search_defines)
		{
//			std::sort(i.second.begin(), i.second.end());
			out1 << "//\n// " << ::FirstToUpper(i.first) << "\n//\n";
			out1 << "enum e" << ::FirstToUpper(i.first) << "\n";
			out1 << "{\n";
			for (auto j : i.second)
			{
				out1 << j;
			}
			out1 << "} e" << ::FirstToUpper(i.first) << ";\t// e" << ::FirstToUpper(i.first) <<  "\n\n";
		}

//		std::sort(other_gl_defines.begin(), other_gl_defines.end());
		out1 << "//\n// " << "eOther GL defines" << "\n//\n";
		out1 << "enum " << "eOther" << "\n";
		out1 << "{\n";
		for (auto i : other_gl_defines)
			out1 << i;
		out1 << "} eOther;\t// " << "eOther" << "\n\n";
	}
	{
		// Place all of the prototypes into a new file in the form
			//      // name
			//      namespace  name
			//		{
			//             list of prototypes containing name (sorted)
			//      }} // name


		ofstream out2("prototypes.txt", std::ios::out);
		for (auto i : typedefs)
		{
			out2 << i << endl;
		}
		for (auto i : search_names)
		{
			std::sort(i.second.begin(), i.second.end());
			out2 << "//\n// " << ::FirstToUpper(i.first) << "\n//\n";
			out2 << "namespace " << ::FirstToUpper(i.first) << "\n";
			out2 << "{\n";
			for (auto j : i.second)
			{
				out2 << j;
			}
			out2 << "}\t // " << ::FirstToUpper(i.first) << "\n\n";
		}

		std::sort(other_names.begin(), other_names.end());
		out2 << "//\n// " << "Other" << "\n//\n";
		out2 << "namespace " << "Other" << "\n";
		out2 << "{\n";
		for (auto i : other_names)
			out2 << i;
		out2 << "}\t // " << "Other"  << "\n\n";
	}

	std::system("pause");
	return 0;
}