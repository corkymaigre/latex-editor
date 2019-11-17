#ifndef MAINDIALOG_HPP
#define MAINDIALOG_HPP

#include <QDialog>
#include <QDir>
#include <QLineEdit>
#include <QMessageBox>
#include <QComboBox>
#include <QDoubleSpinBox>
#include "projecthandler.hpp"

namespace Ui {
class MainDialog;
}

class MainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MainDialog(QWidget *parent = 0);
    ~MainDialog();
    QString getName();
    QString getType();
    QString getFormat();
    QString getColumn();
    QString getSide();
    QString getFontSize();
    int getNumberOfChapters();
    bool getTableOfContents();
    bool getListOfFigures();
    bool getListOfTables();
    int getNumberOfAppendices();
    bool getBibliography();
    bool getState();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::MainDialog  *ui;
    ProjectHandler  *myProject;
    QLineEdit       *name;
    QComboBox       *type;
    QComboBox       *format;
    QComboBox       *column;
    QComboBox       *side;
    QDoubleSpinBox  *fontSize;
    QSpinBox        *numberOfChapters;
    QCheckBox       *tableOfContents;
    QCheckBox       *listOfFigures;
    QCheckBox       *listOfTables;
    QSpinBox        *numberOfAppendices;
    QCheckBox       *bibliography;
    bool            state;
};

#endif // MAINDIALOG_HPP
