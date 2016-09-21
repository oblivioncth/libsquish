include config

VER = 1.14
SOVER = 0

SRC = alpha.cpp clusterfit.cpp colourblock.cpp colourfit.cpp colourset.cpp maths.cpp rangefit.cpp singlecolourfit.cpp squish.cpp

HDR = alpha.h clusterfit.h colourblock.h colourfit.h colourset.h maths.h rangefit.h singlecolourfit.h squish.h
HDR += config.h simd.h simd_float.h simd_sse.h simd_ve.h singlecolourlookup.inl

OBJ = $(SRC:%.cpp=%.o)

SOLIB = libsquish.so.$(SOVER)
LIB = $(SOLIB).0
CPPFLAGS += -fPIC
LIBA = libsquish.a

all: $(LIB) $(LIBA) docs libsquish.pc

install: $(LIB) $(LIBA) libsquish.pc
	$(INSTALL_DIRECTORY) $(INSTALL_DIR)/include $(INSTALL_DIR)/lib
	$(INSTALL_FILE) squish.h $(INSTALL_DIR)/include
	$(INSTALL_FILE) $(LIBA) $(INSTALL_DIR)/lib
ifeq ($(USE_SHARED),1)
	$(INSTALL_FILE) $(LIB) $(INSTALL_DIR)/lib
	ln -s $(LIB) $(INSTALL_DIR)/lib/$(SOLIB)
	ln -s $(LIB) $(INSTALL_DIR)/lib/libsquish.so
	$(INSTALL_DIRECTORY) $(INSTALL_DIR)/lib/pkgconfig
	$(INSTALL_FILE) libsquish.pc $(INSTALL_DIR)/lib/pkgconfig
endif

uninstall:
	$(RM) $(INSTALL_DIR)/include/squish.h
	$(RM) $(INSTALL_DIR)/lib/$(LIBA)
	-$(RM) $(INSTALL_DIR)/lib/$(LIB)
	-$(RM) $(INSTALL_DIR)/lib/$(SOLIB)
	-$(RM) $(INSTALL_DIR)/lib/libsquish.so
	-$(RM) $(INSTALL_DIR)/lib/pkgconfig/libsquish.pc

$(LIB): $(OBJ)
	$(CXX) $(LDFLAGS) -shared -Wl,-soname,$(SOLIB) -o $@ $(OBJ)

$(LIBA): $(OBJ)
	$(AR) cr $@ $?
	ranlib $@

docs: $(SRC) $(HDR)
	@if [ -x "$(command -v doxygen)" ]; then doxygen; fi

libsquish.pc: libsquish.pc.in
	@sed 's|@PREFIX@|$(PREFIX)|' $@.in > $@

tgz: clean
	tar zcf libsquish-$(VER).tgz $(SRC) $(HDR) Makefile config CMakeLists.txt CMakeModules libSquish.* README LICENSE ChangeLog Doxyfile libsquish.pc.in extra

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -I. $(CXXFLAGS) -o $@ -c $<

clean:
	$(RM) $(OBJ) $(LIB) $(LIBA) libsquish.pc
	$(RM) -rf docs
