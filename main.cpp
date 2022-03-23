#include <iostream>

#include "ResponseParser.h"

using namespace std;


int main(int argc, char*argv[])
{
	//input message with one invalid header
	std::string httpResponse = "HTTP/1.0 200 OK\r\n"
		"cache-control: public\r\n"
		"content-length: 0\r\n"
		"content-type: image/svg+xml\r\n"
		"Transfer-encoding: chunked\r\n"
		"date: Tue, 22 Mar 2022 22:23:42 GMT\r\n"
		"invalid_header\r\n"		
		;
		
	//input http response with invalid header, no HTTP version
	std::string httpResponseInvalid = "Header1 :value1\r\n"
		"cache-control: public\r\n"
		"content-length: 0\r\n"
		"content-type: image/svg+xml\r\n"
		"Transfer-encoding: chunked\r\n"
		"date: Tue, 22 Mar 2022 22:23:42 GMT\r\n"		
		;

	//input http response with 2 invalid headers
	std::string httpResponse2Invalid = "HTTP/1.0 200 OK\r\n"
		"cache-control: public\r\n"
		"content-length: 0\r\n"
		"content-type: image/svg+xml\r\n"
		"Transfer-encoding: chunked\r\n"
		"invalid_header\r\n"
		"date: Tue, 22 Mar 2022 22:23:42 GMT\r\n"
		"invalid_header\r\n"
		;

	std::string emptyResponse = "";

	//Create an object of ResponseParser and parse and print output
	std::unique_ptr<ResponseParser> parseObj = std::make_unique<ResponseParser>();
	parseObj->parseResponse(httpResponse);
	//parseObj->parseResponse(httpResponseInvalid);
	//parseObj->parseResponse(httpResponse2Invalid);
	//parseObj->parseResponse(emptyResponse);
	parseObj->printOutPut();

}