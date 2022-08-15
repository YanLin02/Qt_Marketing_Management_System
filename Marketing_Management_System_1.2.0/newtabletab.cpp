#include "newtabletab.h"
#include "ui_newtabletab.h"

NewTableTab::NewTableTab(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::NewTableTab),
	p_goods(nullptr)
{
	ui->setupUi(this);
	
	this->m_tableModel = new QStandardItemModel(this);
	
	ui->tableView->setModel(m_tableModel);
	//整行选中
	ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	//不可编辑
	ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

NewTableTab::~NewTableTab()
{
	delete ui;
}

void NewTableTab::refreshSaleData(const Goods& goods)
{
	this->p_goods = (Goods*)&goods;
	//初始化销售信息表格
	this->m_tableModel->clear();
	this->m_tableModel->setColumnCount(5);
	
	this->m_tableModel->setHorizontalHeaderLabels(QStringList()<<"销售日期"<<"数量"<<"价格"<<"营业员工号"<<"业务类型");
	
	//获取并设置行数信息
	unsigned int  rowNum = goods.m_NumberofData;
	this->m_tableModel->setRowCount(rowNum);
	
	//插入数据
	QStandardItem *aTempItem; //临时的item
	QString tempStr;
	for (unsigned int i = 0; i < rowNum; ++i) {
		Sale tempSaleData = goods.v_SalesData[i];//读取一个商品
		
		tempStr = tempSaleData.m_SaleDate.toString("yy/MM/dd");
		aTempItem = new QStandardItem(tempStr);
		this->m_tableModel->setItem(i, 0, aTempItem);
		
		tempStr = QString::number(tempSaleData.m_Volume);
		aTempItem = new QStandardItem(tempStr);
		this->m_tableModel->setItem(i, 1, aTempItem);
		
		tempStr = QString::number(tempSaleData.m_Price);
		aTempItem = new QStandardItem(tempStr);
		this->m_tableModel->setItem(i, 2, aTempItem);
		
		tempStr = QString::number(tempSaleData.m_EmployeeId);
		aTempItem = new QStandardItem(tempStr);
		this->m_tableModel->setItem(i, 3, aTempItem);
		
		switch (tempSaleData.m_Activity) {
		case 0:
			tempStr = "售出";
			break;
		case 1:
			tempStr = "退货";
			break;
		default:
			tempStr = "未知";
			break;
		}
		aTempItem = new QStandardItem(tempStr);
		this->m_tableModel->setItem(i, 4, aTempItem);
	}	
}

void NewTableTab::refreshSaleData(const QVector<const Sale *> &v_p_sales)
{
	//初始化销售信息表格
	this->m_tableModel->clear();
	this->m_tableModel->setColumnCount(5);
	
	this->m_tableModel->setHorizontalHeaderLabels(QStringList()<<"销售日期"<<"数量"<<"价格"<<"营业员工号"<<"业务类型");
	
	//获取并设置行数信息
	unsigned int  rowNum = v_p_sales.size();
	this->m_tableModel->setRowCount(rowNum);
	
	//插入数据
	QStandardItem *aTempItem; //临时的item
	QString tempStr;
	for (unsigned int i = 0; i < rowNum; ++i) {
		Sale tempSaleData = *(v_p_sales[i]);//读取一个商品
		
		tempStr = tempSaleData.m_SaleDate.toString("yy/MM/dd");
		aTempItem = new QStandardItem(tempStr);
		this->m_tableModel->setItem(i, 0, aTempItem);
		
		tempStr = QString::number(tempSaleData.m_Volume);
		aTempItem = new QStandardItem(tempStr);
		this->m_tableModel->setItem(i, 1, aTempItem);
		
		tempStr = QString::number(tempSaleData.m_Price);
		aTempItem = new QStandardItem(tempStr);
		this->m_tableModel->setItem(i, 2, aTempItem);
		
		tempStr = QString::number(tempSaleData.m_EmployeeId);
		aTempItem = new QStandardItem(tempStr);
		this->m_tableModel->setItem(i, 3, aTempItem);
		
		switch (tempSaleData.m_Activity) {
		case 0:
			tempStr = "售出";
			break;
		case 1:
			tempStr = "退货";
			break;
		default:
			tempStr = "未知";
			break;
		}
		aTempItem = new QStandardItem(tempStr);
		this->m_tableModel->setItem(i, 4, aTempItem);
	}	
	
}

void NewTableTab::refreshGoodsList(const QVector<const Goods*> &v_goodsList, unsigned int dataNum)
{

	this->v_p_goodsList = v_goodsList;
	//初始化商品表格
	this->m_tableModel->clear();
	this->m_tableModel->setColumnCount(8);
	
	this->m_tableModel->setHorizontalHeaderLabels(QStringList()<<"标号"<<"品名"<<"产地"<<"进价"<<"数量"<<"库存"<<"到期日期"<<"进货日期");
	
	//获取并设置行数信息
	unsigned int rowNum = dataNum;
	this->m_tableModel->setRowCount(rowNum);
	
	//插入数据
	QStandardItem *aTempItem; //临时的item
	QString tempStr;
	for (unsigned int i = 0; i < rowNum; ++i) {
		Goods tempGoods = *(v_goodsList[i]);//读取一个商品
		
		tempStr = QString::number(tempGoods.m_ID);
		aTempItem = new QStandardItem(tempStr);
		this->m_tableModel->setItem(i, 0, aTempItem);
		
		tempStr = tempGoods.m_Name;
		aTempItem = new QStandardItem(tempStr);
		this->m_tableModel->setItem(i, 1, aTempItem);
		
		tempStr =tempGoods.m_Origin;
		aTempItem = new QStandardItem(tempStr);
		this->m_tableModel->setItem(i, 2, aTempItem);
		
		tempStr = QString::number(tempGoods.m_BuyingPrice);
		aTempItem = new QStandardItem(tempStr);
		this->m_tableModel->setItem(i, 3, aTempItem);
		
		tempStr = QString::number(tempGoods.m_Amount);
		aTempItem = new QStandardItem(tempStr);
		this->m_tableModel->setItem(i, 4, aTempItem);
		
		tempStr = QString::number(tempGoods.m_Remaining);
		aTempItem = new QStandardItem(tempStr);
		this->m_tableModel->setItem(i, 5, aTempItem);
		
		tempStr = tempGoods.m_DueDate.toString("yy-MM-dd");
		aTempItem = new QStandardItem(tempStr);
		this->m_tableModel->setItem(i, 6, aTempItem);
		
		tempStr = tempGoods.m_PurchaseDate.toString("yy-MM-dd");
		aTempItem = new QStandardItem(tempStr);
		this->m_tableModel->setItem(i, 7, aTempItem);
	}
}

int NewTableTab::getChoosenLine()
{
	QTableView *m_pTableView = ui->tableView;
	QModelIndexList selected = m_pTableView->selectionModel()->selectedRows();
	QList<int> rows;
	foreach( const QModelIndex & index, selected)
		rows.append( index.row() );
	if(rows.isEmpty())
		return -1;
	else
		return rows.at(0);
}
