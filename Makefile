CC=cc
CFLAGS=-std=c99 -Wall -Wextra -g
INCLUDE=-I /usr/include/SDL2 -I /usr/include/schoki_misc
LIB_NAME=schoki_gui
SO_NAME=lib$(LIB_NAME).so

.PHONY: all clean examples install uninstall

all: $(SO_NAME) install

SGUI_menu.o:
	$(CC) -c -fPIC $(CFLAGS) $(INCLUDE) src/SGUI_menu.c

SGUI_label.o:
	$(CC) -c -fPIC $(CFLAGS) $(INCLUDE) src/SGUI_label.c

SGUI_button.o:
	$(CC) -c -fPIC $(CFLAGS) $(INCLUDE) src/SGUI_button.c

SGUI_entry.o:
	$(CC) -c -fPIC $(CFLAGS) $(INCLUDE) src/SGUI_entry.c

SGUI_sprite.o:
	$(CC) -c -fPIC $(CFLAGS) $(INCLUDE) src/SGUI_sprite.c

$(SO_NAME): SGUI_menu.o SGUI_label.o SGUI_button.o SGUI_entry.o SGUI_sprite.o
	$(CC) -shared -o $@ $^

install: $(SO_NAME)
	cp $(SO_NAME) /usr/lib
	chmod 0755 /usr/lib/$(SO_NAME)
	mkdir /usr/include/$(LIB_NAME)
	cp src/*.h /usr/include/$(LIB_NAME)
	ldconfig

clean:
	rm -f *.o
	rm -f $(SO_NAME)
	
	rm -f every_widget
	rm -f multiple_menus
	rm -f grid

uninstall:
	rm -r -f /usr/include/$(LIB_NAME)
	rm -f /usr/lib/$(SO_NAME)

EXFLAGS=-std=c99 -Wall -Wextra -g
EXLIBS=-l schoki_misc -l SDL2 -l SDL2_ttf -l $(LIB_NAME)
EXINCLUDE=$(INCLUDE) -I ./src -L .

examples: every_widget multiple_menus grid

every_widget:
	$(CC) examples/$@.c -o $@ $(EXFLAGS) $(EXLIBS) $(EXINCLUDE)

multiple_menus:
	$(CC) examples/$@.c -o $@ $(EXFLAGS) $(EXLIBS) $(EXINCLUDE)

grid:
	$(CC) examples/$@.c -o $@ $(EXFLAGS) $(EXLIBS) $(EXINCLUDE)
