#include "mydialog.h"

//MyDialog::MyDialog(QWidget *parent)
//    : QWidget{parent}
//{

//}

void MyDialog::Wraningdlg()
{
    QMessageBox::warning(this,"warning","Open file error!",QMessageBox::Ok);
}

QStringList MyDialog::OpenFile()
{
    QStringList path = QFileDialog::getOpenFileNames(this, "Open File", "", "(*.*)");
    return path;
}

QString MyDialog::OpenDir()
{
    QString path = QFileDialog::getExistingDirectory(this, "Open Dir");
    return path;
}
