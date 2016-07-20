#include "frmjniheadergeneratortemp.h"
#include "ui_frmjniheadergeneratortemp.h"

frmJNIHeaderGeneratorTemp::frmJNIHeaderGeneratorTemp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::frmJNIHeaderGeneratorTemp)
{
    ui->setupUi(this);
}

frmJNIHeaderGeneratorTemp::~frmJNIHeaderGeneratorTemp()
{
    delete ui;
}

void frmJNIHeaderGeneratorTemp::on_cmdGenerate_clicked()
{
    QFileDialog objDlg(this,)
}
