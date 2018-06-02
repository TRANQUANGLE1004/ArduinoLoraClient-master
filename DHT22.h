// DHT22.h
#pragma once
#ifndef _DHT22_h
#define _DHT22_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
void createDataDHT(char*id, float temp, float humid, char*data);

#endif

