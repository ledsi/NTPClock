# NTPClock

## Required libraries

* NTPClient

## getTime

```cpp

	// getInstance
	NTPClock& ntpclock = NTPClock::getInstance();

	// Time without seconds
	ntpclock.getTime();

	// Time with seconds
	ntpclock.getTime("full");

	// Hour
	ntpclock.getTime("hour");

	// Minute
	ntpclock.getTime("minute");

	// Second
	ntpclock.getTime("second");
```

## getDate

```cpp

	// getInstance
	NTPClock& ntpclock = NTPClock::getInstance();

	// Full
	ntpclock.getDate();

	// Day
	ntpclock.getTime("day");

	// Month
	ntpclock.getTime("month");

	// Year
	ntpclock.getTime("year");
```

## getWeekDay

Supported languages: de, en

```cpp

	// getInstance
	NTPClock& ntpclock = NTPClock::getInstance();

	// Full
	ntpclock.getWeekday();

	// Full - different language
	ntpclock.getWeekday("full", "en");

	// Short
	ntpclock.getWeekday("short", "en");

	// Short - different language
	ntpclock.getWeekday("short", "en");

	// Number - Sun to Sat (0-6)
	ntpclock.getWeekday("number");

```

## getMonth

Supported languages: de, en

```cpp

	// getInstance
	NTPClock& ntpclock = NTPClock::getInstance();

	// Full
	ntpclock.getMonth();

	// Full - different language
	ntpclock.getMonth("full", "en");

	// Short
	ntpclock.getMonth("short", "en");

	// Short - different language
	ntpclock.getMonth("short", "en");

```
