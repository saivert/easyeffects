easyeffects_sources = [
	'easyeffects.cpp',
	'application.cpp',
	'application_ui.cpp',
	'autogain.cpp',
	'autogain_preset.cpp',
	'autogain_ui.cpp',
	'bass_enhancer.cpp',
	'bass_enhancer_preset.cpp',
	'bass_enhancer_ui.cpp',
	'bass_loudness.cpp',
	'bass_loudness_preset.cpp',
	'bass_loudness_ui.cpp',
	'compressor.cpp',
	'compressor_preset.cpp',
	'compressor_ui.cpp',
	'convolver.cpp',
	'convolver_preset.cpp',
	'convolver_ui.cpp',
	'crossfeed.cpp',
	'crossfeed_preset.cpp',
	'crossfeed_ui.cpp',
	'crystalizer.cpp',
	'crystalizer_preset.cpp',
	'crystalizer_ui.cpp',
	'deesser.cpp',
	'deesser_preset.cpp',
	'deesser_ui.cpp',
	'delay.cpp',
	'delay_preset.cpp',
	'delay_ui.cpp',
	'echo_canceller.cpp',
	'echo_canceller_preset.cpp',
	'echo_canceller_ui.cpp',
	'effects_base_ui.cpp',
	'effects_base.cpp',
	'equalizer.cpp',
	'equalizer_preset.cpp',
	'equalizer_ui.cpp',
	'exciter.cpp',
	'exciter_preset.cpp',
	'exciter_ui.cpp',
	'filter.cpp',
	'filter_preset.cpp',
	'filter_ui.cpp',
	'fir_filter_bandpass.cpp',
	'fir_filter_base.cpp',
	'fir_filter_lowpass.cpp',
	'fir_filter_highpass.cpp',
	'gate.cpp',
	'gate_preset.cpp',
	'gate_ui.cpp',
	'general_settings_ui.cpp',
	'info_holders.cpp',
	'limiter.cpp',
	'limiter_preset.cpp',
	'limiter_ui.cpp',
	'loudness.cpp',
	'loudness_preset.cpp',
	'loudness_ui.cpp',
	'lv2_wrapper.cpp',
	'maximizer.cpp',
	'maximizer_preset.cpp',
	'maximizer_ui.cpp',
	'multiband_compressor.cpp',
	'multiband_compressor_preset.cpp',
	'multiband_compressor_ui.cpp',
	'multiband_gate.cpp',
	'multiband_gate_preset.cpp',
	'multiband_gate_ui.cpp',
	'output_level.cpp',
	'pipe_info_ui.cpp',
	'pipe_manager.cpp',
	'pitch.cpp',
	'pitch_preset.cpp',
	'pitch_ui.cpp',
	'plot.cpp',
	'plugin_base.cpp',
	'plugin_ui_base.cpp',
	'presets_menu_ui.cpp',
	'presets_manager.cpp',
	'reverb.cpp',
	'reverb_preset.cpp',
	'reverb_ui.cpp',
	'resampler.cpp',
	'rnnoise.cpp',
	'rnnoise_preset.cpp',
	'rnnoise_ui.cpp',
	'spectrum.cpp',
	'spectrum_ui.cpp',
	'spectrum_settings_ui.cpp',
	'stereo_tools.cpp',
	'stereo_tools_preset.cpp',
	'stereo_tools_ui.cpp',
	'stream_output_effects_ui.cpp',
	'stream_output_effects.cpp',
	'stream_input_effects_ui.cpp',
	'stream_input_effects.cpp',
	'test_signals.cpp',
	'util.cpp',
	gresources
]

cxx = meson.get_compiler('cpp')

zita_convolver = cxx.find_library('zita-convolver', required: true)

easyeffects_deps = [
	dependency('libpipewire-0.3', version: '>=0.3.31'),
	dependency('glib-2.0', version: '>=2.56'),
	dependency('glibmm-2.68', version: '>=2.68'),
	dependency('gtk4', version: '>=4.2.1'),
	dependency('gtkmm-4.0', version: '>=4.2.0'),
	dependency('sigc++-3.0', version: '>=3.0.6'),
	dependency('lilv-0', version: '>=0.22'),
	dependency('lv2', version: '>=1.18.2'),
	dependency('libbs2b'),
	dependency('sndfile'),
	dependency('fftw3f'),
	dependency('libebur128',version: '>=1.2.0'),
	dependency('rnnoise'),
	dependency('samplerate'),
	dependency('rubberband'),
	dependency('speexdsp'),
	dependency('nlohmann_json', required: true),
	dependency('threads'),
	zita_convolver,
]

executable(
	meson.project_name(),
	easyeffects_sources,
	include_directories : [include_dir,config_h_dir],
	dependencies : easyeffects_deps,
	install: true
)
