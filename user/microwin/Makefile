
BINDIR=src/bin

all clean:
	[ -d src/lib ] || mkdir src/lib
	[ -d src/bin ] || mkdir src/bin
	$(MAKE) -C src $@ || exit 1
ifeq ($(CONFIG_USER_MICROWIN_NXLIB),y)
	$(MAKE) -C nxlib $@
endif

romfs:
	$(MAKE) -C src/bin -f ../../Makefile real_romfs || exit 1
ifeq ($(CONFIG_USER_MICROWIN_NXLIB),y)
	$(MAKE) -C nxlib romfs
endif

real_romfs:
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_LAUNCHER    /bin/launcher
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_LAUNCHER    /bin/launcher.cnf
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_LAUNCHER    /bin/uponface.ppm
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_LAUNCHER    /bin/landmine
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_LAUNCHER    /bin/landmine.ppm
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_LAUNCHER    /bin/nxeyes
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_LAUNCHER    /bin/nxeyes.pgm
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_LAUNCHER    /bin/nxmag
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_LAUNCHER    /bin/logo.ppm
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_LAUNCHER    /bin/ntetris
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_LAUNCHER    /bin/ntetris.ppm
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_LAUNCHER    /bin/tux
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_LAUNCHER    /bin/tux.ppm
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_LAUNCHER    /bin/tux.gif
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_LAUNCHER    /bin/nxkbd
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_LAUNCHER    /bin/nxkbd.pgm
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_LAUNCHER    /bin/nxroach
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_LAUNCHER    /bin/nxroach.pgm
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_LAUNCHER    /bin/nxclock
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_LAUNCHER    /bin/nxclock.pgm
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_LAUNCHER    /bin/nxscribble
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_LAUNCHER    /bin/letters.cl
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_LAUNCHER    /bin/digits.cl
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_LAUNCHER    /bin/nxscribble.ppm
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_LAUNCHER    /bin/nxterm
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_LAUNCHER    /bin/nxterm.ppm
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_LAUNCHER    /bin/slider
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_LAUNCHER    /bin/slidebmp.bmp
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_LAUNCHER    /bin/slider.ppm
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_LAUNCHER    /bin/world
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_LAUNCHER    /bin/world.map
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_LAUNCHER    /bin/world.ppm
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_LANDMINE    /bin/landmine
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_MOVE        /bin/move
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_MINE        /bin/mine
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_MALPHA      /bin/malpha
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_MDEMO       /bin/mdemo
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_MTERM       /bin/mterm
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_MTEST       /bin/mtest
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_MTEST2      /bin/mtest2
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_MUSERFD     /bin/muserfd
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_NANO_X      /bin/nano-X
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_NANO_X      /bin/mwlogo.ppm
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_NANOWM      /bin/nanowm
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_NPANEL      /bin/npanel
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_NTERM       /bin/nterm
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_NXCLOCK     /bin/nxclock
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_NXEV        /bin/nxev
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_NXKBD       /bin/nxkbd
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_NXLSCLIENTS /bin/nxlsclients
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_NXTERM      /bin/nxterm
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_NXVIEW      /bin/nxview
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_NXROACH     /bin/nxroach
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_TUXCHESS    /bin/tuxchess
	if [ "$(CONFIG_USER_MICROWIN_BIN_TUXCHESS)" = "y" ]; then	\
	    mkdir $(ROMFSDIR)/usr/tuxchess;				\
	    mkdir $(ROMFSDIR)/usr/tuxchess/images;			\
	    pwd;	\
	    cp ../demos/tuxchess/images/*.gif $(ROMFSDIR)/usr/tuxchess/images;	\
	fi;
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_SLIDER      /bin/slider
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_SLIDER      /bin/slidebmp.bmp
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_VNC         /bin/vnc	
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_WORLD       /bin/world
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_BIN_WORLD       /bin/world.map
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_NANOXDEMO	/bin/demo
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_NANOXDEMO	/bin/demo2
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_NANOXDEMO	/bin/demo5
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_NANOXDEMO	/bin/demo6
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_NANOXDEMO	/bin/arcdemo
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_NANOXDEMO	/bin/bmpdemo
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_NANOXDEMO	/bin/dashdemo
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_NANOXDEMO	/bin/convpbm
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_NANOXDEMO	/bin/fontdemo
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_NANOXDEMO	/bin/ftdemo
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_NANOXDEMO	/bin/ftdemo.txt
	$(ROMFSINST) -d -e CONFIG_USER_MICROWIN_NANOXDEMO ../fonts/truetype/lt1-r-omega-serif.ttf /usr/fonts/truetype/lt1-r-omega-serif.ttf
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_NANOXDEMO	/bin/grabdemo
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_NANOXDEMO	/bin/pcfdemo
	$(ROMFSINST) -d -e CONFIG_USER_MICROWIN_NANOXDEMO ../fonts/pcf/gb24st.pcf /usr/fonts/pcf/gb24st.pcf
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_NANOXDEMO	/bin/polydemo
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_NANOXDEMO	/bin/rgndemo
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_NANOXDEMO	/bin/t1demo
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_NANOXDEMO	/bin/tsdemo
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_NANOXDEMO	/bin/nxroach.pgm
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_NANOXDEMO	/bin/getselection
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_NANOXDEMO	/bin/setselection
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_NANOXDEMO	/bin/snap_ppm
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_NANOXDEMO	/bin/logfont
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_NANOXDEMO	/bin/nsaver
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_NANOXDEMO	/bin/nxcal
	$(ROMFSINST) -e CONFIG_USER_MICROWIN_NANOXDEMO	/bin/setportrait
