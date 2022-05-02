#ifndef DYNAMICSURFACECONTROLLER_H
#define DYNAMICSURFACECONTROLLER_H
#include <QObject>
#include "../custommesh/surfacegridgeometry.h"
#include "../numeric/equation.h"

class DynamicSurfaceController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(SurfaceGridMesh *target READ target WRITE setTarget NOTIFY targetChanged)
    Q_PROPERTY(float step READ step WRITE setStep NOTIFY stepChanged)

public:
    explicit DynamicSurfaceController(QObject *parent = nullptr);

    void setTarget(SurfaceGridMesh *geometry);
    void setStep(const float step);

    SurfaceGridMesh* target() const { return _target; }
    float step() const { return _step; }
    void setStateCount(const qsizetype size) { data.resize(size); }
    const QVector<float>& firstState() const { return data.at(0); }

public slots:
    void receiveData(const QVector<float>& state, const qsizetype index)
    { data[index] = state; }

private:
    SurfaceGridMesh *_target;
    float _step;
    QVector<QVector<float>> data;

signals:
    void targetChanged();
    void stepChanged();
};

#endif // DYNAMICSURFACECONTROLLER_H
