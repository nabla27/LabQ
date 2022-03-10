#include "graphsettingwidget.h"

GraphSettingWidget::GraphSettingWidget(QWidget *parent)
    : QStackedWidget(parent)
{
    horizontalAxisSetting = new HorizontalAxisSetting(this);

    addWidget(horizontalAxisSetting);
}


/****************************
 * 水平方向の軸に関する設定項目
 ****************************
 *[共通の設定項目]
 *格子の可視性
 *  格子の色
 *ラベルの可視性
 *  ラベルの角度
 *  ラベルの色
 *  ラベルのサイズ
 *線の可視性
 *  線の色
 *最小値と最大値
 *リバース
 *タイトルの可視性
 *  タイトルのテキスト
 *  タイトルのサイズ
 *[ValueAxis]
 *Tickの間隔
 *Tickの数
 *MinorTickの数
 *[BarCategory]
 *各カテゴリ名
 *[Category]
 *カテゴリの追加
 *[DateTime]
 *tickの数
 *[LogValue]
 *底の値
 *minorTickの数
 *[Color]
 *サイズ
 *Tickの数
 *色
 *グラディエント
 */
AxisCommonSetting::AxisCommonSetting(QWidget *parent, Graph2D::AxisType type)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    rangeMin = new LineEditLayout(this, "Min");
    rangeMax = new LineEditLayout(this, "Max");
    titleVisible = new CheckBoxLayout(this, "Show title");
    axisTitle = new LineEditLayout(this, "Title");
    axisTitleSize = new SpinBoxEditLayout(this, "Title size");
    gridVisible = new CheckBoxLayout(this, "Show grid");
    gridColor = new ComboEditLayout(this, "Grid color");
    gridColorCustom = new RGBEditLayout(this);
    labelVisible = new CheckBoxLayout(this, "Show label");
    labelAngle = new LineEditLayout(this, "Label angle");
    labelSize = new SpinBoxEditLayout(this, "Label size");
    labelColor = new ComboEditLayout(this, "Label color");
    labelColorCustom = new RGBEditLayout(this);
    axisVisible = new CheckBoxLayout(this, "Show axisline");
    axisColor = new ComboEditLayout(this, "Axisline color");
    axisColorCustom = new RGBEditLayout(this);
    reverse = new CheckBoxLayout(this, "Reverse");

    layout->addLayout(rangeMin);
    layout->addLayout(rangeMax);
    layout->addLayout(titleVisible);
    layout->addLayout(axisTitle);
    layout->addLayout(axisTitleSize);
    layout->addLayout(gridVisible);
    layout->addLayout(gridColor);
    layout->addLayout(gridColorCustom);
    layout->addLayout(labelVisible);
    layout->addLayout(labelAngle);
    layout->addLayout(labelSize);
    layout->addLayout(labelColor);
    layout->addLayout(labelColorCustom);
    layout->addLayout(axisVisible);
    layout->addLayout(axisColor);
    layout->addLayout(axisColorCustom);
    layout->addLayout(reverse);
}


HorizontalAxisSetting::HorizontalAxisSetting(QWidget *parent)
    : QScrollArea(parent)
{
    /* このスクロールエリア */
    QWidget *contents = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(contents);
    setWidget(contents);
    setWidgetResizable(true);
    contents->setLayout(layout);
    /* 軸を追加する項目 */
    QGroupBox *addGroup = new QGroupBox("Add new Axis", this);
    QVBoxLayout *addGroupLayout = new QVBoxLayout(addGroup);
    axisType = new ComboEditLayout(addGroup, "Type");
    axisAlign = new ComboEditLayout(addGroup, "Align");
    addButton = new PushButtonLayout(addGroup, "Add");
    /* 軸の共通設定項目 */
    settingStack = new QStackedWidget(this);

    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

    layout->addWidget(addGroup);
    addGroupLayout->addLayout(axisType);
    addGroupLayout->addLayout(axisAlign);
    addGroupLayout->addLayout(addButton);
    layout->addWidget(settingStack);
    layout->addItem(spacer);

    settingStack->addWidget(new AxisCommonSetting(settingStack, Graph2D::AxisType::Value));

    axisType->insertComboItems(0, enumToStrings(Graph2D::AxisType(0)));
    axisAlign->insertComboItems(0, QStringList() << "Bottom" << "Top");
}
