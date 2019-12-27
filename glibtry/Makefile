INCLUDE = -I/usr/local/include/glib-2.0 -I/usr/local/lib/glib-2.0/include
CFLAGS  += `pkg-config --cflags glib-2.0`
LDFLAGS += `pkg-config --libs glib-2.0`

all:
	gcc $(INCLUDE) glibtry.c -o glibtry $(CFLAGS) $(LDFLAGS)
	
clean:
	rm -rf *.o glibtry
