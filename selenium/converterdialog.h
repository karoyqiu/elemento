/*! ***********************************************************************************************
 *
 * \file        converterdialog.h
 * \brief       ConverterDialog
 *
 * \version     0.1
 * \date        2016/6/23
 *
 * \author      仇道林 <qiudaolin@zhongfu.net>
 * \copyright   © 2016 中孚信息股份有限公司。
 *
 **************************************************************************************************/
#pragma once

#include <QDialog>

namespace Ui {
class ConverterDialog;
}

class ConverterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConverterDialog(QWidget *parent = Q_NULLPTR);
    virtual ~ConverterDialog();

public slots:
    virtual void accept() Q_DECL_OVERRIDE;

protected:
    virtual void changeEvent(QEvent *e) Q_DECL_OVERRIDE;

private slots:
    void openSourceFile();
    void openDestFile();

private:
    Ui::ConverterDialog *ui;
};
