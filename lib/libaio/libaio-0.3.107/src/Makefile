prefix=/usr
includedir=/usr/include
libdir=/usr/lib
usrlibdir=$(libdir)

CFLAGS += -nostdlib -nostartfiles -Wall -I. -fPIC
SO_CFLAGS=-shared $(CFLAGS)
L_CFLAGS=$(CFLAGS)
LINK_FLAGS=-lgcc -lrt $(LDFLAGS)

soname=libaio.so.1
minor=0
micro=1
libname=$(soname).$(minor).$(micro)
ifeq ($(CONFIG_FMT_USE_FLAT), y) 
all_targets += libaio.a
else
all_targets += libaio.a $(libname)
endif

all: $(all_targets)

# libaio provided functions
libaio_srcs := io_queue_init.c io_queue_release.c
libaio_srcs += io_queue_wait.c io_queue_run.c

# real syscalls
libaio_srcs += io_getevents.c io_submit.c io_cancel.c
libaio_srcs += io_setup.c io_destroy.c

# internal functions
libaio_srcs += raw_syscall.c

# old symbols
libaio_srcs += compat-0_1.c

libaio_objs := $(patsubst %.c,%.ol,$(libaio_srcs))
libaio_sobjs := $(patsubst %.c,%.os,$(libaio_srcs))

$(libaio_objs) $(libaio_sobjs): libaio.h vsys_def.h

%.os: %.c
	$(CC) $(SO_CFLAGS) -c -o $@ $<

%.ol: %.c
	$(CC) $(L_CFLAGS) -c -o $@ $<


AR ?= ar
RANLIB ?= ranlib
libaio.a: $(libaio_objs)
	rm -f libaio.a
	$(AR) r libaio.a $^
	$(RANLIB) libaio.a

$(libname): $(libaio_sobjs) libaio.map
	$(CC) $(SO_CFLAGS) -Wl,--version-script=libaio.map -Wl,-soname,$(soname) -o $@ $(libaio_sobjs) $(LINK_FLAGS)

install: $(all_targets)
	install -D -m 644 libaio.h $(DESTDIR)$(includedir)/libaio.h
	install -D -m 644 libaio.a $(DESTDIR)$(usrlibdir)/libaio.a
ifneq ($(CONFIG_FMT_USE_FLAT), y) 
	install -D -m 755 $(libname) $(DESTDIR)$(libdir)/$(libname)
	ln -sf $(libname) $(DESTDIR)$(usrlibdir)/$(soname)
	ln -sf $(libname) $(DESTDIR)$(usrlibdir)/libaio.so
endif

$(libaio_objs): libaio.h

clean:
	rm -f $(all_targets) $(libaio_objs) $(libaio_sobjs) $(soname).new
	rm -f *.so* *.a *.o
