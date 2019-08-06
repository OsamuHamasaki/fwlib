# ~/makefile
# variables

PROJECT := LampControl
SUFFIX := .exe

SOURCE_DIR := src
INCLUDE_DIR := include
TESTS_DIR := tests
DEBUG_DIR := debug

OBJ_DIR := $(DEBUG_DIR)

PROJECTS_DIR := $(HOME)/projects

CPPFLAGS :=
CPPFLAGS += -Wall
CPPFLAGS += -I$(INCLUDE_DIR)
CPPFLAGS += -I$(SOURCE_DIR)
CPPFLAGS += -I$(TESTS_DIR)
CPPFLAGS += -I$(PROJECTS_DIR)/include
CPPFLAGS += -MMD

CXXFLAGS :=
CXXFLAGS += -Wno-c++14-compat

LDFLAGS := -L$(PROJECTS_DIR)/lib

LDLIBS :=
LDLIBS += -lgtest
LDLIBS += -lgtest_main
LDLIBS += -lpthread
LDLIBS += -lstdc++

TARGET := $(addsuffix $(SUFFIX), $(DEBUG_DIR)/$(PROJECT))

SOURCES :=
SOURCES += $(wildcard $(SOURCE_DIR)/*.c)
SOURCES += $(wildcard $(SOURCE_DIR)/*.cpp)
SOURCES += $(wildcard $(TESTS_DIR)/*.cpp)

OBJS := $(addprefix $(OBJ_DIR)/, $(subst .c,.o, $(subst .cpp,.o, $(SOURCES))))
DEPENDENTS := $(subst .o,.d, $(OBJS))

# Rules

.PHONY: test clean

test: $(TARGET)
	$(TARGET)

$(TARGET): $(OBJS)
	mkdir -p $(dir $@)
	$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(COMPILE.c) -o $@ $<

$(OBJ_DIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(COMPILE.cpp) -o $@ $<

clean:
	rm -rf *~ $(SOURCE_DIR)/*~ $(INCLUDE_DIR)/*~ $(TESTS_DIR)/*~ $(DEBUG_DIR)

ifneq "$(MAKECMDGOALS)" "clean"
-include $(DEPENDENTS)
endif

# End

