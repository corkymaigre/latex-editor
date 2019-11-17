#ifndef PROJECTHANDLER_HPP
#define PROJECTHANDLER_HPP

#include <QString>
#include <QDir>
#include <QTextStream>
#include <QDesktopServices>
#include <QUrl>
#include <QMessageBox>




class ProjectHandler
{
public:
                        ProjectHandler();
                        ProjectHandler(
                                QString name,
                                QString type,
                                QString format,
                                QString column,
                                QString side,
                                QString fontSize,
                                int numberOfChapters,
                                bool tableOfContents,
                                bool listOfFigures,
                                bool listOfTables,
                                int numberOfAppendices,
                                bool bibliography
                                );

    QString             getTitlepageFileData();
    QString             getPackageFileData();
    QString             getCommandFileData();
    QString             getContentFileData();
    bool                test();
    QString             getName();
    void                save(QString arg1, QString arg2, QString arg3);
    void                generatePDF();
    void                modifyPackages(QString fncychap);
    //j'aurais pu créer un tableau de strings et passer ce tableau en argument.
    void                modifyTitlepage(QString arg1, QString arg2, QString arg3, QString arg4, QString arg5, QString arg6);


private:

    QDir                *projectDir;
    QDir                *imgDir;
    QDir                *texDir;
    QDir                *chapterDir;
    QDir                *appendiceDir;
    QFile               *projectFile;
    QFile               *titlepageFile;
    QFile               *packageFile;
    QFile               *commandFile;
    QList<QFile*>       *chaptersList;
    QList<QFile*>       *appendicesList;

    QString             name;
    QString             type;
    QString             format;
    QString             column;
    QString             side;
    QString             fontSize;
    int                 numberOfChapters;
    bool                tableOfContents;
    bool                listOfFigures;
    bool                listOfTables;
    int                 numberOfAppendices;
    bool                bibliography;


    void                createProject();
    void                createTitlepage();
    void                createPackages();
    void                createCommands();
    void                createChapters();
    void                createAppendices();

};






#endif // PROJECTHANDLER_HPP
