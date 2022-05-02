#include "componentmanager.h"

#include "custommesh/surfacegridgeometry.h"
#include "itemsettingwidget/grid_mesh_setting_widget.h"

/* component ---|--- BasicShape ---> BasicShapeSettingWidget
 *
 */


ComponentManager::ComponentManager(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *vLayout = new QVBoxLayout(this);
    addObjectButton = new QPushButton("Add object", this);
    objectTree = new ObjectTree(this);
    stackedWidget = new QStackedWidget(this);

    setLayout(vLayout);
    vLayout->addWidget(addObjectButton);
    vLayout->addWidget(objectTree);
    vLayout->addWidget(stackedWidget);

    initializeAddObjectMenu();
    vLayout->setSpacing(0);
    vLayout->setContentsMargins(0, 0, 0, 0);
    objectTree->setFixedHeight(100);

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
    QMenu *gridLine = new QMenu("Grid line", addObjectMenu);
        QAction *dynamicSurfaceGrid = new QAction("dynamic surface grid", gridLine);

    addObjectMenu->addMenu(basicShape);
        basicShape->addAction(cone);
        basicShape->addAction(cuboid);
        basicShape->addAction(cylinder);
        basicShape->addAction(plane);
        basicShape->addAction(sphere);
        basicShape->addAction(torus);
    addObjectMenu->addMenu(gridLine);
        gridLine->addAction(dynamicSurfaceGrid);

    connect(torus, &QAction::triggered, this, &ComponentManager::requestBasicShapeTorus);
    connect(plane, &QAction::triggered, this, &ComponentManager::requestBasicShapePlane);

    connect(dynamicSurfaceGrid, &QAction::triggered, this, &ComponentManager::requestDynamicSurfaceGrid);

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
    treeItem->setText(0, QString::number(++itemCounter) + "   " + meshWidget->objectName());
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

void ComponentManager::requestDynamicSurfaceGrid()
{
    SurfaceGridMesh *mesh = new SurfaceGridMesh();
    SurfaceGridMeshSettingWidget *w = new SurfaceGridMeshSettingWidget(mesh);
    requestBasicShape(mesh, w);

    emit animationAdded(w->animation());
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




