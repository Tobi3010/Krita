/*
 *  SPDX-FileCopyrightText: 2009 Cyrille Berger <cberger@cberger.net>
 *  SPDX-FileCopyrightText: 2022 Dmitry Kazakov <dimula73@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 */
#include "KisRotationOption.h"

#include <kis_properties_configuration.h>
#include <kis_paint_information.h>
#include <KisStandardOptionData.h>
#include <kis_paintop.h>


KisRotationOption::KisRotationOption(const KisPropertiesConfiguration *setting)
    : KisCurveOption2(initializeFromData(setting))
{
}

qreal KisRotationOption::apply(const KisPaintInformation & info) const
{
    if (!isChecked()) return kisDegreesToRadians(info.canvasRotation());

    const bool absoluteAxesFlipped = info.canvasMirroredH() != info.canvasMirroredV();

    const qreal normalizedBaseAngle = -info.canvasRotation() / 360.0;

    // we should invert scaling part because it is expected
    // to rotate the brush counterclockwise
    const qreal scalingPartCoeff = -1.0;

    qreal value = computeRotationLikeValue(info, normalizedBaseAngle, absoluteAxesFlipped, scalingPartCoeff, info.isHoveringMode());

    /// flip to conform global legacy code
    /// we measure rotation in the opposite direction relative Qt's way
    value = 1.0 - value;

    return normalizeAngle(value * M_PI);
 }

void KisRotationOption::applyFanCornersInfo(KisPaintOp *op)
{
    if (!this->isChecked()) return;

    /**
     * A special case for the Drawing Angle sensor, because it
     * changes the behavior of KisPaintOp::paintLine()
     */
    op->setFanCornersInfo(m_fanCornersEnabled, m_fanCornersStep * M_PI / 180.0);
}

KisRotationOptionData KisRotationOption::initializeFromData(const KisPropertiesConfiguration *setting)
{
    KisRotationOptionData data;
    data.read(setting);

    if (data.sensorDrawingAngle.isActive) {
        m_fanCornersEnabled =
             data.sensorDrawingAngle.fanCornersEnabled &&
             !data.sensorDrawingAngle.lockedAngleMode;
        m_fanCornersStep = qreal(data.sensorDrawingAngle.fanCornersStep);
    }

    return data;
}
