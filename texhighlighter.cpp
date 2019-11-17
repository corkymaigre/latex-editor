#include "texhighlighter.hpp"
#include <QTextCharFormat>
#include <QRegularExpression>

TexHighlighter::TexHighlighter(QObject *parent) :
    QSyntaxHighlighter(parent)
{
}

void TexHighlighter::highlightBlock(const QString &text)
{
    QTextCharFormat format;
    QString exp =
            "\\b"
            "("
            "addto|"
            "addtocontents|"
            "addcontentsline|"
            "appendix|"
            "begin|"
            "captionsfrench|"
            "chaptername|"
            "documentclass|"
            "emph|"
            "end|"
            "fancyhead|"
            "fancyhf|"
            "fancyfoot|"
            "[Hh][Uu][Gg][Ee]|"
            "HRule|"
            "input|"
            "[Ll][Aa][Rr][Gg][Ee]|"
            "listoffigures|"
            "listoftables|"
            "makeatletter|"
            "makeatother|"
            "newcommand|"
            "patchcmd|"
            "renewcommand|"
            "setcounter|"
            "sffamily|"
            "tableofcontents|"
            "textit|"
            "textsc|"
            "textwidth|"
            "thechapter|"
            "thepage|"
            "today|"
            "pagestyle|"
            "up|"
            "usepackage|"
            "vfill|"
            "vskip|"
            "vspace"
            ")\\b"
            "|[][{}]"
            "|\\\\";
    QRegExp rx(exp);

    if(!rx.isValid() || rx.isEmpty() || rx.exactMatch(""))
    {
        setFormat(0, text.length(), format);
        return;
    }
    format.setForeground(QBrush(Qt::blue));
    int index = rx.indexIn(text);
    while(index >= 0)
    {
        int length = rx.matchedLength();
        //setFormat(index, length, Qt::blue);
        setFormat(index, length, format);
        index = rx.indexIn(text, index+length);
    }
}


