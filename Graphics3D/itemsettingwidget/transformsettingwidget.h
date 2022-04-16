#ifndef TRANSFORMSETTINGWIDGET_H
#define TRANSFORMSETTINGWIDGET_H
#include <QWidget>
#include <Qt3DCore/QTransform>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>

class Layout3Dparam : public QHBoxLayout
{
    Q_OBJECT
public:
    explicit Layout3Dparam(const QString& name, QWidget *parent, const int labelWidth = 80);

public slots:
    void setV3Value(const QVector3D& vec);
    void setQuaternionValue(const QQuaternion& qut);
    void setX(const float& val) { editX->setText(QString::number(val)); }
    void setY(const float& val) { editY->setText(QString::number(val)); }
    void setZ(const float& val) { editZ->setText(QString::number(val)); }

private:
    QLineEdit *editX;
    QLineEdit *editY;
    QLineEdit *editZ;

private slots:
    void emitXEdited();
    void emitYEdited();
    void emitZEdited();

signals:
    void xEdited(const float& val);
    void yEdited(const float& val);
    void zEdited(const float& val);
    void xyzEditedVector(const QVector3D& vec);
    void xyzEditedQuaternion(const QQuaternion& qut);
};





class TransformSettingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TransformSettingWidget(Qt3DCore::QTransform *transform,
                                    QWidget *parent = nullptr);
public:
    void changeVisible() { setVisible(!isVisible()); }

signals:
};

#endif // TRANSFORMSETTINGWIDGET_H
