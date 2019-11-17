#include "projecthandler.hpp"
#include <QDebug>
#include <QCoreApplication>
#include <QProcess>
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <cassert>

ProjectHandler::ProjectHandler()
{
}

ProjectHandler::ProjectHandler(
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
        )
:name(name),
type(type),
format(format),
column(column),
side(side),
fontSize(fontSize),
numberOfChapters(numberOfChapters),
tableOfContents(tableOfContents),
listOfFigures(listOfFigures),
listOfTables(listOfTables),
numberOfAppendices(numberOfAppendices),
bibliography(bibliography)
{


    projectDir = new QDir();
    imgDir = new QDir();
    texDir = new QDir();
    chapterDir = new QDir();
    appendiceDir = new QDir();




    projectDir->mkpath(this->name+"/");
    projectDir->setPath(this->name+"/");
    imgDir->mkpath(this->name+"/img");
    imgDir->setPath(this->name+"/img");
    texDir->mkpath(this->name+"/tex");
    texDir->setPath(this->name+"/tex");
    chapterDir->mkpath(this->name+"/tex/_chapters");
    chapterDir->setPath(this->name+"/tex/_chapters");
    appendiceDir->mkpath(this->name+"/tex/_appendices");
    appendiceDir->setPath(this->name+"/tex/_appendices");




    chaptersList = new QList<QFile*>();
    appendicesList = new QList<QFile*>();


    projectFile = new QFile(projectDir->absolutePath()+"/"+name+".tex");
    titlepageFile = new QFile(texDir->absolutePath()+"/_titlepage.tex");
    packageFile = new QFile(texDir->absolutePath()+"/_package.tex");
    commandFile = new QFile(texDir->absolutePath()+"/_command.tex");

    createProject();
    createTitlepage();
    createPackages();
    createCommands();
    createChapters();
    createAppendices();


    std::string mycommand = "pdflatex " + (projectDir->absolutePath()+"/"+name).toStdString() + ".tex "+(projectDir->absolutePath()+"/"+name).toStdString()+".pdf";
    std::system(mycommand.c_str());


}



void ProjectHandler::createProject()
{
    projectFile->open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream stream(projectFile);
    stream << "% " + projectFile->fileName();
    stream << "\n% @author: Corky Maigre";
    stream << "\n%";
    for(int j=0; j<150; j++) stream << "-";
    stream << "\n\\documentclass["+format+", "+column+", "+side+", "+fontSize+"pt]{"+type+"}";
    stream << "\n%";
    for(int j=0; j<150; j++) stream << "-";
    stream << "\n\\input{"+texDir->absolutePath()+"/_package.tex}";
    stream << "\n\\input{"+texDir->absolutePath()+"/_command.tex}";
    stream << "\n%";
    for(int j=0; j<150; j++) stream << "-";
    stream << "\n\\begin{document}";
    stream << "\n%";
    for(int j=0; j<150; j++) stream << "-";
    stream << "\n\\input{"+texDir->absolutePath()+"/_titlepage.tex}";
    stream << "\n\\pagestyle{plain}";
    stream << "\n%\\input{"+texDir->absolutePath()+"/_thanks.tex}";
    stream << "\n%\\input{"+texDir->absolutePath()+"/_confidentiality.tex}";
    stream << "\n\\pagenumbering{Roman}";
    stream << "\n\\pagestyle{fancy}";
    stream << "\n\\setcounter{page}{0}";
    if(tableOfContents)
        stream << "\n\\tableofcontents";
    else
        stream << "\n%\\tableofcontents";
    if(listOfFigures)
        stream << "\n\\listoffigures";
    else
        stream << "\n%\\listoffigures";
    if(listOfTables)
        stream << "\n\\listoftables";
    else
        stream << "\n%\\listoftables";
    stream << "\n%";
    for(int j=0; j<150; j++) stream << "-";
    stream << "\n%\\input{"+texDir->absolutePath()+"/_introduction.tex}";
    stream << "\n\\pagenumbering{arabic}";
    stream << "\n\\pagestyle{fancy}";
    for(int i=1; i<=numberOfChapters; i++)
    {
        stream << "\n\\input{"+this->getName()+"/tex/_chapters/_"+QString::number(i)+".tex}";
    }
    stream << "\n%";
    for(int j=0; j<150; j++) stream << "-";
    if(numberOfAppendices>0)
    {
        stream << "\n\\appendix";
        stream << "\n\\addtocontents{toc}{\\bigskip}";
        stream << "\n\\addcontentsline{toc}{part}{Annexes}";
    }
    else
    {
        stream << "\n%\\appendix";
        stream << "\n%\\addtocontents{toc}{\\bigskip}";
        stream << "\n%\\addcontentsline{toc}{part}{Annexes}";
    }
    stream << "\n%";
    for(int j=0; j<150; j++) stream << "-";
    stream << "\n\\pagestyle{fancy}";
    if(numberOfAppendices>0)
    {
        for(int i=1; i<numberOfAppendices; i++)
            stream << "\n\\input{"+texDir->absolutePath()+"/_appendices/_"+QString::number(i)+".tex}";
    }
    stream << "\n\\pagenumbering{roman}";
    stream << "\n\\setcounter{page}{0}";
    if(numberOfAppendices>0)
    {
        stream << "\n\\bibliographystyle{unsrt}";
        stream << "\n\\bibliography{"+texDir->absolutePath()+"/_biblio.bib}";
        stream << "\n\\addcontentsline{toc}{part}{Bibliographie}";
    }
    stream << "\n%";
    for(int j=0; j<150; j++) stream << "-";
    stream << "\n\\end{document}";
    stream << "\n%";
    for(int j=0; j<150; j++) stream << "-";
    stream << "\n";
    projectFile->close();
}


void ProjectHandler::createChapters()
{
    for(int i=1; i<=numberOfChapters; i++)
    {
        QFile *file = new QFile(chapterDir->absolutePath()+"/_"+QString::number(i)+".tex");
        chaptersList->push_back(file);
        file->open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream stream(file);
        stream << "\n%";
        for(int j=0; j<150; j++) stream << "-";
        stream << "\n";
        stream << "%";
        stream << "\n%                       CHAPTER "+QString::number(i)+" - ";
        stream << "\n%";
        stream << "\n%";
        for(int j=0; j<150; j++) stream << "-";
        stream << "\n";
        stream << "\n\\chapter{Name of chapter}";
        stream << "\n%";
        for(int j=0; j<150; j++) stream << "-";
        stream << "\nEnter your text.";
        file->close();

    }
}



void ProjectHandler::createAppendices()
{
    for(int i=1; i<=numberOfAppendices; i++)
    {

        QFile *file = new QFile(appendiceDir->absolutePath()+"/_"+QString::number(i)+".tex");
        appendicesList->push_back(file);
        file->open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream stream(file);
        stream << "\n% @author: Corky Maigre";
        stream << "\n%";
        for(int j=0; j<150; j++) stream << "-";
        stream << "\n";
        stream << "%";
        stream << "\n%                       APPENDICE "+QString::number(i)+" - ";
        stream << "\n%";
        stream << "\n%";
        for(int j=0; j<150; j++) stream << "-";
        stream << "\n";
        stream << "\n\\chapter{}";
        stream << "\n%";
        for(int j=0; j<150; j++) stream << "-";
        stream << "\n";
        stream << "\n%";
        for(int j=0; j<150; j++) stream << "-";
        stream << "\n\\appendixpagenumbering";
        file->close();

    }
}



void ProjectHandler::createPackages()
{
    packageFile->open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream stream(packageFile);
    stream << "% " + packageFile->fileName();
    stream << "\n% @author: Corky Maigre";
    stream << "\n%";
    for(int j=0; j<150; j++) stream << "-";
    stream << "\n\\usepackage[latin1]{inputenc}";
    stream << "\n\\usepackage[T1]{fontenc}";
    stream << "\n\\usepackage[french]{babel}";
    stream << "\n\\usepackage[top=2cm, bottom=2cm, left=2cm, right=2cm]{geometry}";
    stream << "\n\\usepackage[hypertexnames=false]{hyperref}";
    stream << "\n\\usepackage{setspace}";
    stream << "\n\\usepackage{color}";
    stream << "\n\\usepackage{graphicx}";
    stream << "\n\\usepackage{float}";
    stream << "\n\\usepackage{verbatim}";
    stream << "\n\\usepackage{listings}";
    stream << "\n\\usepackage{amsmath}";
    stream << "\n\\usepackage{amssymb}";
    stream << "\n\\usepackage{mathrsfs}";
    stream << "\n\\usepackage{marvosym}";
    stream << "\n\\usepackage{url}";
    stream << "\n\\usepackage{wrapfig}";
    stream << "\n\\usepackage{soul}";
    stream << "\n\\usepackage{lmodern}";
    stream << "\n\\usepackage{eso-pic}";
    stream << "\n\\usepackage{xcolor}";
    stream << "\n\\usepackage{tikz}";
    stream << "\n\\usepackage{esint}";
    stream << "\n\\usepackage{pifont}";
    stream << "\n\\usepackage{titlesec}";
    stream << "\n%\\usepackage{lipsum}";
    stream << "\n%\\usepackage{microtype}";
    stream << "\n\\usepackage{fancyhdr}";
    stream << "\n\\usepackage{lscape}";
    stream << "\n\\usepackage[Glenn]{fncychap} %Options: Sonny, Lenny, Glenn, Conny, Rejne, Bjarne, Bjornstrup";
    stream << "\n\\usepackage{etoolbox}";
    stream << "\n\\usepackage{slashbox}";
    stream << "\n\\usepackage{pbox}";
    packageFile->close();
}



void ProjectHandler::createCommands()
{
    commandFile->open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream stream(commandFile);
    stream << "% " + commandFile->fileName();
    stream << "\n% @author: Corky Maigre";
    stream << "\n%";
    for(int j=0; j<150; j++) stream << "-";
    stream << "\n%";
    for(int j=0; j<150; j++) stream << "-";
    stream << "\n%";
    stream << "\n%                  LIST OF COMMANDS";
    stream << "\n%";
    stream << "\n%";
    for(int j=0; j<150; j++) stream << "-";
    stream << "\n\n% HEADER ";
    for(int j=0; j<140; j++) stream << "-";
    stream << "\n% \\fancyhf{}";
    stream << "\n% \\fancyhead[LE]{\\sffamily MANIPULATION \\thechapter.}";
    stream << "\n% \\fancyhead[RO]{\\sffamily MANIPULATION \\thechapter.}";
    stream << "\n% \\fancyfoot[C,C]{\\thepage}";
    stream << "\n% \\addto\\captionsfrench{\\renewcommand{\\chaptername}{Manipulation}}";
    stream << "\n%";
    for(int j=0; j<150; j++) stream << "-";
    stream << "\n\n% HEADER ";
    for(int j=0; j<140; j++) stream << "-";
    stream << "\n\\fancyhf{}";
    stream << "\n\\fancyhead[LE]{\\sffamily\\leftmark}";
    stream << "\n\\fancyhead[RO]{\\sffamily\\rightmark}";
    stream << "\n\\fancyfoot[C,C]{\\thepage}";
    stream << "\n\\addto\\captionsfrench{\\renewcommand{\\chaptername}{Chapitre}}";
    stream << "\n%";
    for(int j=0; j<150; j++) stream << "-";
    stream << "\n\n% CHAPTER HEAD ";
    for(int j=0; j<140; j++) stream << "-";
    stream << "\n\\makeatletter";
    stream << "\n   \\patchcmd{\\@makechapterhead}{\\vspace*{50\\p@}}{\\vspace*{-50\\p@}}{}{}";
    stream << "\n   \\patchcmd{\\@makeschapterhead}{\\vspace*{50\\p@}}{\\vspace*{-50\\p@}}{}{}";
    stream << "\n   \\patchcmd{\\DOTI}{\\vskip 10\\p@}{\\vskip -20\\p@}{}{}";
    stream << "\n   \\patchcmd{\\DOTIS}{\\vskip 5\\p@}{\\vskip 0\\p@}{}{}";
    stream << "\n\\makeatother";
    stream << "\n%";
    for(int j=0; j<150; j++) stream << "-";
    stream << "\n\n% SEPARATE LINE ";
    for(int j=0; j<140; j++) stream << "-";
    stream << "\n\\newcommand{\\HRule}{\\rule{\\linewidth}{0.5mm}}";
    stream << "\n%";
    for(int j=0; j<150; j++) stream << "-";
    stream << "\n\n% COLORS ";
    for(int j=0; j<140; j++) stream << "-";
    stream << "\n\\newcommand\\blue[1]{\\color{blue}#1\\color{black}}";
    stream << "\n\\newcommand\\green[1]{\\color{green}#1\\color{black}}";
    stream << "\n\\newcommand\\red[1]{\\color{red}#1\\color{black}}";
    stream << "\n\\newcommand\\brown[1]{\\color{brown}#1\\color{black}}";
    stream << "\n\\newcommand\\purple[1]{\\color{purple}#1\\color{black}}";
    stream << "\n\\newcommand\\orange[1]{\\color{orange}#1\\color{black}}";
    stream << "\n\\newcommand\\gray[1]{\\color{gray}#1\\color{black}}";
    stream << "\n%";
    for(int j=0; j<150; j++) stream << "-";
    stream << "\n\n% REFERENCES ";
    for(int j=0; j<140; j++) stream << "-";
    stream << "\n\\newcommand\\myFigRef[1]{\\red{\\bsc{Figure \\ref{fig:#1}}}}";
    stream << "\n\\newcommand\\myTabRef[1]{\\brown{\\bsc{Table \\ref{tab:#1}}}}";
    stream << "\n\\newcommand\\mySecRef[1]{\\purple{\\bsc{Section \\ref{sec:#1}}}}";
    stream << "\n\\newcommand\\mySubSecRef[1]{\\orange{\\bsc{Sous-section \\ref{subsec:#1}}}}";
    stream << "\n\\newcommand\\myAnnexeRef[1]{\\gray{\\bsc{Annexe \\ref{axn:#1}}}}";
    stream << "\n%";
    for(int j=0; j<150; j++) stream << "-";
    stream << "\n\n% DATE ";
    for(int j=0; j<140; j++) stream << "-";
    stream << "\n\\date{}";
    stream << "\n%";
    for(int j=0; j<150; j++) stream << "-";
    stream << "\n\n% CHAPTER ";
    for(int j=0; j<140; j++) stream << "-";
    stream << "\n\\newcommand\\myChapter[1]{%";
    stream << "\n   \\vspace{-5cm}";
    stream << "\n   \\chapter{#1}%";
    stream << "\n   ~\\\\[-2.5cm]";
    stream << "\n}";
    stream << "\n\\newcommand\\chap[1]{%";
    stream << "\n   \\chapter*{#1}%";
    stream << "\n   \\addcontentsline{toc}{chapter}{#1}%";
    stream << "\n   \\chaptermark{#1}";
    stream << "\n}";
    stream << "\n%";
    for(int j=0; j<150; j++) stream << "-";
    stream << "\n\n% SECTION ";
    for(int j=0; j<140; j++) stream << "-";
    stream << "\n\\makeatletter";
    stream << "\n\\renewcommand\\section{\\@startsection {section}{1}{\\z@}%";
    stream << "\n   {-3.5ex \\@plus -1ex \\@minus -.2ex}%";
    stream << "\n   {2.3ex \\@plus.2ex}%";
    stream << "\n   {\\reset@font\\noindent\\Large\\sffamily}}";
    stream << "\n\\makeatother";
    stream << "\n\\newcommand\\mySection[1]{%";
    stream << "\n   \\section{#1}% \\section*{\\ding{121} #1}";
    stream << "\n}";
    stream << "\n%";
    for(int j=0; j<150; j++) stream << "-";
    stream << "\n\n% SUBSECTION ";
    for(int j=0; j<140; j++) stream << "-";
    stream << "\n\\makeatletter";
    stream << "\n\\renewcommand\\subsection{\\@startsection {subsection}{1}{\\z@}%";
    stream << "\n   {-3.5ex \\@plus -1ex \\@minus -.2ex}%";
    stream << "\n   {2.3ex \\@plus.2ex}%";
    stream << "\n   {\\reset@font\\Large\\sffamily}}";
    stream << "\n\\makeatother";
    stream << "\n\\newcommand\\mySubSection[1]{%";
    stream << "\n   \\subsection{#1}% \\subsection*{\\ding{120} #1}";
    stream << "\n}";
    stream << "\n%";
    for(int j=0; j<150; j++) stream << "-";
    stream << "\n\n% SUBSUBSECTION ";
    for(int j=0; j<140; j++) stream << "-";
    stream << "\n\\makeatletter";
    stream << "\n\\renewcommand\\subsubsection{\\@startsection {subsubsection}{1}{\\z@}%";
    stream << "\n   {-3.5ex \\@plus -1ex \\@minus -.2ex}%";
    stream << "\n   {2.3ex \\@plus.2ex}%";
    stream << "\n   {\\reset@font\\normalsize\\sffamily}}";
    stream << "\n\\makeatother";
    stream << "\n\\newcommand\\mySubSubSection[1]{%";
    stream << "\n   \\subsubsection{#1}% \\subsubsection*{\\indent\\indent\\ding{71} \\underline{#1}}";
    stream << "\n}";
    stream << "\n%";
    for(int j=0; j<150; j++) stream << "-";
    stream << "\n\n%";
    for(int j=0; j<150; j++) stream << "-";
    stream << "\n\\DeclareRobustCommand\\refmark[1]{\\textsuperscript{\\ref{#1}}}";
    stream << "\n\\newcommand{\\appendixpagenumbering}{";
    stream << "\n   \\break";
    stream << "\n   \\pagenumbering{arabic}";
    stream << "\n   \\renewcommand{\\thepage}{\\thechapter-\\arabic{page}}";
    stream << "\n}";
    stream << "\n%";
    for(int j=0; j<150; j++) stream << "-";
    stream << "\n\n% FIGURE ";
    for(int j=0; j<140; j++) stream << "-";
    stream << "\n\\newcommand\\myFigure[3]{%";
    stream << "\n   \\begin{figure}[H]";
    stream << "\n       \\begin{center}";
    stream << "\n           \\includegraphics[scale=#3]{img/#2.png}";
    stream << "\n       \\end{center}";
    stream << "\n       \\caption{#1.\\label{fig:#2}}";
    stream << "\n   \\end{figure}";
    stream << "\n}";
    stream << "\n%";
    for(int j=0; j<150; j++) stream << "-";
    stream << "\n\n% QUOTE ";
    for(int j=0; j<140; j++) stream << "-";
    stream << "\n\\newcommand\\myQuote[1]{%";
    stream << "\n   \\og#1\\fg\\:";
    stream << "\n}";
    stream << "\n%";
    for(int j=0; j<150; j++) stream << "-";
    stream << "\n\n% MANIP FOOTNOTE ";
    for(int j=0; j<140; j++) stream << "-";
    stream << "\n\\newcommand\\myManipFootnote[2]{%";
    stream << "\n   \\footnote{voir Manipulation\\_#1/Simulations/#2.DSN}";
    stream << "\n}";
    stream << "\n%";
    for(int j=0; j<150; j++) stream << "-";
    stream << "\n\n% PORTES LOGIQUES ";
    for(int j=0; j<140; j++) stream << "-";
    stream << "\n\\newcommand\\myNot[1]{\\overline{#1}}";
    stream << "\n\\newcommand\\myAnd[2]{#1.#2}";
    stream << "\n\\newcommand\\myOr[2]{#1+#2}";
    stream << "\n\\newcommand\\myNand[2]{\\myNot{#1.#2}}";
    stream << "\n\\newcommand\\myNor[2]{\\myNot{#1+#2}}";
    stream << "\n\\newcommand\\myXor[2]{#1\\oplus#2}";
    stream << "\n\\newcommand\\myNxor[2]{\\myNot{#1\\oplus#2}}";
    stream << "\n\\newcommand\\myXnor[2]{\\myNot{#1\\oplus#2}}";
    stream << "\n%";
    for(int j=0; j<150; j++) stream << "-";
    commandFile->close();
}

void ProjectHandler::createTitlepage()
{
    titlepageFile->open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream stream(titlepageFile);
    stream << "% " + titlepageFile->fileName();
    stream << "\n% @author: Corky Maigre";
    stream << "\n%";
    for(int j=0; j<150; j++) stream << "-";
    stream << "\n\\begin{titlepage}";
    stream << "\n\\begin{center}";
    //stream << "\n\\includegraphics[scale=1]{img/heh.png}~\\\\[0.8cm]";
    stream << "\n%";
    for(int j=0; j<150; j++) stream << "-";
    stream << "\n\\textsc{\\LARGE \\textsc{HEH}, Campus Technique}\\\\[0.5cm]";
    stream << "\n\\textsc{\\LARGE \\textsc{Institut Supérieur Industriel de Mons}}\\\\[1cm]";
    stream << "\n%";
    for(int j=0; j<150; j++) stream << "-";
    stream << "\n\\HRule \\\\[0.4cm]";
    stream << "\n{\\sffamily\\Huge " << name << "\\\\[0.4cm]}";
    stream << "\n{\\sffamily\\LARGE SubTitle of the document\\\\[0.4cm]}";
    stream << "\n\\HRule \\\\[1cm]";
    stream << "\n%";
    for(int j=0; j<150; j++) stream << "-";
    stream << "\n\\textsc{\\Large What document is it ?}\\\\[1cm]";
    stream << "\n%";
    for(int j=0; j<150; j++) stream << "-";
    //stream << "\n\\includegraphics[scale=2.75]{img/logo.jpg}~\\\\[1cm]";
    stream << "\n%";
    for(int j=0; j<150; j++) stream << "-";
    stream << "\n\\textit{\\today}\\\\[1.5cm]";
    stream << "\n%";
    for(int j=0; j<150; j++) stream << "-";
    stream << "\n       \\begin{minipage}{0.4\\textwidth}";
    stream << "\n           \\begin{flushleft} \\large";
    stream << "\n               \\emph{Auteur:}\\\\";
    stream << "\n               Corky \\bsc{Maigre}\\\\";
    stream << "\n               corky.maigre@std.hecfh.be";
    stream << "\n           \\end{flushleft}";
    stream << "\n       \\end{minipage}";
    stream << "\n       \\begin{minipage}{0.4\\textwidth}";
    stream << "\n           \\begin{flushright} \\large";
    stream << "\n               Section\\";
    stream << "\n               3\\up{ème} Bachelier ISIMs\\";
    stream << "\n               Mr.\\bsc{Prof's name'}";
    stream << "\n           \\end{flushright}";
    stream << "\n       \\end{minipage}";
    stream << "\n%";
    for(int j=0; j<150; j++) stream << "-";
    stream << "\n       \\vfill";
    stream << "\n       {\\large Année Académique 2014-2015}";
    stream << "\n   \\end{center}";
    stream << "\n\\end{titlepage}";
    titlepageFile->close();
}

QString ProjectHandler::getTitlepageFileData()
{
    QString data;
    if(titlepageFile->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        data = titlepageFile->readAll();
        titlepageFile->close();
    }
    return data;
}

QString ProjectHandler::getPackageFileData()
{
    QString data;
    if(packageFile->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        data = packageFile->readAll();
        packageFile->close();
    }
    return data;
}

QString ProjectHandler::getCommandFileData()
{
    QString data;
    if(commandFile->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        data = commandFile->readAll();
        commandFile->close();
    }
    return data;
}

QString ProjectHandler::getContentFileData()
{
    QString data;
    for(int i=1; i<=numberOfChapters; i++)
    {
        QFile *file = new QFile(chapterDir->absolutePath()+"/_"+QString::number(i)+".tex");
        file->open(QIODevice::ReadOnly | QIODevice::Text);
        data += file->readAll();
        file->close();

    }
    return data;
}

bool ProjectHandler::test()
{
    return true;
}

QString ProjectHandler::getName()
{
    return name;
}


void ProjectHandler::save(QString arg1, QString arg2, QString arg3)
{
    titlepageFile->open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream stream1(titlepageFile);
    stream1 <<  arg1;
    titlepageFile->close();
    packageFile->open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream stream2(packageFile);
    stream2 <<  arg2;
    packageFile->close();
    commandFile->open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream stream3(commandFile);
    stream3 <<  arg3;
    commandFile->close();
    //I can't save the chapter yet!

}

void ProjectHandler::generatePDF()
{

    std::string mycommand = "pdflatex " + (projectDir->absolutePath()+"/"+name).toStdString() + ".tex "+(projectDir->absolutePath()+"/"+name).toStdString()+".pdf";
    std::system(mycommand.c_str());
}

void ProjectHandler::modifyPackages(QString fncychap)
{

    packageFile->open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream stream(packageFile);
    stream << "% " + packageFile->fileName();
    stream << "\n% @author: Corky Maigre";
    stream << "\n%";
    for(int j=0; j<150; j++) stream << "-";
    stream << "\n\\usepackage[latin1]{inputenc}";
    stream << "\n\\usepackage[T1]{fontenc}";
    stream << "\n\\usepackage[french]{babel}";
    stream << "\n\\usepackage[top=2cm, bottom=2cm, left=2cm, right=2cm]{geometry}";
    stream << "\n\\usepackage[hypertexnames=false]{hyperref}";
    stream << "\n\\usepackage{setspace}";
    stream << "\n\\usepackage{color}";
    stream << "\n\\usepackage{graphicx}";
    stream << "\n\\usepackage{float}";
    stream << "\n\\usepackage{verbatim}";
    stream << "\n\\usepackage{listings}";
    stream << "\n\\usepackage{amsmath}";
    stream << "\n\\usepackage{amssymb}";
    stream << "\n\\usepackage{mathrsfs}";
    stream << "\n\\usepackage{marvosym}";
    stream << "\n\\usepackage{url}";
    stream << "\n\\usepackage{wrapfig}";
    stream << "\n\\usepackage{soul}";
    stream << "\n\\usepackage{lmodern}";
    stream << "\n\\usepackage{eso-pic}";
    stream << "\n\\usepackage{xcolor}";
    stream << "\n\\usepackage{tikz}";
    stream << "\n\\usepackage{esint}";
    stream << "\n\\usepackage{pifont}";
    stream << "\n\\usepackage{titlesec}";
    stream << "\n%\\usepackage{lipsum}";
    stream << "\n%\\usepackage{microtype}";
    stream << "\n\\usepackage{fancyhdr}";
    stream << "\n\\usepackage{lscape}";
    stream << "\n\\usepackage[" << fncychap << "]{fncychap} %Options: Sonny, Lenny, Glenn, Conny, Rejne, Bjarne, Bjornstrup";
    stream << "\n\\usepackage{etoolbox}";
    stream << "\n\\usepackage{slashbox}";
    stream << "\n\\usepackage{pbox}";
    packageFile->close();



}


void ProjectHandler::modifyTitlepage(QString arg1, QString arg2, QString arg3, QString arg4, QString arg5, QString arg6)
{
    titlepageFile->open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream stream(titlepageFile);
    stream << "% " + titlepageFile->fileName();
    stream << "\n% @author: Corky Maigre";
    stream << "\n%";
    for(int j=0; j<150; j++) stream << "-";
    stream << "\n\\begin{titlepage}";
    stream << "\n\\begin{center}";
    //stream << "\n\\includegraphics[scale=1]{img/heh.png}~\\\\[0.8cm]";
    stream << "\n%";
    for(int j=0; j<150; j++) stream << "-";
    stream << "\n\\textsc{\\LARGE \\textsc{HEH}, Campus Technique}\\\\[0.5cm]";
    stream << "\n\\textsc{\\LARGE \\textsc{Institut Supérieur Industriel de Mons}}\\\\[1cm]";
    stream << "\n%";
    for(int j=0; j<150; j++) stream << "-";
    stream << "\n\\HRule \\\\[0.4cm]";
    stream << "\n{\\sffamily\\Huge " << arg1 << "\\\\[0.4cm]}";
    stream << "\n{\\sffamily\\LARGE " << arg2 << "\\\\[0.4cm]}";
    stream << "\n\\HRule \\\\[1cm]";
    stream << "\n%";
    for(int j=0; j<150; j++) stream << "-";
    stream << "\n\\textsc{\\Large " << arg3 << "}\\\\[1cm]";
    stream << "\n%";
    for(int j=0; j<150; j++) stream << "-";
    //stream << "\n\\includegraphics[scale=2.75]{img/logo.jpg}~\\\\[1cm]";
    stream << "\n%";
    for(int j=0; j<150; j++) stream << "-";
    stream << "\n\\textit{\\today}\\\\[1.5cm]";
    stream << "\n%";
    for(int j=0; j<150; j++) stream << "-";
    stream << "\n       \\begin{minipage}{0.4\\textwidth}";
    stream << "\n           \\begin{flushleft} \\large";
    stream << "\n               \\emph{Auteur:}\\\\";
    stream << "\n               Corky \\bsc{Maigre}\\\\";
    stream << "\n               corky.maigre@std.hecfh.be";
    stream << "\n           \\end{flushleft}";
    stream << "\n       \\end{minipage}";
    stream << "\n       \\begin{minipage}{0.4\\textwidth}";
    stream << "\n           \\begin{flushright} \\large";
    stream << "\n               " << arg4 << "\\\\";
    stream << "\n               3\\up{ème} Bachelier ISIMs\\";
    stream << "\n               Mr.\\bsc{" << arg5 << "}";
    stream << "\n           \\end{flushright}";
    stream << "\n       \\end{minipage}";
    stream << "\n%";
    for(int j=0; j<150; j++) stream << "-";
    stream << "\n       \\vfill";
    stream << "\n       {\\large Année Académique " << arg6 <<"}";
    stream << "\n   \\end{center}";
    stream << "\n\\end{titlepage}";
    titlepageFile->close();

}



