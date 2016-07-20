#ifndef CLSMYQTLIB_H
#define CLSMYQTLIB_H

#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>

enum MsgType{
    Information,
    Question,
    Error,
    Warning
};

class ClsMyQTLib
{
public:
    ClsMyQTLib();

    QString fnShowFileBrowser(QString FileNameFilter);
    int fnMsgBox(MsgType msgType, QString strMsg, QString strInformativeText);
    QString fnShowDirectoryBrowser();

    QString fnInputBox(QString strTitle, QString strMsg,QString strDefaultValue);
};

#endif // CLSMYQTLIB_H
