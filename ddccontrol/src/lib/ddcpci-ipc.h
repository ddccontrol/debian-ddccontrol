/*
    ddc/ci direct PCI memory interface - header file for IPC
    Copyright(c) 2004 Nicolas Boichat (nicolas@boichat.ch)

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef DDCPCI_IPC_H
#define DDCPCI_IPC_H

#include "config.h"

#if !HAVE_DDCPCI
#error "This file mustn\'t be included if ddcpci support is disabled."
#endif

#include <pci/pci.h>

struct i2c_bus {
	word bus;
	byte dev;
	byte func;
	int i2cbus;
};

#define MAX_BUFFER_SIZE 256
#define QUERY_SIZE  (sizeof(struct query) - (MAX_BUFFER_SIZE))
#define ANSWER_SIZE (sizeof(struct answer) - (MAX_BUFFER_SIZE))

/* ddccontrol to ddcpci messages (queries) */
#define QUERY_LIST 0  /* Nothing should be defined */
#define QUERY_OPEN 1  /* i2c_bus must be defined */
#define QUERY_DATA 2  /* addr and flags must be defined (and buffer for write operations) */
#define QUERY_QUIT 3  /* Nothing should be defined */

struct query {
	long mtype; /* Always 1 */
	int qtype; /* see above for possible values */
	/* QUERY_OPEN */
	struct i2c_bus bus;
	/* QUERY_DATA */
	int addr;
	int flags;
	int len; /* only for read queries, number of bytes to read */
	char buffer[MAX_BUFFER_SIZE];
};

/* ddcpci to ddccontrol messages (answers) */
struct answer {
	long mtype; /* Always 2 */
	int status; /* 0 or greater - OK (bytes read/written for answers to QUERY_DATA), -1 - an error occured */
	
	int last; /* 0 - Last message, no bus to read, 1 - Other messages follows (for QUERY_LIST) */
	struct i2c_bus bus; /* For answers to QUERY_LIST */
	char buffer[MAX_BUFFER_SIZE]; /* For answers to QUERY_DATA, read operations */
};

#endif //DDCPCI_IPC_H