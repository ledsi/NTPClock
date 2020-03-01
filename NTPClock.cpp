#include "NTPClock.h"
#include <WiFiUdp.h>
#include <NTPClient.h>

// europe time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 60000);

// Contructor
NTPClock::NTPClock( void )
{

}

// Destructor
NTPClock::~NTPClock( void )
{

}


// begin
// ====================================================
void NTPClock::begin( int customRefreshRate )
{

	#if DEBUG
		Serial.println("");
		Serial.println("==================");
		Serial.println(" NTP CLOCK INIT ");
		Serial.println("==================");
	#endif

	if( customRefreshRate != 0 ) {
		refreshRate = customRefreshRate;
	}

	// timeclient
	timeClient.begin();

	// sync
	sync();

}

// update
// ====================================================
void NTPClock::update( void )
{

	#if DEBUG
		Serial.println("");
		Serial.println("==================");
		Serial.println(" SYNC ");
		Serial.println("==================");
	#endif


	if( delayTimer == 0 ) {
		setDelayTimer();
	}

	// sync
	if( (delayTimer + refreshRate <= millis() )  ) {

		// sync
		sync();

		// setDelayTimer
		setDelayTimer();
	}

}

// sync
// ====================================================
void NTPClock::sync( void ) {

	// time update
	timeClient.update();
	timeStamp = timeClient.getFormattedTime();
	millisSinceSync = millis();

	// values
	hour 	= timeStamp.substring(0, 2).toInt();
	minute 	= timeStamp.substring(3, 5).toInt();
	second 	= timeStamp.substring(6, 8).toInt();

	// convert time to millis
	timeToMillis( hour, minute, second );

	#if DEBUG
		Serial.println("TIME SYNC:");
		Serial.println(timeStamp);
	#endif
}



// timeToMillis
// ====================================================
void NTPClock::timeToMillis( long hour, long minute, long second ) {

	// values
	long milliHour 		= hour * 60000 * 60;
	long milliMinute 	= minute * 60000;
	long milliSecond 	= second * 1000;

	// update millis timestamp
	milliTimeStamp 		= milliHour + milliMinute + milliSecond;

	#if DEBUG
		Serial.println("timeToMillis");
		Serial.println(milliTimeStamp);
	#endif

}

// getTime
// ====================================================
String NTPClock::getTime( String selector ) {

	long calcTimeStamp  = milliTimeStamp + ( millis() - millisSinceSync );

	long allSeconds     = calcTimeStamp / 1000;
	int runHours        = allSeconds / 3600;
	int secsRemaining   = allSeconds % 3600;
	int runMinutes      = secsRemaining / 60;
	int runSeconds      = secsRemaining % 60;

	// hours
	if( runHours < 10 ) {
		timeArray[0] = "0" + String(runHours);
	} else {
		timeArray[0] = String(runHours);
	}

	// minutes
	if( runMinutes < 10 ) {
		timeArray[1] = "0" + String(runMinutes);
	} else {
		timeArray[1] = String(runMinutes);
	}

	// seconds
	if( runSeconds < 10 ) {
		timeArray[2] = "0" + String(runSeconds);
	} else {
		timeArray[2] = String(runSeconds);
	}

	// return
	//
	if( selector == "all" ) {
		return timeArray[0] + ":" + timeArray[1];
	}
	else if( selector == "hour" ) {
		return timeArray[0];
	}
	else if( selector == "minute" ) {
		return timeArray[1];
	}
	else if( selector == "second" ) {
		return timeArray[2];
	}
	else if( selector == "full" ) {
		return timeArray[0] + ":" + timeArray[1] + ":" + timeArray[2];
	}
	else {
		return "Please specify format: all, hour, minute, second, full";
	}

}


// setDelayTimer
// ====================================================
void NTPClock::setDelayTimer( void ) {

	// millis
	delayTimer = millis();

}
