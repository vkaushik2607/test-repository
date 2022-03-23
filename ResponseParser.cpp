#include "ResponseParser.h"
#include <sstream>
#include <iostream>

ResponseParser::ResponseParser()
{
	httpVersion = "";
	httpStatus = "";
	number_of_invalid_headers = 0;
	number_of_valid_headers = 0;
}

ResponseParser::~ResponseParser()
{

}

void ResponseParser::parseResponse(const std::string &response)
{
	if (response.empty())
		return;

	//Logic to parse the response
	std::istringstream streamObj(response);
	std::string header_key;
	std::string::size_type index;

	int lineCount = 0;
	while(std::getline(streamObj, header_key) && header_key != "\r") 
	{
		//Parse first line of the message to get HTTP version
		if (lineCount == 0)
		{			
			std::istringstream iss(header_key);
			do
			{
				std::string subs;
				iss >> subs;	
				// put a check if HTTP header does not contain string HTTP, return "Invalid status line"

				if(subs !=" ")
					httpHeaderInfo.push_back(trim(subs));
			} while (iss);					
		}
		else
		{
			//Now parse rest of the messages
			index = header_key.find(':', 0);
			if (index != std::string::npos)
			{
				//insert values in the map, just in case we need to access those values
				httpMap.insert(std::make_pair(
					(header_key.substr(0, index)),
					(header_key.substr(index + 1))
				));

				//if found a valid header increment
				number_of_valid_headers++;
			}
			else
			{
				//if found an invalid header , increment the invalid count
				number_of_invalid_headers++;
			}

		}	
		
		++lineCount;
	}	
}

void ResponseParser::printOutPut()
{
	//fill the http version info
	if (httpHeaderInfo.empty())
	{
		std::cout << "Invalid status line" << std::endl;
		return;
	}
		
	std::string httpVersionHeader = httpHeaderInfo[0]; //Index 0 has HTTP/version
	httpStatus = httpHeaderInfo[1]; //index 1 contains the status

	if (httpVersionHeader.find("HTTP") == std::string::npos) {
		std::cout << "Invalid status line" << std::endl;
		return;
	}

	//Parse the first line to get http version
	std::string delimiter = "/";
	std::string version = httpVersionHeader.substr(httpVersionHeader.find_first_of(delimiter) + 1); //find the version of the HTTP
	httpVersion = version; // HTTP version

	//Format the output messages
	std::cout << "HTTP Version: "<<httpVersion << std::endl;
	std::cout << "Status: "<<httpStatus << std::endl;
	std::cout << "Number of valid headers: "<<number_of_valid_headers << std::endl;
	std::cout << "Number of invalid headers: "<<number_of_invalid_headers << std::endl;
}