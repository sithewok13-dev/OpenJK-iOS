#pragma once

#include <stdio.h>
#include <string.h>

// "build 80 · Nov 9" (UTF-8 middle dot) from CI's SWBuildNumber and
// SWBuildDate (YYYY-MM-DD); "build dev" when either is missing or odd.
static inline void IOS_FormatBuildStamp( const char *number, const char *date, char *out, size_t size )
{
	static const char *const months[12] = {
		"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
	};
	int year = 0, month = 0, day = 0;
	if ( number && *number && strlen( number ) < 12 && strspn( number, "0123456789" ) == strlen( number ) &&
		date && sscanf( date, "%4d-%2d-%2d", &year, &month, &day ) == 3 &&
		month >= 1 && month <= 12 && day >= 1 && day <= 31 ) {
		snprintf( out, size, "build %s \xC2\xB7 %s %d", number, months[month - 1], day );
	} else {
		snprintf( out, size, "build dev" );
	}
}
