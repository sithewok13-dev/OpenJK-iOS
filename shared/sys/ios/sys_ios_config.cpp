#include "sys_ios.h"
#include "qcommon/qcommon.h"

void Sys_IOS_MigrateConfig( void ) {
	// Old engine defaults that 0.1.0 saved into every config.
	static const struct { const char *name, *oldDefault; } moved[] = {
		{ "cg_thirdPersonRange", "80" },
		{ "cg_fovViewmodel", "0" },
		{ "cg_gunX", "0" },
	};
	const int version = Cvar_Get( "ios_configVersion", "0", CVAR_ARCHIVE | CVAR_NORESTART )->integer;
	if ( version >= 2 )
		return;
	// 2: ANGLE became the default. Every config saved r_glesProvider, so a saved "eagl"
	// cannot tell a choice from the old default: move it to ANGLE once. An autoexec
	// line still wins, and a later choice in the Video menu is kept.
	if ( Cvar_Flags( "r_glesProvider" ) != CVAR_NONEXISTENT && !Q_stricmp( Cvar_VariableString( "r_glesProvider" ), "eagl" ) ) {
		Cvar_Set( "r_glesProvider", "angle" );
		Com_Printf( "ios_configVersion 2: r_glesProvider eagl -> angle\n" );
	}
	Cvar_Set( "ios_configVersion", "2" );
	if ( version >= 1 )
		return;
	for ( const auto &cvar : moved ) {
		const unsigned flags = Cvar_Flags( cvar.name );
		if ( flags == CVAR_NONEXISTENT || !( flags & CVAR_PLATFORM_DEFAULT ) )
			continue;
		char value[MAX_CVAR_VALUE_STRING];
		Q_strncpyz( value, Cvar_VariableString( cvar.name ), sizeof( value ) );
		if ( Q_stricmp( value, cvar.oldDefault ) && !( Q_isanumber( value ) && atof( value ) == atof( cvar.oldDefault ) ) )
			continue;
		Cvar_Reset( cvar.name );
		Com_DPrintf( "ios_configVersion 1: %s %s -> %s\n", cvar.name, value, Cvar_VariableString( cvar.name ) );
	}
}
