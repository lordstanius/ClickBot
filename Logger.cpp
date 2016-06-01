//---------------------------------------------------------------------------
#pragma hdrstop

#include "Logger.h"
#include <string>
#include <ctime>
#include <stdio.h>
//---------------------------------------------------------------------------

#pragma package(smart_init)

Logger::Logger()
{
}

Logger::Logger(_TCHAR* filename)
{
	Open(filename);
}

Logger::~Logger()
{
}

void Logger::Open(_TCHAR* filename)
{
	_tcscpy(_name, filename);
}

void Logger::Write(_TCHAR* string)
{
	out.open(_name, std::ios_base::out | std::ios_base::app);
	struct std::tm* ts;

	std::time_t time;
	std::time(&time);

	ts = std::localtime(&time);


	_TCHAR buf[10240];
	_stprintf(buf, _T("[%02d:%02d:%02d] "), ts->tm_hour, ts->tm_min, ts->tm_sec);
	_tcscat(buf, string);
	_tcscat(buf, _T("\n"));

	out << buf;
	out.close();
}


void Logger::WriteBinary(const char* string, unsigned int size)
{
	ofstream o(_name, std::ios_base::app | std::ios_base::binary);
	o.write(string, size);
	o.close();
}


void Logger::WriteTimestamp()
{
	out.open(_name, std::ios_base::out | std::ios_base::trunc);
	struct std::tm* ts;

	std::time_t time;
	std::time(&time);

	ts = std::localtime(&time);


	_TCHAR buf[1024];
	_stprintf(buf, _T("%04d-%02d-%02d %02d:%02d:%02d"),	ts->tm_year + 1900, ts->tm_mon + 1, ts->tm_mday, ts->tm_hour, ts->tm_min, ts->tm_sec);
	//_tcscat(buf, string);
	_tcscat(buf, _T("\n"));

	out << buf;
	out.close();
}