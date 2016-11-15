/***************************************************************************
    copyright            : (C) by 2003-2004 Stefano Barbato
    email                : stefano@codesink.org
    website		 : http://codesink.org/eeprog.html

    $Id: eeprog.c,v 1.28 2004/02/29 11:06:41 tat Exp $
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#include <stdio.h>
#include <fcntl.h>
#include <getopt.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "24cXX.h"

#define usage_if(a) do { do_usage_if( a , __LINE__); } while(0);
#define IIC0_DEV "/dev/i2c/0"

void do_usage_if(int b, int line)
{
	const static char *eeprog_usage = 
		"I2C-24C08(256 bytes) Read/Write Program, ONLY FOR TEST!\n"
		"Base on 'eeprog' by Stefano Barbato (http://codesink.org/eeprog.html)\n"
		"i.e : i2c -r, i2c-w"
		"FriendlyARM Computer Tech. 2009\n";
		"Slash. 2016\n";
	if(!b)
		return;
	fprintf(stderr, "%s\n[line %d]\n", eeprog_usage, line);
	exit(1);
}


#define die_if(a, msg) do { do_die_if( a , msg, __LINE__); } while(0);
void do_die_if(int b, char* msg, int line)
{
	if(!b)
		return;
	fprintf(stderr, "Error at line %d: %s\n", line, msg);
	fprintf(stderr, "	sysmsg: %s\n", strerror(errno));
	exit(1);
}

#if 0
static int read_from_eeprom(struct eeprom *e, int addr, int size)
{
	int ch, i;
	for(i = 0; i < size; ++i, ++addr)
	{
		die_if((ch = eeprom_read_byte(e, addr)) < 0, "read error");
		if( (i % 16) == 0 ) 
			printf("\n %.4x|  ", addr);
		else if( (i % 8) == 0 ) 
			printf("  ");
		printf("%.2x ", ch);
		fflush(stdout);
	}
	fprintf(stderr, "\n\n");
	return 0;
}

static int write_to_eeprom(struct eeprom *e, int addr)
{
	int i;

	for(i = 0, addr = 0; i < 256; i++, addr++) {
		if( (i % 16) == 0 ) 
			printf("\n %.4x|  ", addr);
		else if ((i % 8) == 0)
			printf("  ");
    
		printf("%.2x ", i);
		fflush(stdout);
		die_if(eeprom_write_byte(e, addr, i), "write error");
	}

	fprintf(stderr, "\n\n");
	return 0;
}
#endif

unsigned char ascii_to_char (char *addr_char)
{
	unsigned char addr = 0;
	
	printf ("addr_char[0] %c\n", addr_char[0]);
	printf ("addr_char[1] %c\n", addr_char[1]);

	if (addr_char[0] >= 'A' && addr_char[0] <= 'Z') {
		addr = (addr_char[0] - 55) << 4;
	} else if (addr_char[0] >= 'a' && addr_char[0] <= 'z') {
		addr = (addr_char[0] - 87) << 4;
	} else {
		addr = (addr_char[0] - 48) << 4;
	}
	
	if (addr_char[1] >= 'A' && addr_char[1] <= 'Z') {
		addr = addr + (addr_char[1] - 55);
	} else if (addr_char[1] >= 'a' && addr_char[1] <= 'z') {
		addr = addr + (addr_char[1] - 87);
	} else {
		addr = addr + (addr_char[1] - 48);
	}
	
	return addr;
}


int main(int argc, char** argv)
{
	struct eeprom e;
	int op, i = 0;
	char tmp, tmp2;
	char *addr_char;
	char *data_char;
	unsigned char addr = 0;
	unsigned char data = 0;
	op = 0;
	
	if (argc == 4) {
		addr_char = argv[2];
		data_char = argv[3];
		
		addr = ascii_to_char (addr_char);
		data = ascii_to_char (data_char);
	
		printf ("addr = 0x%x\n", addr);
		printf ("data = 0x%x\n", data);
	}
	
	
#if 1
//	usage_if(argc != 2 || argv[1][0] != '-' || argv[1][2] != '\0');
	op = argv[1][1];

//	fprintf(stderr, "Open /dev/i2c/0 with 8bit mode\n");
//	if (eeprom_open(IIC0_DEV, 0x50, EEPROM_TYPE_8BIT_ADDR, &e) < 0) {
//		printf ("eeprom_open fail\n");
//	}

	switch(op)
	{
	case 'r':
		fprintf(stderr, "  Reading 256 bytes from 0x0\n");
//		read_from_eeprom(&e, 0, 256);
		break;
	case 'w':
		fprintf(stderr, "  Writing 0x00-0xff into 24C08 \n");
//		write_to_eeprom(&e, 0);
		break;
	case 'x':
	case 'X':
	
//		eeprom_write_byte(e, addr, i);
		printf ("use assigned address\n");
		break;
	default:
		usage_if(1);
		exit(1);
	}
	eeprom_close(&e);
#endif
	return 0;
}

