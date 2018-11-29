base_sources = [
  'criticalsection.cc',
  'checks.cc',
  'event.cc',
  'platform_thread.cc',
  'platform_file.cc',
  'stringutils.cc',
  'thread_checker_impl.cc',
]

base_headers = [
  'arraysize.h',
  'checks.h',
  'constructormagic.h',
  'basictypes.h',
  'maybe.h',
  'platform_file.h',
]

install_headers(base_headers,
    subdir: 'webrtc_audio_processing/webrtc/base'
)

libbase = static_library('libbase',
    base_sources,
    dependencies: common_deps,
    include_directories: webrtc_inc,
    cpp_args : common_cxxflags
)

base_dep = declare_dependency(
    link_with: libbase
)

