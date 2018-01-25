#ifndef _MYKEY_H_
#define _MYKEY_H_

#include "common.h"
#include "include.h"
#include "MK60_port.h"
#include "MK60_gpio.h"

void myKey_init     (void);

void key_get_status (void);

extern int16_t key_status[12];
#endif


