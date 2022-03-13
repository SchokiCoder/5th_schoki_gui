#    schoki_gui
#    Copyright (C) 2022  Andy Frank Schoknecht
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <https://www.gnu.org/licenses/>.

CC = cc
API_SHORT = SGUI
BIN_NAME = lib$(API_SHORT).so
CFLAGS = -std=c99 -Wall -Wextra -O3 -shared -fPIC
INCLUDE = -I /usr/include/SDL2
LIBS = -l SDL2 -l SDL2_image -l SDL2_ttf

PATH_INSTALL_BIN = /usr/lib/
PATH_INSTALL_INCLUDE = /usr/include/$(API_SHORT)

all: install clean

clean:
	rm -f $(BIN_NAME)
	rm -f *.o

install:
	$(CC) src/*.c $(CFLAGS) $(INCLUDE) $(LIBS) -o $(BIN_NAME)

	cp -f $(BIN_NAME) $(PATH_INSTALL_BIN)

	mkdir -p $(PATH_INSTALL_INCLUDE)
	cp -r src/*.h $(PATH_INSTALL_INCLUDE)

uninstall:
	rm -f $(PATH_INSTALL_BIN)$(BIN_NAME)

	rm -f -r $(PATH_INSTALL_INCLUDE)
