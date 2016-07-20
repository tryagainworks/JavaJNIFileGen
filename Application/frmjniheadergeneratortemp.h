#ifndef FRMJNIHEADERGENERATORTEMP_H
#define FRMJNIHEADERGENERATORTEMP_H

#include <QMainWindow>
#include <QFileDialog>

namespace Ui {
class frmJNIHeaderGeneratorTemp;
}

class frmJNIHeaderGeneratorTemp : public QMainWindow
{
    Q_OBJECT

public:
    explicit frmJNIHeaderGeneratorTemp(QWidget *parent = 0);
    ~frmJNIHeaderGeneratorTemp();

private slots:
    void on_cmdGenerate_clicked();

private:
    Ui::frmJNIHeaderGeneratorTemp *ui;
};

#endif // FRMJNIHEADERGENERATORTEMP_H
