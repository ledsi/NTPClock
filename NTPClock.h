#ifndef _H_NTPCLOCK
#define _H_NTPCLOCK

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
	void begin( int customRefreshRate = 0 );
	void update( void );
	void sync( void );
	void timeToMillis( long hour, long minute, long second );
	String getTime( String selector = "all" );
	String getDate( String selector = "full" );
	String getWeekDay( String selector = "full", String lang = "de" );
	String getMonth( String selector = "full", String lang = "de" );
	void setDelayTimer( void );

};

#endif
