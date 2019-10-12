#pragma once

#include <glm/glm.hpp>

#include <string>
#include <vector>

#pragma comment (lib, "Utilities.lib")

class cFormat
{
public:

	// Some helper methods for loading and packing properties
	static glm::vec4 LoadVec4(const std::string& in);
	static std::string PackVec4(const glm::vec4& in);
	static glm::vec3 LoadVec3(const std::string& in);
	static std::string PackVec3(const glm::vec3& in);
	static bool LoadBool(const std::string& in);
	static std::string PackBool(bool in);
	static float LoadFloat(const std::string& in);
	static std::string PackFloat(float in);
	static int LoadInt(const std::string& in);
	static std::string PackInt(int in);
	static void Tokens(const std::string& in, std::vector<std::string>& out, const std::string& separators);

};

