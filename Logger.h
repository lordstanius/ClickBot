//---------------------------------------------------------------------------
#ifndef LoggerH
#define LoggerH
//---------------------------------------------------------------------------
#include <tchar.h>
#include <fstream>



class Logger
{
	#ifdef UNICODE || _UNICODE
	std::wofstream out;
	#else
	std::ofstream out;
	#endif
	_TCHAR _name[1024];

public:
	Logger();
	Logger(_TCHAR* filename);
	~Logger();

    void Open(_TCHAR* filename);
	void Write(_TCHAR* string);
	void WriteBinary(const char* string, unsigned int size);
	void WriteTimestamp();
};

#endif