#pragma once

typedef struct extn_s
{
	int type;
	unsigned short int data;
} extn_t;

typedef struct cl_hello_s
{
	unsigned short int protover;
	unsigned int random;
	unsigned int lsid; /* legacy session id */
	unsigned short int cs; /* cipher suite */
	unsigned char lcm; /* legacy compression method */
	extn_t ext[2];
} cl_hello_t;
