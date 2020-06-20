include prorab.mk

this_name := sintezator

this_srcs += $(call prorab-src-dir,src)

this_cxxflags += -Wall # enable all warnings
this_cxxflags += -Wno-comment # no warnings on nested comments
this_cxxflags += -funsigned-char # the 'char' type is unsigned
this_cxxflags += -Wnon-virtual-dtor # warn if base class has non-virtual destructor
this_cxxflags += -fno-operator-names # do not treat 'and', 'bitand','bitor','compl','not','or','xor' as keywords
this_cxxflags += -Werror # treat warnings as errors
this_cxxflags += -Wfatal-errors # stop on first error encountered
this_cxxflags += -fstrict-aliasing #in order to comply with the c++ standard more strictly
this_cxxflags += -g # include debugging symbols
this_cxxflags += -std=c++14

ifeq ($(debug),true)
    this_cxxflags += -DDEBUG
else
    this_cxxflags += -O3
endif

this_ldlibs += -laumiks -lnitki -lopros -laudout -lpulse -lpulse-simple -lmordavokne-opengl2 -lmorda-opengl2-ren -lGLEW -lGL -lstdc++ -lmorda -lpuu -rdynamic -lm

this_out_dir := build

$(eval $(prorab-build-app))
