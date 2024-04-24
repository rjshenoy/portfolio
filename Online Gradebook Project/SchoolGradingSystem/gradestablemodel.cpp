
#include "gradestablemodel.h"

GradesTableModel::GradesTableModel(QObject *parent)
    : QAbstractTableModel{parent}
{

}

GradesTableModel::GradesTableModel(Assignment* assignment, QObject* parent)
    : QAbstractTableModel(parent),
    m_assignment(assignment)
{
    m_data = m_assignment->getAllScores();
}

int GradesTableModel::rowCount(const QModelIndex& parent) const {
    return m_data.size();
}

int GradesTableModel::columnCount(const QModelIndex& parent) const {
    return 2;
}

QVariant GradesTableModel::data(const QModelIndex& index, int role) const {
    if (role == Qt::DisplayRole) {
        if (index.column() == 0) {
            auto it = std::next(m_data.begin(), index.row());
            return QString::fromStdString(it->first->getName());
        } else if (index.column() == 1) {
            auto it = std::next(m_data.begin(), index.row());
            return it->second;
        }
    }
    return QVariant();
}

QVariant GradesTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            if (section == 0) {
                return tr("Student Name");
            } else if (section == 1) {
                return tr("Score");
            }
        }
    }
    return QVariant();
}
