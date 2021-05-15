include prorab.mk

$(eval $(call prorab-config, config))

this_name := sintezator

this_srcs += $(call prorab-src-dir,src)

this_ldlibs += -laumiks -lnitki -lopros -laudout -lpulse -lpulse-simple -lmordavokne-opengl2 -lmorda-opengl2-ren -lGLEW -lGL -lstdc++ -lmorda -ltreeml -lutki -lm

$(eval $(prorab-build-app))
