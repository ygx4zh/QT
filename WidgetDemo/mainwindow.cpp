#include "mainwindow.h"
// #include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    text1 = new QTextEdit;
    QFont f;
    f.setPixelSize(20);
    text1->setFont(f);
    QColor color;
    color.setRgb(255, 0, 255);
    text1->setTextColor(color);
    this->setCentralWidget(text1);      // 将TextEdit放到对话框的中间

    // 在当前window的菜单栏添加菜单文件
    file = this ->menuBar()->addMenu("文件");

    // 点击时候的下滑菜单
    file_open = new QAction("打开",this);
    file_open->setShortcut(tr("Ctrl+O"));

    file_save = new QAction("保存", this);
    file_save->setShortcut(tr("Ctrl+S"));

    file_exit = new QAction("Exit",this);
    file_exit->setShortcut(tr("Ctrl+E"));

    file->addAction(file_open);
    file->addSeparator();               // 分隔线
    file->addAction(file_save);
    file->addSeparator();
    file->addAction(file_exit);

    // 参数一: 触发这个事件的控件, 第二个参数是对于ACTION来讲, 固定写法SIGNAL(triggered())
    // 参数三: 固定写this
    // 参数四: 指定点击Action后会执行哪个函数
    connect(file_open, SIGNAL(triggered()), this, SLOT(on_open()));
    connect(file_save, SIGNAL(triggered()), this, SLOT(on_save()));
    connect(file_exit, SIGNAL(triggered()), this, SLOT(on_exit()));

    edit = this ->menuBar()->addMenu("编辑");
    edit_copy = new QAction("拷贝", this);
    edit_copy->setShortcut(tr("Ctrl+C"));
    edit_paste = new QAction("粘贴", this);
    edit_paste->setShortcut(tr("Ctrl+P"));
    edit_cut = new QAction("剪切", this);
    edit_cut->setShortcut(tr("Ctrl+Z"));
    edit_select_all = new QAction("select all", this);
    edit_select_all->setShortcut(tr("Ctrl+A"));

    edit->addAction(edit_copy);
    edit->addSeparator();
    edit->addAction(edit_paste);
    edit->addSeparator();
    edit->addAction(edit_cut);
    edit->addSeparator();
    edit->addAction(edit_select_all);
    edit->addSeparator();

    connect(edit_copy, SIGNAL(triggered()), this, SLOT(on_copy()));
    connect(edit_paste, SIGNAL(triggered()), this, SLOT(on_paste()));
    connect(edit_cut, SIGNAL(triggered()), this, SLOT(on_cut()));
    connect(edit_select_all, SIGNAL(triggered()), this, SLOT(on_select_all()));

    build = this -> menuBar()->addMenu("构建");
    compile = new QAction("编译",this);
    compile->setShortcut(tr("Ctrl+B"));
    run = new QAction("执行",this);
    run->setShortcut(tr("Ctrl+R"));

    build->addAction(compile);
    build->addSeparator();
    build->addAction(run);

    connect(compile, SIGNAL(triggered(bool)), this, SLOT(on_compile()));
    connect(run, SIGNAL(triggered(bool)), this, SLOT(on_run()));

    help = this ->menuBar()->addMenu("帮助");
    help_about = new QAction("关于", this);
    help_about->setShortcut(tr("Ctrl+H"));
    help->addAction(help_about);
    connect(help_about, SIGNAL(triggered(bool)), this, SLOT(on_about()));
}

MainWindow::~MainWindow()
{
   //  delete ui;
    delete text1;
}

void MainWindow:: on_open()
{
    // QMessageBox::information(this, "提示","测试");
    QString filename = QFileDialog::getOpenFileName();
    // QMessageBox::information(this, "提示",filename);
    if(filename.isEmpty())
    {
        // QMessageBox::information(this, "提示","");
        return;
    }

    // QMessageBox::information(this, "提示",filename);
    // const char *f_n = filename.toStdString().data();
    // FILE *p = fopen(f_n, "r");
    FILE *p = fopen(filename.toStdString().data(), "r");
    if(p == NULL)
    {
        QMessageBox::information(this, "提示","文件打开失败");
        return;
    }

    QString content;
    char buf[1024] = {0};
    while(!feof(p))
    {
        fgets(buf, sizeof(buf),p);
        content += buf;
    }
    fclose(p);
    text1->setText(content);
    file_name = filename;
}

void MainWindow::on_about()
{
    QMessageBox::information(this, "Abount","ygx Copyright 2018");
}

void MainWindow::on_exit()
{
    QMessageBox::information(this, "hint","exit");
    exit(0);
}

void MainWindow::on_copy()
{
    text1->copy();
}

void MainWindow::on_paste()
{
    text1->paste();
}

void MainWindow::on_cut()
{
    text1->cut();
}

void MainWindow::on_select_all()
{
    text1 -> selectAll();
}

void MainWindow::on_save()
{
    // QFileDialog::getSaveFileName();  //获取保存的路径
    // const char* content_text = text1->toPlainText().toStdString().data()
    QString save_name = QFileDialog::getSaveFileName();
    if(save_name.isEmpty())
    {
        return;
    }

    FILE *p = fopen(save_name.toStdString().data(), "w");
    if(p == NULL)
    {
        QMessageBox::information(this, "打开文件","打开文件失败");
        return;
    }

    fputs(text1->toPlainText().toStdString().data(), p);
    fclose(p);
    file_name = save_name;
}

void MainWindow::on_compile()
{
    // QMessageBox::information(this, "wtf1",file_name);
    if(file_name.isEmpty())
    {
        QMessageBox::information(this, "Error","No Compilable file");
        return;
    }
    /*QString executable_file_path = file_name.replace(".c",".exe");
    QString compile_command = "gcc -o "+executable_file_path+" "+file_name;*/
    // QString executable_file_path = file_name.replace(".java",".class");
    QString compile_command = "javac "+file_name;
    QMessageBox::information(this, "Error",compile_command);
    system(compile_command.toStdString().data());
}

void MainWindow::on_run()
{
    if(file_name.isEmpty())
    {
        QMessageBox::information(this, "error","no executable file");
        return;
    }

    int index = file_name.lastIndexOf("/");

    // 指定路径运行.class文件
    // java -cp D:/code/test;. JavaApp
    QString path = file_name.left(index);   // D:/code/test
    QString file = file_name.right(index);
    QString s = "java -cp " + path+";. "+file.replace(".java","");
    QMessageBox::information(this, "Error",s);
    system(s.toStdString().data());
}
