#ifndef SALE_H
#define SALE_H

#include <QString>
#include <QDate>
#include <QDebug>
using namespace std;

class Sale
{
public:
	///////////////////////////////构造函数区/////////////////////////////////
	
	Sale(QDate date = QDate(0,0,0), double volum = 0, double price = 0, unsigned int empID = 0, int act = 0);
	
	///////////////////////////////文件管理区/////////////////////////////////
	
	void saveData(QTextStream &aStream);
	
	
	
	///////////////////////////////销售信息区/////////////////////////////////
	QDate m_SaleDate;//销售日期
	
	double m_Volume;//数量
	
	double m_Price;//价格
	
	unsigned int m_EmployeeId;//营业员工号
	
	int m_Activity;//业务类型（售出0、退货1）
};

#endif // SALE_H
