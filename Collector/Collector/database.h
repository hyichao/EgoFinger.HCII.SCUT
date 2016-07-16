#ifndef DATABASE_H
#define DATABASE_H

#include "common.h"

#include <QtSql\qsql.h>
#include <QtSql\qsqldatabase.h>
#include <QtSql\qsqlquery.h>
#include <QtSql\qsqltablemodel.h>
#include <QtSql\qsqlerror.h>

enum SQLType
{
	TypeCreate = 0,
	TypeSelect,
	TypeInsert,
	TypeUpdate,
	TypeDelete,
	TypeClear,
	TypeSelectAll,
};

class Database
{
private:
	QSqlDatabase db;

public:
	Database();
	~Database();

	//prepare sql command
	QString getSql(SQLType type);
	void prepareDB(QString targetDir);

	//select
	vector<float> execSelect(int index, QString currentImgName);
	//insert or update
	void execInsert(int index, QString fileName, vector<float> params);
	//write
	void convertDBtoTxt(QString targetDir);
};


#endif // DATABASE_H
