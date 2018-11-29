webrtc_audio_processing_sources = [
  'aec/aec_core.c',
  'aec/aec_rdft.c',
  'aec/aec_resampler.c',
  'aec/echo_cancellation.c',
  'aecm/echo_control_mobile.c',
  'aecm/aecm_core.c',
  'aecm/aecm_core_c.c',
  'agc/legacy/analog_agc.c',
  'agc/legacy/digital_agc.c',
  'agc/agc.cc',
  'agc/agc_manager_direct.cc',
  'agc/histogram.cc',
  'agc/utility.cc',
  'beamformer/array_util.cc',
  'beamformer/covariance_matrix_generator.cc',
  'beamformer/nonlinear_beamformer.cc',
  'intelligibility/intelligibility_enhancer.cc',
  'intelligibility/intelligibility_utils.cc',
  'logging/aec_logging_file_handling.cc',
  'transient/click_annotate.cc',
  'transient/file_utils.cc',
  'transient/moving_moments.cc',
  'transient/transient_detector.cc',
  'transient/transient_suppressor.cc',
  'transient/wpd_node.cc',
  'transient/wpd_tree.cc',
  'utility/delay_estimator.c',
  'utility/delay_estimator_wrapper.c',
  'vad/gmm.cc',
  'vad/pitch_based_vad.cc',
  'vad/pitch_internal.cc',
  'vad/pole_zero_filter.cc',
  'vad/standalone_vad.cc',
  'vad/vad_audio_proc.cc',
  'vad/vad_circular_buffer.cc',
  'vad/voice_activity_detector.cc',
  'audio_buffer.cc',
  'audio_processing_impl.cc',
  'audio_processing_impl.h',
  'echo_cancellation_impl.cc',
  'echo_control_mobile_impl.cc',
  'gain_control_impl.cc',
  'high_pass_filter_impl.cc',
  'level_estimator_impl.cc',
  'noise_suppression_impl.cc',
  'rms_level.cc',
  'splitting_filter.cc',
  'processing_component.cc',
  'three_band_filter_bank.cc',
  'typing_detection.cc',
  'voice_detection_impl.cc',
]

webrtc_audio_processing_beamformer_headers = [
  'beamformer/array_util.h',
]

webrtc_audio_processing_include_headers = [
  'include/audio_processing.h',
]

if get_option('ns_mode') == 'float'
  webrtc_audio_processing_sources += [
    'ns/noise_suppression.c',
    'ns/ns_core.c',
  ]
else
  webrtc_audio_processing_sources += [
    'ns/noise_suppression_x.c',
    'ns/nsx_core.c',
    'ns/nsx_core_c.c',
  ]
  if have_neon
    webrtc_audio_processing_sources += [
      'ns/nsx_core_neon.c',
    ]
  endif
endif

extra_libs = []
if have_x86
  extra_libs += [
    static_library('webrtc_audio_processing_privatearch',
      ['aec/aec_core_sse2.c', 'aec/aec_rdft_sse2.c'],
      dependencies: common_deps,
      include_directories: webrtc_inc,
      c_args: common_cflags + ['-msse2'],
      cpp_args: common_cxxflags + ['-msse2']
    )
  ]
endif

if have_neon
  webrtc_audio_processing_sources += [
    'aec/aec_core_neon.c',
    'aec/aec_rdft_neon.c',
    'aecm/aecm_core_neon.c',
  ]
endif

install_headers(webrtc_audio_processing_beamformer_headers,
    subdir: 'webrtc_audio_processing/webrtc/modules/audio_processing/beamformer'
)

install_headers(webrtc_audio_processing_include_headers,
    subdir: 'webrtc_audio_processing/webrtc/modules/audio_processing/include'
)

libwebrtc_audio_processing = library('webrtc_audio_processing',
    webrtc_audio_processing_sources,
    dependencies: [base_dep, audio_coding_dep, system_wrappers_dep, common_audio_dep, audio_coding_dep, webrtc_dep] + common_deps,
    link_with: extra_libs,
    include_directories: webrtc_inc,
    c_args: common_cflags,
    cpp_args: common_cxxflags,
    soversion: soversion,
    install: true
)

webrtc_audio_processing_dep = declare_dependency(
    link_with: libwebrtc_audio_processing,
    include_directories: webrtc_inc,
    version: meson.project_version()
)
