/*
 *  kis_clipboard.h - part of Krayon
 *
 *  SPDX-FileCopyrightText: 2004 Boudewijn Rempt <boud@valdyas.org>
 *  SPDX-FileCopyrightText: 2019 Dmitrii Utkin <loentar@gmail.com>
 *  SPDX-FileCopyrightText: 2022 L. E. Segovia <amy@amyspark.me>
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 */
#ifndef __KIS_CLIPBOARD_H_
#define __KIS_CLIPBOARD_H_

#include <QObject>
#include <QSize>

#include <KoColorProfile.h>
#include <kis_types.h>

#include <kritaui_export.h>

class QRect;
class QMimeData;
class KisTimeSpan;


/**
 * The Krita clipboard is a clipboard that can store paint devices
 * instead of just qimage's.
 */
class KRITAUI_EXPORT KisClipboard : public QObject
{

    Q_OBJECT
    Q_PROPERTY(bool clip READ hasClip NOTIFY clipChanged)

public:
    enum PasteBehaviour { PASTE_ASSUME_WEB = 0, PASTE_ASSUME_MONITOR, PASTE_ASK };

    KisClipboard();
    ~KisClipboard() override;

    static KisClipboard* instance();

    /**
     * Sets the clipboard to the contents of the specified paint device; also
     * set the system clipboard to a QImage representation of the specified
     * paint device.
     *
     * @param dev The paint device that will be stored on the clipboard
     * @param topLeft a hint about the place where the clip should be pasted by default
     */
    void setClip(KisPaintDeviceSP dev, const QPoint& topLeft);

    void setClip(KisPaintDeviceSP dev, const QPoint& topLeft, const KisTimeSpan &range);

    /**
     * Get the contents of the clipboard in the form of a paint device.
     */
    KisPaintDeviceSP clip(const QRect &imageBounds,
                          bool showPopup,
                          KisTimeSpan *clipRange = nullptr,
                          const KoColorProfile *destProfile = nullptr);

    bool hasClip() const;

    QSize clipSize() const;

    void setLayers(KisNodeList nodes, KisImageSP image, bool forceCopy = false);
    bool hasLayers() const;
    bool hasLayerStyles() const;

    const QMimeData* layersMimeData() const;

    QImage getPreview() const;

    bool hasUrls() const;

    /**
     * load an image from clipboard handling different supported formats
     * @return image
     */
    QImage getImageFromClipboard() const;

    KisPaintDeviceSP fetchImageByURL(const QUrl &originalUrl) const;

Q_SIGNALS:
    void clipCreated();
    void clipChanged();

private:
    bool m_hasClip;
    bool m_pushedClipboard;

private Q_SLOTS:
    void clipboardDataChanged();
};

#endif // __KIS_CLIPBOARD_H_
