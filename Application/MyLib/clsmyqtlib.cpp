#include "clsmyqtlib.h"

ClsMyQTLib::ClsMyQTLib()
{

}

QString ClsMyQTLib::fnShowDirectoryBrowser(){
    QFileDialog qfd;
    qfd.setFileMode(QFileDialog::Directory);
    qfd.setOption(QFileDialog::ShowDirsOnly);
    qfd.setModal(true);
    qfd.show();
    qfd.exec();
    return qfd.selectedFiles().at(0);
}

QString ClsMyQTLib::fnShowFileBrowser(QString FileNameFilter){
    QFileDialog qfd;
    qfd.setFileMode(QFileDialog::AnyFile);

    //qfd.setNameFilter("Java Class files (*.class)");
    //qfd.setNameFilter("Java files (*.java)");
    qfd.setNameFilter(FileNameFilter);
    qfd.setModal(true);
    qfd.show();
    qfd.exec();
    return qfd.selectedFiles().at(0);
}

int ClsMyQTLib::fnMsgBox(MsgType msgType, QString strMsg,QString strInformativeText){
    QMessageBox msgBox;
    //msgBox.setText("The document has been modified.");
    //msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setText(strMsg);
    msgBox.setInformativeText(strInformativeText);
    //msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    //msgBox.setDefaultButton(QMessageBox::Save);

    //if(msgType==Information)
    switch(msgType)  {
    case Information:
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.setIcon(QMessageBox::Information);
        break;
    case Question:
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.setIcon(QMessageBox::Question);
        break;
    case Error:
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.setIcon(QMessageBox::Critical);
        break;
    case Warning:
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.setIcon(QMessageBox::Warning);
        break;
    }


    return msgBox.exec();
}

QString ClsMyQTLib::fnInputBox(QString strTitle, QString strMsg,QString strDefaultValue){
    QInputDialog InputBox;
    InputBox.setLabelText(strMsg);
    InputBox.setTextValue(strDefaultValue);
    //return InputBox.exec();
    return InputBox.getText(0,strTitle, strMsg,QLineEdit::Normal,strDefaultValue);
}
