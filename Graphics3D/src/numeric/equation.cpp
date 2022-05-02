#include "equation.h"

QMap<QString, int> FormulaExp::operatorList =
{
    {"+", -4},
    {"-", -4},
    {"*", -3},
    {"/", -3},
    {"^", -2},
    {"sqrt", 2},
    {"sin", 2},
    {"cos", 2},
    {"tan", 2},
    {"abs", 2},
    {"log", 2},
    {"ln", 2},
};



FormulaExp::FormulaExp(const QString& formula)
{
    if(formula.isEmpty()) return;

    enum class TokenType{ Operator, Value, Bracket, Other, Init };
    TokenType previousT = TokenType::Init, currentT = TokenType::Init;
    qsizetype index = -1;

    for(const QChar& c : formula)
    {
        if(c == ' ') continue;

        if(operatorList.contains(c)) currentT = TokenType::Operator;
        else if(c.isDigit() || c == '.') currentT = TokenType::Value;
        else if(c == '(' || c == ')') currentT = TokenType::Bracket;
        else currentT = TokenType::Other;

        if(currentT != previousT){
            tokenList.append(c);
            index++;
        }
        else
            tokenList[index].append(c);

        previousT = currentT;
    }

    const QString firstToken = tokenList.constFirst();
    if(operatorList.contains(firstToken) && operatorList.value(firstToken) < 0)
        tokenList.push_front("0");
}

double FormulaExp::calculate()
{
    QVector<QString> operatorStack;
    QList<double> valueStack;

    for(const QString& token : tokenList)
    {
        if(token.at(0).isDigit())
            valueStack.append(token.toDouble());
        else if(operatorList.contains(token))
        {
            while(operatorStack.size() > 0)
            {
                const QString lastOperator = operatorStack.takeLast();
                if(operatorList.contains(lastOperator) &&
                   operatorList.value(token) <= operatorList.value(lastOperator))
                {
                    if(operatorList.value(lastOperator) > 0)
                        valueStack.append(applyROperator(lastOperator, valueStack.takeLast()));
                    else
                    {
                        const double val2 = valueStack.takeLast();
                        const double val1 = valueStack.takeLast();
                        valueStack.append(applyLOperator(lastOperator, val1, val2));
                    }
                }
                else
                {
                    operatorStack.append(lastOperator);
                    break;
                }
            }
            operatorStack.append(token);
        }
        else if(token == "(")
            operatorStack.append(token);
        else if(token == ")")
        {
            while(operatorStack.size() > 0)
            {
                const QString ope = operatorStack.takeLast();
                if(ope == "(") break;
                else
                {
                    if(operatorList.value(ope) > 0)
                        valueStack.append(applyROperator(ope, valueStack.takeLast()));
                    else
                    {
                        const double val2 = valueStack.takeLast();
                        const double val1 = valueStack.takeLast();
                        valueStack.append(applyLOperator(ope, val1, val2));
                    }
                }
            }
        }
        else
            valueStack.append(variableList.value(token));
    }

    while(operatorStack.size() > 0)
    {
        const QString ope = operatorStack.takeLast();
        if(operatorList.contains(ope))
        {
            if(operatorList.value(ope) > 0)
                valueStack.append(applyROperator(ope, valueStack.takeLast()));
            else
            {
                const double val2 = valueStack.takeLast();
                const double val1 = valueStack.takeLast();
                valueStack.append(applyLOperator(ope, val1, val2));
            }
        }
    }

    if(valueStack.isEmpty())
        return 0;
    else
        return valueStack.takeFirst();
}
