audio_coding_sources = [
  'codecs/isac/main/source/arith_routines.c',
  'codecs/isac/main/source/arith_routines_hist.c',
  'codecs/isac/main/source/arith_routines_logist.c',
  'codecs/isac/main/source/encode_lpc_swb.c',
  'codecs/isac/main/source/entropy_coding.c',
  'codecs/isac/main/source/filter_functions.c',
  'codecs/isac/main/source/filterbanks.c',
  'codecs/isac/main/source/filterbank_tables.c',
  'codecs/isac/main/source/intialize.c',
  'codecs/isac/main/source/lpc_analysis.c',
  'codecs/isac/main/source/lpc_gain_swb_tables.c',
  'codecs/isac/main/source/lpc_shape_swb12_tables.c',
  'codecs/isac/main/source/lpc_shape_swb16_tables.c',
  'codecs/isac/main/source/lpc_tables.c',
  'codecs/isac/main/source/pitch_estimator.c',
  'codecs/isac/main/source/pitch_filter.c',
  'codecs/isac/main/source/pitch_gain_tables.c',
  'codecs/isac/main/source/pitch_lag_tables.c',
  'codecs/isac/main/source/spectrum_ar_model_tables.c',
]

libaudio_coding = static_library('audio_coding',
    audio_coding_sources,
    dependencies: common_deps,
    include_directories: webrtc_inc,
    c_args: common_cflags,
    cpp_args: common_cxxflags
)

audio_coding_dep = declare_dependency(
    link_with: libaudio_coding
)
