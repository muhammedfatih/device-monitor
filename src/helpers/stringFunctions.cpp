#include "stringFunctions.h"

bool startsWith(string const& fullString, string const& starting) {
	if (fullString.length() >= starting.length()) {
		return (0 == fullString.compare(0, starting.length(), starting));
	}
	else {
		return false;
	}
}

bool replace(std::string& str, const std::string& from, const std::string& to) {
	size_t start_pos = str.find(from);
	if (start_pos == std::string::npos)
		return false;
	str.replace(start_pos, from.length(), to);
	return true;
}