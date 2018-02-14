#ifndef MASTERNODECONFIGDIALOG_H
#define MASTERNODECONFIGDIALOG_H

#include <QDialog>

namespace Ui {
    class MasterNodeConfigDialog;
}

QT_BEGIN_NAMESPACE
class QModelIndex;
QT_END_NAMESPACE

/** Dialog showing transaction details. */
class MasterNodeConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MasterNodeConfigDialog(QWidget *parent = 0, QString nodeAddress = "123.456.789.123:45130", QString privkey="MASTERNODEPRIVKEY");
    ~MasterNodeConfigDialog();

private:
    Ui::MasterNodeConfigDialog *ui;
};

#endif // MASTERNODECONFIGDIALOG_H
