#include "file.h"
#include "ui_file.h"

/*File::File(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::File)
{
    ui->setupUi(this);
}

File::~File()
{
    delete ui;
}*/


#include <QTextCharFormat>
#include <QBrush>
#include <QColor>

void traverseNode(const QDomNode& node, QStringList& a, QString& b)
{
    QDomNode domNode = node.firstChild();
    while ( ! domNode. isNull () ) {
        if(domNode.isElement()) {
            QDomElement domElement = domNode.toElement();
            if ( ! domElement. isNull () ) {
                if(domElement. tagName ( ) == "name"){
                    b = domElement.attribute("file");
                }
                else {
                    a << domElement.text();
                }
            }
        }
        traverseNode(domNode, a, b);
        domNode = domNode.nextSibling();
    }
}


Highlighter::Highlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    keywordFormat.setForeground(Qt::darkBlue);
    keywordFormat.setFontWeight(QFont::Bold);

    QDomDocument domDoc;
    QString Word;
    QStringList KeyWords;
    QFile file ( "C:/Users/user/Documents/LAB3/xml_words.xml") ;
    if(file.open(QIODevice::ReadOnly)) {
        if(domDoc.setContent(&file)) {
            QDomElement domElement= domDoc.documentElement();
            traverseNode(domElement, KeyWords, Word);
        }
        file. close () ;
    }

      foreach (const QString &pattern, KeyWords) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
      }

        classFormat.setFontWeight(QFont::Bold);
        classFormat.setForeground(Qt::darkMagenta);
        rule.pattern = QRegularExpression(QStringLiteral("\\bQ[A-Za-z]+\\b"));
        rule.format = classFormat;
        highlightingRules.append(rule);

        singleLineCommentFormat.setForeground(Qt::green);
        rule.pattern = QRegularExpression(QStringLiteral("//[^\n]*"));
        rule.format = singleLineCommentFormat;
        highlightingRules.append(rule);

        multiLineCommentFormat.setForeground(Qt::green);

        quotationFormat.setForeground(Qt::darkGreen);
        rule.pattern = QRegularExpression(QStringLiteral("\".*\""));
        rule.format = quotationFormat;
        highlightingRules.append(rule);

        functionFormat.setFontItalic(true);
        functionFormat.setForeground(Qt::blue);
        rule.pattern = QRegularExpression(QStringLiteral("\\b[A-Za-z0-9_]+(?=\\()"));
        rule.format = functionFormat;
        highlightingRules.append(rule);

        commentStartExpression = QRegularExpression(QStringLiteral("/\\*"));
        commentEndExpression = QRegularExpression(QStringLiteral("\\*/"));
}

void Highlighter::highlightBlock(const QString &text)
{
    for (const HighlightingRule &rule : qAsConst(highlightingRules)) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }

    setCurrentBlockState(0);
    int startIndex = 0;

    if (previousBlockState() != 1)
        startIndex = text.indexOf(commentStartExpression);

    while (startIndex >= 0) {
         QRegularExpressionMatch match = commentEndExpression.match(text, startIndex);
         int endIndex = match.capturedStart();
         int commentLength = 0;
         if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
          } else {
            commentLength = endIndex - startIndex
                                + match.capturedLength();
          }
          setFormat(startIndex, commentLength, multiLineCommentFormat);
          startIndex = text.indexOf(commentStartExpression, startIndex + commentLength);
    }
}
