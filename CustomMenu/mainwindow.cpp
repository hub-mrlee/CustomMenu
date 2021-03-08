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
    m_parser = new DCustomActionParser(false, nullptr);
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
    QMenu menu;
    QList<QAction *> tempActs;
    if(m_addCustom){
        loadCompositeCustom(tempActs);
        tempActs = tempActs + m_defaultActs;
    }else {
        tempActs = m_defaultActs;
    }
    for (const auto act : tempActs) {
        menu.addAction(act);
        menu.addSeparator();
    }
    QPoint t_tmpPoint = QCursor::pos();
    menu.popup(t_tmpPoint);
    menu.exec();
}

void MainWindow::loadCompositeCustom(QList<QAction *> &customActs)
{
    auto tempEntry = m_parser->getActionFiles();
    for (const auto &temp : tempEntry) {
        QAction *tempAction = new QAction(temp.data().name());
        customActs.append(tempAction);
    }
}

void MainWindow::loadDefaultMenu()
{

}


void MainWindow::on_addCustom_clicked()
{
    m_addCustom = !m_addCustom;
}
