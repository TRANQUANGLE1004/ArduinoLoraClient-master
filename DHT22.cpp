#include "DHT22.h"
#include <SPI.h>
#include "Configurations.h"
//Todo

void createDataDHT(char * id, float temp, float humid, char * data) {
	memset((void*)data, 0, sizeof(data));
	char symbol[] = "*";
	char tempBuff[MAX_LENGTH_BUFFER_SENSOR];
	char humidBuff[MAX_LENGTH_BUFFER_SENSOR];
	dtostrf(temp, sizeof(tempBuff), PRECISION, tempBuff);
	dtostrf(humid, sizeof(humidBuff), PRECISION, humidBuff);
	data[0] = '*';
	strcpy(data + 1, id);
	data[1 + strlen(id)] = '*';
	strcpy(data + 1 + 1 + strlen(id), tempBuff);
	data[1 + 1 + strlen(id) + MAX_LENGTH_BUFFER_SENSOR] = '*';
	strcpy(data + MAX_LENGTH_BUFFER_SENSOR + 1 + strlen(id) + 2, humidBuff);
	data[2 * MAX_LENGTH_BUFFER_SENSOR + 1 + strlen(id) + 2] = '*';
}
