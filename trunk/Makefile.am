## Process this file with automake to produce Makefile.in
## Created by Anjuta

gnomeintdir = @datadir@/applications
SUBDIRS = src 

linjapdocdir = ${prefix}/doc/linjap
linjapdoc_DATA = \
	README\
	COPYING\
	AUTHORS\
	ChangeLog\
	INSTALL\
	NEWS

gnomeint_DATA = linjap.desktop

EXTRA_DIST = $(linjapdoc_DATA) \
	linjap.desktop

# Copy all the spec files. Of cource, only one is actually used.
dist-hook:
	for specfile in *.spec; do \
		if test -f $$specfile; then \
			cp -p $$specfile $(distdir); \
		fi \
	done

