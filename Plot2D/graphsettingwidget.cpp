#include "graphsettingwidget.h"

static const int labelWidth = SETTING_LABEL_WIDTH + 20;

GraphSettingWidget::GraphSettingWidget(QWidget *parent, QChart *graph)
    : QStackedWidget(parent)
{
    generalSetting = new GeneralSetting(this);
    legendSetting = new LegendSetting(this, graph->legend());
    axisSetting = new AxisSetting(this);
    seriesSetting = new SeriesSetting(this);
    graphicsItemSetting = new GraphicsItemSetting(this);

    addWidget(generalSetting);
    addWidget(legendSetting);
    addWidget(axisSetting);
    addWidget(seriesSetting);
    addWidget(graphicsItemSetting);

    seriesSetting->setAxisListModel(axisSetting->getAxisListModel());

    connect(axisSetting, &AxisSetting::axisCreated, seriesSetting, &SeriesSetting::addAxisToList);
    connect(axisSetting, &AxisSetting::removeAxisRequested, seriesSetting, &SeriesSetting::removeAxisFromList);
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
        break;
    }

    /* axisを削除するボタン */
    removeAxis = new PushButtonLayout(this, "Remove");
    layout->addLayout(removeAxis);
    auto requestRemoveAxisFromList = [this, axis]() { emit removeAxisFromListRequested(axis); };
    connect(removeAxis, &PushButtonLayout::buttonReleased, requestRemoveAxisFromList);
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

    axis->setObjectName(enumToString(type) + " " + enumToString(align));
    emit axisCreated(axis, align);

    /* settingWidgetの更新 */
    AxisCommonSetting *axisSetting = new AxisCommonSetting(settingStack, axis);
    axisSetting->setObjectName(enumToString(type) + " " + enumToString(align));
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
    auto removeAxisFromList = [this](QAbstractAxis *axis){
#if 0
        //正しく現在のWidgetが削除されない
        axisIndex->removeItem(axisIndex->currentIndex());
        settingStack->removeWidget(settingStack->currentWidget());
#else
        QWidget *currentWidget = settingStack->currentWidget();
        axisIndex->removeItem(axisIndex->currentIndex());
        settingStack->removeWidget(currentWidget);
#endif
        emit removeAxisRequested(axis);;
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
    connect(axisSetting, &AxisCommonSetting::removeAxisFromListRequested, removeAxisFromList);

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








LegendSetting::LegendSetting(QWidget *parent, QLegend *legend)
    : QScrollArea(parent)
{
    /* このスクロールエリア全体のレイアウト */
    QWidget *contents = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(contents);
    setWidget(contents);
    setWidgetResizable(true);
    contents->setLayout(layout);

    visible = new CheckBoxLayout(contents, "Visible", labelWidth);
    backgroundVisible = new CheckBoxLayout(contents, "Background", labelWidth);
    interactive = new CheckBoxLayout(contents, "Interactive", labelWidth);
    reverseMarker = new CheckBoxLayout(contents, "Reverse marker", labelWidth);
    showToolTip = new CheckBoxLayout(contents, "Show tooltip", labelWidth);
    alignment = new ComboEditLayout(contents, "Alignment", labelWidth);
    markerShape = new ComboEditLayout(contents, "Marker shape", labelWidth);
    fontSize = new SpinBoxEditLayout(contents, "Size", labelWidth);
    color = new ComboEditLayout(contents, "Color", labelWidth);
    colorCustom = new RGBEditLayout(contents, labelWidth);
    borderColor = new ComboEditLayout(contents, "Border color", labelWidth);
    borderColorCustom = new RGBEditLayout(contents, labelWidth);
    labelColor = new ComboEditLayout(contents, "Label color", labelWidth);
    labelColorCustom = new RGBEditLayout(contents, labelWidth);
    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

    layout->addLayout(visible);
    layout->addLayout(backgroundVisible);
    layout->addLayout(interactive);
    layout->addLayout(reverseMarker);
    layout->addLayout(showToolTip);
    layout->addLayout(alignment);
    layout->addLayout(markerShape);
    layout->addLayout(fontSize);
    layout->addLayout(color);
    layout->addLayout(colorCustom);
    layout->addLayout(borderColor);
    layout->addLayout(borderColorCustom);
    layout->addLayout(labelColor);
    layout->addLayout(labelColorCustom);
    layout->addItem(spacer);

    visible->setChecked(legend->isVisible());
    backgroundVisible->setChecked(legend->isBackgroundVisible());
    interactive->setChecked(legend->isInteractive());
    reverseMarker->setChecked(legend->reverseMarkers());
    showToolTip->setChecked(legend->showToolTips());
    alignment->insertComboItems(0, enumToStrings(Graph2D::LegendAlign(0)));
    alignment->setComboCurrentIndex((int)Graph2D::LegendAlign::Top);
    markerShape->insertComboItems(0, enumToStrings(Graph2D::LegendMarkerShape(0)));
    markerShape->setComboCurrentIndex((int)Graph2D::LegendMarkerShape::Rectangle);
    fontSize->setSpinBoxValue(legend->font().pointSize());
    color->insertComboItems(0, colorNameList());
    color->setComboCurrentIndex(QT_GLOBAL_COLOR_COUNT + 1);
    colorCustom->setColor(legend->color());
    borderColor->insertComboItems(0, colorNameList());
    borderColor->setComboCurrentIndex(QT_GLOBAL_COLOR_COUNT + 1);
    borderColorCustom->setColor(legend->borderColor());
    labelColor->insertComboItems(0, colorNameList());
    labelColor->setComboCurrentIndex(QT_GLOBAL_COLOR_COUNT + 1);
    labelColorCustom->setColor(legend->labelColor());

    auto setLegendVisible = [legend](const bool visible){
        legend->setVisible(visible);
    };
    auto setLegendAlignment = [legend](const int index)
    {
        switch(Graph2D::LegendAlign(index))
        {
        case Graph2D::LegendAlign::Bottom:
            legend->setAlignment(Qt::AlignBottom); break;
        case Graph2D::LegendAlign::Left:
            legend->setAlignment(Qt::AlignLeft); break;
        case Graph2D::LegendAlign::Right:
            legend->setAlignment(Qt::AlignRight); break;
        case Graph2D::LegendAlign::Top:
            legend->setAlignment(Qt::AlignTop); break;
        default:
            qDebug() << __FILE__ << __LINE__;
            qDebug() << "Invalid enum index of Graph2D::LegendAlign";
            return;
        }
    };
    auto setLegendMarkerShape = [legend](const int index)
    {
        legend->setMarkerShape(QLegend::MarkerShape(index));
    };
    auto setLegendFontSize = [legend](const int ps)
    {
        QFont font = legend->font();
        font.setPointSize(ps);
        legend->setFont(font);
    };
    connect(visible, &CheckBoxLayout::checkBoxToggled, setLegendVisible);
    connect(backgroundVisible, &CheckBoxLayout::checkBoxToggled, legend, &QLegend::setBackgroundVisible);
    connect(interactive, &CheckBoxLayout::checkBoxToggled, legend, &QLegend::setInteractive);
    connect(reverseMarker, &CheckBoxLayout::checkBoxToggled, legend, &QLegend::setReverseMarkers);
    connect(showToolTip, &CheckBoxLayout::checkBoxToggled, legend, &QLegend::setShowToolTips);
    connect(alignment, &ComboEditLayout::currentComboIndexChanged, setLegendAlignment);
    connect(markerShape, &ComboEditLayout::currentComboIndexChanged, setLegendMarkerShape);
    connect(fontSize, &SpinBoxEditLayout::spinBoxValueChanged, setLegendFontSize);
    connect(color, &ComboEditLayout::currentComboIndexChanged, colorCustom, &RGBEditLayout::setColorAndEditable);
    connect(colorCustom, &RGBEditLayout::colorEdited, legend, &QLegend::setColor);
    connect(borderColor, &ComboEditLayout::currentComboIndexChanged, borderColorCustom, &RGBEditLayout::setColorAndEditable);
    connect(borderColorCustom, &RGBEditLayout::colorEdited, legend, &QLegend::setBorderColor);
    connect(labelColor, &ComboEditLayout::currentComboIndexChanged, labelColorCustom, &RGBEditLayout::setColorAndEditable);
    connect(labelColorCustom, &RGBEditLayout::colorEdited, legend, &QLegend::setLabelColor);
}










AxisAttachingList::AxisAttachingList(QAbstractItemModel *model, QWidget *parent)
    : QHBoxLayout(parent)
{
    axisComboList = new QComboBox;
    attach = new QCheckBox;

    addWidget(axisComboList);
    addWidget(attach);

    axisComboList->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    axisComboList->setModel(model);
    attach->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);

    connect(model, &QAbstractItemModel::rowsAboutToBeInserted, this, &AxisAttachingList::addStateListIndex);
    connect(model, &QAbstractItemModel::rowsRemoved, this, &AxisAttachingList::removeStateList);
    connect(axisComboList, &QComboBox::currentIndexChanged, this, &AxisAttachingList::changeCheckBoxIndex);
    connect(attach, &QCheckBox::toggled, this, &AxisAttachingList::changeState);
}

void AxisAttachingList::addStateListIndex()
{
    stateList.append(false);
}

void AxisAttachingList::removeStateList(const QModelIndex&, int first, int last)
{
    for(int index = first; index <= last; ++index)
        stateList.remove(index);
}

void AxisAttachingList::changeCheckBoxIndex(const int index)
{
    if(index < 0) return;
    attach->setChecked(stateList.at(index));
}

void AxisAttachingList::changeState(const bool checked)
{
    const int index = axisComboList->currentIndex();

    if(index == -1) return;

    stateList[index] = checked;

    emit axisAttachedStateChanged(index, checked);
}


SeriesSetting::SeriesSetting(QWidget *parent)
    : QScrollArea(parent)
{
    QWidget *contents = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(contents);
    seriesCombo = new QComboBox(contents);
    stackWidget = new QStackedWidget(contents);
    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    setWidget(contents);
    setWidgetResizable(true);
    contents->setLayout(layout);
    layout->addWidget(seriesCombo);
    layout->addWidget(stackWidget);
    layout->addItem(spacer);

    connect(seriesCombo, &QComboBox::currentIndexChanged, stackWidget, &QStackedWidget::setCurrentIndex);
}

void SeriesSetting::addSeries(QAbstractSeries *series, const QString& name)
{
    /* 各Seriesが一つもつ設定のためのWidget */
    QWidget *settingWidget = new QWidget(stackWidget);
    QVBoxLayout *layout = new QVBoxLayout(settingWidget);

    /* seriesのaxisのattach/detach設定項目 */
    QLabel *axisAttachLabel = new QLabel("Attach axis", settingWidget);
    AxisAttachingList *axisAttachList = new AxisAttachingList(axisListModel);
    layout->addWidget(axisAttachLabel);
    layout->addLayout(axisAttachList);
    auto attachAxis = [this, series](const int index, const bool attached)
    {
        if(attached) series->attachAxis(axisList.at(index));
        else series->detachAxis(axisList.at(index));
    };
    connect(axisAttachList, &AxisAttachingList::axisAttachedStateChanged, attachAxis);

    /* 共通設定項目 */
    CheckBoxLayout *seriesVisible = new CheckBoxLayout(settingWidget, "Visible", labelWidth);
    LineEditLayout *seriesName = new LineEditLayout(settingWidget, "Name", labelWidth);
    layout->addLayout(seriesVisible);
    layout->addLayout(seriesName);
    seriesVisible->setChecked(series->isVisible());
    connect(seriesVisible, &CheckBoxLayout::checkBoxToggled, series, &QAbstractSeries::setVisible);
    connect(seriesName, &LineEditLayout::lineTextEdited, series, &QAbstractSeries::setName);

    /* comboへ登録 */
    static qsizetype seriesCount = 0;
    seriesCombo->addItem(QString::number(seriesCount++) + "  " + name);

    /* 各Seriesの種別特有の設定項目 */
    const QAbstractSeries::SeriesType type = series->type();
    switch(type)
    {
    case QAbstractSeries::SeriesTypeScatter:
    {
        ComboEditLayout *markerShape = new ComboEditLayout(settingWidget, "Marker shape", labelWidth);
        ComboEditLayout *borderColor = new ComboEditLayout(settingWidget, "Border color", labelWidth);
        RGBEditLayout *borderColorCustom = new RGBEditLayout(settingWidget, labelWidth);
        layout->addLayout(markerShape);
        layout->addLayout(borderColor);
        layout->addLayout(borderColorCustom);
        markerShape->insertComboItems(0, enumToStrings(Graph2D::MarkerShape(0)));
        borderColor->insertComboItems(0, colorNameList());
        borderColor->setComboCurrentIndex(QT_GLOBAL_COLOR_COUNT + 1);

        QScatterSeries *scatterSeries = qobject_cast<QScatterSeries*>(series);

        markerShape->setComboCurrentIndex(scatterSeries->markerShape());
        borderColorCustom->setColor(scatterSeries->borderColor());

        auto setMarkerShape = [scatterSeries](const int index){
            scatterSeries->setMarkerShape(QScatterSeries::MarkerShape(index));
        };

        connect(markerShape, &ComboEditLayout::currentComboIndexChanged, setMarkerShape);
        connect(borderColor, &ComboEditLayout::currentComboIndexChanged, borderColorCustom, &RGBEditLayout::setColorAndEditable);
        connect(borderColorCustom, &RGBEditLayout::colorEdited, scatterSeries, &QScatterSeries::setBorderColor);
    }
    case QAbstractSeries::SeriesTypeLine:
    case QAbstractSeries::SeriesTypeSpline:
    {
        CheckBoxLayout *fitLineVisible = new CheckBoxLayout(settingWidget, "Fit line", labelWidth);
        ComboEditLayout *fitLineColor = new ComboEditLayout(settingWidget, "Fit line color", labelWidth);
        RGBEditLayout *fitLineColorCustom = new RGBEditLayout(settingWidget, labelWidth);
        ComboEditLayout *lineColor = new ComboEditLayout(settingWidget, "Line color", labelWidth);
        RGBEditLayout *lineColorCustom = new RGBEditLayout(settingWidget, labelWidth);
        LineEditLayout *markerSize = new LineEditLayout(settingWidget, "Marker size", labelWidth);
        CheckBoxLayout *pointVisible = new CheckBoxLayout(settingWidget, "Points visible", labelWidth);
        CheckBoxLayout *labelVisible = new CheckBoxLayout(settingWidget, "Label visible", labelWidth);
        CheckBoxLayout *labelClipping = new CheckBoxLayout(settingWidget, "Label clipping", labelWidth);
        ComboEditLayout *labelColor = new ComboEditLayout(settingWidget, "Label color", labelWidth);
        RGBEditLayout *labelColorCustom = new RGBEditLayout(settingWidget, labelWidth);
        SpinBoxEditLayout *labelSize = new SpinBoxEditLayout(settingWidget, "Label size", labelWidth);
        layout->addLayout(fitLineVisible);
        layout->addLayout(fitLineColor);
        layout->addLayout(fitLineColorCustom);
        layout->addLayout(lineColor);
        layout->addLayout(lineColorCustom);
        layout->addLayout(markerSize);
        layout->addLayout(pointVisible);
        layout->addLayout(labelVisible);
        layout->addLayout(labelClipping);
        layout->addLayout(labelColor);
        layout->addLayout(labelColorCustom);
        layout->addLayout(labelSize);
        fitLineColor->insertComboItems(0, colorNameList());
        fitLineColor->setComboCurrentIndex(QT_GLOBAL_COLOR_COUNT + 1);
        lineColor->insertComboItems(0, colorNameList());
        lineColor->setComboCurrentIndex(QT_GLOBAL_COLOR_COUNT + 1);
        labelColor->insertComboItems(0, colorNameList());
        labelColor->setComboCurrentIndex(QT_GLOBAL_COLOR_COUNT + 1);

        QXYSeries *xySeries = qobject_cast<QXYSeries*>(series);

        fitLineVisible->setChecked(xySeries->bestFitLineVisible());
        fitLineColorCustom->setColor(xySeries->bestFitLineColor());
        lineColorCustom->setColor(xySeries->color());
        markerSize->setLineEditValue(xySeries->markerSize());
        pointVisible->setChecked(xySeries->pointsVisible());
        labelVisible->setChecked(xySeries->pointLabelsVisible());
        labelClipping->setChecked(xySeries->pointLabelsClipping());
        labelColorCustom->setColor(xySeries->pointLabelsColor());
        labelSize->setSpinBoxValue(xySeries->pointLabelsFont().pointSize());

        auto setLabelSize = [xySeries](const int ps){
            QFont font = xySeries->pointLabelsFont();
            font.setPointSize(ps);
            xySeries->setPointLabelsFont(font);
        };

        connect(fitLineVisible, &CheckBoxLayout::checkBoxToggled, xySeries, &QXYSeries::setBestFitLineVisible);
        connect(fitLineColor, &ComboEditLayout::currentComboIndexChanged, fitLineColorCustom, &RGBEditLayout::setColorAndEditable);
        connect(fitLineColorCustom, &RGBEditLayout::colorEdited, xySeries, &QXYSeries::setBestFitLineColor);
        connect(lineColor, &ComboEditLayout::currentComboIndexChanged, lineColorCustom, &RGBEditLayout::setColorAndEditable);
        connect(lineColorCustom, &RGBEditLayout::colorEdited, xySeries, &QXYSeries::setColor);
        connect(markerSize, &LineEditLayout::lineValueEdited, xySeries, &QXYSeries::setMarkerSize);
        connect(pointVisible, &CheckBoxLayout::checkBoxToggled, xySeries, &QXYSeries::setPointsVisible);
        connect(labelVisible, &CheckBoxLayout::checkBoxToggled, xySeries, &QXYSeries::setPointLabelsVisible);
        connect(labelClipping, &CheckBoxLayout::checkBoxToggled, xySeries, &QXYSeries::setPointLabelsClipping);
        connect(labelColor, &ComboEditLayout::currentComboIndexChanged, labelColorCustom, &RGBEditLayout::setColorAndEditable);
        connect(labelColorCustom, &RGBEditLayout::colorEdited, xySeries, &QXYSeries::setPointLabelsColor);
        connect(labelSize, &SpinBoxEditLayout::spinBoxValueChanged, setLabelSize);

        break;
    }
    case QAbstractSeries::SeriesTypeBar:
    case QAbstractSeries::SeriesTypePercentBar:
    case QAbstractSeries::SeriesTypeStackedBar:
    case QAbstractSeries::SeriesTypeHorizontalBar:
    case QAbstractSeries::SeriesTypeHorizontalPercentBar:
    case QAbstractSeries::SeriesTypeHorizontalStackedBar:
    {
        LineEditLayout *barWidth = new LineEditLayout(settingWidget, "Bar width", labelWidth, SETTING_EDIT_SWIDTH);
        CheckBoxLayout *labelVisible = new CheckBoxLayout(settingWidget, "Label visible", labelWidth);
        LineEditLayout *labelAngle = new LineEditLayout(settingWidget, "Label angle", labelWidth, SETTING_EDIT_SWIDTH);
        ComboEditLayout *labelPosition = new ComboEditLayout(settingWidget, "Label position", labelWidth);
        SpinBoxEditLayout *labelPrecision = new SpinBoxEditLayout(settingWidget, "Label precision", labelWidth);
        layout->addLayout(barWidth);
        layout->addLayout(labelVisible);
        layout->addLayout(labelAngle);
        layout->addLayout(labelPosition);
        layout->addLayout(labelPrecision);
        labelPosition->insertComboItems(0, enumToStrings(Graph2D::BarLabelPosition(0)));

        QAbstractBarSeries *barSeries = qobject_cast<QAbstractBarSeries*>(series);

        barWidth->setLineEditValue(barSeries->barWidth());
        labelVisible->setChecked(barSeries->isLabelsVisible());
        labelAngle->setLineEditValue(barSeries->labelsAngle());
        labelPosition->setComboCurrentIndex(barSeries->labelsPosition());
        labelPrecision->setSpinBoxValue(barSeries->labelsPrecision());

        auto setLabelPosition = [barSeries](const int index){
            barSeries->setLabelsPosition(QAbstractBarSeries::LabelsPosition(index));
        };

        connect(barWidth, &LineEditLayout::lineValueEdited, barSeries, &QAbstractBarSeries::setBarWidth);
        connect(labelVisible, &CheckBoxLayout::checkBoxToggled, barSeries, &QAbstractBarSeries::setLabelsVisible);
        connect(labelAngle, &LineEditLayout::lineValueEdited, barSeries, &QAbstractBarSeries::setLabelsAngle);
        connect(labelPosition, &ComboEditLayout::currentComboIndexChanged, setLabelPosition);
        connect(labelPrecision, &SpinBoxEditLayout::spinBoxValueChanged, barSeries, &QAbstractBarSeries::setLabelsPrecision);

        break;
    }
    case QAbstractSeries::SeriesTypeArea:
    {
        ComboEditLayout *borderColor = new ComboEditLayout(settingWidget, "Border color", labelWidth);
        RGBEditLayout *borderColorCustom = new RGBEditLayout(settingWidget, labelWidth);
        ComboEditLayout *lineColor = new ComboEditLayout(settingWidget, "Line color", labelWidth);
        RGBEditLayout *lineColorCustom = new RGBEditLayout(settingWidget, labelWidth);
        CheckBoxLayout *pointVisible = new CheckBoxLayout(settingWidget, "Points visible", labelWidth);
        CheckBoxLayout *labelVisible = new CheckBoxLayout(settingWidget, "Label visible", labelWidth);
        CheckBoxLayout *labelClipping = new CheckBoxLayout(settingWidget, "Label clipping", labelWidth);
        ComboEditLayout *labelColor = new ComboEditLayout(settingWidget, "Label color", labelWidth);
        RGBEditLayout *labelColorCustom = new RGBEditLayout(settingWidget, labelWidth);
        SpinBoxEditLayout *labelSize = new SpinBoxEditLayout(settingWidget, "Label size", labelWidth);
        layout->addLayout(borderColor);
        layout->addLayout(borderColorCustom);
        layout->addLayout(lineColor);
        layout->addLayout(lineColorCustom);
        layout->addLayout(pointVisible);
        layout->addLayout(labelVisible);
        layout->addLayout(labelClipping);
        layout->addLayout(labelColor);
        layout->addLayout(labelColorCustom);
        layout->addLayout(labelSize);
        borderColor->insertComboItems(0, colorNameList());
        borderColor->setComboCurrentIndex(QT_GLOBAL_COLOR_COUNT + 1);
        lineColor->insertComboItems(0, colorNameList());
        lineColor->setComboCurrentIndex(QT_GLOBAL_COLOR_COUNT + 1);
        labelColor->insertComboItems(0, colorNameList());
        labelColor->setComboCurrentIndex(QT_GLOBAL_COLOR_COUNT + 1);

        QAreaSeries *areaSeries = qobject_cast<QAreaSeries*>(series);

        borderColorCustom->setColor(areaSeries->borderColor());
        lineColorCustom->setColor(areaSeries->color());
        pointVisible->setChecked(areaSeries->pointsVisible());
        labelVisible->setChecked(areaSeries->pointLabelsVisible());
        labelClipping->setChecked(areaSeries->pointLabelsClipping());
        labelColorCustom->setColor(areaSeries->pointLabelsColor());
        labelSize->setSpinBoxValue(areaSeries->pointLabelsFont().pointSize());

        auto setLabelSize = [areaSeries](const int ps){
            QFont font = areaSeries->pointLabelsFont();
            font.setPointSize(ps);
            areaSeries->setPointLabelsFont(font);
        };

        connect(borderColor, &ComboEditLayout::currentComboIndexChanged, borderColorCustom, &RGBEditLayout::setColorAndEditable);
        connect(borderColorCustom, &RGBEditLayout::colorEdited, areaSeries, &QAreaSeries::setBorderColor);
        connect(lineColor, &ComboEditLayout::currentComboIndexChanged, lineColorCustom, &RGBEditLayout::setColorAndEditable);
        connect(lineColorCustom, &RGBEditLayout::colorEdited, areaSeries, &QAreaSeries::setColor);
        connect(pointVisible, &CheckBoxLayout::checkBoxToggled, areaSeries, &QAreaSeries::setPointsVisible);
        connect(labelVisible, &CheckBoxLayout::checkBoxToggled, areaSeries, &QAreaSeries::setPointLabelsVisible);
        connect(labelClipping, &CheckBoxLayout::checkBoxToggled, areaSeries, &QAreaSeries::setPointLabelsClipping);
        connect(labelColor, &ComboEditLayout::currentComboIndexChanged, labelColorCustom, &RGBEditLayout::setColorAndEditable);
        connect(labelColorCustom, &RGBEditLayout::colorEdited, areaSeries, &QAreaSeries::setPointLabelsColor);
        connect(labelSize, &SpinBoxEditLayout::spinBoxValueChanged, setLabelSize);

        break;
    }
    case QAbstractSeries::SeriesTypeBoxPlot:
    {
        LineEditLayout *boxWidth = new LineEditLayout(settingWidget, "Box width", labelWidth, SETTING_EDIT_SWIDTH);
        CheckBoxLayout *boxOutline = new CheckBoxLayout(settingWidget, "Box outline", labelWidth);
        layout->addLayout(boxWidth);
        layout->addLayout(boxOutline);

        QBoxPlotSeries *boxSeries = qobject_cast<QBoxPlotSeries*>(series);

        boxWidth->setLineEditValue(boxSeries->boxWidth());
        boxOutline->setChecked(boxSeries->boxOutlineVisible());

        connect(boxWidth, &LineEditLayout::lineValueEdited, boxSeries, &QBoxPlotSeries::setBoxWidth);
        connect(boxOutline, &CheckBoxLayout::checkBoxToggled, boxSeries, &QBoxPlotSeries::setBoxOutlineVisible);

        break;
    }
    case QAbstractSeries::SeriesTypeCandlestick:
    {
        CheckBoxLayout *bodyOutline = new CheckBoxLayout(settingWidget, "Body outline", labelWidth);
        LineEditLayout *bodyWidth = new LineEditLayout(settingWidget, "Body width", labelWidth, SETTING_EDIT_SWIDTH);
        CheckBoxLayout *capsVisible = new CheckBoxLayout(settingWidget, "Caps visible", labelWidth);
        LineEditLayout *capsWidth = new LineEditLayout(settingWidget, "Caps width", labelWidth, SETTING_EDIT_SWIDTH);
        ComboEditLayout *decreasingColor = new ComboEditLayout(settingWidget, "Decreasing color", labelWidth);
        RGBEditLayout *decreasingColorCustom = new RGBEditLayout(settingWidget, labelWidth);
        ComboEditLayout *increasingColor = new ComboEditLayout(settingWidget, "Increasing color", labelWidth);
        RGBEditLayout *increasingColorCustom = new RGBEditLayout(settingWidget, labelWidth);
        LineEditLayout *maxColumnWidth = new LineEditLayout(settingWidget, "Max col width", labelWidth, SETTING_EDIT_SWIDTH);
        LineEditLayout *minColumnWidth = new LineEditLayout(settingWidget, "Min col width", labelWidth, SETTING_EDIT_SWIDTH);
        layout->addLayout(bodyOutline);
        layout->addLayout(bodyWidth);
        layout->addLayout(capsVisible);
        layout->addLayout(capsWidth);
        layout->addLayout(decreasingColor);
        layout->addLayout(decreasingColorCustom);
        layout->addLayout(increasingColor);
        layout->addLayout(increasingColorCustom);
        layout->addLayout(maxColumnWidth);
        layout->addLayout(minColumnWidth);
        decreasingColor->insertComboItems(0, colorNameList());
        decreasingColor->setComboCurrentIndex(QT_GLOBAL_COLOR_COUNT);
        increasingColor->insertComboItems(0, colorNameList());
        increasingColor->setComboCurrentIndex(QT_GLOBAL_COLOR_COUNT);

        QCandlestickSeries *candleSeries = qobject_cast<QCandlestickSeries*>(series);

        bodyOutline->setChecked(candleSeries->bodyOutlineVisible());
        bodyWidth->setLineEditValue(candleSeries->bodyWidth());
        capsVisible->setChecked(candleSeries->capsVisible());
        capsWidth->setLineEditValue(candleSeries->capsWidth());
        decreasingColorCustom->setColor(candleSeries->decreasingColor());
        increasingColorCustom->setColor(candleSeries->increasingColor());
        maxColumnWidth->setLineEditValue(candleSeries->maximumColumnWidth());
        minColumnWidth->setLineEditValue(candleSeries->minimumColumnWidth());

        connect(bodyOutline, &CheckBoxLayout::checkBoxToggled, candleSeries, &QCandlestickSeries::setBodyOutlineVisible);
        connect(bodyWidth, &LineEditLayout::lineValueEdited, candleSeries, &QCandlestickSeries::setBodyWidth);
        connect(capsVisible, &CheckBoxLayout::checkBoxToggled, candleSeries, &QCandlestickSeries::setCapsVisible);
        connect(capsWidth, &LineEditLayout::lineValueEdited, candleSeries, &QCandlestickSeries::setCapsWidth);
        connect(decreasingColor, &ComboEditLayout::currentComboIndexChanged, decreasingColorCustom, &RGBEditLayout::setColorAndEditable);
        connect(decreasingColorCustom, &RGBEditLayout::colorEdited, candleSeries, &QCandlestickSeries::setDecreasingColor);
        connect(increasingColor, &ComboEditLayout::currentComboIndexChanged, increasingColorCustom, &RGBEditLayout::setColorAndEditable);
        connect(increasingColorCustom, &RGBEditLayout::colorEdited, candleSeries, &QCandlestickSeries::setIncreasingColor);
        connect(maxColumnWidth, &LineEditLayout::lineValueEdited, candleSeries, &QCandlestickSeries::setMaximumColumnWidth);
        connect(minColumnWidth, &LineEditLayout::lineValueEdited, candleSeries, &QCandlestickSeries::setMinimumColumnWidth);

        break;
    }
    case QAbstractSeries::SeriesTypePie:
    {
        LineEditLayout *holeSize = new LineEditLayout(settingWidget, "Hole size", labelWidth, SETTING_EDIT_SWIDTH);
        LineEditLayout *horizontalPos = new LineEditLayout(settingWidget, "Horizontal pos", labelWidth, SETTING_EDIT_SWIDTH);
        LineEditLayout *verticalPos = new LineEditLayout(settingWidget, "Vertival pos", labelWidth, SETTING_EDIT_SWIDTH);
        CheckBoxLayout *labelVisible = new CheckBoxLayout(settingWidget, "Label visible", labelWidth);
        ComboEditLayout *labelPos = new ComboEditLayout(settingWidget, "Label pos", labelWidth);
        LineEditLayout *pieStartAngle = new LineEditLayout(settingWidget, "Start angle", labelWidth, SETTING_EDIT_SWIDTH);
        LineEditLayout *pieEndAngle = new LineEditLayout(settingWidget, "End angle", labelWidth, SETTING_EDIT_SWIDTH);
        LineEditLayout *pieSize = new LineEditLayout(settingWidget, "Pie size", labelWidth, SETTING_EDIT_SWIDTH);
        layout->addLayout(holeSize);
        layout->addLayout(horizontalPos);
        layout->addLayout(verticalPos);
        layout->addLayout(labelVisible);
        layout->addLayout(labelPos);
        layout->addLayout(pieStartAngle);
        layout->addLayout(pieEndAngle);
        layout->addLayout(pieSize);
        labelPos->insertComboItems(0, enumToStrings(Graph2D::PieLabelPosition(0)));

        QPieSeries *pieSeries = qobject_cast<QPieSeries*>(series);

        holeSize->setLineEditValue(pieSeries->holeSize());
        horizontalPos->setLineEditValue(pieSeries->horizontalPosition());
        verticalPos->setLineEditValue(pieSeries->verticalPosition());
        labelVisible->setChecked(false); //変更した場合、すでに追加されている物に対してラベルのvisibleが設定され、それ以降のものはデフォルトのfalseである
        labelPos->setComboCurrentIndex(QPieSlice::LabelOutside); //変更した場合、すでに追加されているすべてに対して反映される。それ以降追加したものはでフォルトのLabelOutsizeである
        pieStartAngle->setLineEditValue(pieSeries->pieStartAngle());
        pieEndAngle->setLineEditValue(pieSeries->pieEndAngle());
        pieSize->setLineEditValue(pieSeries->pieSize());

        auto setLabelPosition = [pieSeries](const int index){
            pieSeries->setLabelsPosition(QPieSlice::LabelPosition(index));
        };

        connect(holeSize, &LineEditLayout::lineValueEdited, pieSeries, &QPieSeries::setHoleSize);
        connect(horizontalPos, &LineEditLayout::lineValueEdited, pieSeries, &QPieSeries::setHorizontalPosition);
        connect(verticalPos, &LineEditLayout::lineValueEdited, pieSeries, &QPieSeries::setVerticalPosition);
        connect(labelVisible, &CheckBoxLayout::checkBoxToggled, pieSeries, &QPieSeries::setLabelsVisible);
        connect(labelPos, &ComboEditLayout::currentComboIndexChanged, setLabelPosition);
        connect(pieStartAngle, &LineEditLayout::lineValueEdited, pieSeries, &QPieSeries::setPieStartAngle);
        connect(pieEndAngle, &LineEditLayout::lineValueEdited, pieSeries, &QPieSeries::setPieEndAngle);
        connect(pieSize, &LineEditLayout::lineValueEdited, pieSeries, &QPieSeries::setPieSize);

        break;
    }
    default:
        qDebug() << __FILE__ << __LINE__;
        qDebug() << "Invalid enum index of QAbstractSeries::SeriesType";
        break;
    }

    /* seriesの削除するボタン */
    PushButtonLayout *removeSeries = new PushButtonLayout(settingWidget, "Remove");
    layout->addLayout(removeSeries);
    auto requestRemoveSeries = [this, series](){
        QWidget *currentWidget = stackWidget->currentWidget();
        stackWidget->removeWidget(currentWidget);
        seriesCombo->removeItem(seriesCombo->currentIndex());
        emit removeSeriesRequested(series);
    };
    connect(removeSeries, &PushButtonLayout::buttonReleased, requestRemoveSeries);

    stackWidget->addWidget(settingWidget);
}












GraphicsItemSetting::GraphicsItemSetting(QWidget *parent)
    : QScrollArea(parent)
{
    /* このスクロールエリア全体のレイアウト */
    QWidget *contents = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(contents);
    setWidget(contents);
    setWidgetResizable(true);
    contents->setLayout(layout);

    itemCombo = new QComboBox(contents);
    settingStack = new QStackedWidget(contents);
    layout->addWidget(itemCombo);
    layout->addWidget(settingStack);

    connect(itemCombo, &QComboBox::currentIndexChanged, settingStack, &QStackedWidget::setCurrentIndex);
    connect(settingStack, &QStackedWidget::currentChanged, itemCombo, &QComboBox::setCurrentIndex);
}

void GraphicsItemSetting::addTextItemSettingWidget(GraphicsTextItem *textItem)
{
    itemCombo->addItem(QString::number(itemCount++) + "  " + "Text Item");

    QWidget *widget = new QWidget(settingStack);
    QVBoxLayout *layout = new QVBoxLayout(widget);
    widget->setLayout(layout);
    settingStack->addWidget(widget);

    LineEditLayout *textEdit = new LineEditLayout(widget, "Text", labelWidth);
    SpinBoxEditLayout *textSize = new SpinBoxEditLayout(widget, "Size", labelWidth);
    CheckBoxLayout *textBold = new CheckBoxLayout(widget, "Text bold", labelWidth);
    CheckBoxLayout *textItaric = new CheckBoxLayout(widget, "Text itaric", labelWidth);
    LineEditLayout *rotation = new LineEditLayout(widget, "Rotation", labelWidth, SETTING_EDIT_SWIDTH);
    ComboEditLayout *textColor = new ComboEditLayout(widget, "Text color", labelWidth);
    RGBEditLayout *textColorCustom = new RGBEditLayout(widget, labelWidth);
    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

    layout->addLayout(textEdit);
    layout->addLayout(textSize);
    layout->addLayout(textBold);
    layout->addLayout(textItaric);
    layout->addLayout(rotation);
    layout->addLayout(textColor);
    layout->addLayout(textColorCustom);
    layout->addItem(spacer);

    /* アイテムが選択された時に呼び出される。各Itemの値を設定し、settingStackとitemComboを現在のアイテムに切り替える */
    auto setThisWidget = [=](){
        rotation->setLineEditValue(textItem->rotation());
        settingStack->setCurrentWidget(widget);
    };

    /* 各項目の初期化 */
    setThisWidget();
    textEdit->setLineEditText(textItem->text());
    textSize->setSpinBoxValue(textItem->font().pointSize());
    textBold->setChecked(textItem->font().bold());
    textItaric->setChecked(textItem->font().italic());
    textColor->insertComboItems(0, colorNameList());
    textColor->setComboCurrentIndex(QT_GLOBAL_COLOR_COUNT + 1);
    textColorCustom->setColor(textItem->brush().color());

    connect(textItem, &GraphicsTextItem::itemSelected, setThisWidget);
    connect(textEdit, &LineEditLayout::lineTextEdited, textItem, &GraphicsTextItem::setItemText);
    connect(textSize, &SpinBoxEditLayout::spinBoxValueChanged, textItem, &GraphicsTextItem::setItemTextSize);
    connect(textBold, &CheckBoxLayout::checkBoxToggled, textItem, &GraphicsTextItem::setItemTextBold);
    connect(textItaric, &CheckBoxLayout::checkBoxToggled, textItem, &GraphicsTextItem::setItemTextItaric);
    connect(rotation, &LineEditLayout::lineValueEdited, textItem, &GraphicsTextItem::setItemRotation);
    connect(textColor, &ComboEditLayout::currentComboIndexChanged, textColorCustom, &RGBEditLayout::setColorAndEditable);
    connect(textColorCustom, &RGBEditLayout::colorEdited, textItem, &GraphicsTextItem::setItemTextColor);
}

void GraphicsItemSetting::addLineItemSettingWidget(GraphicsLineItem *lineItem)
{
    itemCombo->addItem(QString::number(itemCount++) + "  " + "Line Item");

    QWidget *widget = new QWidget(settingStack);
    QVBoxLayout *layout = new QVBoxLayout(widget);
    widget->setLayout(layout);
    settingStack->addWidget(widget);

    SpinBoxEditLayout *lineWidth = new SpinBoxEditLayout(widget, "Width", labelWidth);
    LineEditLayout *lineLength = new LineEditLayout(widget, "Length", labelWidth, SETTING_EDIT_SWIDTH);
    LineEditLayout *lineAngle = new LineEditLayout(widget, "Rotation", labelWidth, SETTING_EDIT_SWIDTH);
    ComboEditLayout *lineColor = new ComboEditLayout(widget, "Color", labelWidth);
    RGBEditLayout *lineColorCustom = new RGBEditLayout(widget, labelWidth);
    ComboEditLayout *lineStyle = new ComboEditLayout(widget, "Style", labelWidth);
    LineEditLayout *lineStyleCustom = new LineEditLayout(widget, "", labelWidth);
    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

    layout->addLayout(lineWidth);
    layout->addLayout(lineLength);
    layout->addLayout(lineAngle);
    layout->addLayout(lineColor);
    layout->addLayout(lineColorCustom);
    layout->addLayout(lineStyle);
    layout->addLayout(lineStyleCustom);
    layout->addItem(spacer);

    /* アイテムが選択された時に呼び出される。各Itemの値を設定し、settingStackとitemComboを現在のアイテムに切り替える */
    auto setThisWidget = [=](){
        lineAngle->setLineEditValue(lineItem->rotation());
        settingStack->setCurrentWidget(widget);
    };

    /* 各項目の初期化 */
    setThisWidget();
    lineWidth->setSpinBoxValue(lineItem->pen().width());
    lineLength->setLineEditValue(lineItem->line().length());
    lineColor->insertComboItems(0, colorNameList());
    lineColor->setComboCurrentIndex(QT_GLOBAL_COLOR_COUNT + 1);
    lineColorCustom->setColor(lineItem->pen().color());
    lineStyle->insertComboItems(0, enumToStrings(Graph2D::PenStyle(0)));
    lineStyle->setComboCurrentIndex(lineItem->pen().style());

    connect(lineItem, &GraphicsLineItem::itemSelected, setThisWidget);
    connect(lineWidth, &SpinBoxEditLayout::spinBoxValueChanged, lineItem, &GraphicsLineItem::setItemLineWidth);
    connect(lineLength, &LineEditLayout::lineValueEdited, lineItem, &GraphicsLineItem::setItemLineLength);
    connect(lineAngle, &LineEditLayout::lineValueEdited, lineItem, &GraphicsLineItem::setItemLineAngle);
    connect(lineColor, &ComboEditLayout::currentComboIndexChanged, lineColorCustom, &RGBEditLayout::setColorAndEditable);
    connect(lineColorCustom, &RGBEditLayout::colorEdited, lineItem, &GraphicsLineItem::setItemLineColor);
    connect(lineStyle, &ComboEditLayout::currentComboIndexChanged, lineItem, &GraphicsLineItem::setItemLineStyle);
    connect(lineStyleCustom, &LineEditLayout::lineTextEdited, lineItem, &GraphicsLineItem::setItemLineStyleCustom);
}

void GraphicsItemSetting::addRectItemSettingWidget(GraphicsRectItem *rectItem)
{
    itemCombo->addItem(QString::number(itemCount++) + "  " + "Rectangle Item");

    QWidget *widget = new QWidget(settingStack);
    QVBoxLayout *layout = new QVBoxLayout(widget);
    widget->setLayout(layout);
    settingStack->addWidget(widget);

    LineEditLayout *rectWidth = new LineEditLayout(widget, "Width", labelWidth, SETTING_EDIT_SWIDTH);
    LineEditLayout *rectHeight = new LineEditLayout(widget, "Height", labelWidth, SETTING_EDIT_SWIDTH);
    LineEditLayout *rotation = new LineEditLayout(widget, "Rotation", labelWidth, SETTING_EDIT_SWIDTH);
    SpinBoxEditLayout *borderWidth = new SpinBoxEditLayout(widget, "Border width", labelWidth);
    ComboEditLayout *borderColor = new ComboEditLayout(widget, "Border color", labelWidth);
    RGBEditLayout *borderColorCustom = new RGBEditLayout(widget, labelWidth);
    ComboEditLayout *borderStyle = new ComboEditLayout(widget, "Border style", labelWidth);
    LineEditLayout *borderStyleCustom = new LineEditLayout(widget, "", labelWidth);
    ComboEditLayout *fillColor = new ComboEditLayout(widget, "Fill color", labelWidth);
    RGBEditLayout *fillColorCustom = new RGBEditLayout(widget, labelWidth);
    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

    layout->addLayout(rectWidth);
    layout->addLayout(rectHeight);
    layout->addLayout(rotation);
    layout->addLayout(borderWidth);
    layout->addLayout(borderColor);
    layout->addLayout(borderColorCustom);
    layout->addLayout(borderStyle);
    layout->addLayout(borderStyleCustom);
    layout->addLayout(fillColor);
    layout->addLayout(fillColorCustom);
    layout->addItem(spacer);

    /* アイテムが選択された時に呼び出される。各Itemの値を設定し、settingStackとitemComboを現在のアイテムに切り替える */
    auto setThisWidget = [=](){
        rotation->setLineEditValue(rectItem->rotation());
        settingStack->setCurrentWidget(widget);
    };

    /* 各項目の値の初期化 */
    setThisWidget();
    rectWidth->setLineEditValue(rectItem->rect().width());
    rectHeight->setLineEditValue(rectItem->rect().height());
    borderWidth->setSpinBoxValue(rectItem->pen().width());
    borderColor->insertComboItems(0, colorNameList());
    borderColor->setComboCurrentIndex(QT_GLOBAL_COLOR_COUNT + 1);
    borderColorCustom->setColor(rectItem->pen().color());
    borderStyle->insertComboItems(0, enumToStrings(Graph2D::PenStyle(0)));
    borderStyle->setComboCurrentIndex(rectItem->pen().style());
    fillColor->insertComboItems(0, colorNameList());
    fillColor->setComboCurrentIndex(QT_GLOBAL_COLOR_COUNT);
    fillColorCustom->setColor(rectItem->brush().color());

    connect(rectItem, &GraphicsRectItem::itemSelected, setThisWidget);
    connect(rectWidth, &LineEditLayout::lineValueEdited, rectItem, &GraphicsRectItem::setItemWidth);
    connect(rectHeight, &LineEditLayout::lineValueEdited, rectItem, &GraphicsRectItem::setItemHeight);
    connect(rotation, &LineEditLayout::lineValueEdited, rectItem, &GraphicsRectItem::setItemAngle);
    connect(borderWidth, &SpinBoxEditLayout::spinBoxValueChanged, rectItem, &GraphicsRectItem::setItemBorderWidth);
    connect(borderColor, &ComboEditLayout::currentComboIndexChanged, borderColorCustom, &RGBEditLayout::setColorAndEditable);
    connect(borderColorCustom, &RGBEditLayout::colorEdited, rectItem, &GraphicsRectItem::setItemBorderColor);
    connect(borderStyle, &ComboEditLayout::currentComboIndexChanged, rectItem, &GraphicsRectItem::setItemBorderStyle);
    connect(borderStyleCustom, &LineEditLayout::lineTextEdited, rectItem, &GraphicsRectItem::setItemBorderStyleCustom);
    connect(fillColor, &ComboEditLayout::currentComboIndexChanged, fillColorCustom, &RGBEditLayout::setColorAndEditable);
    connect(fillColorCustom, &RGBEditLayout::colorEdited, rectItem, &GraphicsRectItem::setItemFillColor);
}

void GraphicsItemSetting::addEllipseItemSettingWidget(GraphicsEllipseItem *ellipseItem)
{
    itemCombo->addItem(QString::number(itemCount++) + "  " + "Ellipse Item");

    QWidget *widget = new QWidget(settingStack);
    QVBoxLayout *layout = new QVBoxLayout(widget);
    widget->setLayout(layout);
    settingStack->addWidget(widget);

    LineEditLayout *ellipseWidth = new LineEditLayout(widget, "Width", labelWidth, SETTING_EDIT_SWIDTH);
    LineEditLayout *ellipseHeight = new LineEditLayout(widget, "Height", labelWidth, SETTING_EDIT_SWIDTH);
    LineEditLayout *rotation = new LineEditLayout(widget, "Rotation", labelWidth, SETTING_EDIT_SWIDTH);
    SpinBoxEditLayout *spanAngle = new SpinBoxEditLayout(widget, "Span angle", labelWidth);
    SpinBoxEditLayout *startAngle = new SpinBoxEditLayout(widget, "Start angle", labelWidth);
    SpinBoxEditLayout *borderWidth = new SpinBoxEditLayout(widget, "Border width", labelWidth);
    ComboEditLayout *borderColor = new ComboEditLayout(widget, "Border color", labelWidth);
    RGBEditLayout *borderColorCustom = new RGBEditLayout(widget, labelWidth);
    ComboEditLayout *borderStyle = new ComboEditLayout(widget, "Border style", labelWidth);
    LineEditLayout *borderStyleCustom = new LineEditLayout(widget, "", labelWidth);
    ComboEditLayout *fillColor = new ComboEditLayout(widget, "Fill color", labelWidth);
    RGBEditLayout *fillColorCustom = new RGBEditLayout(widget, labelWidth);

    layout->addLayout(ellipseWidth);
    layout->addLayout(ellipseHeight);
    layout->addLayout(rotation);
    layout->addLayout(spanAngle);
    layout->addLayout(startAngle);
    layout->addLayout(borderWidth);
    layout->addLayout(borderColor);
    layout->addLayout(borderColorCustom);
    layout->addLayout(borderStyle);
    layout->addLayout(borderStyleCustom);
    layout->addLayout(fillColor);
    layout->addLayout(fillColorCustom);

    /* アイテムが選択された時に呼び出される。各Itemの値を設定し、settingStackとitemComboを現在のアイテムに切り替える */
    auto setThisWidget = [=](){
        rotation->setLineEditValue(ellipseItem->rotation());
        settingStack->setCurrentWidget(widget);
    };

    /* 各項目の値を初期化 */
    setThisWidget();
    ellipseWidth->setLineEditValue(ellipseItem->rect().width());
    ellipseHeight->setLineEditValue(ellipseItem->rect().height());
    spanAngle->setSpinBoxMaxValue(360 * 16);
    spanAngle->setSpinBoxValue(ellipseItem->spanAngle());
    startAngle->setSpinBoxMaxValue(360 * 16);
    startAngle->setSpinBoxValue(ellipseItem->startAngle());
    borderWidth->setSpinBoxValue(ellipseItem->pen().width());
    borderColor->insertComboItems(0, colorNameList());
    borderColor->setComboCurrentIndex(QT_GLOBAL_COLOR_COUNT + 1);
    borderColorCustom->setColor(ellipseItem->pen().color());
    borderStyle->insertComboItems(0, enumToStrings(Graph2D::PenStyle(0)));
    borderStyle->setComboCurrentIndex(ellipseItem->pen().style());
    fillColor->insertComboItems(0, colorNameList());
    fillColor->setComboCurrentIndex(QT_GLOBAL_COLOR_COUNT + 1);
    fillColorCustom->setColor(ellipseItem->brush().color());

    connect(ellipseItem, &GraphicsEllipseItem::itemSelected, setThisWidget);
    connect(ellipseWidth, &LineEditLayout::lineValueEdited, ellipseItem, &GraphicsEllipseItem::setItemWidth);
    connect(ellipseHeight, &LineEditLayout::lineValueEdited, ellipseItem, &GraphicsEllipseItem::setItemHeight);
    connect(rotation, &LineEditLayout::lineValueEdited, ellipseItem, &GraphicsEllipseItem::setItemAngle);
    connect(spanAngle, &SpinBoxEditLayout::spinBoxValueChanged, ellipseItem, &GraphicsEllipseItem::setItemSpanAngle);
    connect(startAngle, &SpinBoxEditLayout::spinBoxValueChanged, ellipseItem, &GraphicsEllipseItem::setItemStartAngle);
    connect(borderWidth, &SpinBoxEditLayout::spinBoxValueChanged, ellipseItem, &GraphicsEllipseItem::setItemBorderWidth);
    connect(borderColor, &ComboEditLayout::currentComboIndexChanged, borderColorCustom, &RGBEditLayout::setColorAndEditable);
    connect(borderColorCustom, &RGBEditLayout::colorEdited, ellipseItem, &GraphicsEllipseItem::setItemBorderColor);
    connect(borderStyle, &ComboEditLayout::currentComboIndexChanged, ellipseItem, &GraphicsEllipseItem::setItemBorderStyle);
    connect(borderStyleCustom, &LineEditLayout::lineTextEdited, ellipseItem, &GraphicsEllipseItem::setItemBorderStyleCustom);
    connect(fillColor, &ComboEditLayout::currentComboIndexChanged, fillColorCustom, &RGBEditLayout::setColorAndEditable);
    connect(fillColorCustom, &RGBEditLayout::colorEdited, ellipseItem, &GraphicsEllipseItem::setItemFillColor);
}





























