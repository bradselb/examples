#ifndef MYCRC32_H
#define MYCRC32_H

void initCrc32Table();
unsigned int crc32(unsigned int crc, void* buf, int size);

unsigned int calcCrc32(unsigned int crc, void* buf, int size);

#endif
