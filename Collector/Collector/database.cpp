#include "database.h"

#include "recorder.h"

Database::Database()
{
}


Database::~Database()
{
}


//*****************
// 分类准备SQL语句
//*****************
QString Database::getSql(SQLType type)
{
	QString create_sql = "create table positions (id int primary key, "
		"filename varchar(256), tlx float, tly float, brx float, bry float, "
		"iftx float, ifty float, ifjx float, ifjy float, tfjx float, tfjy float, "
		"btx float, bty float, bjx float, bjy float)";

	QString select_sql = "select * from positions where id = ?";

	QString insert_sql = "insert into positions values ( "
		" :id, :filename, "
		" :tlx, :tly, :brx, :bry,"
		" :iftx, :ifty, :ifjx, :ifjy, :tfjx, :tfjy, :btx, :bty, :bjx, :bjy"
		" )";


	QString update_sql = "update positions set "
		" tlx = :tlx, tly = :tly, brx = :brx, bry = :bry,"
		" iftx = :iftx, ifty = :ifty, ifjx = :ifjx, ifjy = :ifjy, tfjx = :tfjx, tfjy = :tfjy,"
		" btx = :btx, bty = :bty, bjx = :bjx, bjy = :bjy"
		" where id = :id";


	QString delete_sql = "delete from positions where id = ?";

	QString clear_sql = "delete from positions";

	QString select_all_sql = "select * from positions order by id";

	switch (type)
	{
	case TypeCreate:
		return create_sql;
		break;
	case TypeSelect:
		return select_sql;
		break;
	case TypeInsert:
		return insert_sql;
		break;
	case TypeUpdate:
		return update_sql;
		break;
	case TypeDelete:
		return delete_sql;
		break;
	case TypeClear:
		return clear_sql;
		break;
	case TypeSelectAll:
		return select_all_sql;
		break;
	default:
		break;
	}
}

void Database::prepareDB(QString targetDir)
{
	db = QSqlDatabase::addDatabase("QSQLITE");
	QString dbpath = targetDir + "/database.db";
	db.setDatabaseName(dbpath);
	
	if (!db.open()){
		QMessageBox::information(NULL, "database", "database fail to create at: "+ dbpath);
		return;
	}
	

	QSqlQuery query(db);
	query.exec("drop table files");
	QString str = getSql(TypeCreate);

	if (!query.exec(str))
	{
		//创建一个表
		qDebug() << "create table fail!";
	}
}

//*****************
// Select语句
//*****************
vector<float> Database::execSelect(int index, QString currentImgName)
{
	//prepare a vector
	vector<float> positionVec;

	//check database for index
	QSqlQuery query(db);
	QString str = getSql(TypeSelect);
	query.prepare(str);
	query.addBindValue(index);
	if (!query.exec()) return positionVec;


	query.next();//query.next()指向查找到的第一条记录，然后每次后移一条记录  
	int id = query.value(0).toInt();//query.value(0)是id的值，将其转换为int型   
	QString fileName = query.value(1).toString();
	if (id != index || fileName != currentImgName)
	{
		qDebug() << "current index and record not match!";
		return positionVec;
	}
	const int query_result_start = 2;
	const int query_result_end = query_result_start + COLLECT_PARAM_COUNT;
	for (int i = query_result_start; i < query_result_end; i++)
	{
		float temp = query.value(i).toFloat();
		positionVec.push_back(temp);
	}

	return positionVec;
}

//*****************
// Insert或Update语句
//*****************
void Database::execInsert(int index, QString fileName,vector<float> params)
{
	//analyze vector
	float tlx = params[0]; float tly = params[1];
	float brx = params[2]; float bry = params[3];
	float iftx = params[4]; float ifty = params[5];
	float ifjx = params[6]; float ifjy = params[7];
	float tfjx = params[8]; float tfjy = params[9];
	float btx = params[10]; float bty = params[11];
	float bjx = params[12]; float bjy = params[13];

	//check exist by select sentence
	QSqlQuery query(db);
	QString str = getSql(TypeSelect);
	query.prepare(str);
	query.addBindValue(index);
	if (!query.exec())
		return;

	query.next();//用query读取db的时候，exec后面需要用next把指针指向返回结果的第一条！
	qDebug() << "id: " << query.value(0)
		<< ", file name: " << query.value(1).toString();
	if (query.numRowsAffected() != -1 && query.value(0) != index){
		//if not exist, insert
		qDebug() << "Nothing on index: " << index << ". Need insertion.";
		QString str_insert = getSql(TypeInsert);
		query.prepare(str_insert);
		query.bindValue(":filename", fileName);
	}
	else
	{
		qDebug() << "Something on index: " << index << ". Need update.";
		//if exist, update
		QString str_update = getSql(TypeUpdate);
		query.prepare(str_update);
	}

	//both insert and update need 
	query.bindValue(":id", index);
	query.bindValue(":tlx", tlx);
	query.bindValue(":tly", tly);
	query.bindValue(":brx", brx);
	query.bindValue(":bry", bry);
	query.bindValue(":iftx", iftx);
	query.bindValue(":ifty", ifty);
	query.bindValue(":ifjx", ifjx);
	query.bindValue(":ifjy", ifjy);
	query.bindValue(":tfjx", tfjx);
	query.bindValue(":tfjy", tfjy);
	query.bindValue(":btx", btx);
	query.bindValue(":bty", bty);
	query.bindValue(":bjx", bjx);
	query.bindValue(":bjy", bjy);

	if (!query.exec()){
		qDebug() << query.lastError();
	}
	else{
		qDebug() << "Update finish!";
	}
}

//*****************
// 转化db文件成为txt
//*****************
void Database::convertDBtoTxt(QString targetDir)
{
	Recorder rec;
	rec.initFileStream(targetDir);

	QSqlQuery query(db);

	QString selectall_str = getSql(TypeSelectAll);
	if (!query.exec(selectall_str)){
		qDebug() << "select all fail!";
	}

	while (query.next())//query.next()指向查找到的第一条记录，然后每次后移一条记录   
	{
		int id = query.value(0).toInt();//query.value(0)是id的值，将其转换为int型   
		QString fileName = query.value(1).toString();

		vector<float> params;
		float tlx = query.value(2).toFloat(); params.push_back(tlx);
		float tly = query.value(3).toFloat(); params.push_back(tly);
		float brx = query.value(4).toFloat(); params.push_back(brx);
		float bry = query.value(5).toFloat(); params.push_back(bry);
		float iftx = query.value(6).toFloat(); params.push_back(iftx);
		float ifty = query.value(7).toFloat(); params.push_back(ifty);
		float ifjx = query.value(8).toFloat(); params.push_back(ifjx);
		float ifjy = query.value(9).toFloat(); params.push_back(ifjy);
		float tfjx = query.value(10).toFloat(); params.push_back(tfjx);
		float tfjy = query.value(11).toFloat(); params.push_back(tfjy);
		float btx = query.value(12).toFloat(); params.push_back(btx);
		float bty = query.value(13).toFloat(); params.push_back(bty);
		float bjx = query.value(14).toFloat(); params.push_back(bjx);
		float bjy = query.value(15).toFloat(); params.push_back(bjy);

		//append data in recorder's list
		rec.appendStringList(fileName, params);
		//debug
		qDebug() << id << "," << fileName << "," << tlx << "," << tly
			<< "," << brx << "," << bry
			<< "," << iftx << "," << ifty
			<< "," << ifjx << "," << ifjy
			<< "," << tfjx << "," << tfjy;
	}

	//write data into txt via recorder
	rec.writeDataFile();
}
