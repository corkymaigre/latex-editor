#include "maindialog.hpp"
#include "ui_maindialog.h"



MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog)
{
    ui->setupUi(this);
    state = false;
    name = (QLineEdit*) ui->lineEdit;
    type = (QComboBox*) ui->comboBox_5;
    format = (QComboBox*) ui->comboBox;
    column = (QComboBox*) ui->comboBox_2;
    side = (QComboBox*) ui->comboBox_3;
    fontSize = (QDoubleSpinBox*) ui->doubleSpinBox;
    numberOfChapters = (QSpinBox*) ui->spinBox;
    tableOfContents = (QCheckBox*) ui->checkBox;
    listOfFigures = (QCheckBox*) ui->checkBox_2;
    listOfTables = (QCheckBox*) ui->checkBox_3;
    numberOfAppendices = (QSpinBox*) ui->spinBox_2;
    bibliography = (QCheckBox*) ui->checkBox_4;

}

MainDialog::~MainDialog()
{
    delete ui;
}

void MainDialog::on_buttonBox_accepted()
{
    if(name->text().isEmpty())
        QMessageBox::critical(
                    this,
                    "Error",
                    "No supported name for project, please try again.",
                    QMessageBox::Ok|QMessageBox::Close, QMessageBox::Ok);
    else
    {
        state = true;
        this->close();
    }
}

void MainDialog::on_buttonBox_rejected()
{
    state = false;
    this->close();
}

QString MainDialog::getName()
{
    return name->text();
}

QString MainDialog::getType()
{
    return type->currentText();
}

QString MainDialog::getFormat()
{
    return format->currentText();
}

QString MainDialog::getColumn()
{
    return column->currentText();
}

QString MainDialog::getSide()
{
    return side->currentText();
}

QString MainDialog::getFontSize()
{
    return fontSize->text();
}

int MainDialog::getNumberOfChapters()
{
    return numberOfChapters->text().toInt();
}

bool MainDialog::getTableOfContents()
{
    return tableOfContents->isChecked();
}

bool MainDialog::getListOfFigures()
{
    return listOfFigures->isChecked();
}

bool MainDialog::getListOfTables()
{
    return listOfTables->isChecked();
}

int MainDialog::getNumberOfAppendices()
{
    return numberOfAppendices->text().toInt();
}

bool MainDialog::getBibliography()
{
    return bibliography->isChecked();
}

bool MainDialog::getState()
{
    return state;
}


