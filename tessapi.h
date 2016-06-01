#ifndef TESSAPI_H
#define TESSAPI_H

extern "C" int   __stdcall TessAPI_Initialize(const char* dataPath, const char* language);
extern "C" void  __stdcall TessAPI_SetImage(unsigned char* pBuffer, int width, int height, int bytesPerPixel, int bytesPerLine);
extern "C" char* __stdcall TessAPI_GetUTF8Text();
extern "C" void  __stdcall TessAPI_Clear();
extern "C" void  __stdcall TessAPI_End();

#endif
