common_audio_sources = [
  'resampler/push_resampler.cc',
  'resampler/push_sinc_resampler.cc',
  'resampler/resampler.cc',
  'resampler/sinc_resampler.cc',
  'resampler/sinusoidal_linear_chirp_source.cc',
  'signal_processing/auto_corr_to_refl_coef.c',
  'signal_processing/auto_correlation.c',
  'signal_processing/complex_fft.c',
  'signal_processing/copy_set_operations.c',
  'signal_processing/cross_correlation.c',
  'signal_processing/division_operations.c',
  'signal_processing/dot_product_with_scale.c',
  'signal_processing/downsample_fast.c',
  'signal_processing/energy.c',
  'signal_processing/filter_ar.c',
  'signal_processing/filter_ma_fast_q12.c',
  'signal_processing/get_hanning_window.c',
  'signal_processing/get_scaling_square.c',
  'signal_processing/ilbc_specific_functions.c',
  'signal_processing/levinson_durbin.c',
  'signal_processing/lpc_to_refl_coef.c',
  'signal_processing/min_max_operations.c',
  'signal_processing/randomization_functions.c',
  'signal_processing/real_fft.c',
  'signal_processing/refl_coef_to_lpc.c',
  'signal_processing/resample.c',
  'signal_processing/resample_48khz.c',
  'signal_processing/resample_by_2.c',
  'signal_processing/resample_by_2_internal.c',
  'signal_processing/resample_fractional.c',
  'signal_processing/spl_init.c',
  'signal_processing/spl_sqrt.c',
  'signal_processing/splitting_filter.c',
  'signal_processing/sqrt_of_one_minus_x_squared.c',
  'signal_processing/vector_scaling_operations.c',
  'vad/vad.cc',
  'vad/vad_core.c',
  'vad/vad_filterbank.c',
  'vad/vad_gmm.c',
  'vad/vad_sp.c',
  'vad/webrtc_vad.c',
  'audio_converter.cc',
  'audio_ring_buffer.cc',
  'audio_util.cc',
  'blocker.cc',
  'channel_buffer.cc',
  'fft4g.c',
  'fir_filter.cc',
  'lapped_transform.cc',
  'real_fourier.cc',
  'real_fourier_ooura.cc',
  'ring_buffer.c',
  'sparse_fir_filter.cc',
  'wav_file.cc',
  'wav_header.cc',
  'window_generator.cc',
]

arch_libs = []
if have_x86
  arch_libs += [static_library('common_audio_sse2',
    ['resampler/sinc_resampler_sse.cc', 'fir_filter_sse.cc'],
    dependencies: common_deps,
    include_directories: webrtc_inc,
    c_args: common_cflags + ['-msse2'],
    cpp_args: common_cxxflags + ['-msse2'])]
endif

if have_arm
  common_audio_sources += [
    'signal_processing/complex_bit_reverse_arm.S',
    'signal_processing/spl_sqrt_floor_arm.S',
  ]
endif

if have_armv7
  common_audio_sources += [
    'signal_processing/filter_ar_fast_q12_armv7.S',
  ]
endif

if have_neon
  common_audio_sources += [
    'resampler/sinc_resampler_neon.cc',
    'signal_processing/cross_correlation_neon.c',
    'signal_processing/downsample_fast_neon.c',
    'signal_processing/min_max_operations_neon.c',
    'fir_filter_neon.cc',
  ]
endif

if not have_arm
  common_audio_sources += [
    'signal_processing/complex_bit_reverse.c',
    'signal_processing/filter_ar_fast_q12.c',
    'signal_processing/spl_sqrt_floor.c',
  ]
endif

libcommon_audio = static_library('common_audio',
    common_audio_sources,
    dependencies: common_deps,
    include_directories: webrtc_inc,
    c_args: common_cflags,
    cpp_args: common_cxxflags
)

common_audio_dep = declare_dependency(
  link_with: [libcommon_audio] + arch_libs,
)
