#include "componentmanager.h"

/* component ---|--- BasicShape ---> BasicShapeSettingWidget
 *
 *
 *
 *
 *
 */

ComponentManager::ComponentManager(QWidget *parent)
    : QScrollArea(parent)
{
    QWidget *contents = new QWidget(this);
    QVBoxLayout *vLayout = new QVBoxLayout(contents);
    addObjectButton = new QPushButton("Add object", contents);
    objectTree = new ObjectTree(this);
    stackedWidget = new QStackedWidget(contents);
    QSpacerItem *item = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

    setWidget(contents);
    contents->setLayout(vLayout);
    vLayout->addWidget(addObjectButton);
    vLayout->addWidget(objectTree);
    vLayout->addWidget(stackedWidget);
    vLayout->addItem(item);

    setWidgetResizable(true);
    contents->setFixedWidth(300);
    initializeAddObjectMenu();

    connect(objectTree, &ObjectTree::objectSelected, stackedWidget, &QStackedWidget::setCurrentWidget);
}

void ComponentManager::initializeAddObjectMenu()
{
    addObjectMenu = new QMenu(addObjectButton);

    QMenu *basicShape = new QMenu("Basic shape", addObjectMenu);
        QAction *cone = new QAction("cone", basicShape);
        QAction *cuboid = new QAction("cuboid", basicShape);
        QAction *cylinder = new QAction("cylinder", basicShape);
        QAction *plane = new QAction("plane", basicShape);
        QAction *sphere = new QAction("sphere", basicShape);
        QAction *torus = new QAction("torus", basicShape);

    addObjectMenu->addMenu(basicShape);
        basicShape->addAction(cone);
        basicShape->addAction(cuboid);
        basicShape->addAction(cylinder);
        basicShape->addAction(plane);
        basicShape->addAction(sphere);
        basicShape->addAction(torus);

    connect(torus, &QAction::triggered, this, &ComponentManager::requestBasicShapeTorus);
    connect(plane, &QAction::triggered, this, &ComponentManager::requestBasicShapePlane);

    addObjectButton->setMenu(addObjectMenu);
}

void ComponentManager::requestBasicShape(Qt3DRender::QGeometryRenderer *mesh, QWidget *meshWidget)
{
    Qt3DCore::QEntity *entity = new Qt3DCore::QEntity();
    Qt3DRender::QMaterial *material = new Qt3DExtras::QPhongMaterial(entity);
    Qt3DCore::QTransform *transform = new Qt3DCore::QTransform(entity);
    mesh->setParent(entity);

    entity->addComponent(mesh);
    entity->addComponent(material);
    entity->addComponent(transform);

    /* 設定ページ(stackedWidget)への追加 */
    BasicShapeSettingWidget *widget = new BasicShapeSettingWidget(mesh, transform, material, meshWidget, this);
    stackedWidget->addWidget(widget);
    stackedWidget->setCurrentWidget(widget);

    /* オブジェクト一覧(objectTree)への追加 */
    ObjectTreeItem *treeItem = new ObjectTreeItem(objectTree, widget);
    static unsigned int itemCounter = 0;
    treeItem->setText(0, meshWidget->objectName() + " " + QString::number(++itemCounter));
    treeItem->setCheckState(0, Qt::CheckState::Checked);
    connect(treeItem, &ObjectTreeItem::clickedCheckState0, entity, &Qt3DCore::QEntity::setEnabled);

    emit objectAdded(entity);
    emit animationAdded(widget->animation());
}

void ComponentManager::requestBasicShapeTorus()
{
    Qt3DExtras::QTorusMesh *mesh = new Qt3DExtras::QTorusMesh();
    requestBasicShape(mesh, new TorusMeshSettingWidget(mesh));
}

void ComponentManager::requestBasicShapePlane()
{
    Qt3DExtras::QPlaneMesh *mesh = new Qt3DExtras::QPlaneMesh();
    requestBasicShape(mesh, new PlaneMeshSettingWidget(mesh));
}












ObjectTree::ObjectTree(QWidget *parent)
    : QTreeWidget(parent)
{
    setHeaderHidden(true);

    connect(this, &ObjectTree::itemClicked, this, &ObjectTree::emitClick);
    connect(this, &ObjectTree::itemDoubleClicked, this, &ObjectTree::emitSelectedObject);
}

void ObjectTree::emitClick(QTreeWidgetItem *item, int column)
{
    if(item == nullptr) return;
    emit static_cast<ObjectTreeItem*>(item)->clickedCheckState0((item->checkState(column) == Qt::Checked) ? true : false);
}

void ObjectTree::emitSelectedObject(QTreeWidgetItem *item, int column)
{
    if(item == nullptr)
        return;
    if(column == 0)
        emit objectSelected(static_cast<ObjectTreeItem*>(item)->settingWidget());
}




ObjectTreeItem::ObjectTreeItem(ObjectTreeItem *item, QWidget *settingWidget)
    : QTreeWidgetItem(item)
    , _settingWidget(settingWidget)
{

}

ObjectTreeItem::ObjectTreeItem(ObjectTree *tree, QWidget *settingWidget)
    : QTreeWidgetItem(tree)
    , _settingWidget(settingWidget)
{

}




