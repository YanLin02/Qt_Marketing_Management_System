#ifndef MARKETINGMANAGER_H
#define MARKETINGMANAGER_H

#include <algorithm>
#include <QVector>

#include "goods.h"
#include "sale.h"

using namespace std;

class MarketingManager
{
public:
	///////////////////////////////构造函数区/////////////////////////////////	
	MarketingManager();
	
	
	///////////////////////////////功能接口区/////////////////////////////////
	
	QVector<const Goods*> findGoods(QString key, int type);//查找指定商品
	// 1: ID  2: Name  3: Origin  4: DueDate 5: PurchaseDate
	
	bool addGoods(const Goods& g);//添加商品
	
	bool deleteGoods(unsigned int index);//删除商品
	void deleteGoods(const Goods& g);
	
	///////////////////////////////文件管理区/////////////////////////////////
	
	bool saveGoodsFile(const QString& path);//保存商品数据
	
	bool deleteGoodsFile(const QString& path);//清除商品数据
	
	bool readGoodsFile(const QString& path);//读取商品文件
	
	bool saveAllFile(const QString& path);//保存所有数据
	
	bool readAllFile(const QString& path);//读取所有文件	
	
	bool deleteAllFile(const QString& path);//删库跑路
	
	///////////////////////////////商品信息区/////////////////////////////////
	
	QVector<Goods> v_GoodsList;//商品清单
	unsigned int m_NumberofGoods;//商品数量
	
};

#endif // MARKETINGMANAGER_H
