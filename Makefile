# -*- Makefile -*-
# ----------------------------------------------------------------------

TARGETS = \
  $(ACMACS_WHOCC_DATA_LIB)

SOURCES = \
  vaccines.cc labs.cc

# ----------------------------------------------------------------------

SRC_DIR = $(abspath $(ACMACSD_ROOT)/sources)

all: install

include $(ACMACSD_ROOT)/share/Makefile.config

ACMACS_WHOCC_DATA_LIB_MAJOR = 1
ACMACS_WHOCC_DATA_LIB_MINOR = 0
ACMACS_WHOCC_DATA_LIB = $(DIST)/$(call shared_lib_name,libacmacswhoccdata,$(ACMACS_WHOCC_DATA_LIB_MAJOR),$(ACMACS_WHOCC_DATA_LIB_MINOR))

LDLIBS = \
  $(AD_LIB)/$(call shared_lib_name,libacmacsbase,1,0) \
  $(AD_LIB)/$(call shared_lib_name,libacmacsvirus,1,0) \
  $(XZ_LIBS) $(CXX_LIBS)

# ----------------------------------------------------------------------

install: install-headers $(TARGETS)
	$(call install_lib,$(ACMACS_WHOCC_DATA_LIB))
	# ln -sf $(DIST)/* $(AD_BIN)
	# ln -sf $(abspath bin)/* $(AD_BIN)
	for jd in clades vaccines; do if [ ! -f $(AD_SHARE)/conf/$${jd}.json ]; then mkdir -p $(AD_SHARE)/conf; ln -sf $(abspath conf/$${jd}.json) $(AD_SHARE)/conf; fi; done

test: install
	@#test/test
.PHONY: test

# ----------------------------------------------------------------------

$(ACMACS_WHOCC_DATA_LIB): $(patsubst %.cc,$(BUILD)/%.o,$(SOURCES)) | $(DIST)
	$(call echo_shared_lib,$@)
	$(call make_shared_lib,libacmacswhoccdata,$(ACMACS_WHOCC_DATA_LIB_MAJOR),$(ACMACS_WHOCC_DATA_LIB_MINOR)) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(DIST)/%: $(BUILD)/%.o | $(DIST)
	$(call echo_link_exe,$@)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS) $(AD_RPATH)

# ======================================================================
### Local Variables:
### eval: (if (fboundp 'eu-rename-buffer) (eu-rename-buffer))
### End:
