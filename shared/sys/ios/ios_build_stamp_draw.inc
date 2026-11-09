// Included by code/ and codemp/ client/cl_scrn.cpp (OPENJK_IOS): the build
// stamp, small and dim at the bottom right of the main menus (inside the
// safe area; on a phone it sits in the side band beside the 4:3 menu).
// IOS_STAMP_RE: a pointer to the renderer exports ((&re) in SP, re in MP).
static void SCR_DrawIOSBuildStamp( void ) {
	if ( cls.state != CA_DISCONNECTED || !( Key_GetCatcher() & KEYCATCH_UI ) || !cls.charSetShader )
		return;
	const aspectLayout_t &layout = SCR_GetAspectLayout();
	float pointW = 0, pointH = 0;
	Sys_IOS_GetViewPointSize( GLimp_IOS_Window(), &pointW, &pointH );
	if ( layout.W <= 0 || layout.H <= 0 || pointW <= 0 )
		return;
	const double p = layout.W / pointW;	// pixels per point
	const double charH = 12 * p, charW = 6 * p, margin = 6 * p;
	const char *text = Sys_IOS_BuildStamp();
	int cells = 0;
	for ( const char *s = text; *s; ++s )
		if ( ( (unsigned char)*s & 0xC0 ) != 0x80 ) ++cells;	// one cell per UTF-8 character
	double x = layout.W - layout.safeR - margin - cells * charW;
	const double y = layout.H - layout.safeB - margin - charH;
	const vec4_t dim = { 1, 1, 1, 0.5f };
	IOS_STAMP_RE->SetColor( dim );
	for ( const unsigned char *s = (const unsigned char *)text; *s; ++s, x += charW ) {
		if ( s[0] == 0xC2 && s[1] == 0xB7 ) {	// the middle dot, drawn as a small square
			const double d = charW * 0.35;
			const aspectPoint_t o = SCR_PixelsToVirtual( x + ( charW - d ) / 2, y + charH * 0.55 - d / 2 );
			const aspectPoint_t z = SCR_PixelSizeToVirtual( d, d );
			SCR_FillRect( o.x, o.y, z.x, z.y, dim );
			IOS_STAMP_RE->SetColor( dim );
			++s;
			continue;
		}
		if ( *s == ' ' || *s >= 0x80 )
			continue;
		const float u = ( *s & 15 ) / 16.0f, v = ( *s >> 4 ) / 16.0f;
		const aspectPoint_t o = SCR_PixelsToVirtual( x, y );
		const aspectPoint_t z = SCR_PixelSizeToVirtual( charW, charH );
		IOS_STAMP_RE->DrawStretchPic( o.x, o.y, z.x, z.y, u, v, u + .03125f, v + .0625f, cls.charSetShader );
	}
	IOS_STAMP_RE->SetColor( NULL );
}
