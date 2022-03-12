#include "graphsettingwidget.h"

static const int labelWidth = SETTING_LABEL_WIDTH + 20;

GraphSettingWidget::GraphSettingWidget(QWidget *parent)
    : QStackedWidget(parent)
{
    generalSetting = new GeneralSetting(this);
    axisSetting = new AxisSetting(this);

    addWidget(generalSetting);
    addWidget(axisSetting);
}


/****************************
 * 水平方向の軸に関する設定項目
 ****************************
 *[共通の設定項目]
 *格子の可視性
 *  色
 *ラベルの可視性
 *  角度/色/サイズ
 *線の可視性
 *  色
 *最小値と最大値
 *リバース
 *タイトルの可視性
 *  テキスト/サイズ
 *[ValueAxis]
 *Tickの間隔/Tickの数/MinorTickの数
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
 *サイズ/Tickの数/色/グラディエント
 */
AxisCommonSetting::AxisCommonSetting(QWidget *parent, QAbstractAxis *const axis)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    rangeMin = new LineEditLayout(this, "Min", labelWidth);
    rangeMax = new LineEditLayout(this, "Max", labelWidth);
    titleVisible = new CheckBoxLayout(this, "Show title", labelWidth);
    axisTitle = new LineEditLayout(this, "Title", labelWidth);
    axisTitleSize = new SpinBoxEditLayout(this, "Title size", labelWidth);
    gridVisible = new CheckBoxLayout(this, "Show grid", labelWidth);
    gridColor = new ComboEditLayout(this, "Grid color", labelWidth);
    gridColorCustom = new RGBEditLayout(this, labelWidth);
    labelVisible = new CheckBoxLayout(this, "Show label", labelWidth);
    labelAngle = new LineEditLayout(this, "Label angle", labelWidth, SETTING_EDIT_SWIDTH);
    labelSize = new SpinBoxEditLayout(this, "Label size", labelWidth);
    labelColor = new ComboEditLayout(this, "Label color", labelWidth);
    labelColorCustom = new RGBEditLayout(this, labelWidth);
    axisVisible = new CheckBoxLayout(this, "Show axisline", labelWidth);
    axisColor = new ComboEditLayout(this, "Axisline color", labelWidth);
    axisColorCustom = new RGBEditLayout(this, labelWidth);
    reverse = new CheckBoxLayout(this, "Reverse", labelWidth);

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

    connect(rangeMin, &LineEditLayout::lineValueEdited, this, &AxisCommonSetting::rangeMinSet);
    connect(rangeMax, &LineEditLayout::lineValueEdited, this, &AxisCommonSetting::rangeMaxSet);
    connect(titleVisible, &CheckBoxLayout::checkBoxToggled, this, &AxisCommonSetting::titleVisibleChanged);
    connect(axisTitle, &LineEditLayout::lineTextEdited, this, &AxisCommonSetting::titleSet);
    connect(axisTitleSize, &SpinBoxEditLayout::spinBoxValueChanged, this, &AxisCommonSetting::titleSizeSet);
    connect(gridVisible, &CheckBoxLayout::checkBoxToggled, this, &AxisCommonSetting::gridVisibleChanged);
    connect(gridColor, &ComboEditLayout::currentComboIndexChanged, gridColorCustom, &RGBEditLayout::setColorAndEditable);
    connect(gridColorCustom, &RGBEditLayout::colorEdited, this, &AxisCommonSetting::gridColorSet);
    connect(labelVisible, &CheckBoxLayout::checkBoxToggled, this, &AxisCommonSetting::labelVisibleChanged);
    connect(labelAngle, &LineEditLayout::lineValueEdited, this, &AxisCommonSetting::labelAngleSet);
    connect(labelSize, &SpinBoxEditLayout::spinBoxValueChanged, this, &AxisCommonSetting::labelSizeSet);
    connect(labelColor, &ComboEditLayout::currentComboIndexChanged, labelColorCustom, &RGBEditLayout::setColorAndEditable);
    connect(labelColorCustom, &RGBEditLayout::colorEdited, this, &AxisCommonSetting::labelColorSet);
    connect(axisVisible, &CheckBoxLayout::checkBoxToggled, this, &AxisCommonSetting::axisVisibleChanged);
    connect(axisColor, &ComboEditLayout::currentComboIndexChanged, axisColorCustom, &RGBEditLayout::setColorAndEditable);
    connect(axisColorCustom, &RGBEditLayout::colorEdited, this, &AxisCommonSetting::axisColorSet);
    connect(reverse, &CheckBoxLayout::checkBoxToggled, this, &AxisCommonSetting::reverseChanged);

    titleVisible->setChecked(axis->isTitleVisible());
    axisTitleSize->setSpinBoxValue(axis->titleFont().pointSize());
    gridVisible->setChecked(axis->isGridLineVisible());
    gridColor->setComboCurrentIndex(QT_GLOBAL_COLOR_COUNT + 1);
    gridColorCustom->setColor(axis->gridLineColor());
    labelVisible->setChecked(axis->isLineVisible());
    labelAngle->setLineEditValue(axis->labelsAngle());
    labelSize->setSpinBoxValue(axis->labelsFont().pointSize());
    labelColor->setComboCurrentIndex(QT_GLOBAL_COLOR_COUNT + 1);
    labelColorCustom->setColor(axis->labelsColor());
    axisVisible->setChecked(axis->isLineVisible());
    axisColor->setComboCurrentIndex(QT_GLOBAL_COLOR_COUNT + 1);
    axisColorCustom->setColor(axis->linePenColor());
    gridColor->insertComboItems(0, colorNameList());
    labelColor->insertComboItems(0, colorNameList());
    axisColor->insertComboItems(0, colorNameList());

    const QAbstractAxis::AxisType type = axis->type();
    switch(type)
    {
    case QAbstractAxis::AxisTypeValue:
    {
        LineEditLayout *tickAnchor = new LineEditLayout(this, "Tich anchor", labelWidth, SETTING_EDIT_SWIDTH);
        LineEditLayout *tickCount = new LineEditLayout(this, "Tick count", labelWidth, SETTING_EDIT_SWIDTH);
        LineEditLayout *tickInterval = new LineEditLayout(this, "Tick interval", labelWidth, SETTING_EDIT_SWIDTH);
        LineEditLayout *minorTickCount = new LineEditLayout(this, "MinorTick count", labelWidth, SETTING_EDIT_SWIDTH);
        layout->addLayout(tickAnchor);
        layout->addLayout(tickCount);
        layout->addLayout(tickInterval);
        layout->addLayout(minorTickCount);

        QValueAxis *valueAxis = qobject_cast<QValueAxis*>(axis);

        rangeMin->setLineEditValue(valueAxis->min());
        rangeMax->setLineEditValue(valueAxis->max());
        tickAnchor->setLineEditValue(valueAxis->tickAnchor());
        tickCount->setLineEditValue(valueAxis->tickCount());
        tickInterval->setLineEditValue(valueAxis->tickInterval());
        minorTickCount->setLineEditValue(valueAxis->minorTickCount());

        connect(tickAnchor, &LineEditLayout::lineValueEdited, valueAxis, &QValueAxis::setTickAnchor);
        connect(valueAxis, &QValueAxis::tickAnchorChanged, tickAnchor, &LineEditLayout::setLineEditValue);
        connect(tickCount, &LineEditLayout::lineValueEdited, valueAxis, &QValueAxis::setTickCount);
        connect(valueAxis, &QValueAxis::tickCountChanged, tickCount, &LineEditLayout::setLineEditValue);
        connect(tickInterval, &LineEditLayout::lineValueEdited, valueAxis, &QValueAxis::setTickInterval);
        connect(valueAxis, &QValueAxis::tickIntervalChanged, tickInterval, &LineEditLayout::setLineEditValue);
        connect(minorTickCount, &LineEditLayout::lineValueEdited, valueAxis, &QValueAxis::setMinorTickCount);
        connect(valueAxis, &QValueAxis::minorTickCountChanged, minorTickCount, &LineEditLayout::setLineEditValue);
        connect(rangeMin, &LineEditLayout::lineValueEdited, valueAxis, &QValueAxis::setMin);
        connect(rangeMax, &LineEditLayout::lineValueEdited, valueAxis, &QValueAxis::setMax);
        connect(valueAxis, &QValueAxis::minChanged, rangeMin, &LineEditLayout::setLineEditValue);
        connect(valueAxis, &QValueAxis::maxChanged, rangeMax, &LineEditLayout::setLineEditValue);
        break;
    }
    case QAbstractAxis::AxisTypeBarCategory:
    {
        QBarCategoryAxis *barCategoryAxis = qobject_cast<QBarCategoryAxis*>(axis);

        rangeMin->setLineEditText(barCategoryAxis->min());
        rangeMax->setLineEditText(barCategoryAxis->max());

        connect(rangeMin, &LineEditLayout::lineTextEdited, barCategoryAxis, &QBarCategoryAxis::setMin);
        connect(rangeMax, &LineEditLayout::lineTextEdited, barCategoryAxis, &QBarCategoryAxis::setMax);
        connect(barCategoryAxis, &QBarCategoryAxis::minChanged, rangeMin, &LineEditLayout::setLineEditText);
        connect(barCategoryAxis, &QBarCategoryAxis::maxChanged, rangeMax, &LineEditLayout::setLineEditText);
        break;
    }
    case QAbstractAxis::AxisTypeCategory:
    {
        QLabel *categoryLabel = new QLabel("Category");
        QSpacerItem *space = new QSpacerItem(0, 30, QSizePolicy::Minimum, QSizePolicy::Minimum);
        QHBoxLayout *addCategoryLayout = new QHBoxLayout;
        QLineEdit *categoryName = new QLineEdit(this);
        QLineEdit *categoryValue = new QLineEdit(this);
        QPushButton *categoryAddButton = new QPushButton("Add");
        QHBoxLayout *removeCategoryLayout = new QHBoxLayout;
        QComboBox *categoryNameForRemove = new QComboBox;
        QPushButton *categoryRemoveButton = new QPushButton("Remove");
        layout->addItem(space);
        layout->addWidget(categoryLabel);
        layout->addLayout(addCategoryLayout);
        addCategoryLayout->addWidget(categoryName);
        addCategoryLayout->addWidget(categoryValue);
        addCategoryLayout->addWidget(categoryAddButton);
        layout->addLayout(removeCategoryLayout);
        removeCategoryLayout->addWidget(categoryNameForRemove);
        removeCategoryLayout->addWidget(categoryRemoveButton);
        categoryValue->setMaximumWidth(SETTING_EDIT_SWIDTH);
        categoryAddButton->setMaximumWidth(SETTING_EDIT_SWIDTH + 20);
        categoryRemoveButton->setMaximumWidth(SETTING_EDIT_SWIDTH + 20);

        QCategoryAxis *categoryAxis = qobject_cast<QCategoryAxis*>(axis);

        rangeMin->setLineEditValue(categoryAxis->min());
        rangeMax->setLineEditValue(categoryAxis->max());

        auto addCategory = [categoryAxis, categoryName, categoryValue, categoryNameForRemove](){
            categoryAxis->append(categoryName->text(), categoryValue->text().toDouble());
            categoryNameForRemove->insertItem(0, categoryName->text());
        };
        auto removeCategory = [categoryAxis, categoryNameForRemove]()
        {
            categoryAxis->remove(categoryNameForRemove->currentText());
            categoryNameForRemove->removeItem(categoryNameForRemove->currentIndex());
        };
        connect(categoryAddButton, &QPushButton::released, addCategory);
        connect(categoryRemoveButton, &QPushButton::released, removeCategory);
        connect(rangeMin, &LineEditLayout::lineValueEdited, categoryAxis, &QCategoryAxis::setMin);
        connect(rangeMax, &LineEditLayout::lineValueEdited, categoryAxis, &QCategoryAxis::setMax);
        connect(categoryAxis, &QCategoryAxis::minChanged, rangeMin, &LineEditLayout::setLineEditValue);
        connect(categoryAxis, &QCategoryAxis::maxChanged, rangeMax, &LineEditLayout::setLineEditValue);
        break;
    }
    case QAbstractAxis::AxisTypeDateTime:
    {
        LineEditLayout *tickCount = new LineEditLayout(this, "Tick count", labelWidth, SETTING_EDIT_SWIDTH);
        layout->addLayout(tickCount);

        QDateTimeAxis *dateAxis = qobject_cast<QDateTimeAxis*>(axis);

        rangeMin->setLineEditDate(dateAxis->min());
        rangeMax->setLineEditDate(dateAxis->max());
        tickCount->setLineEditValue(dateAxis->tickCount());

        connect(tickCount, &LineEditLayout::lineValueEdited, dateAxis, &QDateTimeAxis::setTickCount);
        connect(dateAxis, &QDateTimeAxis::tickCountChanged, tickCount, &LineEditLayout::setLineEditValue);
        connect(rangeMin, &LineEditLayout::lineDateEdited, dateAxis, &QDateTimeAxis::setMin);
        connect(rangeMax, &LineEditLayout::lineDateEdited, dateAxis, &QDateTimeAxis::setMax);
        connect(dateAxis, &QDateTimeAxis::minChanged, rangeMin, &LineEditLayout::setLineEditDate);
        connect(dateAxis, &QDateTimeAxis::maxChanged, rangeMax, &LineEditLayout::setLineEditDate);
        break;
    }
    case QAbstractAxis::AxisTypeLogValue:
    {
        LineEditLayout *baseValue = new LineEditLayout(this, "Base", labelWidth);
        LineEditLayout *minorTickCount = new LineEditLayout(this, "MinorTick count", labelWidth, SETTING_EDIT_SWIDTH);
        layout->addLayout(baseValue);
        layout->addLayout(minorTickCount);

        QLogValueAxis *logAxis = qobject_cast<QLogValueAxis*>(axis);

        rangeMin->setLineEditValue(logAxis->min());
        rangeMax->setLineEditValue(logAxis->max());
        baseValue->setLineEditValue(logAxis->base());
        minorTickCount->setLineEditValue(logAxis->minorTickCount());

        connect(baseValue, &LineEditLayout::lineValueEdited, logAxis, &QLogValueAxis::setBase);
        connect(minorTickCount, &LineEditLayout::lineValueEdited, logAxis, &QLogValueAxis::setMinorTickCount);
        connect(logAxis, &QLogValueAxis::minorTickCountChanged, minorTickCount, &LineEditLayout::setLineEditValue);
        connect(rangeMin, &LineEditLayout::lineValueEdited, logAxis, &QLogValueAxis::setMin);
        connect(rangeMax, &LineEditLayout::lineValueEdited, logAxis, &QLogValueAxis::setMax);
        connect(logAxis, &QLogValueAxis::minChanged, rangeMin, &LineEditLayout::setLineEditValue);
        connect(logAxis, &QLogValueAxis::maxChanged, rangeMax, &LineEditLayout::setLineEditValue);
        break;
    }
    case QAbstractAxis::AxisTypeColor:
    {
        LineEditLayout *tickCount = new LineEditLayout(this, "Tick count", labelWidth, SETTING_EDIT_SWIDTH);
        LineEditLayout *size = new LineEditLayout(this, "Size", labelWidth, SETTING_EDIT_SWIDTH);
        layout->addLayout(tickCount);
        layout->addLayout(size);

        QColorAxis *colorAxis = qobject_cast<QColorAxis*>(axis);

        rangeMin->setLineEditValue(colorAxis->min());
        rangeMax->setLineEditValue(colorAxis->max());
        tickCount->setLineEditValue(colorAxis->tickCount());
        size->setLineEditValue(colorAxis->size());

        /* tickCount,sizeの変更が即座に変更されない。新しく軸を追加すると更新される */

        connect(tickCount, &LineEditLayout::lineValueEdited, colorAxis, &QColorAxis::setTickCount);
        connect(colorAxis, &QColorAxis::tickCountChanged, tickCount, &LineEditLayout::setLineEditValue);
        connect(size, &LineEditLayout::lineValueEdited, colorAxis, &QColorAxis::setSize);
        connect(colorAxis, &QColorAxis::sizeChanged, size, &LineEditLayout::setLineEditValue);
        connect(rangeMin, &LineEditLayout::lineValueEdited, colorAxis, &QColorAxis::setMin);
        connect(rangeMax, &LineEditLayout::lineValueEdited, colorAxis, &QColorAxis::setMax);
        connect(colorAxis, &QColorAxis::minChanged, rangeMin, &LineEditLayout::setLineEditValue);
        connect(colorAxis, &QColorAxis::maxChanged, rangeMax, &LineEditLayout::setLineEditValue);
        break;
    }
    default:
        qDebug() << __FILE__ << __LINE__;
        qDebug() << "Invalid enum index of QAbstractAxis";
        return;
    }
}


AxisSetting::AxisSetting(QWidget *parent)
    : QScrollArea(parent)
{
    /* このスクロールエリア */
    QWidget *contents = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(contents);
    setWidget(contents);
    setWidgetResizable(true);
    contents->setLayout(layout);
    /* 軸を追加する項目 */
    QGroupBox *addGroup = new QGroupBox("Add new Axis", contents);
    QVBoxLayout *addGroupLayout = new QVBoxLayout(addGroup);
    axisType = new ComboEditLayout(addGroup, "Type");
    axisAlign = new ComboEditLayout(addGroup, "Align");
    addButton = new PushButtonLayout(addGroup, "Add");
    axisIndex = new QComboBox(contents);
    /* 軸の共通設定項目 */
    settingStack = new QStackedWidget(contents);

    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

    layout->addWidget(addGroup);
    addGroupLayout->addLayout(axisType);
    addGroupLayout->addLayout(axisAlign);
    addGroupLayout->addLayout(addButton);
    layout->addWidget(axisIndex);
    layout->addWidget(settingStack);
    layout->addItem(spacer);

    axisType->insertComboItems(0, enumToStrings(Graph2D::AxisType(0)));
    axisAlign->insertComboItems(0, enumToStrings(Graph2D::AxisAlign(0)));

    connect(addButton, &PushButtonLayout::buttonReleased, this, &AxisSetting::createNewAxis);
    connect(axisIndex, &QComboBox::currentIndexChanged, settingStack, &QStackedWidget::setCurrentIndex);
}

/*
 * HorizontalAxisSettingのWidget内のボタンを押す事によって呼び出される。
 * 軸のインスタンスの生成とシグナル&スロットの設定を行う
 * graphにそのインスタンスを追加処理はGraph2D::addAxis()で行う
 */
void AxisSetting::createNewAxis()
{
    static qsizetype axisCount = 0;

    const Graph2D::AxisType type = Graph2D::AxisType(axisType->currentComboIndex());
    const Graph2D::AxisAlign align = Graph2D::AxisAlign(axisAlign->currentComboIndex());

    //QColorAxisをAlignLeftまたはAlignRightに追加するとcrashする
    if(type == Graph2D::AxisType::Color && (align == Graph2D::AxisAlign::Left || align == Graph2D::AxisAlign::Right)) return;

    /* 新しいインスタンスの作成 */
    QAbstractAxis *axis;
    switch(type)
    {
    case Graph2D::AxisType::Value:
        axis = new QValueAxis; break;
    case Graph2D::AxisType::BarCategory:
        axis = new QBarCategoryAxis; break;
    case Graph2D::AxisType::Category:
        axis = new QCategoryAxis; break;
    case Graph2D::AxisType::DateTime:
        axis = new QDateTimeAxis; break;
    case Graph2D::AxisType::LogValue:
        axis = new QLogValueAxis; break;
    case Graph2D::AxisType::Color:
        axis = new QColorAxis; break;
    default:
        qDebug() << __FILE__ << __LINE__;
        qDebug() << "Invalid enum index of AxisType";
        return;
    }

    emit axisCreated(axis, align);

    /* settingWidgetの更新 */
    AxisCommonSetting *axisSetting = new AxisCommonSetting(settingStack, axis);
    settingStack->addWidget(axisSetting);
    axisIndex->addItem(QString::number(axisCount) + ((axisAlign->currentComboIndex() < 2) ? "  Vertical  " : "  Horizontal  ") + enumToString(type) + "  Axis");
    axisIndex->setCurrentIndex(axisIndex->count() - 1);

    /* シグナル&スロット */
    auto setTitleSize = [axis](const int ps){
        QFont titleFont = axis->titleFont();
        titleFont.setPointSize(ps);
        axis->setTitleFont(titleFont);
    };
    auto setLabelSize = [axis](const int ps){
        QFont labelFont = axis->labelsFont();
        labelFont.setPointSize(ps);
        axis->setLabelsFont(labelFont);
    };
    connect(axisSetting, &AxisCommonSetting::rangeMinSet, axis, &QAbstractAxis::setMin);
    connect(axisSetting, &AxisCommonSetting::rangeMaxSet, axis, &QAbstractAxis::setMax);
    connect(axisSetting, &AxisCommonSetting::titleVisibleChanged, axis, &QAbstractAxis::setTitleVisible);
    connect(axisSetting, &AxisCommonSetting::titleSet, axis, &QAbstractAxis::setTitleText);
    connect(axisSetting, &AxisCommonSetting::titleSizeSet, setTitleSize);
    connect(axisSetting, &AxisCommonSetting::gridVisibleChanged, axis, &QAbstractAxis::setGridLineVisible);
    connect(axisSetting, &AxisCommonSetting::gridColorSet, axis, &QAbstractAxis::setGridLineColor);
    connect(axisSetting, &AxisCommonSetting::labelVisibleChanged, axis, &QAbstractAxis::setLabelsVisible);
    connect(axisSetting, &AxisCommonSetting::labelAngleSet, axis, &QAbstractAxis::setLabelsAngle);
    connect(axisSetting, &AxisCommonSetting::labelSizeSet, setLabelSize);
    connect(axisSetting, &AxisCommonSetting::labelColorSet, axis, &QAbstractAxis::setLabelsColor);
    connect(axisSetting, &AxisCommonSetting::axisVisibleChanged, axis, &QAbstractAxis::setLineVisible);
    connect(axisSetting, &AxisCommonSetting::axisColorSet, axis, &QAbstractAxis::setLinePenColor);

    axisCount++;
}






GeneralSetting::GeneralSetting(QWidget *parent)
    : QScrollArea(parent)
{
    /* このスクロールエリア全体のレイアウト */
    QWidget *contents = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(contents);
    setWidget(contents);
    setWidgetResizable(true);
    contents->setLayout(layout);

    /* 設定項目のレイアウト */
    pointX = new LineEditLayout(contents, "X:", labelWidth);
    pointY = new LineEditLayout(contents, "Y:", labelWidth);
    QHBoxLayout *setMarginLayout = new QHBoxLayout;
    QLabel *setMarginLabel = new QLabel("Mergin (L,R,B,T)", contents);
    marginLeft = new QLineEdit(contents);
    marginRight = new QLineEdit(contents);
    marginBottom = new QLineEdit(contents);
    marginTop = new QLineEdit(contents);
    QSpacerItem *setMarginSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    graphTitle = new LineEditLayout(contents, "Title", labelWidth);
    graphTitleSize = new SpinBoxEditLayout(contents, "Title size", labelWidth);
    graphTheme = new ComboEditLayout(contents, "Theme", labelWidth);
    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

    layout->addLayout(pointX);
    layout->addLayout(pointY);
    layout->addLayout(setMarginLayout);
    setMarginLayout->addWidget(setMarginLabel);
    setMarginLayout->addWidget(marginLeft);
    setMarginLayout->addWidget(marginRight);
    setMarginLayout->addWidget(marginBottom);
    setMarginLayout->addWidget(marginTop);
    setMarginLayout->addItem(setMarginSpacer);
    layout->addLayout(graphTitle);
    layout->addLayout(graphTitleSize);
    layout->addLayout(graphTheme);
    layout->addItem(spacer);

    pointX->setReadOnly(true);
    pointY->setReadOnly(true);
    setMarginLabel->setMinimumWidth(labelWidth);
    marginLeft->setMaximumWidth(SETTING_EDIT_SWIDTH - 12);
    marginRight->setMaximumWidth(SETTING_EDIT_SWIDTH - 12);
    marginBottom->setMaximumWidth(SETTING_EDIT_SWIDTH - 12);
    marginTop->setMaximumWidth(SETTING_EDIT_SWIDTH - 12);
    graphTheme->insertComboItems(0, enumToStrings(Graph2D::Theme(0)));

    connect(marginLeft, &QLineEdit::textEdited, this, &GeneralSetting::marginLeftSet);
    connect(marginRight, &QLineEdit::textEdited, this, &GeneralSetting::marginRightSet);
    connect(marginBottom, &QLineEdit::textEdited, this, &GeneralSetting::marginBottomSet);
    connect(marginTop, &QLineEdit::textEdited, this, &GeneralSetting::marginTopSet);
    connect(graphTitle, &LineEditLayout::lineTextEdited, this, &GeneralSetting::graphTitleSet);
    connect(graphTitleSize, &SpinBoxEditLayout::spinBoxValueChanged, this, &GeneralSetting::graphTitleSizeSet);
    connect(graphTheme, &ComboEditLayout::currentComboIndexChanged, this, &GeneralSetting::graphThemeSet);
}































