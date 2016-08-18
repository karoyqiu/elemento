/*! ***********************************************************************************************
 *
 * \file        main.cpp
 * \brief
 *
 * \version     0.1
 * \date        2016/6/23
 *
 * \author      仇道林 <qiudaolin@zhongfu.net>
 * \copyright   © 2016 中孚信息股份有限公司。
 *
 **************************************************************************************************/
#include "stable.h"
#include "converterdialog.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setApplicationName(QS("Selenium"));
    QApplication::setApplicationDisplayName(QS("Selenium"));
    QApplication::setApplicationVersion(QS("0.1"));
    QApplication::setOrganizationName(QS("Zhongfu"));
    QApplication::setOrganizationDomain(QS("zhongfu.net"));

    qDebug() << "Supported formats:" << QImageReader::supportedImageFormats();

    ConverterDialog w;
    w.show();

    return a.exec();
}
