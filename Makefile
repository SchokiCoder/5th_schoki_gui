CC=cc
CFLAGS=-std=c99 -Wall -Wextra -O3
INCLUDE=-lSDL2 -lSDL2_ttf -lSDL2_image -lschoki_misc
INCLUDE_DIR=-I/usr/include/SDL2 -I/usr/include/schoki_misc
LIB_NAME=schoki_gui
SO_NAME=lib$(LIB_NAME).so

all: $(SO_NAME) install

SGUI_menu.o:
	$(CC) -c -fPIC $(CFLAGS) $(INCLUDE_DIR) src/SGUI_menu.c

SGUI_label.o:
	$(CC) -c -fPIC $(CFLAGS) $(INCLUDE_DIR) src/SGUI_label.c

SGUI_button.o:
	$(CC) -c -fPIC $(CFLAGS) $(INCLUDE_DIR) src/SGUI_button.c

SGUI_entry.o:
	$(CC) -c -fPIC $(CFLAGS) $(INCLUDE_DIR) src/SGUI_entry.c

SGUI_sprite.o:
	$(CC) -c -fPIC $(CFLAGS) $(INCLUDE_DIR) src/SGUI_sprite.c

$(SO_NAME): SGUI_menu.o SGUI_label.o SGUI_button.o SGUI_entry.o SGUI_sprite.o
	$(CC) -shared -o $@ $^

install:
	cp $(SO_NAME) /usr/lib
	chmod 0755 /usr/lib/$(SO_NAME)
	mkdir /usr/include/$(LIB_NAME)
	cp src/*.h /usr/include/$(LIB_NAME)
	ldconfig

clean:
	rm -f *.o
	rm -f $(SO_NAME)

uninstall:
	rm -r -f /usr/include/$(LIB_NAME)
	rm -f /usr/lib/$(SO_NAME)
