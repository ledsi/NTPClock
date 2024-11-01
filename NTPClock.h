#ifndef _H_NTPCLOCK
#define _H_NTPCLOCK
#include <Arduino.h>

class NTPClock
{
  private:

	// Contructor
	// ====================================================
	NTPClock( void );

	// timer
  	unsigned long delayTimer = 0;
  	int refreshRate = 15 * 60 * 1000;

	// time
	String timeArray[3];
	String timeStamp;
	long hour;
	long minute;
	long second;
	long millisSinceSync;
	long milliTimeStamp;
	unsigned long epochTime;
	int timeOffset;
	int epochDay;


	public:

		static NTPClock& getInstance( void )
		{
			static NTPClock ntpclock;
			return ntpclock;
		}

	// destructor
	~NTPClock( void );

	// M
	// ====================================================
	void begin( int offset = 0, int customRefreshRate = 0 );
	void update( void );
	void sync( void );
	bool isDST(time_t t);
	void timeToMillis( long hour, long minute, long second );
	String getFormattedTime( unsigned long epochTime );
	String getTime( String selector = "all" );
	String getDate( String selector = "full" );
	String getWeekDay( String selector = "full", String lang = "de" );
	String getMonth( String selector = "full", String lang = "de" );
	void setDelayTimer( void );

};

#endif
