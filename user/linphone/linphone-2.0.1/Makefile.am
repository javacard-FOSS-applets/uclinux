## Process this file with automake to produce Makefile.in

# let make re-run automake upon need
ACLOCAL_AMFLAGS = -I m4

if EXTERNAL_ORTP
ORTP_DIR =
else
ORTP_DIR = oRTP
endif

SUBDIRS = m4 pixmaps po ipkg $(ORTP_DIR) mediastreamer2\
		media_api coreapi console gtk share


EXTRA_DIST = config.rpath   linphone2.glade BUGS linphone.kdevprj \
				intltool-extract.in	\
				intltool-merge.in	\
				intltool-update.in \
				README.arm \
				autogen.sh \
				linphone.spec.in linphone.spec
ACLOCAL_FLAGS=-I$(top_srcdir)/m4

DISTCLEANFILES= intltool-extract intltool-merge intltool-update po/stamp-it po/.intltool-merge-cache

# `make rpm'

all-local: linphone.spec
linphone.spec: linphone.spec.in

.phony: rpm
rpm:
	$(MAKE) dist
# Create "Specfile" at the same level as the tarball content
	-rm -f $(PACKAGE)-$(VERSION).tar
	gunzip $(PACKAGE)-$(VERSION).tar.gz
	cp $(PACKAGE).spec Specfile
	tar --append --file=$(PACKAGE)-$(VERSION).tar Specfile
	gzip $(PACKAGE)-$(VERSION).tar
# <https://bugzilla.redhat.com/bugzilla/show_bug.cgi?id=2068410>
	TAR_OPTIONS=--wildcards rpmbuild -ta --clean --rmsource --rmspec $(PACKAGE)-$(VERSION).tar.gz
