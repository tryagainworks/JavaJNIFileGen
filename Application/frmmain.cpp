#include "frmmain.h"
#include "ui_frmmain.h"
#include "testclass.h"
#include "ClsCreateHeaderFile_CPP.h"
#include <vector>
#include <string>

FrmMain::FrmMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FrmMain)
{
    ui->setupUi(this);
    this->setMaximumSize(this->width(),this->height());
    //fnCodeTestArea();
    fnLoadAllProfiles();
    fnPoupMenuSetup();
}

FrmMain::~FrmMain()
{
    delete ui;
}

void FrmMain::fnCodeTestArea(){
    ui->txtJNI_h->setPlainText("Apple");
}

void FrmMain::on_cmdGenFiles_clicked()
{
    clsGenFiles c;
    vector<string> strValue;
    strValue.push_back(ClsFileSettings::me()->JAVAH_PATH);
    strValue.push_back(ui->txtOutDir->toPlainText().toStdString());
    strValue.push_back(ui->txtClsPth->toPlainText().toStdString());
    strValue.push_back(ui->txtClsFile->toPlainText().toStdString());
    strValue.push_back(ui->txtJavaFile->toPlainText().toStdString());
    strValue.push_back(ui->txtJNI_h->toPlainText().toStdString());
    strValue.push_back(ui->txtJNI_cpp->toPlainText().toStdString());
    strValue.push_back(ui->txtCls_h->toPlainText().toStdString());
    strValue.push_back(ui->txtCls_cpp->toPlainText().toStdString());
    c.fnGenFiles(strValue);
}

void FrmMain::on_cmdBrowseOutDir_clicked()
{
    ui->txtOutDir->setPlainText(objQtLib.fnShowDirectoryBrowser());
}

void FrmMain::on_cmdBrowseClsPth_clicked()
{
    ui->txtClsPth->setPlainText(objQtLib.fnShowDirectoryBrowser());
}

void FrmMain::on_cmdBrowseClsFile_clicked()
{
    if(ui->txtClsPth->toPlainText().isEmpty()){
        objQtLib.fnMsgBox(Information,"Please select the class path and proceed.","");
        return;
    }
    QString strClass = objQtLib.fnShowFileBrowser("Class Files (*.class)");
    strClass.remove(0,ui->txtClsPth->toPlainText().size()+1); //add one more '/' char
    strClass.replace("/",".");
    strClass.replace(".class","");
    ui->txtClsFile->setPlainText(strClass);
}

void FrmMain::fnClearEditableCtrls(){
    ui->txtClsFile->clear();
    ui->txtClsPth->clear();
    ui->txtOutDir->clear();
    ui->txtOutName->clear();
    ui->txtJavaFile->clear();
}
void FrmMain::fnClearNonEditableCtrls(){
    ui->txtCls_cpp->clear();
    ui->txtCls_h->clear();
    ui->txtJNI_cpp->clear();
    ui->txtJNI_h->clear();
}

void FrmMain::fnPoupMenuSetup()
{
    actFolder = new QAction("Select Folder",this);
    actSingleCPJar = new QAction("Select Single Jar File",this);
    actMultiJar = new QAction("Select \\* (Multi Jar)",this);
    actDeleteMultiCP = new QAction("Delete Selected Entry(s)",this);

    mnuPopupMultiCPPath = new QMenu(this);

    mnuPopupMultiCPPath->addAction(actFolder);
    mnuPopupMultiCPPath->addAction(actSingleCPJar);
    mnuPopupMultiCPPath->addAction(actMultiJar);
    mnuPopupMultiCPPath->addAction(actDeleteMultiCP);

    ui->cmdBrowseMultiClsPth->setMenu(mnuPopupMultiCPPath);

    connect(actFolder,SIGNAL(triggered(bool)),this,SLOT(on_FolderSelect()));
    connect(actSingleCPJar,SIGNAL(triggered(bool)),this,SLOT(on_SingleJarSelect()));
    connect(actMultiJar,SIGNAL(triggered(bool)),this,SLOT(on_MultiJarSelect()));
    connect(actDeleteMultiCP,SIGNAL(triggered(bool)),this,SLOT(on_DeleteMultiCP()));

    actSingleBootCPJar = new QAction("Select Single Jar File",this);
    actDeleteMultiBootCP = new QAction("Delete Selected Entry(s)",this);

    mnuPopupMultiBootCPPath = new QMenu(this);

    mnuPopupMultiBootCPPath->addAction(actSingleBootCPJar);
    mnuPopupMultiBootCPPath->addAction(actDeleteMultiBootCP);

    ui->cmdBrowseMultiBootClsPth->setMenu(mnuPopupMultiBootCPPath);

    connect(actSingleBootCPJar,SIGNAL(triggered(bool)),this,SLOT(on_SingleJarSelect_BCP()));
    connect(actDeleteMultiBootCP,SIGNAL(triggered(bool)),this,SLOT(on_DeleteMultiCP_BCP()));
}

void FrmMain::fnGetFieldValues(vector<string> &strValue){
    strValue.push_back(ui->txtClsFile->toPlainText().toStdString());
    strValue.push_back(ui->txtClsPth->toPlainText().toStdString());
    strValue.push_back(ui->txtCls_cpp->toPlainText().toStdString());
    strValue.push_back(ui->txtCls_h->toPlainText().toStdString());
    strValue.push_back(ui->txtJNI_cpp->toPlainText().toStdString());
    strValue.push_back(ui->txtJNI_h->toPlainText().toStdString());
    strValue.push_back(ui->txtOutDir->toPlainText().toStdString());
    strValue.push_back(ui->txtOutName->toPlainText().toStdString());
    strValue.push_back(ui->txtJavaFile->toPlainText().toStdString());
    strValue.push_back(ui->optFileApndDateTime->isChecked() ? "Append" : "Not Append" );
}

void FrmMain::fnSetFieldValues(vector<string> &strValue){
    fnClearEditableCtrls();
    fnClearNonEditableCtrls();
    if(strValue.size()>=10){
        ui->txtClsFile->setPlainText(QString::fromStdString(strValue[0]));
        ui->txtClsPth->setPlainText(QString::fromStdString(strValue[1]));
        ui->txtOutDir->setPlainText(QString::fromStdString(strValue[6]));
        ui->txtOutName->setPlainText(QString::fromStdString(strValue[7]));
        ui->txtJavaFile->setPlainText(QString::fromStdString(strValue[8]));
        ui->txtCls_cpp->setPlainText(QString::fromStdString(strValue[2]));
        ui->txtCls_h->setPlainText(QString::fromStdString(strValue[3]));
        ui->txtJNI_cpp->setPlainText(QString::fromStdString(strValue[4]));
        ui->txtJNI_h->setPlainText(QString::fromStdString(strValue[5]));

        strValue[9].find("Not")==string::npos ? ui->optFileApndDateTime->setChecked(true) : ui->optFileOverWrite->setChecked(true);
        //ui->optFileApndDateTime->isChecked() ? "Append" : "Not Append" );
    }
}

void FrmMain::fnLoadProfileData(){
    vector<string> strValue;
    string str = ClsFileSettings::me()->PROFILE_BASE_PATH;
    str.append(ui->cboProfiles->currentText().toStdString());
    objStdLib.fnReadDataFromFile(str,strValue);
    fnSetFieldValues(strValue);
}

void FrmMain::fnLoadAllProfiles(){
    vector<string> strValue;
    objStdLib.fnGetAllFiles(strValue,ClsFileSettings::me()->PROFILE_BASE_PATH);
    ui->cboProfiles->clear();
    for(vector<string>::iterator itr = strValue.begin();itr!=strValue.end();itr++){
        ui->cboProfiles->addItem(QString::fromStdString(*itr));
    }
    ui->cboProfiles->setCurrentIndex(0);
}

void FrmMain::on_cmdCreateProfile_clicked()
{
    bool blnCreteOnly=false;
    if(objQtLib.fnMsgBox(Question,"Clear Parameters", "Do you want to clear the parameters?")==QMessageBox::Ok){
        fnClearEditableCtrls();
        fnClearNonEditableCtrls();
        blnCreteOnly=true;
    }else{
        blnCreteOnly=false;
    }
    QString strFileName = objQtLib.fnInputBox("Profile Name","Enter Profile Name","NewProfile");
    if(blnCreteOnly){
        strFileName.insert(0,QString::fromStdString(ClsFileSettings::me()->PROFILE_BASE_PATH));
        ui->cboProfiles->addItem(QString::fromStdString(objStdLib.fnCreateFile(strFileName.toStdString(),ClsFileSettings::me()->GLOBAL_EXTN,true)));
    }else{
        vector<string> strValue;
        fnGetFieldValues(strValue);
        strFileName.insert(0,QString::fromStdString(ClsFileSettings::me()->PROFILE_BASE_PATH));
        ui->cboProfiles->addItem(QString::fromStdString(objStdLib.fnWriteDataToFile(strValue, strFileName.toStdString(),ClsFileSettings::me()->GLOBAL_EXTN,true)));
    }
    ui->cboProfiles->setCurrentIndex(ui->cboProfiles->count()-1);
}

void FrmMain::on_cboProfiles_currentIndexChanged(const QString &arg1)
{
    fnLoadProfileData();
}

void FrmMain::on_cmsSaveArgs_clicked()
{
    vector<string> strValues;
    fnGetFieldValues(strValues);
    objStdLib.fnUpdateDataToFile(strValues,(ClsFileSettings::me()->PROFILE_BASE_PATH + ui->cboProfiles->currentText().toStdString()));
}

void FrmMain::on_txtOutName_textChanged()
{
    string strDateTime;
    QString strValue = ui->txtOutName->toPlainText();
    if(strValue!=""){
        if(ui->optFileApndDateTime->isChecked()){
            strDateTime = objStdLib.fnGetCurrDateTime();
        }
        //ui->txtCls_cpp->setPlainText(strValue + QString::fromStdString("_" + strDateTime + ClsFileSettings::me()->CPP_CPP_Suffix));
        //ui->txtCls_h->setPlainText(strValue + QString::fromStdString("_" + strDateTime + ClsFileSettings::me()->CPP_H_Suffix));
        //ui->txtJNI_cpp->setPlainText(strValue + QString::fromStdString("_" + strDateTime + ClsFileSettings::me()->JNI_CPP_Suffix));
        //ui->txtJNI_h->setPlainText(strValue + QString::fromStdString("_" + strDateTime + ClsFileSettings::me()->JNI_H_Suffix));

        ui->txtCls_cpp->setPlainText(strValue + QString::fromStdString(ClsFileSettings::me()->CPP_CPP_Suffix));
        ui->txtCls_h->setPlainText(strValue + QString::fromStdString(ClsFileSettings::me()->CPP_H_Suffix));
        ui->txtJNI_cpp->setPlainText(strValue + QString::fromStdString(ClsFileSettings::me()->JNI_CPP_Suffix));
        ui->txtJNI_h->setPlainText(strValue + QString::fromStdString(ClsFileSettings::me()->JNI_H_Suffix));
    }
    else
    {
        fnClearNonEditableCtrls();
    }
}

void FrmMain::on_cmdBrowseJavaFile_clicked()
{
    ui->txtJavaFile->setPlainText(objQtLib.fnShowFileBrowser("Java Files (*.java)"));
}

void FrmMain::on_FolderSelect()
{
    ui->lstMultiClassPath->addItem(new QListWidgetItem(objQtLib.fnShowDirectoryBrowser()));
}

void FrmMain::on_SingleJarSelect()
{
    ui->lstMultiClassPath->addItem(new QListWidgetItem(objQtLib.fnShowFileBrowser("Jar Files (*.jar)")));
}

void FrmMain::on_MultiJarSelect()
{
    ui->lstMultiClassPath->addItem(new QListWidgetItem(objQtLib.fnShowDirectoryBrowser()+"/*"));
}

void FrmMain::on_DeleteMultiCP()
{
    QList<QListWidgetItem*> lst = ui->lstMultiClassPath->selectedItems();
    for(int iCount=0;iCount<lst.size();iCount++){
        //ui->lstMultiClassPath->->removeItemWidget(lst.at(iCount));
        delete lst.at(iCount);
    }
}

void FrmMain::on_SingleJarSelect_BCP()
{
    ui->lstMultiBootClassPath->addItem(new QListWidgetItem(objQtLib.fnShowFileBrowser("Jar Files (*.jar)")));
}

void FrmMain::on_DeleteMultiCP_BCP()
{
    QList<QListWidgetItem*> lst = ui->lstMultiBootClassPath->selectedItems();
    for(int iCount=0;iCount<lst.size();iCount++){
        //ui->lstMultiClassPath->->removeItemWidget(lst.at(iCount));
        delete lst.at(iCount);
    }
}

void FrmMain::on_cmdBrowseMultiClsPth_clicked()
{

}

void FrmMain::on_cmdBrowseMultiBootClsPth_clicked()
{
    ui->lstMultiBootClassPath->addItem(new QListWidgetItem(objQtLib.fnShowFileBrowser("Jar Files (*.jar)")));
}

void FrmMain::on_lstMultiClassPath_itemPressed(QListWidgetItem *item)
{

}
