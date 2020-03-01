#include <NTPClock.h>
#include <ESP8266WiFi.h>

const char *ssid     = "<SSID>";
const char *password = "<PASSWORD>";

void setup(){
	Serial.begin(115200);

	WiFi.begin(ssid, password);

	while ( WiFi.status() != WL_CONNECTED ) {
		delay ( 500 );
		Serial.print ( "." );
	}

	// NTPClock begin
	NTPClock& ntpclock = NTPClock::getInstance();
	ntpclock.begin();
}

void loop() {


	// NTPTime update
	NTPClock& ntpclock = NTPClock::getInstance();
	ntpclock.update();

	// Time without seconds
	Serial.print( "Time without seconds:" );
	Serial.println( ntpclock.getTime() );

	// Time with seconds
	Serial.print( "Time with seconds:" );
	Serial.println( ntpclock.getTime("full") );

	// Hour
	Serial.print( "Hour:" );
	Serial.println( ntpclock.getTime("hour") );

	// Minute
	Serial.print( "Minute:" );
	Serial.println( ntpclock.getTime("minute") );

	// Second
	Serial.print( "Second:" );
	Serial.println( ntpclock.getTime("second") );

	// wait
	delay(1000);
}
