/*
 *  SPDX-FileCopyrightText: 2008, 2010 Lukáš Tvrdý <lukast.dev@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 */
#include <kis_curve_paintop_settings_widget.h>
#include <kis_properties_configuration.h>
#include <kis_curve_paintop_settings.h>

#include <KisPaintingModeOptionWidget.h>
#include <KisPaintOpOptionUtils.h>
#include "kis_curve_line_option.h"
#include <kis_curve_option_widget.h>
#include <kis_pressure_opacity_option.h>
#include <kis_linewidth_option.h>
#include "kis_curves_opacity_option.h"
#include <KisCompositeOpOptionWidget.h>

KisCurvePaintOpSettingsWidget:: KisCurvePaintOpSettingsWidget(QWidget* parent)
    : KisPaintOpSettingsWidget(parent)
{
    namespace kpou = KisPaintOpOptionUtils;

    addPaintOpOption(new KisCurveOpOption());
    addPaintOpOption(new KisCurveOptionWidget(new KisPressureOpacityOption(), i18n("Transparent"), i18n("Opaque")));
    addPaintOpOption(new KisCurveOptionWidget(new KisLineWidthOption(), i18n("0%"), i18n("100%")));
    addPaintOpOption(new KisCurveOptionWidget(new KisCurvesOpacityOption(), i18n("0%"), i18n("100%")));
    addPaintOpOption(kpou::createOptionWidget<KisCompositeOpOptionWidget>());
    addPaintOpOption(kpou::createOptionWidget<KisPaintingModeOptionWidget>());
}

KisCurvePaintOpSettingsWidget::~ KisCurvePaintOpSettingsWidget()
{
}


KisPropertiesConfigurationSP  KisCurvePaintOpSettingsWidget::configuration() const
{
    KisCurvePaintOpSettings* config = new KisCurvePaintOpSettings(resourcesInterface());
    config->setProperty("paintop", "curvebrush"); // XXX: make this a const id string
    writeConfiguration(config);
    return config;
}

