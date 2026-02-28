#pragma once

#include "processingnode.h"

#include <QMap>
#include <QStringList>

class NodeRegistry {
public:
    NodeRegistry();

    QStringList nodeNames() const;
    ProcessingNode node(const QString& name) const;

private:
    QMap<QString, ProcessingNode> m_nodes;
};
