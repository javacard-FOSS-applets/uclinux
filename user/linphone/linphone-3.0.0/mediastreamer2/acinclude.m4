dnl -*- autoconf -*-
AC_DEFUN([MS_CHECK_DEP],[
	dnl $1=dependency description
	dnl $2=dependency short name, will be suffixed with _CFLAGS and _LIBS
	dnl $3=headers's place
	dnl $4=lib's place
	dnl $5=header to check
	dnl $6=lib to check
	dnl $7=function to check in library
	
	dep_name=$2
	dep_headersdir=$3
	dep_libsdir=$4
	dep_header=$5
	dep_lib=$6
	dep_funclib=$7
	other_libs=$8	
	
	CPPFLAGS_save=$CPPFLAGS
	LDFLAGS_save=$LDFLAGS
	LIBS_save=$LIBS
	CPPFLAGS=`echo "-I$dep_headersdir"|sed -e "s:-I/usr/include[\ ]*$::"`
	LIBS="-l$dep_lib"
	LDFLAGS=`echo "-L$dep_libsdir"|sed -e "s:-L/usr/lib\(64\)*[\ ]*::"`
	
	$2_CFLAGS="$CPPFLAGS"
	$2_LIBS="$LDFLAGS $LIBS"

	AC_CHECK_HEADERS([$dep_header],[AC_CHECK_LIB([$dep_lib],[$dep_funclib],found=yes,found=no, [$other_libs])
	],found=no)
	
	if test "$found" = "yes" ; then
		eval $2_found=yes
	else
		eval $2_found=no
		eval $2_CFLAGS=
		eval $2_LIBS=
	fi
	AC_SUBST($2_CFLAGS)
	AC_SUBST($2_LIBS)
	CPPFLAGS=$CPPFLAGS_save
	LDFLAGS=$LDFLAGS_save
	LIBS=$LIBS_save
])


AC_DEFUN([MS_CHECK_VIDEO],[

	dnl conditionnal build of video support
	AC_ARG_ENABLE(video,
		  [  --enable-video    Turn on video support compiling],
		  [case "${enableval}" in
			yes) video=true ;;
			no)  video=false ;;
			*) AC_MSG_ERROR(bad value ${enableval} for --enable-video) ;;
		  esac],[video=true])
		  
	AC_ARG_WITH( ffmpeg,
		  [  --with-ffmpeg		Sets the installation prefix of ffmpeg, needed for video support. [default=/usr] ],
		  [ ffmpegdir=${withval}],[ ffmpegdir=/usr ])
	
	AC_ARG_WITH( sdl,
		  [  --with-sdl		Sets the installation prefix of libSDL, needed for video support. [default=/usr] ],
		  [ libsdldir=${withval}],[ libsdldir=/usr ])
	
	if test "$video" = "true"; then
		
		dnl test for ffmpeg presence
		PKG_CHECK_MODULES(FFMPEG, [libavcodec >= 50.0.0 ],ffmpeg_found=yes , ffmpeg_found=no)
		dnl workaround for debian...
		PKG_CHECK_MODULES(FFMPEG, [libavcodec >= 0d.50.0.0 ], ffmpeg_found=yes, ffmpeg_found=no)
		if test x$ffmpeg_found = xno ; then
			AC_MSG_ERROR([Could not find ffmpeg headers and library. This is mandatory for video support])
		fi

		dnl check for new/old ffmpeg header file layout
		CPPFLAGS_save=$CPPFLAGS
		CPPFLAGS=$FFMPEG_CFLAGS
		AC_CHECK_HEADERS(libavcodec/avcodec.h)
		CPPFLAGS=$CPPFLAGS_save

		dnl to workaround a bug on debian and ubuntu, check if libavcodec needs -lvorbisenc to compile	
		AC_CHECK_LIB(avcodec,avcodec_register_all, novorbis=yes , [
			LIBS="$LIBS -lvorbisenc"
		], $FFMPEG_LIBS )

		dnl when swscale feature is not provided by
		dnl libswscale, its features are swallowed by
		dnl libavcodec, but without swscale.h and without any
		dnl declaration into avcodec.h (this is to be
		dnl considered as an ffmpeg bug).
		dnl 
		dnl #if defined(HAVE_LIBAVCODEC_AVCODEC_H) && !defined(HAVE_LIBSWSCALE_SWSCALE_H)
		dnl # include "swscale.h" // private linhone swscale.h
		dnl #endif
		CPPFLAGS_save=$CPPFLAGS
		CPPFLAGS=$FFMPEG_CFLAGS
		AC_CHECK_HEADERS(libswscale/swscale.h)
		CPPFLAGS=$CPPFLAGS_save

		PKG_CHECK_MODULES(SWSCALE, [libswscale >= 0.5.0 ], [echo "We have libswscale"], 
			[echo "We don't have libswscale, let's hope its symbols are in libavcodec"] )

		MS_CHECK_DEP([SDL],[SDL],[${libsdldir}/include],[${libsdldir}/lib],[SDL/SDL.h],[SDL],[SDL_Init])
		if test "$SDL_found" = "no" ; then
			AC_MSG_ERROR([Could not find libsdl headers and library. This is mandatory for video support])
		fi

		PKG_CHECK_MODULES(THEORA, [theora >= 1.0alpha7 ], [have_theora=yes],
					[have_theora=no])
		AC_CHECK_HEADERS(X11/Xlib.h)
		
		VIDEO_CFLAGS=" $FFMPEG_CFLAGS $SDL_CFLAGS -DVIDEO_ENABLED "
		VIDEO_LIBS=" $FFMPEG_LIBS $SWSCALE_LIBS $SDL_LIBS"

		if test "${ac_cv_header_X11_Xlib_h}" = "yes" ; then
			VIDEO_LIBS="$VIDEO_LIBS -lX11"
		fi
	fi
	
	AC_SUBST(VIDEO_CFLAGS)
	AC_SUBST(VIDEO_LIBS)
])
