#pragma once

#include <QGraphicsScene>
#include <QImage>
#include <QStringList>

class NodeGraphScene : public QGraphicsScene {
    Q_OBJECT
public:
    explicit NodeGraphScene(QObject* parent = nullptr);

    void setPipeline(const QStringList& pipeline);
    void setPreviewImage(const QImage& image);

private:
    void rebuild();

    QStringList m_pipeline;
    QImage m_preview;
};
