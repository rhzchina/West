#ifndef TOOL_H 
#define TOOL_H
#include <math.h>
#include <string>

#ifdef WIN32
	#include "iconv\iconv.h"
	#define CONV(gbkStr,str) \
	{\
		gbkStr = str;\
		iconv_t iconvH;\
		iconvH = iconv_open("utf-8","gbk");\
		if(iconvH != 0){\
			const char* strChar = gbkStr;\
			const char** pin = &strChar;\
			\
			size_t strLength = strlen(gbkStr);\
			char* outbuf = (char*)malloc(strLength*4);\
			char* pBuff = outbuf;\
			memset(outbuf,0,strLength*4);\
			size_t outLength = strLength*4;\
			if(-1 == iconv(iconvH,pin,&strLength,&outbuf,&outLength))\
			{\
				iconv_close(iconvH);\
			}else{\
				gbkStr = pBuff;\
				iconv_close(iconvH);\
			}\
		}\
}
#else
	#define CONV(gbkStr,str) gbkStr = str 
#endif

#define POINT_INSTANCE(_p1,_p2) \
	sqrt((_p1.x + _p2.x) * \
	(_p1.x + _p2.x) + \
	(_p1.y + _p2.y) + \
	(_p1.y + _p2.y))

#define SETANCHPOS(target,x,y,anchX,anchY) \
	target->setPosition(ccp(x,y)); \
	target->setAnchorPoint(ccp(anchX,anchY));
	

#endif