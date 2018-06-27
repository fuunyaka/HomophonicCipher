#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "homo_cipher.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::on_keyButton_clicked(void){
    QString filename;
    filename = QFileDialog::getOpenFileName(this, "Файл ключа", "./", "Text file (*.txt);;All Files (*)");

    ui->keyFile->setText(filename);
    ui->keyFile->setToolTip(filename);
}

void MainWindow::on_plainButton_clicked(void){
    QString filename;
    filename = QFileDialog::getOpenFileName(this, "Файл текста", "./", "Text file (*.txt);;All Files (*)");

    ui->plainFile->setText(filename);
    ui->plainFile->setToolTip(filename);
}
void MainWindow::on_outputButton_clicked(void){
    QString filename;
    filename = QFileDialog::getSaveFileName(this, "Файл шифротекста", "./", "Text file (*.txt);;All Files (*)");

    ui->outFile->setText(filename);
    ui->outFile->setToolTip(filename);
}

void MainWindow::on_Encrypt_clicked(void){
    QFile plain_file(ui->plainFile->text());
    QFile out_file(ui->outFile->text());
    QFile key_file(ui->keyFile->text());

    if (!plain_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::information(this, tr("Ошибка при чтении файла"), plain_file.errorString());
        return;
    }

    if (!out_file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        QMessageBox::information(this, tr("Ошибка при чтении файла"), out_file.errorString());
        return;
    }

    if (!key_file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        QMessageBox::information(this, tr("Ошибка при чтении файла"), key_file.errorString());
        return;
    }

    QTextStream out(&out_file);
    QTextStream in(&plain_file);
    QTextStream key(&key_file);

    QStringList data = in.readAll().split("\n\n");

    for(QStringList::iterator i = data.begin(); i < data.end(); ++i){
        homo_cipher HomoHomo(*i);
        key << HomoHomo.get_key() << '\n';
        out << HomoHomo.encrypt(*i) << '\n';
    }
}

void MainWindow::on_Decrypt_clicked(void){
    QFile cipher_file(ui->plainFile->text());
    QFile out_file(ui->outFile->text());
    QFile key_file(ui->keyFile->text());

    if (!cipher_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::information(this, tr("Ошибка при чтении файла"), cipher_file.errorString());
        return;
    }

    if (!out_file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        QMessageBox::information(this, tr("Ошибка при чтении файла"), out_file.errorString());
        return;
    }

    if (!key_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::information(this, tr("Ошибка при чтении файла"), key_file.errorString());
        return;
    }

    QTextStream out(&out_file);
    QTextStream in(&cipher_file);
    QTextStream key(&key_file);

    QStringList data = in.readAll().split("\n\n");
    QStringList key_data= key.readAll().split("\n\n");

    for(QStringList::iterator i = data.begin(), j = key_data.begin(); i < data.end() && j < key_data.end(); ++i, ++j){
        homo_cipher HomoHomo;

        if(!(*i).isEmpty() && !(*j).isEmpty()){
            HomoHomo.set_key(*j);

            out << HomoHomo.decrypt(*i) << '\n';
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
