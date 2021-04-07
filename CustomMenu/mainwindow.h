#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "customAcitons/dcustomactionparser.h"
#include <QMainWindow>
#include <QMenu>
#include <QAction>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void contextMenuEvent(QContextMenuEvent *event) override;
private slots:
    void on_addCustom_clicked();

private:
    void init();
    void defaultAcitons();
    void customActions();
    void loadMenu();
    void loadCompositeCustom(QMenu &tempMenu);
    void loadCustomAction(QAction *tempAc, const DCustomActionData &tempActData);
    void loadDefaultMenu();


private:
    Ui::MainWindow *ui;
    DCustomActionParser *m_parser = nullptr;
    QList<QAction *> m_defaultActs;
    bool m_addCustom = false;
    QString m_customPath;
};

#endif // MAINWINDOW_H
