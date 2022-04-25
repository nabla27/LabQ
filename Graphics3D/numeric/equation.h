#ifndef EQUATION_H
#define EQUATION_H

#include <QList>
#include <QMap>
#include <array>
#include <QDebug>

/* 以下のboostインクルードで<boost/mpl/bitand.hpp>が含まれるが、そのままでは
 * コンパイルエラーになる。これはmocかboostのバグが原因。
 * そのため、マクロを自分で追加する必要があった。詳細は以下を参照
 * https://bugreports.qt.io/browse/QBS-1632
 * (2022/04/24) boost1_76_0 qt6.2.3 windows QtCreatorMSVC2019
 */
#include "boost/numeric/odeint.hpp"


namespace equation
{
    using State = std::array<double, 3>;



    struct EquationParameter
    {
        QList<double> initValue = {};
        QList<double> paramValue = {};
        int algorithmType = 0;
        double startT = 0;
        double endT = 10;
        double step = 0.05;
    };





    class PositionObserver : public QObject
    {
        Q_OBJECT
    public:
        PositionObserver() : data(new QList<std::array<double, 4>>) {}
        ~PositionObserver() { delete data; }

        void operator()(const State& x, double t)
        {
            (*data)[count++] = std::array<double, 4>({t, x.at(0), x.at(1), x.at(2)});
            emit inProgress(count);
        }

        void setDataSize(const size_t size)
        {
            data->resize(size);
            emit dataSizeChanged(size);
        }

    public:
        QList<std::array<double, 4>> *data;
        size_t count = 0;

    signals:
        void inProgress(const size_t progress);
        void dataSizeChanged(const size_t size);
    };





    template<typename System, typename State, typename Time, typename Observer>
    static size_t boost_integrate_const(int stepperType, System system, State& start_state,
                           Time start_time, Time end_time, Time dt, Observer observer)
    {
        using namespace boost::numeric::odeint;
        switch(stepperType)
        {
        case 0: return integrate_const(euler<State>(), system, start_state, start_time, end_time, dt, observer);
        case 1: return integrate_const(modified_midpoint<State>(), system, start_state, start_time, end_time, dt, observer);
        case 2: return integrate_const(runge_kutta4<State>(), system, start_state, start_time, end_time, dt, observer);
        case 3: return integrate_const(runge_kutta_cash_karp54<State>(), system, start_state, start_time, end_time, dt, observer);
        case 4: return integrate_const(runge_kutta_fehlberg78<State>(), system, start_state, start_time, end_time, dt, observer);
        case 5: return integrate_const(bulirsch_stoer<State>(), system, start_state, start_time, end_time, dt, observer);
        case 6: return integrate_const(bulirsch_stoer_dense_out<State>(), system, start_state, start_time, end_time, dt, observer);
        //case 4: return integrate_const(runge_kutta_dopri5<State>(), system, start_state, start_time, end_time, dt, observer);
        //case 6: return integrate_const(controlled_runge_kutta<State>(), system, start_state, start_time, end_time, dt, observer);
        //case 7: return integrate_const(dense_output_runge_kutta<State>(), system, start_state, start_time, end_time, dt, observer);
        //case 10: return integrate_const(implicit_euler<State>(), system, start_state, start_time, end_time, dt, observer);
        //case 11: return integrate_const(rosenbrock4<State>(), system, start_state, start_time, end_time, dt, observer);
        //case 12: return integrate_const(rosenbrock4_controller<State>(), system, start_state, start_time, end_time, dt, observer);
        //case 13: return integrate_const(rosenbrock4_dense_output<State>(), system, start_state, start_time, end_time, dt, observer);
        //case 14: return integrate_const(symplectic_euler<State>(), system, start_state, start_time, end_time, dt, observer);
        //case 15: return integrate_const(symplectic_rkn_sb3a_mclachlan<State>(), system, start_state, start_time, end_time, dt, observer);
        default: qDebug() << "Invalid index " << __FILE__ << __LINE__; return -1;
        }
    }


    inline QStringList stepperAlgorithmList()
    {
        QStringList list;
        list << "euler"
             << "modified modipoint"
             << "runge kutta4"
             << "runge kutta cash karp54"
             << "runge kutta fehlberg78"
             << "bulirsch stoer"
             << "bulirsch stoer dense out";
        return list;
    }

}



class FormulaExp
{
public:
    FormulaExp(const QString& formula);

public:
    const double calculate();
    QMap<QString, double> variableList = { {"pi", 3.141592653589793238} };
    static QMap<QString, int> operatorList;

private:
    const double applyLOperator(const QString& ope, const double& val1, const double& val2);
    const double applyROperator(const QString& ope, const double& val);

private:
    QList<QString> tokenList;
};

inline const double FormulaExp::applyLOperator(const QString &ope, const double& val1, const double& val2)
{
    if(ope == "+") return val1 + val2;
    else if(ope == "-") return val1 - val2;
    else if(ope == "*") return val1 * val2;
    else if(ope == "/") return val1 / val2;
    else if(ope == "^") return pow(val1, val2);
    else return NAN;
}

inline const double FormulaExp::applyROperator(const QString &ope, const double& val)
{
    if(ope == "sqrt") return sqrt(val);
    else if(ope == "sin") return sin(val);
    else if(ope == "cos") return cos(val);
    else if(ope == "tan") return tan(val);
    else if(ope == "abs") return (val > 0) ? val : -val;
    else if(ope == "log") return log10(val);
    else if(ope == "ln") return log(val);
    else return NAN;
}


#endif // EQUATION_H
