#ifndef WAVE_H
#define WAVE_H

#include "../numeric/pde.h"


namespace equation
{

    class WaveEquation : public PDEquation
    {
        Q_OBJECT
    public:
        WaveEquation(QObject *parent) : PDEquation(parent) {}

    public slots:
        void calculate() override
        {
            QVector<float> pre(init);
            QVector<float> current(init);
            QVector<float> next(init);

            const size_t col = horizontalGridCount;
            const size_t row_1 = verticalGridCount - 1;
            const size_t col_1 = col - 1;
            const float cof = dt * dt * constant.at(0) * constant.at(0) / (dx * dx);

            size_t step = 0;

            do
            {
                for(size_t i = 1; i < row_1; ++i){
                    for(size_t j = 1; j < col_1; ++j)
                    {
                        const size_t index = col * i + j;

                        /* 5点差分格子 */
                        const float u = current.at(index);
                        const float left = current.at(col * i + (j - 1));
                        const float right = current.at(col * i + (j + 1));
                        const float top = current.at(col * (i - 1) + j);
                        const float bottom = current.at(col * (i + 1) + j);

                        /* 更新 */
                        next[index] = u + u - pre.at(index) + cof * (-4.0f * u + left + right + top + bottom);
                    }
                }

                emit stepChanged(step);
                emit stateChanged(current, step);

                pre.swap(current);
                current.swap(next);

                step++;

            } while(step < stepCount);

            emit finished();
        }
    };

}

#endif // WAVE_H
