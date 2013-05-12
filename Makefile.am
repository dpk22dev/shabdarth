## Process this file with automake to produce Makefile.in
## Created by Anjuta

SUBDIRS = src dbs desktop

shabdarthdocdir = ${prefix}/doc/shabdarth
shabdarthdoc_DATA = \
	README\
	COPYING\
	AUTHORS\
	ChangeLog\
	INSTALL\
	NEWS


EXTRA_DIST = $(shabdarthdoc_DATA)


# Remove doc directory on uninstall
uninstall-local:
	-rm -r $(shabdarthdocdir)
