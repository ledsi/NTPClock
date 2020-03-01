# NTPClock

## Required libraries

* NTPClient

## getTime

Vaild time requests:  

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
