#ifndef IOFILE_H
#define IOFILE_H

#include <QString>
#include <QFile>
#include <QTextStream>

inline bool toFileTxt(const QString& fileName, const QString& data)
{
    QFile file(fileName);

    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        out << data;
        file.close();
        return true;
    }

    return false;
}

inline bool toFileCsv(const QString& filename, const QList<QList<QString> >& sheet)
{
    QString data;
    for(qsizetype row = 0; row < sheet.size(); ++row){
        for(qsizetype col = 0; col < sheet.at(row).size(); ++col)
        {
            data += sheet.at(row).at(col);
            if(col != sheet.at(row).size() - 1) { data += ","; }
        }
        if(row != sheet.size() - 1) { data += "\n"; }
    }

    return toFileTxt(filename, data);
}

inline QString readFileTxt(const QString& fileName)
{
    QFile file(fileName);

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        const QString data = in.readAll();
        return data;
    }

    return "\0";
}

inline QList<QList<QString> > readFileCsv(const QString& fileName)
{
    const QString data = readFileTxt(fileName);  //ファイルの内容(text)をQString型で保持

    QList<QList<QString> > sheet(1);             //csvデータを2次元のQString型で返す
    qsizetype row = 0;                           //行数
    QString stack = "";                          //スタック

    for(const QChar& c : data)
    {
        if(c == '\n'){
            sheet[row] << stack;
            stack.clear();
            sheet.append(QList<QString>(0));
            row++;
        }
        else if(c == ','){
            sheet[row] << stack;
            stack.clear();
        }
        else
            stack += c;
    }
    sheet[row] << stack;

    return sheet;
}

#endif // IOFILE_H
