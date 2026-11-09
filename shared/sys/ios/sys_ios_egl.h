#pragma once

bool Sys_IOS_EGL_Probe( void );
bool Sys_IOS_EGL_Attach( void *metalLayer, float nativeScale );
bool Sys_IOS_EGL_MakeCurrent( void );
bool Sys_IOS_EGL_Present( void );
void *Sys_IOS_EGL_GetProcAddress( const char *name );
void Sys_IOS_EGL_CheckSize( int width, int height, bool afterSwap );
void Sys_IOS_EGL_AbortInit( void );
// Start guard: a marker file is written before ANGLE starts and removed after
// its first presents, so a launch that died starting ANGLE is seen next time.
bool Sys_IOS_EGL_PreviousStartFailed( void );	// also clears the marker
void Sys_IOS_EGL_BeginStartGuard( void );
void Sys_IOS_EGL_EndStartGuard( void );
