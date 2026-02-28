#include "noderegistry.h"

#include <QColor>

namespace {
QImage toGray(const QImage& input) {
    if (input.isNull()) {
        return input;
    }

    QImage output = input.convertToFormat(QImage::Format_ARGB32);
    for (int y = 0; y < output.height(); ++y) {
        QRgb* row = reinterpret_cast<QRgb*>(output.scanLine(y));
        for (int x = 0; x < output.width(); ++x) {
            const QColor color = QColor::fromRgba(row[x]);
            const int gray = qGray(color.rgb());
            row[x] = qRgba(gray, gray, gray, color.alpha());
        }
    }
    return output;
}

QImage invert(const QImage& input) {
    if (input.isNull()) {
        return input;
    }

    QImage output = input.convertToFormat(QImage::Format_ARGB32);
    output.invertPixels(QImage::InvertRgba);
    return output;
}

QImage blur3x3(const QImage& input) {
    if (input.isNull()) {
        return input;
    }

    const QImage src = input.convertToFormat(QImage::Format_ARGB32);
    QImage output(src.size(), QImage::Format_ARGB32);

    auto clamp = [](int value, int min, int max) {
        return value < min ? min : (value > max ? max : value);
    };

    for (int y = 0; y < src.height(); ++y) {
        for (int x = 0; x < src.width(); ++x) {
            int red = 0;
            int green = 0;
            int blue = 0;
            int alpha = 0;
            int count = 0;

            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    const int sx = clamp(x + dx, 0, src.width() - 1);
                    const int sy = clamp(y + dy, 0, src.height() - 1);
                    const QColor pixel = QColor::fromRgba(src.pixel(sx, sy));
                    red += pixel.red();
                    green += pixel.green();
                    blue += pixel.blue();
                    alpha += pixel.alpha();
                    ++count;
                }
            }

            output.setPixelColor(x, y, QColor(red / count, green / count, blue / count, alpha / count));
        }
    }

    return output;
}
} // namespace

NodeRegistry::NodeRegistry() {
    m_nodes.insert("Grayscale", ProcessingNode("Grayscale", toGray));
    m_nodes.insert("Invert", ProcessingNode("Invert", invert));
    m_nodes.insert("Blur3x3", ProcessingNode("Blur3x3", blur3x3));
}

QStringList NodeRegistry::nodeNames() const {
    return m_nodes.keys();
}

ProcessingNode NodeRegistry::node(const QString& name) const {
    return m_nodes.value(name, ProcessingNode("Identity", [](const QImage& input) { return input; }));
}
