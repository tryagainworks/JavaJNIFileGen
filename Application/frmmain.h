#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QMainWindow>
#include "MyLib/clsmystdlib.h"
#include "MyLib/clsmyqtlib.h"
#include <clsfilesettings.h>
#include <QAction>
#include <QMenu>
#include <QListWidget>

using namespace std;

namespace Ui {
class FrmMain;
}

class FrmMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit FrmMain(QWidget *parent = 0);
    ~FrmMain();

private slots:
    void on_cmdGenFiles_clicked();
    void on_cmdBrowseOutDir_clicked();

    void on_cmdBrowseClsPth_clicked();

    void on_cmdBrowseClsFile_clicked();

    void on_cmdCreateProfile_clicked();

    void on_cboProfiles_currentIndexChanged(const QString &arg1);

    void on_cmsSaveArgs_clicked();

    void on_txtOutName_textChanged();

    void on_cmdBrowseJavaFile_clicked();

    void on_cmdBrowseMultiClsPth_clicked();

    void on_FolderSelect();
    void on_SingleJarSelect();
    void on_MultiJarSelect();
    void on_DeleteMultiCP();
    void on_SingleJarSelect_BCP();
    void on_DeleteMultiCP_BCP();
    void on_cmdBrowseMultiBootClsPth_clicked();
    void on_lstMultiClassPath_itemPressed(QListWidgetItem *item);

private:
    Ui::FrmMain *ui;
    void fnCodeTestArea();
    void fnClearEditableCtrls();
    clsMySTDLib objStdLib;
    ClsMyQTLib objQtLib;
    void fnGetFieldValues(vector<string> &strValue);
    void fnLoadProfileData();
    void fnSetFieldValues(vector<string> &strValue);
    void fnLoadAllProfiles();
    void fnGetAllFiles(vector<string> &strValue);
    void fnClearNonEditableCtrls();
    QAction *actFolder, *actSingleCPJar, *actMultiJar, *actDeleteMultiCP, *actDeleteMultiBootCP, *actSingleBootCPJar;
    QMenu *mnuPopupMultiCPPath,*mnuPopupMultiBootCPPath;
    void fnPoupMenuSetup();
};

#endif // FRMMAIN_H
