/*! ***********************************************************************************************
 *
 * \file        converterdialog.cpp
 * \brief       ConverterDialog
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
#include "ui_converterdialog.h"


ConverterDialog::ConverterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ConverterDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBrowseSource, &QToolButton::clicked, this, &ConverterDialog::openSourceFile);
    connect(ui->buttonBrowseDestination, &QToolButton::clicked, this, &ConverterDialog::openDestFile);
}


ConverterDialog::~ConverterDialog()
{
    delete ui;
}


void ConverterDialog::accept()
{
    if (!QFileInfo::exists(ui->editSource->text()))
    {
        QMessageBox::critical(this, tr("Error"), tr("Source file doesn't exist."));
        return;
    }

    QFileInfo destDir(ui->editDestination->text());

    if (!destDir.exists() || !destDir.isDir())
    {
        QMessageBox::critical(this, tr("Error"), tr("Destination directory doesn't exist."));
        return;
    }

    QFileInfo fileInfo(ui->editSource->text());
    QSvgRenderer renderer(ui->editSource->text());

    for (int i = 0; i < ui->listWidget->count(); i++)
    {
        QListWidgetItem *item = ui->listWidget->item(i);
        QString text = item->text();
        text.chop(2);
        int size = text.toInt();

        QImage image(size, size, QImage::Format_ARGB32);
        image.fill(Qt::transparent);

        QPainter painter(&image);
        renderer.render(&painter);

        QString fileName = QString("%1/%2_%3.png").arg(destDir.absoluteFilePath()).arg(fileInfo.baseName()).arg(size);
        image.save(fileName);
    }

    QDialog::accept();
}


void ConverterDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);

    switch (e->type())
    {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


void ConverterDialog::openSourceFile()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open source file"), QString(),
                                                    tr("SVG files (*.svg);;All files (*)"));

    if (!filename.isEmpty())
    {
        QImage image(filename);

        if (image.isNull())
        {
            QMessageBox::critical(this, QString(), tr("Invalid image file."));
        }
        else
        {
            ui->editSource->setText(QDir::toNativeSeparators(filename));
        }
    }
}


void ConverterDialog::openDestFile()
{
    QStringList formats;

    for (const QByteArray &f : QImageWriter::supportedImageFormats())
    {
        formats << "*." + f;
    }

    QString filename = QFileDialog::getExistingDirectory(this);

    if (!filename.isEmpty())
    {
        ui->editDestination->setText(QDir::toNativeSeparators(filename));
    }
}
