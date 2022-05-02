#ifndef PDE_H
#define PDE_H
#include <QVector>
#include <QObject>
#include "equation.h"

namespace equation
{



class PDEquation : public QObject
{
    Q_OBJECT
public:
    PDEquation(QObject *parent) : QObject(parent) {}
    ~PDEquation() {}

public slots:
    virtual void calculate() {}

public:
    void setGridWidth(const float& dx) { this->dx = dx; }
    void setStartTime(const float& startT) { this->startT = startT; }
    void setDeltaTime(const float& dt) { this->dt = dt; }
    void setConstantValue(const QVector<float>& constant) { this->constant = constant; }
    void setStepCount(const size_t& steps) { stepCount = steps; }
    void setInitializeState(const QVector<float>& init, const size_t& row, const size_t& col)
    { this->init = init; horizontalGridCount = col; verticalGridCount = row; }

public:
    PDEquation& operator=(const PDEquation& eq)
    {
        horizontalGridCount = eq.horizontalGridCount;
        verticalGridCount = eq.verticalGridCount;
        startT = eq.startT;
        dt = eq.dt;
        dx = eq.dx;
        constant = eq.constant;
        stepCount = eq.stepCount;
        init = eq.init;

        return *this;
    }

protected:
    size_t horizontalGridCount;
    size_t verticalGridCount;
    float startT;
    float dt;
    float dx;
    QVector<float> constant;
    size_t stepCount;
    QVector<float> init;

signals:
    void stepChanged(const size_t& step);
    void stateChanged(const QVector<float>& state, const qsizetype& step);
    void finished();
};



/*    __________ +x (col)
 *   |
 *   |
 *   |
 *   |
 *  +z
 * (row)
 */


class InitWithFormulaExpCondition : public QObject
{
    Q_OBJECT
public:
    InitWithFormulaExpCondition(QObject *parent) : QObject(parent) {}

    struct Range
    {
        QPair<float, bool> xl = {0.0f, false};
        QPair<float, bool> xr = {0.0f, false};
        QPair<float, bool> zl = {0.0f, false};
        QPair<float, bool> zr = {0.0f, false};
    };

public slots:
    void calculate(const QList<InitWithFormulaExpCondition::Range>& range,
                   const QStringList& condition,
                   const qsizetype row,
                   const qsizetype col,
                   const float dx)
    {
        const qsizetype conditionCount = range.count();

        QVector<float> init(row * col);

        for(qsizetype index = 0; index < conditionCount; ++index)
        {
            FormulaExp exp(condition.at(index));

            for(qsizetype i = 0; i < row; ++i)
            {
                //const float z = - (row - 1) / 2.0f * dx + dx * i;
                const float z = - dx * ((row - 1) / 2.0f - i);

                if(range.at(index).zl.second) if(z < range.at(index).zl.first) continue;
                if(range.at(index).zr.second) if(z > range.at(index).zr.first) continue;

                exp.variableList.insert("z", z);

                for(qsizetype j = 0; j < col; ++j)
                {
                    //const float x = - (col - 1) / 2.0f  * dx + dx * j;
                    const float x = - dx * ((col - 1) / 2.0f - j);

                    if(range.at(index).xl.second) if(x < range.at(index).xl.first) continue;
                    if(range.at(index).xr.second) if(x > range.at(index).xr.first) continue;

                    exp.variableList.insert("x", x);

                    init[col * i + j] = exp.calculate();
                }
            }
        }

        emit calculated(init);
    }

signals:
    void requestCalculation(const QList<InitWithFormulaExpCondition::Range>& range,
                            const QStringList& condition,
                            const qsizetype row,
                            const qsizetype col,
                            const float dx);
    void calculated(const QVector<float>& init);
};


}

#endif // PDE_H
