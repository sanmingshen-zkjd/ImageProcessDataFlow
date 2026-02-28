#pragma once

#include <QImage>
#include <QString>
#include <functional>

class ProcessingNode {
public:
    using Operation = std::function<QImage(const QImage&)>;

    ProcessingNode(QString name, Operation operation)
        : m_name(std::move(name)), m_operation(std::move(operation)) {}

    const QString& name() const { return m_name; }

    QImage process(const QImage& input) const {
        if (!m_operation) {
            return input;
        }
        return m_operation(input);
    }

private:
    QString m_name;
    Operation m_operation;
};
