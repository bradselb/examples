#include "crc32.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	unsigned int crc = 0;
	unsigned int resid = 0;

	int bufsize = 4096;
	unsigned char* buf = malloc(bufsize);

	buf[0] = 0x21; buf[1] = 0x34; buf[2] = 0x67; buf[3]=0x99; buf[4]=0x3c; buf[5]=0xef;
	resid = 0;
	crc = crc32(resid, buf, 6);
	printf("crc32(0x%08x,0x213467993cef) is: 0x%08x\n", resid, crc);
	resid = crc;
	crc = crc32(resid, buf, 6);
	printf("crc32(0x%08x,0x213467993cef) is: 0x%08x\n", resid, crc);


	resid = 0x08765309;
	crc = crc32(resid, buf, 6);
	printf("crc32(0x%08x, 0x213467993cef) is: 0x%08x\n", resid, crc);
	crc = crc32(crc, buf, 6);
	printf("crc32(0x%08x, 0x213467993cef) is: 0x%08x\n", crc, crc);

/*

	memset(buf, 0xff, bufsize);
	crc = crc32(0, buf, 4);
	printf("  crc32(0,0xffffffff) is: 0x%08x\n", crc);
	crc = crc32(0xffffffff, buf, 10);
	printf("  crc32(-1,-1) is: 0x%08x\n", crc);

	memset(buf, 0, bufsize);
	crc = crc32(0, buf, 10);
	printf("  crc32(0,0) is: 0x%08x\n", crc);
	crc = crc32(0xffffffff, buf, 10);
	printf("  crc32(-1,0) is: 0x%08x\n", crc);

	buf[0] = 0x21; buf[1] = 0x34; buf[2] = 0x67; buf[3]=0x99; buf[4]=0x3c; buf[5]=0xef;
	crc = crc32(0, buf, 6);
	printf("  crc32(0,0x213467993cef) is: 0x%08x\n", crc);
	crc = crc32(crc, buf, 6);
	printf("crc32(crc,0x213467993cef) is: 0x%08x\n", crc);
	crc = crc32(0, buf, 6);
	printf("crc32(0,0x213467993cef) is: 0x%08x\n", crc);
	crc = crc32(crc, buf, 6);
	printf("crc32(crc,0x213467993cef) is: 0x%08x\n", crc);

	// now do it for the string data
	crc = crc32(0, data, strlen(data));
	printf("  crc32(0,data) is: 0x%08x\n", crc);

	crc = crc32(crc, data, strlen(data));
	printf("crc32(crc,data) is: 0x%08x\n", crc);

	crc = crc32(0, data, strlen(data));
	printf("  crc32(0,data) is: 0x%08x\n", crc);

	crc = crc32(crc, data, strlen(data));
	printf("crc32(crc,data) is: 0x%08x\n", crc);

	crc = crc32(~0U, data, strlen(data));
	printf(" crc32(-1,data) is: 0x%08x\n", crc);
	crc = crc32(crc, data, strlen(data));
	printf("crc32(crc,data) is: 0x%08x\n", crc);
*/	
	free(buf);
	return 0;
}


