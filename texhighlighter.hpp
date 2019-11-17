#ifndef TEXHIGHLIGHTER_H
#define TEXHIGHLIGHTER_H

#include <QSyntaxHighlighter>

class TexHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    explicit TexHighlighter(QObject *parent = 0);

    void highlightBlock(const QString &text);



signals:

public slots:

};

#endif // TEXHIGHLIGHTER_H
