//#include "tool.h"ShopItem.cpp
#include "tool.h"
char* conv(const char* str){
#ifdef WIN32
	char* result = "error";
	iconv_t iconvH;
	iconvH = iconv_open("utf-8","gbk");
	if(iconvH != 0){
		const char* strChar = str;
		const char** pin = &strChar;

		size_t strLength = strlen(str);
		char* outbuf = (char*)malloc(strLength * 4);
		char* pBuff = outbuf;
		memset(outbuf,0,strLength * 4);
		size_t outLength = strLength * 4;
		if(iconv(iconvH,pin,&strLength,&outbuf,&outLength) == -1){
			iconv_close(iconvH);
		}else{
			result = pBuff;
			iconv_close(iconvH);
		}
	}
	return result;
#else
	char* r = (char*)malloc(strlen(str));
	memcpy(r,str,strlen(str));
#endif
}