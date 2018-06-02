#include "DHT22.h"
#include <SPI.h>
#include <RH_RF95.h>
#include "Ricer5Protocol.h"
#include "Configurations.h"
#include <DHT.h>
//Section: GLobal data
	RH_RF95 client(RFM95_SLAVE_SELECT_PIN, RFM95_SLAVE_INTERRUPT_PIN);
	ClientStatus clientStatus;
	DHT dhtSensorData(DHT_PIN, DHT22);
//Endsection: Global data
//-------------------------------
//Section: To be removed
	char* id = "9";
	char data[25];
//Endsection: To be removed
//-------------------------------
void setup() {
	//-------------------------------
	//Section: Led setup
		pinMode(LED, OUTPUT);
	//Endsection: Led setup
	//-------------------------------
	//Section: Serial setup
		Serial.begin(9600);
	//Endsection: Setial setup
	//-------------------------------
	//Section: RF95 setup
		clientStatus = BEGINNING;
		while (!client.init()) {
			Serial.println("LoRa radio init failed");
			while (1);
		}
		Serial.println("LoRa radio init OK!");
	//Endsection: RF95 setup
		if (!client.setFrequency(RF95_FREQUENCY)) {
			Serial.println("Setup Frequency Failse.");
		}
		Serial.println("LORA setup Frequency OK !");
		dhtSensorData.begin();
}
//-------------------------------
//Section: Program flow
void loop()
{
	clientStatus = BEGINNING;
	sendID(id, (void*)&client);
	clientStatus = waitForServerResponse(id, (void*)&client);
	if (clientStatus == WAITING) {
		clientStatus = waitForServerRequest(id, (void*)&client);
		if (clientStatus == OK) {
			createDataDHT(id, dhtSensorData.readTemperature(), dhtSensorData.readHumidity(), data);
			sendData(data, (void*)&client);
		}
		else if (clientStatus == TIME_OUT) Serial.println("Waiting timed out.");
	}
	else if (clientStatus == TIME_OUT) Serial.println("Register timed out.");
	delay(INTERVAL_TIME_MILLISECOND);
}
//Endsection: Program flow
//-------------------------------