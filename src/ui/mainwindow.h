#pragma once

#include "../core/noderegistry.h"

#include <QMainWindow>

class QListWidget;
class QGraphicsView;
class QPushButton;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);

private slots:
    void loadImage();
    void addNode();
    void removeNode();
    void runPipeline();

private:
    void buildUi();

    NodeRegistry m_registry;
    QImage m_sourceImage;

    QListWidget* m_nodeList{nullptr};
    QListWidget* m_pipelineList{nullptr};
    QGraphicsView* m_graphView{nullptr};
};
