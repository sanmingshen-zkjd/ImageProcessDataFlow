#include "mainwindow.h"

#include "nodegraphscene.h"

#include <QFileDialog>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    buildUi();
    setWindowTitle("Image Processing DataFlow (Qt/C++)");
    resize(1100, 720);
}

void MainWindow::buildUi() {
    auto* central = new QWidget(this);
    auto* layout = new QHBoxLayout(central);

    auto* leftPanel = new QWidget(central);
    auto* leftLayout = new QVBoxLayout(leftPanel);

    auto* loadBtn = new QPushButton("Load Image", leftPanel);
    connect(loadBtn, &QPushButton::clicked, this, &MainWindow::loadImage);

    leftLayout->addWidget(loadBtn);
    leftLayout->addWidget(new QLabel("Available Nodes", leftPanel));

    m_nodeList = new QListWidget(leftPanel);
    m_nodeList->addItems(m_registry.nodeNames());
    leftLayout->addWidget(m_nodeList);

    auto* addBtn = new QPushButton("Add ->", leftPanel);
    connect(addBtn, &QPushButton::clicked, this, &MainWindow::addNode);
    leftLayout->addWidget(addBtn);

    leftLayout->addWidget(new QLabel("Pipeline", leftPanel));
    m_pipelineList = new QListWidget(leftPanel);
    leftLayout->addWidget(m_pipelineList);

    auto* removeBtn = new QPushButton("Remove", leftPanel);
    connect(removeBtn, &QPushButton::clicked, this, &MainWindow::removeNode);
    leftLayout->addWidget(removeBtn);

    auto* runBtn = new QPushButton("Run Pipeline", leftPanel);
    connect(runBtn, &QPushButton::clicked, this, &MainWindow::runPipeline);
    leftLayout->addWidget(runBtn);
    leftLayout->addStretch();

    m_graphView = new QGraphicsView(central);
    auto* scene = new NodeGraphScene(m_graphView);
    scene->setPipeline({"Input"});
    m_graphView->setScene(scene);

    layout->addWidget(leftPanel, 1);
    layout->addWidget(m_graphView, 3);

    setCentralWidget(central);
}

void MainWindow::loadImage() {
    const QString path = QFileDialog::getOpenFileName(this, "Select image", {}, "Images (*.png *.jpg *.jpeg *.bmp)");
    if (path.isEmpty()) {
        return;
    }

    m_sourceImage.load(path);
    if (m_sourceImage.isNull()) {
        QMessageBox::warning(this, "Load failed", "Could not read image file.");
        return;
    }

    runPipeline();
}

void MainWindow::addNode() {
    if (!m_nodeList->currentItem()) {
        return;
    }
    m_pipelineList->addItem(m_nodeList->currentItem()->text());
}

void MainWindow::removeNode() {
    delete m_pipelineList->takeItem(m_pipelineList->currentRow());
}

void MainWindow::runPipeline() {
    auto* scene = qobject_cast<NodeGraphScene*>(m_graphView->scene());
    if (!scene) {
        return;
    }

    QStringList pipeline{"Input"};
    QImage current = m_sourceImage;

    for (int i = 0; i < m_pipelineList->count(); ++i) {
        const QString nodeName = m_pipelineList->item(i)->text();
        pipeline << nodeName;
        current = m_registry.node(nodeName).process(current);
    }

    if (pipeline.size() == 1) {
        pipeline << "(No operation)";
    }

    scene->setPipeline(pipeline);
    scene->setPreviewImage(current);
}
