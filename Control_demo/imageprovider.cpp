#include "imageprovider.h"



QPixmap ImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    Q_UNUSED(id);
    m_pixmap.scaled(requestedSize);
    if (size) *size = QSize(requestedSize);
    return m_pixmap;
}
