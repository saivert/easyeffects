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

#include "equalizer_preset.hpp"

EqualizerPreset::EqualizerPreset()
    : input_settings_left(Gio::Settings::create("com.github.wwmm.easyeffects.equalizer.channel",
                                                "/com/github/wwmm/easyeffects/streaminputs/equalizer/leftchannel/")),
      input_settings_right(Gio::Settings::create("com.github.wwmm.easyeffects.equalizer.channel",
                                                 "/com/github/wwmm/easyeffects/streaminputs/equalizer/rightchannel/")),
      output_settings_left(Gio::Settings::create("com.github.wwmm.easyeffects.equalizer.channel",
                                                 "/com/github/wwmm/easyeffects/streamoutputs/equalizer/leftchannel/")),
      output_settings_right(
          Gio::Settings::create("com.github.wwmm.easyeffects.equalizer.channel",
                                "/com/github/wwmm/easyeffects/streamoutputs/equalizer/rightchannel/")) {
  input_settings = Gio::Settings::create("com.github.wwmm.easyeffects.equalizer",
                                         "/com/github/wwmm/easyeffects/streaminputs/equalizer/");

  output_settings = Gio::Settings::create("com.github.wwmm.easyeffects.equalizer",
                                          "/com/github/wwmm/easyeffects/streamoutputs/equalizer/");
}

void EqualizerPreset::save(nlohmann::json& json,
                           const std::string& section,
                           const Glib::RefPtr<Gio::Settings>& settings) {
  json[section]["equalizer"]["input-gain"] = settings->get_double("input-gain");

  json[section]["equalizer"]["output-gain"] = settings->get_double("output-gain");

  json[section]["equalizer"]["mode"] = settings->get_string("mode").c_str();

  json[section]["equalizer"]["split-channels"] = settings->get_boolean("split-channels");

  const auto& nbands = settings->get_int("num-bands");

  json[section]["equalizer"]["num-bands"] = nbands;

  if (section == "input") {
    save_channel(json[section]["equalizer"]["left"], input_settings_left, nbands);
    save_channel(json[section]["equalizer"]["right"], input_settings_right, nbands);
  } else if (section == "output") {
    save_channel(json[section]["equalizer"]["left"], output_settings_left, nbands);
    save_channel(json[section]["equalizer"]["right"], output_settings_right, nbands);
  }
}

void EqualizerPreset::save_channel(nlohmann::json& json,
                                   const Glib::RefPtr<Gio::Settings>& settings,
                                   const int& nbands) {
  for (int n = 0; n < nbands; n++) {
    const auto& bandn = "band" + std::to_string(n);

    json[bandn]["type"] = settings->get_string(bandn + "-type").c_str();

    json[bandn]["mode"] = settings->get_string(bandn + "-mode").c_str();

    json[bandn]["slope"] = settings->get_string(bandn + "-slope").c_str();

    json[bandn]["solo"] = settings->get_boolean(bandn + "-solo");

    json[bandn]["mute"] = settings->get_boolean(bandn + "-mute");

    json[bandn]["gain"] = settings->get_double(bandn + "-gain");

    json[bandn]["frequency"] = settings->get_double(bandn + "-frequency");

    json[bandn]["q"] = settings->get_double(bandn + "-q");
  }
}

void EqualizerPreset::load(const nlohmann::json& json,
                           const std::string& section,
                           const Glib::RefPtr<Gio::Settings>& settings) {
  update_key<double>(json.at(section).at("equalizer"), settings, "input-gain", "input-gain");

  update_key<double>(json.at(section).at("equalizer"), settings, "output-gain", "output-gain");

  update_string_key(json.at(section).at("equalizer"), settings, "mode", "mode");

  update_key<int>(json.at(section).at("equalizer"), settings, "num-bands", "num-bands");

  update_key<bool>(json.at(section).at("equalizer"), settings, "split-channels", "split-channels");

  const auto& nbands = settings->get_int("num-bands");

  if (section == "input") {
    load_channel(json.at(section).at("equalizer").at("left"), input_settings_left, nbands);
    load_channel(json.at(section).at("equalizer").at("right"), input_settings_right, nbands);
  } else if (section == "output") {
    load_channel(json.at(section).at("equalizer").at("left"), output_settings_left, nbands);
    load_channel(json.at(section).at("equalizer").at("right"), output_settings_right, nbands);
  }
}

void EqualizerPreset::load_channel(const nlohmann::json& json,
                                   const Glib::RefPtr<Gio::Settings>& settings,
                                   const int& nbands) {
  for (int n = 0; n < nbands; n++) {
    const auto& bandn = "band" + std::to_string(n);

    update_string_key(json.at(bandn), settings, bandn + "-type", "type");

    update_string_key(json.at(bandn), settings, bandn + "-mode", "mode");

    update_string_key(json.at(bandn), settings, bandn + "-slope", "slope");

    update_key<bool>(json.at(bandn), settings, bandn + "-solo", "solo");

    update_key<bool>(json.at(bandn), settings, bandn + "-mute", "mute");

    update_key<double>(json.at(bandn), settings, bandn + "-gain", "gain");

    update_key<double>(json.at(bandn), settings, bandn + "-frequency",
                       "frequency");

    update_key<double>(json.at(bandn), settings, bandn + "-q", "q");
  }
}
