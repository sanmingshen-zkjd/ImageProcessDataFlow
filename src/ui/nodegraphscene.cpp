#include "nodegraphscene.h"

#include <QBrush>
#include <QFont>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QPen>

NodeGraphScene::NodeGraphScene(QObject* parent) : QGraphicsScene(parent) {
    setBackgroundBrush(QColor("#1f1f1f"));
}

void NodeGraphScene::setPipeline(const QStringList& pipeline) {
    m_pipeline = pipeline;
    rebuild();
}

void NodeGraphScene::setPreviewImage(const QImage& image) {
    m_preview = image;
    rebuild();
}

void NodeGraphScene::rebuild() {
    clear();

    constexpr int nodeWidth = 160;
    constexpr int nodeHeight = 70;
    constexpr int spacing = 45;
    constexpr int y = 40;

    QPen linePen(QColor("#66c2ff"));
    linePen.setWidth(3);

    for (int i = 0; i < m_pipeline.size(); ++i) {
        const int x = 30 + i * (nodeWidth + spacing);

        auto* rect = addRect(x, y, nodeWidth, nodeHeight, QPen(QColor("#8f8f8f"), 2), QBrush(QColor("#2f2f2f")));
        rect->setZValue(1);

        auto* text = addText(m_pipeline.at(i), QFont("Sans", 10, QFont::Bold));
        text->setDefaultTextColor(Qt::white);
        text->setPos(x + 14, y + 22);
        text->setZValue(2);

        if (i < m_pipeline.size() - 1) {
            const int x1 = x + nodeWidth;
            const int x2 = x + nodeWidth + spacing;
            addLine(x1, y + nodeHeight / 2, x2, y + nodeHeight / 2, linePen);
        }
    }

    if (!m_preview.isNull()) {
        const QPixmap pixmap = QPixmap::fromImage(m_preview).scaled(260, 260, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        auto* preview = addPixmap(pixmap);
        preview->setPos(40, y + nodeHeight + 80);

        auto* label = addText("Pipeline Output", QFont("Sans", 10, QFont::DemiBold));
        label->setDefaultTextColor(QColor("#dddddd"));
        label->setPos(40, y + nodeHeight + 50);
    }

    setSceneRect(itemsBoundingRect().adjusted(-20, -20, 20, 20));
}
