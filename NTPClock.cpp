#include "NTPClock.h"
#include <WiFiUdp.h>
#include <NTPClient.h>

// europe time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 0, 60000);

// Contructor
NTPClock::NTPClock( void )
{

}

// Destructor
NTPClock::~NTPClock( void )
{

}


// init
// ====================================================
void NTPClock::begin( int offset, int customRefreshRate )
{

	#if NTPCLOCK_DEBUG
		Serial.println("");
		Serial.println("==================");
		Serial.println(" NTP CLOCK INIT ");
		Serial.println("==================");
	#endif

	timeOffset = offset;

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

	#if DEBUG_NTPCLOCK
		// Serial.println("");
		// Serial.println("==================");
		// Serial.println(" SYNC ");
		// Serial.println("==================");
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

	// date
	epochTime = timeClient.getEpochTime() + timeOffset;

	// time
	timeStamp = getFormattedTime(epochTime);

	// millisSinceSync
	millisSinceSync = millis();

	// epochDay
	epochDay = (( (epochTime + ( millis() - millisSinceSync )) / 86400) + 4) % 7;

	// values
	hour 	= timeStamp.substring(0, 2).toInt();
	minute 	= timeStamp.substring(3, 5).toInt();
	second 	= timeStamp.substring(6, 8).toInt();

	// convert time to millis
	timeToMillis( hour, minute, second );

	#if DEBUG_NTPCLOCK
		Serial.println("TIME SYNC:");
		Serial.println(timeStamp);
	#endif
}


// getFormattedTime
// ====================================================
String NTPClock::getFormattedTime( unsigned long epochTime ) {

  unsigned long hours = (epochTime % 86400L) / 3600;
  String hoursStr = hours < 10 ? "0" + String(hours) : String(hours);

  unsigned long minutes = (epochTime % 3600) / 60;
  String minuteStr = minutes < 10 ? "0" + String(minutes) : String(minutes);

  unsigned long seconds = epochTime % 60;
  String secondStr = seconds < 10 ? "0" + String(seconds) : String(seconds);

  return hoursStr + ":" + minuteStr + ":" + secondStr;
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

	#if DEBUG_NTPCLOCK
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


// getDate
// ====================================================
String NTPClock::getDate( String selector ) {
	time_t rawtime = epochTime;
	struct tm * ti;
	ti = localtime (&rawtime);

	uint8_t day = ti->tm_mday;
	String dayStr = day < 10 ? "0" + String(day) : String(day);

	uint8_t month = ti->tm_mon + 1;
	String monthStr = month < 10 ? "0" + String(month) : String(month);

	uint16_t year = ti->tm_year + 1900;
	String yearStr = String(year);

	// return
	if( selector == "full" ) {
		return dayStr + "." + monthStr + "." + yearStr;
	}
	else if( selector == "day") {
		return dayStr;
	}
	else if( selector == "month") {
		return monthStr;
	}
	else if( selector == "year") {
		return yearStr;
	}
	else {
		return dayStr + "." + monthStr + "." + yearStr;
	}
}

// getWeekDay
// ====================================================
String NTPClock::getWeekDay( String selector, String lang ) {
	String dateString;
	int lang_num;

	// language
	if( lang == "de" ) {lang_num = 0;}
	else if( lang == "en" ) {lang_num = 1;}

	// names
	const String name_full[][7] = {
		{"Sonntag", "Montag", "Dienstag", "Mittwoch", "Donnerstag", "Freitag", "Samstag"},
		{"Sunday", "Monday", "Tuesday", "Wednesday", "Thurstay", "Friday", "Saturday"}
	};
	const String name_short[][7] = {
		{"So", "Mo", "Di", "Mi", "Do", "Fr", "Sa"},
		{"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"}
	};

	// select
	if( selector == "number" ) {
		dateString = String(epochDay);
	}
	else if( selector == "full" ) {
		dateString = name_full[lang_num][epochDay];
	}
	else if( selector == "short" ) {
		dateString = name_short[lang_num][epochDay];
	}

	return dateString;
}

// getMonth
// ====================================================
String NTPClock::getMonth( String selector, String lang ) {
	String monthString;
	String date = getDate();
	int lang_num;

	// getMonth
	int month = date.substring(3, 5).toInt() -1;

	// language
	if( lang == "de" ) {lang_num = 0;}
	else if( lang == "en" ) {lang_num = 1;}

	// names
	const String month_full[][12] = {
		{"Januar", "Februar", "März", "April", "Mai", "Juni", "Juli", "August", "September", "Oktober", "November", "Dezember"},
		{"January", "February", "March", "April", "May", "June", "July", "August", "Semtember", "October", "November", "December"}
	};
	const String month_short[][12] = {
		{"Jan", "Feb", "Mrz", "Apr", "Mai", "Jun", "Jul", "Aug", "Sep", "Okt", "Nov", "Dez"},
		{"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"}
	};

	// select
	if( selector == "full" ) {
		monthString = month_full[lang_num][month];
	}
	else if( selector == "short" ) {
		monthString = month_short[lang_num][month];
	}

	return monthString;
}


// setDelayTimer
// ====================================================
void NTPClock::setDelayTimer( void ) {

	// millis
	delayTimer = millis();

}
