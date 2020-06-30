#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QTextCharFormat>

QT_BEGIN_NAMESPACE
class QTextDocument;
QT_END_NAMESPACE

class CppHighlighter : public QSyntaxHighlighter //由QSyntaxHightliaghter派生的C++语法高亮类
{
    Q_OBJECT

public:
    CppHighlighter(QTextDocument *parent = nullptr);  //构造函数（添加语法高亮）
    void clearHighlight();  //清除语法高亮

protected:
    void highlightBlock(const QString &text) override;  //重写基类的highlightBlock函数

private:
    struct HighlightingRule  //高亮的语法规则
    {
        QRegularExpression pattern;  //高亮内容（正则表达式）
        QTextCharFormat format;  //高亮样式
    };
    QVector<HighlightingRule> highlightingRules;  //高亮规则向量（内含多个高亮规则）

    QTextCharFormat keywordFormat;  //关键词
    QTextCharFormat functionFormat;  //函数
    QTextCharFormat numberFormat;  //数字
    QTextCharFormat quotationFormat;  //引号
    QTextCharFormat singleLineCommentFormat;  //单行注释
};

#endif // HIGHLIGHTER_H
