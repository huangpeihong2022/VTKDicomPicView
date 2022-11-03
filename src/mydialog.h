#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QString>

class MyDialog : public QWidget
{
    Q_OBJECT
public:
//    explicit MyDialog(QWidget *parent = nullptr);
    void Wraningdlg();
    QStringList OpenFile();
    QString OpenDir();
signals:

};

#endif // MYDIALOG_H
