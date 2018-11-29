SUBDIRS = webrtc

bin_PROGRAMS = audio_test_main

audio_test_main_SOURCES = audio_test_main.cc

audio_test_main_CFLAGS = $(AM_CFLAGS) $(COMMON_CFLAGS)
audio_test_main_CXXFLAGS = $(AM_CXXFLAGS) $(COMMON_CXXFLAGS)
audio_test_main_LDADD   = webrtc/modules/audio_processing/.libs/libwebrtc_audio_processing.la							
						
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = webrtc-audio-processing.pc

webrtcincludedir = $(includedir)/webrtc_audio_processing
nobase_webrtcinclude_HEADERS = webrtc/base/arraysize.h \
			       webrtc/base/checks.h \
			       webrtc/base/constructormagic.h \
			       webrtc/base/basictypes.h \
			       webrtc/base/maybe.h \
			       webrtc/base/platform_file.h \
			       webrtc/common.h \
			       webrtc/common_types.h \
			       webrtc/typedefs.h \
			       webrtc/modules/audio_processing/beamformer/array_util.h \
			       webrtc/modules/audio_processing/include/audio_processing.h \
			       webrtc/modules/interface/module_common_types.h \
			       webrtc/system_wrappers/include/trace.h

EXTRA_DIST = NEWS \
	     README.md \
	     UPDATING.md
