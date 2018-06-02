#include "Ricer5Protocol.h"
#include <RH_RF95.h>
#include "Configurations.h"

void sendID(char * id, void* media) {
	RH_RF95* client = (RH_RF95*)media;
	char idPacket[RH_RF95_MAX_MESSAGE_LEN];
	//strcpy(idPacket, "id");
	strcpy(idPacket , id);
	client->send((uint8_t*)idPacket, strlen(id) + 1);
	client->waitPacketSent();
	Serial.print("Sent: ");
	Serial.println(idPacket);
}

int receive(char* msgBuffer, uint8_t* receiveLength, void* media) {
	RH_RF95* client = (RH_RF95*)media;
	memset((void*)msgBuffer, 0, RH_RF95_MAX_MESSAGE_LEN);
	if (client->available()) {
		if (client->recv((uint8_t*)msgBuffer, receiveLength)) {
			return strlen(msgBuffer);
		}
	}
	return 0;
}

ClientStatus waitForServerResponse(char * id, void* media) {
	RH_RF95* client = (RH_RF95*)media;
	char msgBuffer[RH_RF95_MAX_MESSAGE_LEN];
	uint8_t msgLength = RH_RF95_MAX_MESSAGE_LEN;
	unsigned long startTime = millis();
	while (1) {
		while (receive(msgBuffer, &msgLength, media) == 0) {
			if (millis() - startTime > TIMEOUT_PERIOD_MILLISECOND) return TIME_OUT;
		}
		if (millis() - startTime > TIMEOUT_PERIOD_MILLISECOND) return TIME_OUT;
		if (msgBuffer[0] != 'w' && msgBuffer[0] != 'W') {
			Serial.print("Invalid response: ");
			Serial.println(msgBuffer);
			continue;
		}
		else {
			if (strcmp(id, msgBuffer + 1) != 0) {
				Serial.print("Invalid response: ");
				Serial.println(msgBuffer);
				continue;
			}
			else {
				Serial.print("Register successfully with response: ");
				Serial.println(msgBuffer);
				return WAITING;
			}
		}
	}
}

ClientStatus waitForServerRequest(char * id, void * media) {
	RH_RF95* client = (RH_RF95*)media;
	char msgBuffer[RH_RF95_MAX_MESSAGE_LEN];
	uint8_t msgLength = RH_RF95_MAX_MESSAGE_LEN;
	unsigned long startTime = millis();
	while (1) {
		while (receive(msgBuffer, &msgLength, media) == 0) {
			if (millis() - startTime > TIMEOUT_PERIOD_MILLISECOND) return TIME_OUT;
		}
		if (millis() - startTime > TIMEOUT_PERIOD_MILLISECOND) {
			Serial.print("Invalid request: ");
			Serial.println(msgBuffer);
			return TIME_OUT;
		}
		if (msgBuffer[0] != 'o' && msgBuffer[0] != 'O') {
			Serial.print("Invalid request: ");
			Serial.println(msgBuffer);
			continue;
		}
		else {
			if (msgBuffer[1] != 'k' && msgBuffer[1] != 'K') {
				Serial.print("Invalid request: ");
				Serial.println(msgBuffer);
				continue;
			}
			else {
				if (strcmp(id, msgBuffer + 2) != 0) {
					Serial.print("Invalid request: ");
					Serial.println(msgBuffer);
					continue;
				}
				else {
					Serial.print("Request received: ");
					Serial.println(msgBuffer);
					return OK;
				}
			}
		}
	}
}

void sendData(char * data, void* media) {
	RH_RF95* client = (RH_RF95*)media;
	client->send((uint8_t*)data, strlen(data));
	client->waitPacketSent();
	Serial.print("Sent: ");
	Serial.println(data);
}
