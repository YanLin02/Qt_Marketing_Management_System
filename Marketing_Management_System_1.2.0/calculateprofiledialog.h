#ifndef CALCULATEPROFILEDIALOG_H
#define CALCULATEPROFILEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QRegExpValidator>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class CalculateProfileDialog;
}

class CalculateProfileDialog : public QDialog
{
	Q_OBJECT
	
public:
	explicit CalculateProfileDialog(QWidget *parent = nullptr);
	~CalculateProfileDialog();
	
	
	void setBuyingPrice(double p);
	void setSalePrice(double p);
	void setSaleNum(double p);
	
public slots:
	
	void on_pushButton_clicked();
	
private slots:
	
	void on_buyPriceLine_editingFinished();
	
	void on_salePriceLine_editingFinished();
	
	void on_sale_Amount_editingFinished();
	
private:
	Ui::CalculateProfileDialog *ui;
	
	double m_buyingPrice;
	double m_salePrice;
	double m_saleNum;
};

#endif // CALCULATEPROFILEDIALOG_H
