#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QMenu>
#include <QMenuBar>
#include <QAction>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QTextEdit *text1;
    QMenu *file;
    QMenu *edit;
    QMenu *help;
    QMenu *build;

    QAction *file_open;
    QAction *file_save;
    QAction *file_exit;
    QAction *edit_open;
    QAction *help_open;

    QAction *help_about;

    QAction *edit_copy;
    QAction *edit_paste;
    QAction *edit_cut;
    QAction *edit_select_all;

    QAction *compile;
    QAction *run;

    QString file_name;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // slots必须写, 要不然connect的时候不起作用
private slots:
    void on_open();
    // 貌似必须要实现, 否则无法通过编译
    void on_about();
    void on_exit();
    void on_copy();
    void on_paste();
    void on_cut();
    void on_select_all();
    void on_save();
    void on_compile();
    void on_run();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
