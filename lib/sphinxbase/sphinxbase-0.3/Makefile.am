SUBDIRS = src \
	doc \
	include \
	test

EXTRA_DIST = autogen.sh				\
	sphinxbase.pc.in			\
	sphinxbase.dsw				\
	sphinxbase.vcw				\
	win32/libsphinxad/libsphinxad.dsp	\
	win32/libsphinxad/libsphinxad.vcp	\
	win32/libsphinxfe/libsphinxfe.dsp	\
	win32/libsphinxfe/libsphinxfe.vcp	\
	win32/libsphinxfeat/libsphinxfeat.dsp	\
	win32/libsphinxfeat/libsphinxfeat.vcp	\
	win32/libsphinxutil/libsphinxutil.dsp	\
	win32/libsphinxutil/libsphinxutil.vcp	\
	win32/sphinx_cepview/sphinx_cepview.dsp	\
	win32/sphinx_fe/sphinx_fe.dsp

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = sphinxbase.pc
CLEANFILES = sphinxbase.pc

etags:
	etags `find . -name "*.[ch]"`

ctags:
	ctags `find . -name "*.[ch]"`

doxygen: 
	doxygen ./doc/doxygen.cfg
