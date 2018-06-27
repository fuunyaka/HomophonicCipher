#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_keyButton_clicked(void);
    void on_plainButton_clicked(void);
    void on_outputButton_clicked(void);
    void on_Encrypt_clicked(void);
    void on_Decrypt_clicked(void);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
