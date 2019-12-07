#ifndef FILE_H
#define FILE_H

#include <QWidget>

/*namespace Ui {
class File;
}

class File : public QWidget
{
    Q_OBJECT

public:
    explicit File(QWidget *parent = nullptr);
    ~File();

    Ui::File *ui;

private:

};*/

#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QRegExp>
#include <QDomNode>
#include <QString>

QT_BEGIN_NAMESPACE
class QTextDocument;
class QTextCharFormat;
QT_END_NAMESPACE

class Highlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    Highlighter(QTextDocument *parent = nullptr);

protected:
    void highlightBlock(const QString &text) override;

private:
    struct HighlightingRule
    {
        QRegularExpression pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;

    QRegularExpression commentStartExpression;
    QRegularExpression commentEndExpression;

    QTextCharFormat keywordFormat;
    QTextCharFormat classFormat;
    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat multiLineCommentFormat;
    QTextCharFormat quotationFormat;
    QTextCharFormat functionFormat;
};

#endif // FILE_H
