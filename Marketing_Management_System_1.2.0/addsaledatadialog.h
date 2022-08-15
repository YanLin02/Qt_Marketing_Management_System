#ifndef ADDSALEDATADIALOG_H
#define ADDSALEDATADIALOG_H

#include <QDialog>

namespace Ui {
class AddSaleDataDialog;
}

class AddSaleDataDialog : public QDialog
{
	Q_OBJECT
	
public:
	explicit AddSaleDataDialog(const QString& GoodsName, QWidget *parent = nullptr);
	~AddSaleDataDialog();
	
	///////////////////////////////获取信息区/////////////////////////////////
	
	QDate getSaleDate();//销售日期
	
	QString getVolume();//数量
	
	QString getPrice();//价格
	
	QString getEmployeeId();//营业员工号
	
	int getActivity();//业务类型（售出0、退货1）
	
	int actNow;
	
private slots:
	void on_OperationType_currentIndexChanged(int index);
	
private:
	Ui::AddSaleDataDialog *ui;
};

#endif // ADDSALEDATADIALOG_H
