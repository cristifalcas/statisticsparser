#ifndef PARSE_H
#define PARSE_H

#include <QFile>
#include <QString>
#include <QList>
#include <QDateTime>
#include <QRegExp>
#include <QtDebug>
#include <QMap>

#include "rrdtool.h"

#define SAMPLE_INTERVAL 30

const QString stringDSType[] = {
    "GAUGE",
    "COUNTER",
    "DERIVE",
    "ABSOLUTE"
};

class Parse
{
public:
    Parse(QFileInfo name);
    Parse();
    ~Parse();
    int run();
    void setStatsFilename(QFileInfo name);
    void setRRDFileName(QFileInfo name);

protected:
    quint64 lineNumber, blockNumber, intTime, error, blockLineNumber, lasttimestamp;
    QFile statisticsfile;
    QByteArray block, line;
    QList<QByteArray> header;
    QList<double> crtBlockValues;

    struct datasource {
        QStringList datasourcesType, datasourcesName;
        QStringList datasourcesMin, datasourcesMax;
        QMap<quint64, QList<double> > values;
    } ds;
    enum typeDSType {
        yGAUGE,
        yCOUNTER,
        yDERIVE,
        yABSOLUTE,
        yDSTYPELAST
    } dstype;

    void setError(int, QByteArray = "");
    void timeIncrement();
    void timeFromLine();
    void printMap();
    virtual void setDatasourceInfo();
    virtual void setTime();
    virtual int process_line() = 0;
    virtual bool newBlock();
    virtual void buildHeaders();
private:
    RRDTool *rrd;
    QRegExp date_regex;
    void sendToRRD();
    void clear();
    void init();
    bool isValidData();
};

#endif // PARSE_H
