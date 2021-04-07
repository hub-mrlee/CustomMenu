#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QDebug>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("自定义菜单测试");
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    Q_UNUSED(event)
    loadMenu();
}

void MainWindow::init()
{
    m_parser = new DCustomActionParser(nullptr);
    defaultAcitons();

    m_customPath =  QCoreApplication::applicationDirPath() + "/CustomFile";
    m_parser->loadDir(m_customPath);

}

void MainWindow::defaultAcitons()
{
    QAction *temp1 = new QAction("默认菜单项一");
    QAction *temp2 = new QAction("默认菜单项二");
    QAction *temp3 = new QAction("默认菜单项三");
    QAction *temp4 = new QAction("默认菜单项四");
    QAction *temp5 = new QAction("默认菜单项五");
    QAction *temp6 = new QAction("默认菜单项六");

    m_defaultActs.append(temp1);
    m_defaultActs.append(temp2);
    m_defaultActs.append(temp3);
    m_defaultActs.append(temp4);
    m_defaultActs.append(temp5);
    m_defaultActs.append(temp6);
}

void MainWindow::customActions()
{

}

void MainWindow::loadMenu()
{
    //这里以顶部为自定义区域，
    QMenu menu;
    if(m_addCustom){
        loadCompositeCustom(menu);
    }
    for (const auto act : m_defaultActs) {
        menu.addAction(act);
    }
    QPoint t_tmpPoint = QCursor::pos();
    menu.popup(t_tmpPoint);
    menu.exec();
}

void MainWindow::loadCompositeCustom(QMenu &tempMenu)
{
    auto tempEntry = m_parser->getActionFiles(true);
    for (const auto &temp : tempEntry) {
        //top
        auto separator = temp.data().separator();
        //上分割线
        if (separator & DCustomActionDefines::Top) {
            tempMenu.addSeparator();
        }

        //add action
        QAction *tempAct = new QAction(temp.data().name());
        tempMenu.addAction(tempAct);

        //bottom
        if (separator & DCustomActionDefines::Bottom) {
            tempMenu.addSeparator();
        }
        if (temp.data().acitons().size() > 0)
            loadCustomAction(tempAct, temp.data());
    }
}

void MainWindow::loadCustomAction(QAction *tempAc, const DCustomActionData &tempActData)
{
     QMenu *tpMenu = new QMenu (this) ;
    auto acts = tempActData.acitons();

    for (const auto &temp : acts) {
        //top
        auto separator = temp.separator();
        //上分割线
        if (separator & DCustomActionDefines::Top) {
            tpMenu->addSeparator();
        }
        //add action
        QAction *tempAct = new QAction(temp.name());
        tpMenu->addAction(tempAct);

        //bottom
        if (separator & DCustomActionDefines::Bottom) {
            tpMenu->addSeparator();
        }
        if (temp.acitons().size() > 0)
            loadCustomAction(tempAct, temp);
    }

    tempAc->setMenu(tpMenu);
}

void MainWindow::loadDefaultMenu()
{

}


void MainWindow::on_addCustom_clicked()
{
    m_addCustom = !m_addCustom;
}
