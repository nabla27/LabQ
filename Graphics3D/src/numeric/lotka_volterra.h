#ifndef LOTKA_VOLTERRA_H
#define LOTKA_VOLTERRA_H

#include <QStringList>
#include <QPixmap>
#include "equation.h"
#include "boost/numeric/odeint.hpp"


namespace equation
{


    class LotkaVolterraSystem
    {
    public:
        LotkaVolterraSystem(const double& alpha,
                            const double& beta,
                            const double& gamma,
                            const double& delta)
            : alpha(alpha)
            , beta(beta)
            , gamma(gamma)
            , delta(delta) {}

        void operator()(State& x, State& dx, double)
        {
            dx[0] = x[0] * (alpha - beta * x[1]);
            dx[1] = -x[1] * (gamma - delta * x[0]);
        }

    private:
        double alpha;
        double beta;
        double gamma;
        double delta;
    };






    class LotkaVolterra : public QObject
    {
        Q_OBJECT

    public slots:
        static void solve(const equation::EquationParameter& p, equation::PositionObserver *observer)
        {










            LotkaVolterraSystem system(p.paramValue.at(0),
                                       p.paramValue.at(1),
                                       p.paramValue.at(2),
                                       p.paramValue.at(3));

            State state({p.initValue.at(0),
                         p.initValue.at(1),
                         p.initValue.at(2)});

            boost::numeric::odeint::euler<State> stepper;

            boost_integrate_const(p.algorithmType, system, state, p.startT, p.endT, p.step, std::ref(*observer));
        }

    public:
        static QStringList varList() { return QStringList() << "x1" << "x2" << "x3"; }
        static QStringList paramList() { return QStringList() << "α" << "β" << "γ" << "δ"; }
        static QPixmap equationPixmap() { return QPixmap(":/equation_lotka_volterra"); }
    };


}//namespace { calculate }

#endif // LOTKA_VOLTERRA_H
