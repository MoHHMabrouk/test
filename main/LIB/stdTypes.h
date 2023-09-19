#ifndef STDTYPES_H_
#define STDTYPES_H_

typedef unsigned char u8;
typedef signed char s8;

typedef char c8;

typedef unsigned int u16;
typedef signed int s16;

typedef unsigned long u32;
typedef signed long s32;

typedef volatile unsigned char* pu8;

#define MAX_U16 ((u16)65535)

#define MAX_U8 ((u8)255)
#define MIN_U8 ((u8)0)

#define MAX_S8 ((u8)127)
#define MIN_S8 ((u8)-128)

#define ZERO_U8 ((s8)0)

typedef enum
{
	OK,
	NOK,
	NULLPTR,
	OUT_OF_RANGE
}error_type;

typedef enum
{
	FALSE=0,
	TRUE
}Bool_type;

#define NULL_PTR ((void*)0)
#define NULL ((char)0)


#endif /* STDTYPES_H_ */