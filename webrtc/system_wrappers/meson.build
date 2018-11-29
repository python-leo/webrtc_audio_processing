system_wrappers_sources = [
  'source/aligned_malloc.cc',
  'source/cpu_features.cc',
  'source/event.cc',
  'source/file_impl.cc',
  'source/critical_section.cc',
  'source/logging.cc',
  'source/metrics_default.cc',
  'source/rw_lock.cc',
  'source/sleep.cc',
  'source/thread.cc',
  'source/trace_impl.cc',
]

if have_posix
  system_wrappers_sources += [
    'source/critical_section_posix.cc',
    'source/event_timer_posix.cc',
    'source/rw_lock_posix.cc',
    'source/thread_posix.cc',
    'source/trace_posix.cc',
  ]
endif

if have_win
  system_wrappers_sources += [
    'source/critical_section_win.cc',
    'source/condition_variable.cc',
    'source/condition_variable_event_win.cc',
    'source/condition_variable_native_win.cc',
    'source/event_timer_win.cc',
    'source/rw_lock_win.cc',
    'source/rw_lock_generic.cc',
    'source/thread_win.cc',
    'source/trace_win.cc',
  ]
endif

system_headers = [
  'include/trace.h',
]

install_headers(system_headers,
    subdir: 'webrtc_audio_processing/webrtc/system_wrappers/include'
)

libsystem_wrappers = static_library('system_wrappers',
    system_wrappers_sources,
    dependencies: common_deps,
    include_directories: webrtc_inc,
    c_args : common_cflags,
    cpp_args : common_cxxflags
)

system_wrappers_dep = declare_dependency(
    link_with: libsystem_wrappers
)
