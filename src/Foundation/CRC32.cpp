/*
 * CRC32.cpp
 *
 *  Created on: Dec 21, 2012
 *      Author: kique
 */


#include "CRC32.h"

///
uint32_t rt_crc32(const char * str)
{
	uint32_t crc = 0xFFFFFFFF;

	while (*str != '\0')
	{
		crc = ( crc >> 8 ) ^ crc_table[(crc ^ *str) & 0x000000FF];
		++str;
	}

	return crc ^ 0xFFFFFFFF;
}
