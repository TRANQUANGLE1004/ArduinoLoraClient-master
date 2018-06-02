#pragma once
#ifndef _RICER5_PROTOCOL_H_
#define _RICER5_PROTOCOL_H_
#include <RH_RF95.h>


//-------------------------------
//Section: Ricer5 protocol datastruct definitions
	
//Endsection: Ricer5 protocol datastruct definitions
//-------------------------------
//Section: Ricer5 Server
	//Section: Server status enumerations
		enum ServerStatus {

		};
	//Endsection: Server status enumerations
	//Section: Server string constant definitions
		
	//Endsection: Server string constant definitions
//Endsection: Ricer5 Server
//-------------------------------
//Section: Ricer5 Client
	//-------------------------------
	//Section: Client status enumerations
		enum ClientStatus {
			BEGINNING = 0,
			TIME_OUT = 1,
			WAITING = 2,
			OK = 3
		};
	//Endsection: Client status enumerations
	//-------------------------------
	//Section: Client string constant definitions
		
	//Endsection: Client string constant definitions
	//-------------------------------
	//Section: Client features
		void sendID(char* id, void* media);
		ClientStatus waitForServerResponse(char * id, void* media);
		ClientStatus waitForServerRequest(char * id, void* media);
		void sendData(char* data, void* media);

	//Endsection: Client features
	//-------------------------------
//Endsection: Ricer5 Client
//-------------------------------

#endif // !_RICER5_PROTOCOL_H_
