# Test files
TEST_C_SOURCES := $(wildcard test/*.c)

TEST_C_OBJ := $(TEST_C_SOURCES:.c=.o)

MAIN_C_SOURCES := $(wildcard src/*.c)

# Check OS
CFLAGS 				:=

ifeq '$(findstring ;,$(PATH))' ';'
    detected_OS := Windows
else
    detected_OS := $(shell uname 2>/dev/null || echo Unknown)
    detected_OS := $(patsubst CYGWIN%,Cygwin,$(detected_OS))
    detected_OS := $(patsubst MSYS%,MSYS,$(detected_OS))
    detected_OS := $(patsubst MINGW%,MSYS,$(detected_OS))
endif


ifeq ($(detected_OS),Windows)
    CFLAGS += -D WIN32
	ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
		CFLAGS += -D AMD64
	endif
	ifeq ($(PROCESSOR_ARCHITECTURE),x86)
		CFLAGS += -D IA32
	endif
else
	ifeq ($(detected_OS),Darwin)        # Mac OS X
    	CFLAGS += -D OSX
	endif
	ifeq ($(detected_OS),Linux)
    	CFLAGS   +=   -D LINUX
	endif
	ifeq ($(detected_OS),GNU)           # Debian GNU Hurd
    	CFLAGS   +=   -D GNU_HURD
	endif
	ifeq ($(detected_OS),GNU/kFreeBSD)  # Debian kFreeBSD
    	CFLAGS   +=   -D GNU_kFreeBSD
	endif
	ifeq ($(detected_OS),FreeBSD)
    	CFLAGS   +=   -D FreeBSD
	endif
	ifeq ($(detected_OS),NetBSD)
    	CFLAGS   +=   -D NetBSD
	endif
	ifeq ($(detected_OS),DragonFly)
    	CFLAGS   +=   -D DragonFly
	endif
	ifeq ($(detected_OS),Haiku)
    	CFLAGS   +=   -D Haiku
	endif
	UNAME_P := $(shell uname -p)
	ifeq ($(UNAME_P),x86_64)
		CFLAGS += -D AMD64
	endif
	ifneq ($(filter %86,$(UNAME_P)),)
		CFLAGS += -D IA32
	endif
	ifneq ($(filter arm%,$(UNAME_P)),)
		OSFLAG += -D ARM
	endif
endif


os_detect:
	@echo ${CFLAGS}

ls_test:
	@echo ${TEST_C_OBJ}



# $(TEST_C_OBJ): $(TEST_C_SOURCES)
# 	gcc -c -o $@ $< $(CFLAGS) -Isrc -D WIN_32_LEAN_AND_MEAN -mwindows

# test: $(TEST_C_OBJ)
# 	@echo $(TEST_C_OBJ)
# 	gcc -o $@ $^ $(CFLAGS) -Isrc  -D WIN_32_LEAN_AND_MEAN -mwindows

.PHONY:test

test:
	@echo $(TEST_C_SOURCES)
	@echo $(MAIN_C_SOURCES)
	gcc -Wall $(TEST_C_SOURCES) $(MAIN_C_SOURCES) -o test.exe -Isrc -Isrc/ -I/src -I. $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(TEST_C_OBJ)
