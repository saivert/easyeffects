/*
 *  Copyright © 2017-2022 Wellington Wallace
 *
 *  This file is part of EasyEffects.
 *
 *  EasyEffects is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  EasyEffects is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with EasyEffects.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "equalizer_ui.hpp"

namespace {

auto bandtype_enum_to_int(GValue* value, GVariant* variant, gpointer user_data) -> gboolean {
  const auto* v = g_variant_get_string(variant, nullptr);

  if (g_strcmp0(v, "Off") == 0) {
    g_value_set_int(value, 0);
  } else if (g_strcmp0(v, "Bell") == 0) {
    g_value_set_int(value, 1);
  } else if (g_strcmp0(v, "Hi-pass") == 0) {
    g_value_set_int(value, 2);
  } else if (g_strcmp0(v, "Hi-shelf") == 0) {
    g_value_set_int(value, 3);
  } else if (g_strcmp0(v, "Lo-pass") == 0) {
    g_value_set_int(value, 4);
  } else if (g_strcmp0(v, "Lo-shelf") == 0) {
    g_value_set_int(value, 5);
  } else if (g_strcmp0(v, "Notch") == 0) {
    g_value_set_int(value, 6);
  } else if (g_strcmp0(v, "Resonance") == 0) {
    g_value_set_int(value, 7);
  } else if (g_strcmp0(v, "Allpass") == 0) {
    g_value_set_int(value, 8);
  }

  return 1;
}

auto int_to_bandtype_enum(const GValue* value, const GVariantType* expected_type, gpointer user_data) -> GVariant* {
  switch (g_value_get_int(value)) {
    case 0:
      return g_variant_new_string("Off");

    case 1:
      return g_variant_new_string("Bell");

    case 2:
      return g_variant_new_string("Hi-pass");

    case 3:
      return g_variant_new_string("Hi-shelf");

    case 4:
      return g_variant_new_string("Lo-pass");

    case 5:
      return g_variant_new_string("Lo-shelf");

    case 6:
      return g_variant_new_string("Notch");

    case 7:
      return g_variant_new_string("Resonance");

    case 8:
      return g_variant_new_string("Allpass");

    default:
      return g_variant_new_string("Bell");
  }
}

auto mode_enum_to_int(GValue* value, GVariant* variant, gpointer user_data) -> gboolean {
  const auto* v = g_variant_get_string(variant, nullptr);

  if (g_strcmp0(v, "IIR") == 0) {
    g_value_set_int(value, 0);
  } else if (g_strcmp0(v, "FIR") == 0) {
    g_value_set_int(value, 1);
  } else if (g_strcmp0(v, "FFT") == 0) {
    g_value_set_int(value, 2);
  } else if (g_strcmp0(v, "SPM") == 0) {
    g_value_set_int(value, 3);
  }

  return 1;
}

auto int_to_mode_enum(const GValue* value, const GVariantType* expected_type, gpointer user_data) -> GVariant* {
  switch (g_value_get_int(value)) {
    case 0:
      return g_variant_new_string("IIR");

    case 1:
      return g_variant_new_string("FIR");

    case 2:
      return g_variant_new_string("FFT");

    case 3:
      return g_variant_new_string("SPM");

    default:
      return g_variant_new_string("IIR");
  }
}

auto bandmode_enum_to_int(GValue* value, GVariant* variant, gpointer user_data) -> gboolean {
  const auto* v = g_variant_get_string(variant, nullptr);

  if (g_strcmp0(v, "RLC (BT)") == 0) {
    g_value_set_int(value, 0);
  } else if (g_strcmp0(v, "RLC (MT)") == 0) {
    g_value_set_int(value, 1);
  } else if (g_strcmp0(v, "BWC (BT)") == 0) {
    g_value_set_int(value, 2);
  } else if (g_strcmp0(v, "BWC (MT)") == 0) {
    g_value_set_int(value, 3);
  } else if (g_strcmp0(v, "LRX (BT)") == 0) {
    g_value_set_int(value, 4);
  } else if (g_strcmp0(v, "LRX (MT)") == 0) {
    g_value_set_int(value, 5);
  } else if (g_strcmp0(v, "APO (DR)") == 0) {
    g_value_set_int(value, 6);
  }

  return 1;
}

auto int_to_bandmode_enum(const GValue* value, const GVariantType* expected_type, gpointer user_data) -> GVariant* {
  switch (g_value_get_int(value)) {
    case 0:
      return g_variant_new_string("RLC (BT)");

    case 1:
      return g_variant_new_string("RLC (MT)");

    case 2:
      return g_variant_new_string("BWC (BT)");

    case 3:
      return g_variant_new_string("BWC (MT)");

    case 4:
      return g_variant_new_string("LRX (BT)");

    case 5:
      return g_variant_new_string("LRX (MT)");

    case 6:
      return g_variant_new_string("APO (DR)");

    default:
      return g_variant_new_string("RLC (BT)");
  }
}

auto bandslope_enum_to_int(GValue* value, GVariant* variant, gpointer user_data) -> gboolean {
  const auto* v = g_variant_get_string(variant, nullptr);

  if (g_strcmp0(v, "x1") == 0) {
    g_value_set_int(value, 0);
  } else if (g_strcmp0(v, "x2") == 0) {
    g_value_set_int(value, 1);
  } else if (g_strcmp0(v, "x3") == 0) {
    g_value_set_int(value, 2);
  } else if (g_strcmp0(v, "x4") == 0) {
    g_value_set_int(value, 3);
  }

  return 1;
}

auto int_to_bandslope_enum(const GValue* value, const GVariantType* expected_type, gpointer user_data) -> GVariant* {
  switch (g_value_get_int(value)) {
    case 0:
      return g_variant_new_string("x1");

    case 1:
      return g_variant_new_string("x2");

    case 2:
      return g_variant_new_string("x3");

    case 3:
      return g_variant_new_string("x4");

    default:
      return g_variant_new_string("x1");
  }
}

}  // namespace

EqualizerUi::EqualizerUi(BaseObjectType* cobject,
                         const Glib::RefPtr<Gtk::Builder>& builder,
                         const std::string& schema,
                         const std::string& schema_path,
                         const std::string& schema_channel,
                         const std::string& schema_channel_left_path,
                         const std::string& schema_channel_right_path)
    : Gtk::Box(cobject),
      PluginUiBase(builder, schema, schema_path),
      settings_left(Gio::Settings::create(schema_channel, schema_channel_left_path)),
      settings_right(Gio::Settings::create(schema_channel, schema_channel_right_path)) {
  name = plugin_name::equalizer;

  // loading builder widgets

  bands_box_left = builder->get_widget<Gtk::Box>("bands_box_left");
  bands_box_right = builder->get_widget<Gtk::Box>("bands_box_right");

  flat_response = builder->get_widget<Gtk::Button>("flat_response");
  calculate_freqs = builder->get_widget<Gtk::Button>("calculate_freqs");
  import_apo = builder->get_widget<Gtk::Button>("import_apo");

  split_channels = builder->get_widget<Gtk::ToggleButton>("split_channels");

  stack = builder->get_widget<Gtk::Stack>("stack");
  stack_switcher = builder->get_widget<Gtk::StackSwitcher>("stack_switcher");

  mode = builder->get_widget<Gtk::ComboBoxText>("mode");

  nbands = builder->get_widget<Gtk::SpinButton>("nbands");

  // signals connections

  nbands->signal_value_changed().connect(sigc::mem_fun(*this, &EqualizerUi::on_nbands_changed));

  // reset equalizer
  reset_button->signal_clicked().connect(sigc::mem_fun(*this, &EqualizerUi::reset));

  flat_response->signal_clicked().connect(sigc::mem_fun(*this, &EqualizerUi::on_flat_response));

  calculate_freqs->signal_clicked().connect(sigc::mem_fun(*this, &EqualizerUi::on_calculate_frequencies));

  import_apo->signal_clicked().connect(sigc::mem_fun(*this, &EqualizerUi::on_import_apo_preset_clicked));

  connections.push_back(settings->signal_changed("split-channels").connect([=, this](const auto& sc) {
    stack->set_visible_child("page_left_channel");

    on_nbands_changed();
  }));

  // gsettings bindings

  settings->bind("num-bands", nbands->get_adjustment().get(), "value");
  settings->bind("split-channels", split_channels, "active");
  settings->bind("split-channels", stack_switcher, "visible", Gio::Settings::BindFlags::GET);

  g_settings_bind_with_mapping(settings->gobj(), "mode", mode->gobj(), "active", G_SETTINGS_BIND_DEFAULT,
                               mode_enum_to_int, int_to_mode_enum, nullptr, nullptr);

  setup_input_output_gain(builder);

  // explicitly invoke the method to build equalizer bands (fixes #843)
  // if the preset num-bands value is equal to the default schema value
  // otherwise it's automatically invoked at startup by the functor on signal_value_changed

  Glib::Variant<gint32> default_nbands;

  settings->get_default_value("num-bands", default_nbands);

  if (default_nbands.get() == settings->get_int("num-bands")) {
    on_nbands_changed();
  }
}

EqualizerUi::~EqualizerUi() {
  for (auto& c : connections_bands) {
    c.disconnect();
  }

  util::debug(name + " ui destroyed");
}

auto EqualizerUi::add_to_stack(Gtk::Stack* stack, const std::string& schema_path) -> EqualizerUi* {
  const auto& builder = Gtk::Builder::create_from_resource("/com/github/wwmm/easyeffects/ui/equalizer.ui");

  auto* const ui = Gtk::Builder::get_widget_derived<EqualizerUi>(
      builder, "top_box", "com.github.wwmm.easyeffects.equalizer", schema_path + "equalizer/",
      "com.github.wwmm.easyeffects.equalizer.channel", schema_path + "equalizer/leftchannel/",
      schema_path + "equalizer/rightchannel/");

  stack->add(*ui, plugin_name::equalizer);

  return ui;
}

void EqualizerUi::on_nbands_changed() {
  for (auto& c : connections_bands) {
    c.disconnect();
  }

  for (auto* child = bands_box_left->get_last_child(); child != nullptr; child = bands_box_left->get_last_child()) {
    bands_box_left->remove(*child);
  }

  for (auto* child = bands_box_right->get_last_child(); child != nullptr; child = bands_box_right->get_last_child()) {
    bands_box_right->remove(*child);
  }

  connections_bands.clear();

  const auto& split = settings->get_boolean("split-channels");

  const auto& nb = static_cast<int>(nbands->get_value());

  build_bands(bands_box_left, settings_left, nb, split);

  if (split) {
    build_bands(bands_box_right, settings_right, nb, split);
  }
}

void EqualizerUi::build_bands(Gtk::Box* bands_box,
                              const Glib::RefPtr<Gio::Settings>& cfg,
                              const int& nbands,
                              const bool& split_mode) {
  for (int n = 0; n < nbands; n++) {
    const auto& bandn = "band" + std::to_string(n);

    const auto& builder = Gtk::Builder::create_from_resource("/com/github/wwmm/easyeffects/ui/equalizer_band.ui");

    auto* band_box = builder->get_widget<Gtk::Box>("band_box");

    auto* band_type = builder->get_widget<Gtk::ComboBoxText>("band_type");
    auto* band_mode = builder->get_widget<Gtk::ComboBoxText>("band_mode");
    auto* band_slope = builder->get_widget<Gtk::ComboBoxText>("band_slope");

    auto* band_width = builder->get_widget<Gtk::Label>("band_width");
    auto* band_label = builder->get_widget<Gtk::Label>("band_label");
    auto* band_quality_label = builder->get_widget<Gtk::Label>("band_quality_label");

    auto* reset_frequency = builder->get_widget<Gtk::Button>("reset_frequency");
    auto* reset_quality = builder->get_widget<Gtk::Button>("reset_quality");

    auto* band_solo = builder->get_widget<Gtk::ToggleButton>("band_solo");
    auto* band_mute = builder->get_widget<Gtk::ToggleButton>("band_mute");

    auto* band_scale = builder->get_widget<Gtk::Scale>("band_scale");

    auto* band_frequency = builder->get_widget<Gtk::SpinButton>("band_frequency");
    auto* band_quality = builder->get_widget<Gtk::SpinButton>("band_quality");

    prepare_scale(band_scale, "");

    prepare_spinbutton(band_frequency, "Hz");
    prepare_spinbutton(band_quality, "");

    auto update_quality_width = [=, this]() {
      const auto& q = band_quality->get_value();

      band_quality_label->set_text("Q " + level_to_localized_string(q, 2));

      if (q > 0.0) {
        band_width->set_text(level_to_localized_string(band_frequency->get_value() / q, 1) + " Hz");
      } else {
        band_width->set_text(_("infinity"));
      }
    };

    auto update_band_label = [=, this]() {
      if (const auto& f = band_frequency->get_value(); f > 1000.0) {
        band_label->set_text(level_to_localized_string(f / 1000.0, 1) + " kHz");
      } else {
        band_label->set_text(level_to_localized_string(f, 0) + " Hz");
      }
    };

    // connections

    connections_bands.push_back(band_frequency->signal_value_changed().connect(update_quality_width));

    connections_bands.push_back(band_frequency->signal_value_changed().connect(update_band_label));

    connections_bands.push_back(band_quality->signal_value_changed().connect(update_quality_width));

    if (split_mode) {
      // split channels mode

      connections_bands.push_back(
          reset_frequency->signal_clicked().connect([=]() { cfg->reset(bandn + "-frequency"); }));

      connections_bands.push_back(reset_quality->signal_clicked().connect([=]() { cfg->reset(bandn + "-q"); }));
    } else {
      // unified mode

      /* Right channel
         We need the bindgins below for the right channel equalizer to be updated.
         They have to be done before the bindings for the left channel.
       */

      connections_bands.push_back(band_scale->signal_value_changed().connect(
          [=, this]() { settings_right->set_double(bandn + "-gain", band_scale->get_value()); }));

      connections_bands.push_back(band_frequency->signal_value_changed().connect(
          [=, this]() { settings_right->set_double(bandn + "-frequency", band_frequency->get_value()); }));

      connections_bands.push_back(band_quality->signal_value_changed().connect(
          [=, this]() { settings_right->set_double(bandn + "-q", band_quality->get_value()); }));

      connections_bands.push_back(band_type->signal_changed().connect(
          [=, this]() { settings_right->set_enum(bandn + "-type", band_type->get_active_row_number()); }));

      connections_bands.push_back(band_mode->signal_changed().connect(
          [=, this]() { settings_right->set_enum(bandn + "-mode", band_mode->get_active_row_number()); }));

      connections_bands.push_back(band_slope->signal_changed().connect(
          [=, this]() { settings_right->set_enum(bandn + "-slope", band_slope->get_active_row_number()); }));

      connections_bands.push_back(band_solo->signal_toggled().connect(
          [=, this]() { settings_right->set_boolean(bandn + "-solo", band_solo->get_active()); }));

      connections_bands.push_back(band_mute->signal_toggled().connect(
          [=, this]() { settings_right->set_boolean(bandn + "-mute", band_mute->get_active()); }));

      // Left channel

      connections_bands.push_back(reset_frequency->signal_clicked().connect([=, this]() {
        settings_left->reset(bandn + "-frequency");

        settings_right->reset(bandn + "-frequency");
      }));

      connections_bands.push_back(reset_quality->signal_clicked().connect([=, this]() {
        settings_left->reset(bandn + "-q");

        settings_right->reset(bandn + "-q");
      }));
    }

    connections_bands.push_back(band_type->signal_changed().connect([=]() {
      // disable gain scale if type is "Off", "Hi-pass" or "Lo-pass"

      const auto& row = band_type->get_active_row_number();

      band_scale->set_sensitive((row == 0 || row == 2 || row == 4) ? false : true);
    }));

    cfg->bind(bandn + "-gain", band_scale->get_adjustment().get(), "value");
    cfg->bind(bandn + "-frequency", band_frequency->get_adjustment().get(), "value");
    cfg->bind(bandn + "-q", band_quality->get_adjustment().get(), "value");
    cfg->bind(bandn + "-solo", band_solo, "active");
    cfg->bind(bandn + "-mute", band_mute, "active");

    g_settings_bind_with_mapping(cfg->gobj(), std::string(bandn + "-type").c_str(), band_type->gobj(), "active",
                                 G_SETTINGS_BIND_DEFAULT, bandtype_enum_to_int, int_to_bandtype_enum, nullptr, nullptr);

    g_settings_bind_with_mapping(cfg->gobj(), std::string(bandn + "-mode").c_str(), band_mode->gobj(), "active",
                                 G_SETTINGS_BIND_DEFAULT, bandmode_enum_to_int, int_to_bandmode_enum, nullptr, nullptr);

    g_settings_bind_with_mapping(cfg->gobj(), std::string(bandn + "-slope").c_str(), band_slope->gobj(), "active",
                                 G_SETTINGS_BIND_DEFAULT, bandslope_enum_to_int, int_to_bandslope_enum, nullptr,
                                 nullptr);

    bands_box->append(*band_box);
  }

  bands_box->show();
}

void EqualizerUi::on_flat_response() {
  for (int n = 0; n < max_bands; n++) {
    const auto& bandn = "band" + std::to_string(n);

    // left channel

    settings_left->reset(bandn + "-gain");

    // right channel

    settings_right->reset(bandn + "-gain");
  }
}

void EqualizerUi::on_calculate_frequencies() {
  static const double min_freq = 20.0;
  static const double max_freq = 20000.0;

  double freq0 = min_freq;
  double freq1 = 0.0;

  const auto& nbands = settings->get_int("num-bands");

  // code taken from gstreamer equalizer sources: gstiirequalizer.c
  // function: gst_iir_equalizer_compute_frequencies

  const double step = std::pow(max_freq / min_freq, 1.0 / static_cast<double>(nbands));

  auto config_band = [&](const auto& cfg, const auto& n, const auto& freq, const auto& q) {
    const auto& bandn = "band" + std::to_string(n);

    cfg->set_double(bandn + "-frequency", freq);

    cfg->set_double(bandn + "-q", q);
  };

  for (int n = 0; n < nbands; n++) {
    freq1 = freq0 * step;

    const double freq = freq0 + 0.5 * (freq1 - freq0);
    const double width = freq1 - freq0;
    const double q = freq / width;

    // std::cout << n << "\t" << freq << "\t" << width << std::endl;

    config_band(settings_left, n, freq, q);
    config_band(settings_right, n, freq, q);

    freq0 = freq1;
  }
}

void EqualizerUi::reset() {
  bypass->set_active(false);

  settings->reset("input-gain");

  settings->reset("output-gain");

  settings->reset("mode");
  settings->reset("num-bands");
  settings->reset("split-channels");

  for (int n = 0; n < max_bands; n++) {
    const auto& bandn = "band" + std::to_string(n);

    // left channel

    settings_left->reset(bandn + "-gain");
    settings_left->reset(bandn + "-frequency");
    settings_left->reset(bandn + "-q");
    settings_left->reset(bandn + "-type");
    settings_left->reset(bandn + "-mode");
    settings_left->reset(bandn + "-slope");
    settings_left->reset(bandn + "-solo");
    settings_left->reset(bandn + "-mute");

    // right channel

    settings_right->reset(bandn + "-gain");
    settings_right->reset(bandn + "-frequency");
    settings_right->reset(bandn + "-q");
    settings_right->reset(bandn + "-type");
    settings_right->reset(bandn + "-mode");
    settings_right->reset(bandn + "-slope");
    settings_right->reset(bandn + "-solo");
    settings_right->reset(bandn + "-mute");
  }
}

void EqualizerUi::on_import_apo_preset_clicked() {
  Glib::RefPtr<Gtk::FileChooserNative> dialog;

  if (transient_window != nullptr) {
    dialog = Gtk::FileChooserNative::create(_("Import APO Preset File"), *transient_window,
                                            Gtk::FileChooser::Action::OPEN, _("Open"), _("Cancel"));
  } else {
    dialog = Gtk::FileChooserNative::create(_("Import APO Preset File"), Gtk::FileChooser::Action::OPEN, _("Open"),
                                            _("Cancel"));
  }

  auto dialog_filter = Gtk::FileFilter::create();

  dialog_filter->set_name(_("APO Presets"));
  dialog_filter->add_pattern("*.txt");

  dialog->add_filter(dialog_filter);

  dialog->signal_response().connect([=, this](const auto& response_id) {
    switch (response_id) {
      case Gtk::ResponseType::ACCEPT: {
        import_apo_preset(dialog->get_file()->get_path());

        break;
      }
      default:
        break;
    }
  });

  dialog->set_modal(true);
  dialog->show();
}

// returns false if we cannot parse given line successfully
bool EqualizerUi::parse_apo_preamp(const std::string& line, double& preamp) {
  std::smatch matches;

  static const auto i = std::regex::icase;

  std::regex_search(line, matches, std::regex(R"(preamp:\s*+([+-]?+\d++\.?+\d*+)\s*+db)", i));

  if (matches.size() != 2U) {
    return false;
  }

  preamp = std::stod(matches.str(1));
  return true;
}

// returns false if we cannot parse given line successfully

auto EqualizerUi::parse_apo_filter(const std::string& line, struct ImportedBand& filter) -> bool {
  std::smatch matches;

  static const auto i = std::regex::icase;

  // get filter type

  std::regex_search(line, matches, std::regex(R"(filter\s++\d*+:\s*+on\s++([a-z]++))", i));

  if (matches.size() != 2U) {
    return false;
  }

  try {
    filter.type = EqualizerUi::FilterTypeMap.at(matches.str(1));
  } catch (...) {
    return false;
  }

  // get center frequency

  std::regex_search(line, matches, std::regex(R"(fc\s++(\d++\.?+\d*+)\s*+hz)", i));

  if (matches.size() != 2U) {
    return false;
  }

  filter.freq = std::stof(matches.str(1));

  // get slope

  if ((filter.type & (LOW_SHELF_xdB | HIGH_SHELF_xdB | LOW_SHELF | HIGH_SHELF)) != 0U) {
    std::regex_search(line, matches,
                      std::regex(R"(filter\s++\d*+:\s*+on\s++[a-z]++\s++([+-]?+\d++\.?+\d*+)\s*+db)", i));

    // _xdB variants require the dB parameter

    if (((filter.type & (LOW_SHELF_xdB | HIGH_SHELF_xdB)) != 0U) && (matches.size() != 2U)) {
      return false;
    }

    if (matches.size() == 2U) {
      // we satisfied the condition, now assign the paramater if given

      filter.slope_dB = std::stof(matches.str(1));
    }
  }

  // get gain

  if ((filter.type & (PEAKING | LOW_SHELF_xdB | HIGH_SHELF_xdB | LOW_SHELF | HIGH_SHELF)) != 0U) {
    std::regex_search(line, matches, std::regex(R"(gain\s++([+-]?+\d++\.?+\d*+)\s*+db)", i));

    // all Shelf types (i.e. all above except for Peaking) require the gain parameter

    if (((filter.type & PEAKING) == 0U) && (matches.size() != 2U)) {
      return false;
    }

    if (matches.size() == 2U) {
      filter.gain = std::stof(matches.str(1));
    }
  }

  // get quality factor
  if ((filter.type & (PEAKING | LOW_PASS_Q | HIGH_PASS_Q | LOW_SHELF_xdB | HIGH_SHELF_xdB | NOTCH | ALL_PASS)) != 0U) {
    std::regex_search(line, matches, std::regex(R"(q\s++(\d++\.?+\d*+))", i));

    // Peaking and All-Pass filter types require the quality factor parameter

    if (((filter.type & (PEAKING | ALL_PASS)) != 0U) && (matches.size() != 2U)) {
      return false;
    }

    if (matches.size() == 2U) {
      filter.quality_factor = std::stof(matches.str(1));
    }
  }

  return true;
}

void EqualizerUi::import_apo_preset(const std::string& file_path) {
  std::filesystem::path p{file_path};

  if (std::filesystem::is_regular_file(p)) {
    std::ifstream eq_file;
    std::vector<struct ImportedBand> bands;
    double preamp = 0.0;

    eq_file.open(p.c_str());

    if (eq_file.is_open()) {
      std::string line;

      while (getline(eq_file, line)) {
        struct ImportedBand filter {};

        if (!parse_apo_preamp(line, preamp)) {
          if (parse_apo_filter(line, filter)) {
            bands.push_back(filter);
          }
        }
      }
    }

    eq_file.close();

    if (bands.empty()) {
      return;
    }

    settings->set_int("num-bands", bands.size());
    settings->set_double("input-gain", preamp);

    for (int n = 0; n < max_bands; n++) {
      const auto& bandn = "band" + std::to_string(n);

      if (n < static_cast<int>(bands.size())) {
        settings_left->set_string(bandn + "-mode", "APO (DR)");

        if (!settings->get_boolean("split-channels")) {
          settings_left->set_string(bandn + "-type", "Bell");
          settings_left->set_double(bandn + "-gain", bands[n].gain);
          settings_left->set_double(bandn + "-frequency", bands[n].freq);
          settings_left->set_double(bandn + "-q", bands[n].quality_factor);

          settings_right->set_string(bandn + "-type", "Bell");
          settings_right->set_double(bandn + "-gain", bands[n].gain);
          settings_right->set_double(bandn + "-frequency", bands[n].freq);
          settings_right->set_double(bandn + "-q", bands[n].quality_factor);
        } else {
          if (stack->get_visible_child_name() == "page_left_channel") {
            settings_left->set_string(bandn + "-type", "Bell");
            settings_left->set_double(bandn + "-gain", bands[n].gain);
            settings_left->set_double(bandn + "-frequency", bands[n].freq);
            settings_left->set_double(bandn + "-q", bands[n].quality_factor);
          } else {
            settings_right->set_string(bandn + "-type", "Bell");
            settings_right->set_double(bandn + "-gain", bands[n].gain);
            settings_right->set_double(bandn + "-frequency", bands[n].freq);
            settings_right->set_double(bandn + "-q", bands[n].quality_factor);
          }
        }
      } else {
        settings_left->set_string(bandn + "-type", "Off");

        settings_right->set_string(bandn + "-type", "Off");
      }
    }
  }
}
