#include "sale.h"


Sale::Sale(QDate date, double volum, double price, unsigned int empID, int act)
	:m_SaleDate(date),m_Volume(volum),m_Price(price),m_EmployeeId(empID),m_Activity(act){}

void Sale::saveData(QTextStream &aStream)
{	
	aStream << m_SaleDate.year() <<" "<< m_SaleDate.month() <<" "<< m_SaleDate.day() << "\n";
	aStream << m_Volume <<" "<< m_Price <<"\n";
	aStream << m_EmployeeId <<"\n";
	aStream << m_Activity <<"\n";;
	
}
