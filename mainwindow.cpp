#include "mainwindow.hpp"
#include "projecthandler.hpp"
#include "ui_mainwindow.h"
#include "Constants.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    titlepageText = (QTextEdit*) ui->textEdit;
    packageText = (QTextEdit*) ui->textEdit_2;
    commandText = (QTextEdit*) ui->textEdit_3;
    contentText = (QTextEdit*) ui->textEdit_4;


    titlepageHighlighter = new TexHighlighter(this);
    packageHighlighter = new TexHighlighter(this);
    commandHighlighter = new TexHighlighter(this);
    contentHighlighter = new TexHighlighter(this);

    titlepageHighlighter->setDocument(ui->textEdit->document());
    packageHighlighter->setDocument(ui->textEdit_2->document());
    commandHighlighter->setDocument(ui->textEdit_3->document());
    contentHighlighter->setDocument(ui->textEdit_4->document());

    ui->textEdit->document()->setDefaultFont(QFont(FONT));
    ui->textEdit->setFontPointSize(qreal(9));
    ui->textEdit_2->document()->setDefaultFont(QFont(FONT));
    ui->textEdit_2->setFontPointSize(qreal(9));
    ui->textEdit_3->document()->setDefaultFont(QFont(FONT));
    ui->textEdit_3->setFontPointSize(qreal(9));
    ui->textEdit_4->document()->setDefaultFont(QFont(FONT));
    ui->textEdit_4->setFontPointSize(qreal(9));



    mainDialog = new MainDialog(this);


    QObject::connect(mainDialog, SIGNAL(finished(int)), this, SLOT(create_project()));
    QObject::connect(this, SIGNAL(handledProject()), this, SLOT(load_project()));
}


MainWindow::~MainWindow()
{
   delete ui;
}

void MainWindow::on_actionNew_File_triggered()
{
    mainDialog->exec();
    mainDialog->setModal(true);
}

void MainWindow::create_project()
{
    if(mainDialog->getState())
    {
        myProject = new ProjectHandler(
                mainDialog->getName(),
                mainDialog->getType(),
                mainDialog->getFormat(),
                mainDialog->getColumn(),
                mainDialog->getSide(),
                mainDialog->getFontSize(),
                mainDialog->getNumberOfChapters(),
                mainDialog->getTableOfContents(),
                mainDialog->getListOfFigures(),
                mainDialog->getListOfTables(),
                mainDialog->getNumberOfAppendices(),
                mainDialog->getBibliography()
                );
        emit handledProject();
     }
}

void MainWindow::load_project()
{
    QMessageBox::information(
                this,
                "Request succeeded",
                QString("Project directory was sucessfully created to %1.").arg(myProject->getName()),
                QMessageBox::Ok, QMessageBox::Ok);

    titlepageText->setText(myProject->getTitlepageFileData());
    packageText->setText(myProject->getPackageFileData());
    commandText->setText(myProject->getCommandFileData());
    contentText->setText(myProject->getContentFileData());

    ui->lineEdit->setText(myProject->getName());
    ui->lineEdit_2->setText("Subtitle");
    ui->lineEdit_3->setText("Type of document");
    ui->lineEdit_4->setText("Section");
    ui->lineEdit_5->setText("Prof");
    ui->lineEdit_6->setText("Année");

    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_3->setEnabled(true);
}





void MainWindow::on_fontComboBox_highlighted(const QString &arg1)
{
    ui->textEdit->document()->setDefaultFont(QFont(arg1));
}

void MainWindow::on_fontComboBox_2_highlighted(const QString &arg1)
{
    ui->textEdit_2->document()->setDefaultFont(QFont(arg1));
}

void MainWindow::on_fontComboBox_3_highlighted(const QString &arg1)
{
    ui->textEdit_3->document()->setDefaultFont(QFont(arg1));
}

void MainWindow::on_fontComboBox_4_highlighted(const QString &arg1)
{
    ui->textEdit_4->document()->setDefaultFont(QFont(arg1));
}






void MainWindow::on_pushButton_clicked()
{
    QString titlepageText = ui->textEdit->toPlainText();
    QString packageText = ui->textEdit_2->toPlainText();
    QString commandText = ui->textEdit_3->toPlainText();
    myProject->save(titlepageText, packageText, commandText);
    QMessageBox::information(
        this,
        "Request succeeded",
        QString("Your project was successfully saved."),
        QMessageBox::Ok, QMessageBox::Ok);
}


void MainWindow::on_pushButton_2_clicked()
{
    QProgressDialog dialog;
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setRange(0,0);
    dialog.show();
    myProject->generatePDF();
    QMessageBox::information(
        this,
        "Request succeeded",
        QString("Your project was successfully compiled and your\n"
             "pdf is created."),
        QMessageBox::Ok, QMessageBox::Ok);
}

void MainWindow::on_pushButton_3_clicked()
{
    if(!QDesktopServices::openUrl(QUrl::fromLocalFile(myProject->getName()+".pdf")))
    {
        QMessageBox::critical(
            this,
            "Error",
            "Sorry, we can't find your pdf.",
            QMessageBox::Ok|QMessageBox::Close, QMessageBox::Ok);
    }

}

void MainWindow::on_radioButton_clicked()
{
    myProject->modifyPackages(ui->radioButton->text());
    packageText->setText(myProject->getPackageFileData());
}

void MainWindow::on_radioButton_2_clicked()
{
    myProject->modifyPackages(ui->radioButton_2->text());
    packageText->setText(myProject->getPackageFileData());
}

void MainWindow::on_radioButton_3_clicked()
{
    myProject->modifyPackages(ui->radioButton_3->text());
    packageText->setText(myProject->getPackageFileData());
}

void MainWindow::on_radioButton_4_clicked()
{
    myProject->modifyPackages(ui->radioButton_4->text());
    packageText->setText(myProject->getPackageFileData());
}

void MainWindow::on_radioButton_5_clicked()
{
    myProject->modifyPackages(ui->radioButton_5->text());
    packageText->setText(myProject->getPackageFileData());
}

void MainWindow::on_radioButton_6_clicked()
{
    myProject->modifyPackages(ui->radioButton_6->text());
    packageText->setText(myProject->getPackageFileData());
}

void MainWindow::on_radioButton_7_clicked()
{
    myProject->modifyPackages(ui->radioButton_7->text());
    packageText->setText(myProject->getPackageFileData());
}

void MainWindow::on_pushButton_4_clicked()
{
    myProject->modifyTitlepage(
                ui->lineEdit->text(),
                ui->lineEdit_2->text(),
                ui->lineEdit_3->text(),
                ui->lineEdit_4->text(),
                ui->lineEdit_5->text(),
                ui->lineEdit_6->text()
                );
    titlepageText->setText(myProject->getTitlepageFileData());
}
