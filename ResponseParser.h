#pragma once

#include <map>
#include <string>
#include <vector>

class ResponseParser
{
public:
	ResponseParser();
	~ResponseParser();

	//function to parse the http response
	void parseResponse(const std::string &response);
	
	//function to print output message
	void printOutPut();
private:	
	//Map to hold header key and values
	std::map<std::string, std::string> httpMap;

	//Vector to hold all values of the first HTTP version line separated by space
	std::vector<std::string> httpHeaderInfo;

	//function to trim the strings for white spaces
	inline std::string trim(std::string& str)
	{
		str.erase(str.find_last_not_of(' ') + 1); //removing suffixing spaces
		str.erase(0, str.find_first_not_of(' ')); //removing prefixing spaces
		return str;
	};		

	std::string httpVersion;
	std::string httpStatus;
	int number_of_valid_headers;
	int number_of_invalid_headers;	
};