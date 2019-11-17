#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QTextEdit>
#include <QProgressDialog>
#include "MainDialog.hpp"
#include "projecthandler.hpp"
#include "texhighlighter.hpp"

namespace Ui {
class MainWindow;
class MainDialog;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit            MainWindow(QWidget *parent = 0);
        virtual             ~MainWindow();


    private slots:
        void                on_actionNew_File_triggered();
        void                create_project();
        void                load_project();


        void on_fontComboBox_highlighted(const QString &arg1);
        void on_fontComboBox_2_highlighted(const QString &arg1);
        void on_fontComboBox_3_highlighted(const QString &arg1);
        void on_fontComboBox_4_highlighted(const QString &arg1);


        void on_pushButton_clicked();

        void on_pushButton_2_clicked();

        void on_pushButton_3_clicked();

        void on_radioButton_clicked();

        void on_radioButton_2_clicked();

        void on_radioButton_3_clicked();

        void on_radioButton_4_clicked();

        void on_radioButton_5_clicked();

        void on_radioButton_6_clicked();

        void on_radioButton_7_clicked();

        void on_pushButton_4_clicked();

signals:
        void                handledProject();

    private:
            Ui::MainWindow                      *ui;
            MainDialog                          *mainDialog;
            ProjectHandler                      *myProject;
            QTextEdit                           *titlepageText;
            QTextEdit                           *packageText;
            QTextEdit                           *commandText;
            QTextEdit                           *contentText;
            TexHighlighter                      *titlepageHighlighter;
            TexHighlighter                      *packageHighlighter;
            TexHighlighter                      *commandHighlighter;
            TexHighlighter                      *contentHighlighter;

};

#endif // MAINWINDOW_HPP
