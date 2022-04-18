#ifndef MATERIALSETTINGWIDGET_H
#define MATERIALSETTINGWIDGET_H
#include <QWidget>
#include <Qt3DCore/QEntity>
#include <Qt3DRender/QMaterial>
#include <Qt3DExtras/QDiffuseMapMaterial>
#include <Qt3DExtras/QDiffuseSpecularMapMaterial>
#include <Qt3DExtras/QDiffuseSpecularMaterial>
#include <Qt3DExtras/QGoochMaterial>
#include <Qt3DExtras/QMetalRoughMaterial>
#include <Qt3DExtras/QMorphPhongMaterial>
#include <Qt3DExtras/QNormalDiffuseMapMaterial>
#include <Qt3DExtras/QNormalDiffuseSpecularMapMaterial>
#include <Qt3DExtras/QPerVertexColorMaterial>
#include <Qt3DExtras/QPhongAlphaMaterial>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QTextureMaterial>

#include <QColorDialog>
#include "layoutparts.h"

class DiffuseMapSettingWidget;
class DiffuseSpecularMapSettingWidget;
class DiffuseSpecularSettingWidget;
class GoochSettingWidget;
class MetalRoughSettingWidget;
class MorphPhongSettingWidget;
class NormalDiffuseMapSettingWidget;
class NormalDiffuseSpecularMapSettingWidget;
class PerVertexColorSettingWidget;
class PhongAlphaSettingWidget;
class PhongSettingWidget;
class TextureSettingWidget;

class MaterialSettingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MaterialSettingWidget(Qt3DRender::QMaterial *material, QWidget *parent);
    void changeVisible() { setVisible(!isVisible()); }

private slots:
    void changeMaterial(const int index);

private:
    Qt3DRender::QMaterial *material;
    mlayout::ComboBoxLayout *materialCombo;
    QStackedWidget *stackedWidget;

    DiffuseMapSettingWidget *diffuseMap;
    DiffuseSpecularMapSettingWidget *diffuseSpecularMap;
    DiffuseSpecularSettingWidget *diffuseSpecular;
    GoochSettingWidget *gooch;
    MetalRoughSettingWidget *metalRough;
    MorphPhongSettingWidget *morphPhong;
    NormalDiffuseMapSettingWidget *normalDiffuseMap;
    NormalDiffuseSpecularMapSettingWidget *normalDiffuseSpecularMap;
    PerVertexColorSettingWidget *perVertexColor;
    PhongAlphaSettingWidget *phongAlpha;
    PhongSettingWidget *phong;
    TextureSettingWidget *texture;

signals:

};

class DiffuseMapSettingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DiffuseMapSettingWidget(QWidget *parent);
    void setMaterial(Qt3DExtras::QDiffuseMapMaterial *material);
};

class DiffuseSpecularMapSettingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DiffuseSpecularMapSettingWidget(QWidget *parent);
    void setMaterial(Qt3DExtras::QDiffuseSpecularMapMaterial *material);
};

class DiffuseSpecularSettingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DiffuseSpecularSettingWidget(QWidget *parent);
    void setMaterial(Qt3DExtras::QDiffuseSpecularMaterial *material);
};

class GoochSettingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GoochSettingWidget(QWidget *parent);
    void setMaterial(Qt3DExtras::QGoochMaterial *material);
};

class MetalRoughSettingWidget : public QWidget
{
    Q_OBJECT
public:
    MetalRoughSettingWidget(QWidget *parent);
    void setMaterial(Qt3DExtras::QMetalRoughMaterial *material);
};

class MorphPhongSettingWidget : public QWidget
{
    Q_OBJECT
public:
    MorphPhongSettingWidget(QWidget *parent);
    void setMaterial(Qt3DExtras::QMorphPhongMaterial *material);
};

class NormalDiffuseMapSettingWidget : public QWidget
{
    Q_OBJECT
public:
    NormalDiffuseMapSettingWidget(QWidget *parent);
    void setMaterial(Qt3DExtras::QNormalDiffuseMapMaterial *material);
};

class NormalDiffuseSpecularMapSettingWidget : public QWidget
{
    Q_OBJECT
public:
    NormalDiffuseSpecularMapSettingWidget(QWidget *parent);
    void setMaterial(Qt3DExtras::QNormalDiffuseSpecularMapMaterial *material);
};

class PerVertexColorSettingWidget : public QWidget
{
    Q_OBJECT
public:
    PerVertexColorSettingWidget(QWidget *parent);
    void setMaterial(Qt3DExtras::QPerVertexColorMaterial *material);
};

class PhongAlphaSettingWidget : public QWidget
{
    Q_OBJECT
public:
    PhongAlphaSettingWidget(QWidget *parent);
    void setMaterial(Qt3DExtras::QPhongAlphaMaterial *material);
};

class PhongSettingWidget : public QWidget
{
    Q_OBJECT
public:
    PhongSettingWidget(QWidget *parent);
    void setMaterial(Qt3DExtras::QPhongMaterial *material);
    void initParameter(Qt3DExtras::QPhongMaterial *material);

private:
    mlayout::ColorButtonLayout *ambient;
    mlayout::ColorButtonLayout *diffuse;
    mlayout::ColorButtonLayout *specular;
    mlayout::DoubleSbLayout *shininess;
};

class TextureSettingWidget : public QWidget
{
    Q_OBJECT
public:
    TextureSettingWidget(QWidget *parent);
    void setMaterial(Qt3DExtras::QTextureMaterial *material);
};

#endif // MATERIALSETTINGWIDGET_H
