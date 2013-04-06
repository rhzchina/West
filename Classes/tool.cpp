//#include "tool.h"
//int GBKToUTF8(char* gbkStr,const char* toCode,const char* formCode)
//{
//	iconv_t iconvH;
//	iconvH = iconv_open(formCode,toCode);
//	if(iconvH == 0)
//	{
//		return -1;
//	}
//
//	const char* strChar = gbkStr;
//	const char** pin = &strChar;
//
//	size_t strLength = strlen(gbkStr);
//	char* outbuf = (char*)malloc(strLength*4);
//	char* pBuff = outbuf;
//	memset(outbuf,0,strLength*4);
//	size_t outLength = strLength*4;
//	if(-1 == iconv(iconvH,pin,&strLength,&outbuf,&outLength))
//	{
//		iconv_close(iconvH);
//		return -1;
//	}
//
//	gbkStr = pBuff;
//	iconv_close(iconvH);
//	return 0;
//}
