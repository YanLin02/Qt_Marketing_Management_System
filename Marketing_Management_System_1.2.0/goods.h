#ifndef GOODS_H
#define GOODS_H

#include <QString>
#include <QDate>
#include <QVector>
#include <QFile>
#include <qfile.h>
#include <QTextStream>
#include <QTextCodec>
#include <QDir>

#include "sale.h"

class Goods
{
public:
	///////////////////////////////构造函数区/////////////////////////////////
	Goods();//万一要用
	Goods(unsigned int id, QString name, QString org, double pric, double amou, QDate due, QDate purc);//新增用
	Goods(unsigned int id, QString name, QString org, double pric, double amou, double rem, QDate due, QDate purc);//读文件用
	
	
	///////////////////////////////功能接口区/////////////////////////////////
	
	QVector<const Sale*> findSaleData(QString key, int type);//查找指定商品
	// 0: 销售日期  1: 数量  2: 价格  3: 营业员工号 4: 业务类型（售出0、退货1）
	
	
	bool addSalesDate(const Sale& sa);//传入销售信息并加入到向量中
	
	bool deleteSalesDate(unsigned int index);//输入条目删除销售信息
	
	double getProfit(double price);//输入售价查询毛利率(未使用)
	
	double getProfit(unsigned int index);//输入条目查询毛利率(未使用)
	
	bool operator==(const Goods& g);
	
	///////////////////////////////文件管理区/////////////////////////////////
	
	bool saveSalesFile(const QString& path);//保存销售数据
	
	bool deleteSalesFile(const QString& path);//清除销售数据
	
	bool readSalesFile(const QString& path);//读取销售文件
	
	void saveGoods(QTextStream &aStream);
	
	///////////////////////////////商品数据区/////////////////////////////////
	
	unsigned int m_ID;//标号
	QString m_Name;//品名
	
	QString m_Origin;//产地
	
	double m_BuyingPrice;//进价
	
	double m_Amount;//数量
	double m_Remaining;//剩余数量
	
	QDate m_DueDate;//到期日期
	QDate m_PurchaseDate;//进货日期
	
	QVector<Sale> v_SalesData;//销售数据集
	unsigned int m_NumberofData;//销售数据集数据量
};

#endif // GOODS_H
