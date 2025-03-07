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

#include "autogain_ui.hpp"

namespace {

auto reference_enum_to_int(GValue* value, GVariant* variant, gpointer user_data) -> gboolean {
  const auto* v = g_variant_get_string(variant, nullptr);

  if (g_strcmp0(v, "Momentary") == 0) {
    g_value_set_int(value, 0);
  } else if (g_strcmp0(v, "Shortterm") == 0) {
    g_value_set_int(value, 1);
  } else if (g_strcmp0(v, "Integrated") == 0) {
    g_value_set_int(value, 2);
  } else if (g_strcmp0(v, "Geometric Mean") == 0) {
    g_value_set_int(value, 3);
  }

  return 1;
}

auto int_to_reference_enum(const GValue* value, const GVariantType* expected_type, gpointer user_data) -> GVariant* {
  switch (g_value_get_int(value)) {
    case 0:
      return g_variant_new_string("Momentary");

    case 1:
      return g_variant_new_string("Shortterm");

    case 2:
      return g_variant_new_string("Integrated");

    default:
      return g_variant_new_string("Geometric Mean");
  }
}

}  // namespace

AutoGainUi::AutoGainUi(BaseObjectType* cobject,
                       const Glib::RefPtr<Gtk::Builder>& builder,
                       const std::string& schema,
                       const std::string& schema_path)
    : Gtk::Box(cobject), PluginUiBase(builder, schema, schema_path) {
  name = plugin_name::autogain;

  // loading builder widgets

  m_level = builder->get_widget<Gtk::LevelBar>("m_level");
  s_level = builder->get_widget<Gtk::LevelBar>("s_level");
  i_level = builder->get_widget<Gtk::LevelBar>("i_level");
  r_level = builder->get_widget<Gtk::LevelBar>("r_level");
  g_level = builder->get_widget<Gtk::LevelBar>("g_level");
  l_level = builder->get_widget<Gtk::LevelBar>("l_level");
  lra_level = builder->get_widget<Gtk::LevelBar>("lra_level");

  m_label = builder->get_widget<Gtk::Label>("m_label");
  s_label = builder->get_widget<Gtk::Label>("s_label");
  i_label = builder->get_widget<Gtk::Label>("i_label");
  r_label = builder->get_widget<Gtk::Label>("r_label");
  g_label = builder->get_widget<Gtk::Label>("g_label");
  l_label = builder->get_widget<Gtk::Label>("l_label");
  lra_label = builder->get_widget<Gtk::Label>("lra_label");

  reset_history = builder->get_widget<Gtk::Button>("reset");

  target = builder->get_widget<Gtk::SpinButton>("spinbutton_target");

  reference = builder->get_widget<Gtk::ComboBoxText>("reference");

  // gsettings bindings

  settings->bind("target", target->get_adjustment().get(), "value");

  g_settings_bind_with_mapping(settings->gobj(), "reference", reference->gobj(), "active", G_SETTINGS_BIND_DEFAULT,
                               reference_enum_to_int, int_to_reference_enum, nullptr, nullptr);

  // it is ugly but will ensure that third party tools are able to reset this plugin history

  reset_history->signal_clicked().connect(
      [=, this]() { settings->set_boolean("reset-history", !settings->get_boolean("reset-history")); });

  prepare_spinbutton(target, "dB");

  setup_input_output_gain(builder);
}

AutoGainUi::~AutoGainUi() {
  util::debug(name + " ui destroyed");
}

auto AutoGainUi::add_to_stack(Gtk::Stack* stack, const std::string& schema_path) -> AutoGainUi* {
  const auto& builder = Gtk::Builder::create_from_resource("/com/github/wwmm/easyeffects/ui/autogain.ui");

  auto* const ui = Gtk::Builder::get_widget_derived<AutoGainUi>(
      builder, "top_box", "com.github.wwmm.easyeffects.autogain", schema_path + "autogain/");

  stack->add(*ui, plugin_name::autogain);

  return ui;
}

void AutoGainUi::on_new_results(const double& loudness,
                                const double& gain,
                                const double& momentary,
                                const double& shortterm,
                                const double& integrated,
                                const double& relative,
                                const double& range) {
  l_level->set_value(util::db_to_linear(loudness));
  l_label->set_text(level_to_localized_string(loudness, 0));

  g_level->set_value(gain);
  g_label->set_text(level_to_localized_string(util::linear_to_db(gain), 0));

  m_level->set_value(util::db_to_linear(momentary));
  m_label->set_text(level_to_localized_string(momentary, 0));

  s_level->set_value(util::db_to_linear(shortterm));
  s_label->set_text(level_to_localized_string(shortterm, 0));

  i_level->set_value(util::db_to_linear(integrated));
  i_label->set_text(level_to_localized_string(integrated, 0));

  r_level->set_value(util::db_to_linear(relative));
  r_label->set_text(level_to_localized_string(relative, 0));

  lra_level->set_value(util::db_to_linear(range));
  lra_label->set_text(level_to_localized_string(range, 0));
}

void AutoGainUi::reset() {
  bypass->set_active(false);

  settings->reset("input-gain");

  settings->reset("output-gain");

  settings->reset("target");
}
