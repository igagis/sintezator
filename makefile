include prorab.mk

$(eval $(call prorab-config, config))

this_name := sintezator

this_srcs += $(call prorab-src-dir,src)

this_ldlibs += -laumiks -lnitki -lopros -laudout -lpulse -lpulse-simple -lruisapp-opengl -lruis-render-opengl -lGLEW -lGL -lstdc++ -lruis -ltml -lutki -lm

$(eval $(prorab-build-app))
