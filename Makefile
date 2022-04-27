CXX = g++-11
CC = g++-11
CXXFLAGS = -std=c++20 -O2 -fmodules-ts -D_GLIBCXX_USE_CXX11_ABI=0

MODS_DIR = gcm.cache

hash := \# # escaping '#' inline seems to break things on Linux
sed_sys_mods = $(shell sed -En 's/^[[:space:]]*import[[:space:]]+<(.*)>[[:space:]]*\;/\1/p' $(1) 2> /dev/null)
sed_local_mods = $(shell sed -En 's/^[[:space:]]*(import|module)[[:space:]]+([[:alpha:]].*)[[:space:]]*\;/\2/p' $(1) 2> /dev/null)
sed_export_mods = $(shell sed -En 's/^[[:space:]]*export[[:space:]]+module[[:space:]]+([[:alpha:]].*)[[:space:]]*\;/\1/p' $(1) 2> /dev/null)
grep_mod_exporter = $(shell grep -REl '^[[:space:]]*export[[:space:]]+module[[:space:]]+$(1)[[:space:]]*\;' . | head -n1)

find_sys_dir = $(shell echo '$(hash)include<$(mod)>' | g++-11 -M -xc++ - | tr " " "\n" | grep -E '/$(mod)$$')
find_mods = $(call sed_local_mods,$(1)) $(foreach mod,$(call sed_sys_mods,$(1)),$(find_sys_dir))
parse_mod_deps = $(addprefix $(MODS_DIR)/, $(addsuffix .gcm, $(call find_mods,$(1))))

$(MODS_DIR)//%.gcm: # double forward-slash hack distinguishes system headers (which we format in this way)
	$(CXX) $(CXXFLAGS)   -xc++-system-header $(basename $(notdir $@))

.SECONDEXPANSION:
pc := %
$(MODS_DIR)/%.gcm : $$(patsubst $$(pc).cpp,$$(pc).o,$$(call grep_mod_exporter,$$*))
	$(eval EXPORTER := $(call grep_mod_exporter,$(basename $(notdir $@))))
	@# hack needed because the compiled module seems to break if relevant precompiled system headers are still present
	@for SYSINC in $$(sed -En 's/^[[:space:]]*#include[[:space:]]+<(.*)>[[:space:]]*$$/\1/p' $(EXPORTER)); do find $(MODS_DIR)/*/ -name $$SYSINC.gcm -exec rm {} \; || true; done
	$(CXX) $(CXXFLAGS) -fmodule-only   -c $(call grep_mod_exporter,$(basename $(notdir $@)))

LIB_SOURCE = $(shell find src -name '*.cpp')
LIB_OBJECTS = $(LIB_SOURCE:.cpp=.o)
LIB = libneuralnets.a
TEST_SOURCE = $(shell find tests -name '*.cpp')
TEST_OBJECTS = $(TEST_SOURCE:.cpp=.o)
OBJECTS = $(LIB_OBJECTS) $(TEST_OBJECTS)
TESTS = $(TEST_SOURCE:.cpp=)

$(LIB): $(LIB_OBJECTS)
	ar rcs $@ $^
	ranlib $@

.PHONY: tests
tests: $(TESTS)

$(TESTS) : % : %.o $(LIB)

$(OBJECTS) : %.o : %.cpp $$(call parse_mod_deps,$$*.cpp)

.PHONY: clean
clean:
	rm -rf $(MODS_DIR) $(OBJECTS) $(TESTS) $(LIB)
