#include "highlighter.h"

//构造函数（添加语法高亮）
CppHighlighter::CppHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    /***********关键词*************/

    keywordFormat.setForeground(QColor(128,128,0));  //浅黄色
    QStringList keywordPatterns;  //列举关键词
    keywordPatterns << "\\bint\\b" << "\\bfloat\\b" << "\\bdouble\\b" << "\\bchar\\b"
                    << "\\bstruct\\b" << "\\benum\\b" << "\\bbool\\b" << "\\bvoid\\b"
                    << "\\bshort\\b" << "\\blong\\b" << "\\bsigned\\b" << "\\bunsigned\\b"
                    << "\\bfor\\b" << "\\bwhile\\b" << "\\bdo\\b" << "\\bbreak\\b"
                    << "\\bif\\b" << "\\belse\\b" << "\\bswitch\\b" << "\\bcase\\b"
                    << "\\btry\\b" << "\\bcatch\\b" << "\\bthrow\\b"
                    << "\\btrue\\b" << "\\bfalse\\b" << "\\bstatic\\b" << "\\bconst\\b"
                    << "\\bclass\\b" << "\\bnew\\b" << "\\bdelete\\b"
                    << "\\bprivate\\b" << "\\bpublic\\b" << "\\bprotected\\b" << "\\bfriend\\b"
                    << "\\bvirtual\\b" << "\\binline\\b" << "\\bexplicit\\b" << "\\bslots\\b"
                    << "\\bnamespace\\b" << "\\btemplate\\b" << "\\btypedef\\b"
                    << "\\boperator\\b" << "\\bnull\\b" << "\\bthis\\b"<< "\\breturn\\b";
    foreach (const QString &pattern, keywordPatterns)
    {
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    /***********函数*************/

    functionFormat.setFontItalic(true);  //斜体
    functionFormat.setFontWeight(75);  //粗体
    functionFormat.setForeground(QColor(9,46,100));  //蓝绿色
    rule.pattern = QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = functionFormat;
    highlightingRules.append(rule);

    /***********数字*************/

    numberFormat.setForeground(QColor(128,0,128));  //紫红色
    rule.pattern = QRegularExpression("\\b[0-9\\.]+\\b");
    rule.format = numberFormat;
    highlightingRules.append(rule);

    /***********引号*************/

    quotationFormat.setForeground(QColor(0,128,0));  //绿色
    rule.pattern = QRegularExpression("\".*\"|'.*'");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    /***********单行注释*************/

    singleLineCommentFormat.setForeground(QColor(153,153,153));  //灰色
    rule.pattern = QRegularExpression("//[^\n]*|#[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);
}

//清除语法高亮
void CppHighlighter::clearHighlight(void)
{
    highlightingRules.clear();
}

//重写基类的highlightBlock函数
void CppHighlighter::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, highlightingRules)
    {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext())
        {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
}
