## Process this file with automake to produce Makefile.in

## Created by Anjuta

PACKAGE = @PACKAGE@
sharesdir = @datadir@/$(PACKAGE)

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" $(LINJAP_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = linjap

linjap_SOURCES = \
	main.cc \
	Queue.h \
	Queue.cc \
	PopWindow.h \
	PopWindow.cc \
	NeWindow.h \
	NeWindow.cc \
	MainWindow.h \
	MainWindow.cc \
	LinkedList.h \
	LinkedList.cc \
	LinkNode.h \
	LinkNode.cc \
	HelpWindow.h \
	HelpWindow.cc \
	Engine.h \
	Engine.cc 

shares_DATA = \
	genki.dict \
	jping.png

EXTRA_DIST = genki.dict \
	jping.png

linjap_LDFLAGS = 

linjap_LDADD = $(LINJAP_LIBS)

