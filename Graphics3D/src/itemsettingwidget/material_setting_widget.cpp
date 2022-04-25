#include "material_setting_widget.h"

static const int label_width_material = 100;

MaterialSettingWidget::MaterialSettingWidget(Qt3DRender::QMaterial *material,
                                             QWidget *parent)
    : QWidget(parent), material(material)
{
    QVBoxLayout *vLayout = new QVBoxLayout(this);
    materialCombo = new mlayout::ComboBoxLayout("Type", this, label_width_material);
    stackedWidget = new QStackedWidget(this);
    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

    setLayout(vLayout);
    vLayout->addLayout(materialCombo);
    vLayout->addWidget(stackedWidget);
    vLayout->addItem(spacer);

    materialCombo->setItems(QStringList()
                            << "Diffuse map"
                            << "Diffuse specular map"
                            << "Diffuse specular"
                            << "Gooch"
                            << "Metal rough"
                            << "Morph phong"
                            << "Normal diffuse map"
                            << "Normal diffuse specular map"
                            << "Per vertex color"
                            << "Phong alpha"
                            << "Phong"
                            << "Texture");

    diffuseMap = new DiffuseMapSettingWidget(this);
    diffuseSpecularMap = new DiffuseSpecularMapSettingWidget(this);
    diffuseSpecular = new DiffuseSpecularSettingWidget(this);
    gooch = new GoochSettingWidget(this);
    metalRough = new MetalRoughSettingWidget(this);
    morphPhong = new MorphPhongSettingWidget(this);
    normalDiffuseMap = new NormalDiffuseMapSettingWidget(this);
    normalDiffuseSpecularMap = new NormalDiffuseSpecularMapSettingWidget(this);
    perVertexColor = new PerVertexColorSettingWidget(this);
    phongAlpha = new PhongAlphaSettingWidget(this);
    phong = new PhongSettingWidget(this);
    texture = new TextureSettingWidget(this);

    stackedWidget->addWidget(diffuseMap);
    stackedWidget->addWidget(diffuseSpecularMap);
    stackedWidget->addWidget(diffuseSpecular);
    stackedWidget->addWidget(gooch);
    stackedWidget->addWidget(metalRough);
    stackedWidget->addWidget(morphPhong);
    stackedWidget->addWidget(normalDiffuseMap);
    stackedWidget->addWidget(normalDiffuseSpecularMap);
    stackedWidget->addWidget(perVertexColor);
    stackedWidget->addWidget(phongAlpha);
    stackedWidget->addWidget(phong);
    stackedWidget->addWidget(texture);

    materialCombo->setCurrentIndex(10);
    stackedWidget->setCurrentIndex(10);
    vLayout->setContentsMargins(0, 0, 0, 0);

    phong->initParameter(qobject_cast<Qt3DExtras::QPhongMaterial*>(material));

    connect(materialCombo, &mlayout::ComboBoxLayout::currentIndexChanged, this, &MaterialSettingWidget::changeMaterial);
}

void MaterialSettingWidget::changeMaterial(const int index)
{
    Qt3DRender::QMaterial *previousMaterial = material;
    Qt3DCore::QNode *pNode = material->parentNode();

    switch(index)
    {
    case 0:
        material = new Qt3DExtras::QDiffuseMapMaterial(pNode);
        diffuseMap->setMaterial(qobject_cast<Qt3DExtras::QDiffuseMapMaterial*>(material));
        break;
    case 1:
        material = new Qt3DExtras::QDiffuseSpecularMapMaterial(pNode);
        diffuseSpecularMap->setMaterial(qobject_cast<Qt3DExtras::QDiffuseSpecularMapMaterial*>(material));
        break;
    case 2:
        material = new Qt3DExtras::QDiffuseSpecularMaterial(pNode);
        diffuseSpecular->setMaterial(qobject_cast<Qt3DExtras::QDiffuseSpecularMaterial*>(material));
        break;
    case 3:
        material = new Qt3DExtras::QGoochMaterial(pNode);
        gooch->setMaterial(qobject_cast<Qt3DExtras::QGoochMaterial*>(material));
        break;
    case 4:
        material = new Qt3DExtras::QMetalRoughMaterial(pNode);
        metalRough->setMaterial(qobject_cast<Qt3DExtras::QMetalRoughMaterial*>(material));
        break;
    case 5:
        material = new Qt3DExtras::QMorphPhongMaterial(pNode);
        morphPhong->setMaterial(qobject_cast<Qt3DExtras::QMorphPhongMaterial*>(material));
        break;
    case 6:
        material = new Qt3DExtras::QNormalDiffuseMapMaterial(pNode);
        normalDiffuseMap->setMaterial(qobject_cast<Qt3DExtras::QNormalDiffuseMapMaterial*>(material));
        break;
    case 7:
        material = new Qt3DExtras::QNormalDiffuseSpecularMapMaterial(pNode);
        normalDiffuseSpecularMap->setMaterial(qobject_cast<Qt3DExtras::QNormalDiffuseSpecularMapMaterial*>(material));
        break;
    case 8:
        material = new Qt3DExtras::QPerVertexColorMaterial(pNode);
        perVertexColor->setMaterial(qobject_cast<Qt3DExtras::QPerVertexColorMaterial*>(material));
        break;
    case 9:
        material = new Qt3DExtras::QPhongAlphaMaterial(pNode);
        phongAlpha->setMaterial(qobject_cast<Qt3DExtras::QPhongAlphaMaterial*>(material));
        break;
    case 10:
        material = new Qt3DExtras::QPhongMaterial(pNode);
        phong->setMaterial(qobject_cast<Qt3DExtras::QPhongMaterial*>(material));
        break;
    case 11:
        material = new Qt3DExtras::QTextureMaterial(pNode);
        texture->setMaterial(qobject_cast<Qt3DExtras::QTextureMaterial*>(texture));
        break;
    default:
        break;
    }

    stackedWidget->setCurrentIndex(index);

    Qt3DCore::QEntity *entity = qobject_cast<Qt3DCore::QEntity*>(pNode);
    entity->removeComponent(previousMaterial);
    entity->addComponent(material);
    delete previousMaterial; previousMaterial = nullptr;
}




DiffuseMapSettingWidget::DiffuseMapSettingWidget(QWidget *parent)
    : QWidget(parent)
{

}

void DiffuseMapSettingWidget::setMaterial(Qt3DExtras::QDiffuseMapMaterial *material)
{

}




DiffuseSpecularMapSettingWidget::DiffuseSpecularMapSettingWidget(QWidget *parent)
    : QWidget(parent)
{

}

void DiffuseSpecularMapSettingWidget::setMaterial(Qt3DExtras::QDiffuseSpecularMapMaterial *material)
{

}




DiffuseSpecularSettingWidget::DiffuseSpecularSettingWidget(QWidget *parent)
    : QWidget(parent)
{

}

void DiffuseSpecularSettingWidget::setMaterial(Qt3DExtras::QDiffuseSpecularMaterial *material)
{

}




GoochSettingWidget::GoochSettingWidget(QWidget *parent)
    : QWidget(parent)
{

}

void GoochSettingWidget::setMaterial(Qt3DExtras::QGoochMaterial *material)
{

}




MetalRoughSettingWidget::MetalRoughSettingWidget(QWidget *parent)
    : QWidget(parent)
{

}

void MetalRoughSettingWidget::setMaterial(Qt3DExtras::QMetalRoughMaterial *material)
{

}




MorphPhongSettingWidget::MorphPhongSettingWidget(QWidget *parent)
    : QWidget(parent)
{

}

void MorphPhongSettingWidget::setMaterial(Qt3DExtras::QMorphPhongMaterial *material)
{

}




NormalDiffuseMapSettingWidget::NormalDiffuseMapSettingWidget(QWidget *parent)
{

}

void NormalDiffuseMapSettingWidget::setMaterial(Qt3DExtras::QNormalDiffuseMapMaterial *material)
{

}




NormalDiffuseSpecularMapSettingWidget::NormalDiffuseSpecularMapSettingWidget(QWidget *parent)
    : QWidget(parent)
{

}

void NormalDiffuseSpecularMapSettingWidget::setMaterial(Qt3DExtras::QNormalDiffuseSpecularMapMaterial *material)
{

}




PerVertexColorSettingWidget::PerVertexColorSettingWidget(QWidget *parent)
    : QWidget(parent)
{

}

void PerVertexColorSettingWidget::setMaterial(Qt3DExtras::QPerVertexColorMaterial *material)
{

}




PhongAlphaSettingWidget::PhongAlphaSettingWidget(QWidget *parent)
    : QWidget(parent)
{

}

void PhongAlphaSettingWidget::setMaterial(Qt3DExtras::QPhongAlphaMaterial *material)
{

}




PhongSettingWidget::PhongSettingWidget(QWidget *parent)
{
    QVBoxLayout *vLayout = new QVBoxLayout(this);
    ambient = new mlayout::ColorButtonLayout("Ambient", this, label_width_material);
    diffuse = new mlayout::ColorButtonLayout("Diffuse", this, label_width_material);
    specular = new mlayout::ColorButtonLayout("Specular", this, label_width_material);
    shininess = new mlayout::DoubleSbLayout("Shininess", this, label_width_material);
    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

    setLayout(vLayout);
    vLayout->addLayout(ambient);
    vLayout->addLayout(diffuse);
    vLayout->addLayout(specular);
    vLayout->addLayout(shininess);
    vLayout->addItem(spacer);

    shininess->setSpinBoxMaxValue(100000);

    vLayout->setContentsMargins(0, 0, 0, 0);
}

void PhongSettingWidget::setMaterial(Qt3DExtras::QPhongMaterial *material)
{
    material->setAmbient(ambient->getColor());
    material->setDiffuse(diffuse->getColor());
    material->setSpecular(specular->getColor());
    material->setShininess(shininess->value());

    connect(ambient, &mlayout::ColorButtonLayout::colorChanged, material, &Qt3DExtras::QPhongMaterial::setAmbient);
    connect(diffuse, &mlayout::ColorButtonLayout::colorChanged, material, &Qt3DExtras::QPhongMaterial::setDiffuse);
    connect(specular, &mlayout::ColorButtonLayout::colorChanged, material, &Qt3DExtras::QPhongMaterial::setSpecular);
    connect(shininess, &mlayout::DoubleSbLayout::valueChanged, material, &Qt3DExtras::QPhongMaterial::setShininess);
    connect(material, &Qt3DExtras::QPhongMaterial::ambientChanged, ambient, &mlayout::ColorButtonLayout::setColor);
    connect(material, &Qt3DExtras::QPhongMaterial::diffuseChanged, diffuse, &mlayout::ColorButtonLayout::setColor);
    connect(material, &Qt3DExtras::QPhongMaterial::specularChanged, specular, &mlayout::ColorButtonLayout::setColor);
    connect(material, &Qt3DExtras::QPhongMaterial::shininessChanged, shininess, &mlayout::DoubleSbLayout::setValue);
}

void PhongSettingWidget::initParameter(Qt3DExtras::QPhongMaterial *material)
{
    ambient->setColor(material->ambient());
    diffuse->setColor(material->diffuse());
    specular->setColor(material->diffuse());
    shininess->setValue(material->shininess());

    connect(ambient, &mlayout::ColorButtonLayout::colorChanged, material, &Qt3DExtras::QPhongMaterial::setAmbient);
    connect(diffuse, &mlayout::ColorButtonLayout::colorChanged, material, &Qt3DExtras::QPhongMaterial::setDiffuse);
    connect(specular, &mlayout::ColorButtonLayout::colorChanged, material, &Qt3DExtras::QPhongMaterial::setSpecular);
    connect(shininess, &mlayout::DoubleSbLayout::valueChanged, material, &Qt3DExtras::QPhongMaterial::setShininess);
    connect(material, &Qt3DExtras::QPhongMaterial::ambientChanged, ambient, &mlayout::ColorButtonLayout::setColor);
    connect(material, &Qt3DExtras::QPhongMaterial::diffuseChanged, diffuse, &mlayout::ColorButtonLayout::setColor);
    connect(material, &Qt3DExtras::QPhongMaterial::specularChanged, specular, &mlayout::ColorButtonLayout::setColor);
    connect(material, &Qt3DExtras::QPhongMaterial::shininessChanged, shininess, &mlayout::DoubleSbLayout::setValue);
}





TextureSettingWidget::TextureSettingWidget(QWidget *parent)
    : QWidget(parent)
{

}

void TextureSettingWidget::setMaterial(Qt3DExtras::QTextureMaterial *material)
{

}




















