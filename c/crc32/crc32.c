#include <stdio.h>
//#include <string.h>

#if !defined USE_TABLE_CRC32
unsigned int helpCrc32(unsigned int reg, unsigned char data, unsigned int polynomial)
//unsigned int helpCrc32(unsigned int reg, unsigned int data, unsigned int polynomial)
{
	int j;
	for (j=0; j<8; ++j) {
		if (reg & 0x80000000) {
			printf("%d %08x %02x %08x\n", j, reg, data, polynomial);
			reg = ((reg<<1) | ((data>>7)&1)) ^ polynomial;
		} else {
			printf("%d %08x %02x\n", j, reg, data);
			reg = (reg<<1) | ((data>>7)&1);
		}
		data = data << 1;
	}
	return reg;
}

unsigned int crc32(unsigned int crc, void* buf, int size)
{
	unsigned int polynomial = 0x04C11DB7; // standard CRC32 polynomial
	//unsigned int polynomial = 0x1edc6f41; // castagnoli CRC32 polynomial
	unsigned int reg = 0;
	unsigned char* p = buf;
	unsigned char* end = p+size;
	unsigned char data;
/*
	reg = *p++;
	reg = reg<<8 | *p++;
	reg = reg<<8 | *p++;
	reg = reg<<8 | *p++;
*/
	reg = reg ^ ~0;

	while (p < end) {
		reg = helpCrc32(reg, (*p++), polynomial);
	}
	data = (crc & (0x0ff<<24)) >> 24; 
	reg = helpCrc32(reg, data, polynomial);
	data = (crc & (0x0ff<<16)) >> 16; 
	reg = helpCrc32(reg, data, polynomial);
	data = (crc & (0x0ff<< 8)) >>  8; 
	reg = helpCrc32(reg, data, polynomial);
	data = (crc & 0x0ff); 
	reg = helpCrc32(reg, data, polynomial);

	reg = reg ^ ~0;
	return reg;
}

#else

static unsigned int g_Crc32Table[256];
static int g_Crc32TableInitialized = 0;
void initCrc32Table();

unsigned int crc32(unsigned int crc, void* buf, int bufsize)
{
	unsigned int reg = 0;
	unsigned char* data = buf;
	unsigned char* end = buf + bufsize;

	if (!g_Crc32TableInitialized) {
		initCrc32Table();
	}

/*
	reg = *data++;
	reg = reg<<8 | *data++;
	reg = reg<<8 | *data++;
	reg = reg<<8 | *data++;
*/
	reg = reg ^ ~0;

	while (data < end) {
		reg = (reg<<8 | *data++) ^ g_Crc32Table[reg>>24];
	}

	reg = (reg<<8 | (crc & (0x0ff<<24)) >> 24) ^ g_Crc32Table[reg>>24];
	reg = (reg<<8 | (crc & (0x0ff<<16)) >> 16) ^ g_Crc32Table[reg>>24];
	reg = (reg<<8 | (crc & (0x0ff<< 8)) >>  8) ^ g_Crc32Table[reg>>24];
	reg = (reg<<8 | (crc &  0x0ff)) ^ g_Crc32Table[reg>>24];

	reg =  reg ^ ~0;
	return reg;
}


void initCrc32Table()
{
	int i, j;
	unsigned int table_entry;
	unsigned int polynomial = 0x04C11DB7; // standard CRC32 polynomial
	//unsigned int polynomial = 0x1edc6f41; // castagnoli CRC32 polynomial

	for (i=0; i<256; ++i) {
		table_entry = i<<24;
		for (j=0; j<8; ++j) {
			if (table_entry & 0x80000000) {
				table_entry = (table_entry << 1) ^ polynomial;
			} else {
				table_entry = table_entry << 1;
			}
		}
		g_Crc32Table[i] = table_entry;
	}
	g_Crc32TableInitialized = 1;
}

void showTable(unsigned int* pTable, int size)
{
	int i;
	for (i=0; i<size; ++i) {
		printf("0x%08x, ", *pTable++);
		if (0 != i && 0 == (i+1)%8) {
			printf("\n");
		}
	}
	printf("\n");
}

#endif

