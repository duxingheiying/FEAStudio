#include "DealWithXML.h"

#include <QMessageBox>
#include <QDebug>

DealWithXML::DealWithXML(QWidget *parent)
    : QWidget(parent)
{
    m_pXMLFileToRead = new QFile(this);
    m_pXMLFileToWrite = new QFile(this);
    m_pXMLStreamToRead = new QXmlStreamReader();
    m_pXMLStreamToWrite = new QXmlStreamWriter();

    readXML("InterfaceButtons.xml");
    writeXML("writeXml.xml");
}

bool DealWithXML::readXML(const QString xmlfile_)
{
    m_pXMLFileToRead->setFileName(xmlfile_);
    if (!m_pXMLFileToRead->open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this,"Load XML File Problem",
                              "Couldn't open m_pXMLFileToRead.xml to load settings for download",
                              QMessageBox::Ok);
        return false;
    }
//    m_pXMLStreamToRead = new QXmlStreamReader(m_pXMLFileToRead);
    m_pXMLStreamToRead->setDevice(m_pXMLFileToRead);

    //Parse the XML until we reach end of it
    while(!m_pXMLStreamToRead->atEnd() && !m_pXMLStreamToRead->hasError()) {
        // Read next element
        QXmlStreamReader::TokenType token = m_pXMLStreamToRead->readNext();
        //If token is just StartDocument - go to next
        if(token == QXmlStreamReader::StartDocument) {
            continue;
        }
        //If token is StartElement - read it
        if(token == QXmlStreamReader::StartElement) {
            if(m_pXMLStreamToRead->name() == "Root") {
                continue;
            }
            else if (m_pXMLStreamToRead->name() == "menubar") {
                continue;
            }
            else if (m_pXMLStreamToRead->name() == "file") {
                continue;
            }
            else if (m_pXMLStreamToRead->name() == "Button name") {
                qDebug() << m_pXMLStreamToRead->readElementText();
            }
            else if (m_pXMLStreamToRead->name() == "label") {
                qDebug() << m_pXMLStreamToRead->readElementText();
            }
            else if (m_pXMLStreamToRead->name() == "shortcut") {
                qDebug() << m_pXMLStreamToRead->readElementText();
            }
            else if (m_pXMLStreamToRead->name() == "picture") {
                qDebug() << m_pXMLStreamToRead->readElementText();
            }
            else if (m_pXMLStreamToRead->name() == "function") {
                qDebug() << m_pXMLStreamToRead->readElementText();
            }
            else if (m_pXMLStreamToRead->name() == "enabled") {
                qDebug() << m_pXMLStreamToRead->readElementText();
            }
            else if (m_pXMLStreamToRead->name() == "checkable") {
                qDebug() << m_pXMLStreamToRead->readElementText();
            }
        }
    }

    if(m_pXMLStreamToRead->hasError()) {
        QMessageBox::critical(this,
                              "m_pXMLFileToRead.xml Parse Error",m_pXMLStreamToRead->errorString(),
                              QMessageBox::Ok);
        return false;
    }

    //close reader and flush file
    m_pXMLStreamToRead->clear();
    m_pXMLFileToRead->close();

    return true;
}

bool DealWithXML::writeXML(const QString xmlfile_)
{
    m_pXMLFileToWrite->setFileName( xmlfile_ );
    if (!m_pXMLFileToWrite->open(QFile::WriteOnly | QFile::Text)) {
        qDebug() << "Error: Cannot write file: "
                 << qPrintable(m_pXMLFileToWrite->errorString());
        return false;
    }

    m_pXMLStreamToWrite->setDevice(m_pXMLFileToWrite);
    m_pXMLStreamToWrite->setAutoFormatting(true);
    m_pXMLStreamToWrite->writeStartDocument();
    m_pXMLStreamToWrite->writeStartElement("bookindex");
    m_pXMLStreamToWrite->writeStartElement("entry");
    m_pXMLStreamToWrite->writeAttribute("term", "sidebearings");
    m_pXMLStreamToWrite->writeTextElement("page", "10");
    m_pXMLStreamToWrite->writeTextElement("page", "34-35");
    m_pXMLStreamToWrite->writeTextElement("page", "307-308");
    m_pXMLStreamToWrite->writeEndElement();
    m_pXMLStreamToWrite->writeStartElement("entry");
    m_pXMLStreamToWrite->writeAttribute("term", "subtraction");
    m_pXMLStreamToWrite->writeStartElement("entry");
    m_pXMLStreamToWrite->writeAttribute("term", "of pictures");
    m_pXMLStreamToWrite->writeTextElement("page", "115");
    m_pXMLStreamToWrite->writeTextElement("page", "224");
    m_pXMLStreamToWrite->writeEndElement();
    m_pXMLStreamToWrite->writeStartElement("entry");
    m_pXMLStreamToWrite->writeAttribute("term", "of vectors");
    m_pXMLStreamToWrite->writeTextElement("page", "9");
    m_pXMLStreamToWrite->writeEndElement();
    m_pXMLStreamToWrite->writeEndElement();
    m_pXMLStreamToWrite->writeEndDocument();
    m_pXMLFileToWrite->close();
    if (m_pXMLFileToWrite->error()) {
        qDebug() << "Error: Cannot write file: "
                 << qPrintable(m_pXMLFileToWrite->errorString());
        return false;
    }
    return true;
}

DealWithXML::~DealWithXML()
{
    if (m_pXMLFileToRead != nullptr) {
        delete m_pXMLFileToRead;
        m_pXMLFileToRead = nullptr;
    }

    if (m_pXMLFileToWrite != nullptr) {
        delete m_pXMLFileToWrite;
        m_pXMLFileToWrite = nullptr;
    }

    if (m_pXMLStreamToRead != nullptr) {
        delete m_pXMLStreamToRead;
        m_pXMLStreamToRead = nullptr;
    }

    if (m_pXMLStreamToWrite != nullptr) {
        delete m_pXMLStreamToWrite;
        m_pXMLStreamToWrite = nullptr;
    }
}
