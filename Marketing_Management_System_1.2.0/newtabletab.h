#ifndef NEWTABLETAB_H
#define NEWTABLETAB_H

#include <QWidget>

#include <QMessageBox>
#include <QFileDialog>
#include "QStandardItemModel"
#include <QLabel>


#include "goods.h"
#include "marketingmanager.h"
#include "sale.h"
#include "addgoodsdialog.h"


namespace Ui {
class NewTableTab;
}

class NewTableTab : public QWidget
{
	Q_OBJECT
	
public:
	explicit NewTableTab(QWidget *parent = nullptr);
	~NewTableTab();
	
	void refreshSaleData(const Goods& goods);//刷新销售信息
	void refreshSaleData(const QVector<const Sale *>& v_p_sales);//刷新销售信息
	
	void refreshGoodsList(const QVector<const Goods*>& v_goodsList,unsigned int dataNum);//刷新商品列表
	
	int getChoosenLine();
	
private:
	Ui::NewTableTab *ui;
	
	QStandardItemModel* m_tableModel;
	
public:
	Goods* p_goods;//如果是销售清单用这个
	QVector<const Goods*> v_p_goodsList;//查找清单用这个
};

#endif // NEWTABLETAB_H
