
#ifndef GRADESTABLEMODEL_H
#define GRADESTABLEMODEL_H

#include <QAbstractTableModel>

#include "assignment.h"
#include "student.h"

class GradesTableModel : public QAbstractTableModel
{
    public:
        explicit GradesTableModel(QObject *parent = nullptr);
        GradesTableModel(Assignment* assignment, QObject* parent = nullptr);
        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        int columnCount(const QModelIndex& parent = QModelIndex()) const override;
        QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    private:
        Assignment *m_assignment;
        std::map<Student*, int> m_data;
};

#endif // GRADESTABLEMODEL_H
