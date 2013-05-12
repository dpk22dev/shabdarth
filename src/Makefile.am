## Process this file with automake to produce Makefile.in

## Created by Anjuta


uidir = $(pkgdatadir)/ui
ui_DATA = shabdarth.ui


AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	$(SHABDARTH_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = shabdarth

shabdarth_SOURCES = \
	main.c \
	shabdarth.h \
	shabdarth.c \
	list_func.c \
	list_func.h \
	read_db.c \
	read_db.h \
	gui.h	

shabdarth_LDFLAGS = \
	-Wl,--export-dynamic

shabdarth_LDADD = $(SHABDARTH_LIBS)


EXTRA_DIST = $(ui_DATA)

# Remove ui directory on uninstall
uninstall-local:
	-rm -r $(uidir)
	-rm -r $(pkgdatadir)

