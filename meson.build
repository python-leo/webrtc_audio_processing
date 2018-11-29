project('webrtc-audio-processing', 'c', 'cpp',
  version : '0.3.1',
  meson_version : '>= 0.47',
  default_options : [ 'warning_level=1',
                      'buildtype=debugoptimized' ])

soversion = 0

cc = meson.get_compiler('c')

host_system = host_machine.system()

platform_cflags = []
os_cflags = []
os_deps = []
have_posix = false
have_win = false

if ['darwin', 'ios'].contains(host_system)
  os_cflags = ['-DWEBRTC_MAC', '-DWEBRTC_THREAD_RR', '-DWEBRTC_CLOCK_TYPE_REALTIME']
  if host_system == 'ios'
    os_cflags += ['-DWEBRTC_IOS']
  endif
  have_posix = true
elif host_system == 'android'
  os_cflags += ['-DWEBRTC_ANDROID', '-DWEBRTC_LINUX', '-DWEBRTC_THREAD_RR', '-DWEBRTC_CLOCK_TYPE_REALTIME']
  os_deps += [cc.find_library('log')]
  os_deps += [dependency('gnustl', required : get_option('gnustl'))]
  have_posix = true
elif host_system == 'linux'
  os_cflags += ['-DWEBRTC_LINUX', '-DWEBRTC_THREAD_RR']
  os_deps += [cc.find_library('rt', required : false)]
  os_deps += [dependency('threads')]
  have_posix = true
elif host_system == 'windows'
  platform_cflags += ['-DWEBRTC_WIN', '-D_WIN32', '-U__STRICT_ANSI__']
  os_deps += [cc.find_library('winmm')]
  have_win = true
endif

if have_posix
  platform_cflags += ['-DWEBRTC_POSIX']
endif

arch_cflags = []
have_arm = false
have_armv7 = false
have_neon = false
have_x86 = false
if ['arm', 'armv7', 'aarch64'].contains(host_machine.cpu_family())
  have_arm = true
  arch_cflags = ['-DWEBRTC_ARCH_ARM']
  if cc.compiles('''#ifndef __ARM_ARCH_7A__
#error no armv7 arch
#endif''')
    have_armv7 = true
    arch_cflags = ['-DWEBRTC_ARCH_ARM_V7']
  endif
  if cc.compiles('''#ifndef __aarch64__
#error no aarch64 arch
#endif''')
    have_neon = true
    arch_cflags = ['-DWEBRTC_ARCH_ARM64', '-DWEBRTC_HAS_NEON']
  endif
endif
if ['x86', 'x86_64'].contains(host_machine.cpu_family())
  have_x86 = true
endif

neon_opt = get_option('neon')
if neon_opt != 'no'
  if neon_opt != 'runtime'
    if cc.compiles('#include <arm_neon.h>', args : '-mfpu=neon')
      arch_cflags += ['-mfpu=neon', '-DWEBRTC_HAS_NEON']
      have_neon = true
    endif
  else
    neon_opt += ['-DWEBRTC_DETECT_NEON', '-mfpu=neon']
    have_neon = true
  endif
endif

noise_cflags = []
if get_option('ns_mode') == 'float'
  noise_cflags += ['-DWEBRTC_NS_FLOAT=1']
else
  noise_cflags += ['-DWEBRTC_NS_FIXED=1']
endif

common_cflags = ['-DWEBRTC_AUDIO_PROCESSING_ONLY_BUILD', '-DNDEBUG'] + platform_cflags + os_cflags + arch_cflags + noise_cflags
common_cxxflags = ['-std=c++11'] + common_cflags
common_deps = os_deps
webrtc_inc = include_directories('.')

subdir('webrtc')

pkgconfig = import('pkgconfig')

pkgconfig.generate(
    name: 'webrtc-audio-processing',
    description: 'WebRTC Audio Processing library',
    version: meson.project_version(),
    filebase: 'webrtc-audio-processing',
    subdirs: 'webrtc_audio_processing',
    extra_cflags: [
      '-DWEBRTC_AUDIO_PROCESSING_ONLY_BUILD',
    ] + platform_cflags,
    # XXX: passing the libwebrtc_audio_processing object result in adding not-installed libraries to Libs.private
    libraries: '-lwebrtc_audio_processing',
    libraries_private: common_deps,
)
