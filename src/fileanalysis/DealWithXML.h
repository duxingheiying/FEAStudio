#ifndef DEALWITHXML_H
#define DEALWITHXML_H

#include <QWidget>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QMessageBox>

class DealWithXML : public QWidget
{
    Q_OBJECT

public:
    explicit DealWithXML(QWidget *parent = nullptr);
    ~DealWithXML();

public:
    bool readXML(const QString xmlfile_);   // read xml file
    bool writeXML(const QString xmlfile_);  // writee xml file

protected:

private:
    QFile *m_pXMLFileToRead;
    QFile *m_pXMLFileToWrite;
    QXmlStreamReader *m_pXMLStreamToRead;
    QXmlStreamWriter *m_pXMLStreamToWrite;

public:

protected:

private:

signals:

public slots:
};

#endif // DEALWITHXML_H
