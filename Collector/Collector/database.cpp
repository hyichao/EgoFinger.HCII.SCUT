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
QString Database::getSql(SQLType type, QString videoType = " ")
{
	//###create不同的表格
	QString create_sql_single_one = "create table positions (id int primary key, "
		"filename varchar(256), tlx float, tly float, brx float, bry float, "
		"iftx float, ifty float, ifjx float, ifjy float) ";
	QString create_sql_single_two = "create table positions (id int primary key, "
		"filename varchar(256), tlx float, tly float, brx float, bry float, "
		"iftx float, ifty float, ifjx float, ifjy float, "
		"mftx float, mfty float, mfjx float, mfjy float)";
	QString create_sql_single_three = "create table positions (id int primary key, "
		"filename varchar(256), tlx float, tly float, brx float, bry float, "
		"iftx float, ifty float, ifjx float, ifjy float, "
		"mftx float, mfty float, mfjx float, mfjy float, "
		"rftx float, rfty float, rfjx float, rfjy float)";
	QString create_sql_single_four = "create table positions (id int primary key, "
		"filename varchar(256), tlx float, tly float, brx float, bry float, "
		"iftx float, ifty float, ifjx float, ifjy float, "
		"mftx float, mfty float, mfjx float, mfjy float, "
		"rftx float, rfty float, rfjx float, rfjy float, "
		"tftx float, tfty float, tfjx float, tfjy float)";
	QString create_sql_single_five = "create table positions (id int primary key, "
		"filename varchar(256), tlx float, tly float, brx float, bry float, "
		"iftx float, ifty float, ifjx float, ifjy float, "
		"mftx float, mfty float, mfjx float, mfjy float, "
		"rftx float, rfty float, rfjx float, rfjy float, "
		"tftx float, tfty float, tfjx float, tfjy float, "
		"btx float, bty float, bjx float, bjy float)";
	QString create_sql_single_six = "create table positions (id int primary key, "
		"filename varchar(256), tlx float, tly float, brx float, bry float, "
		"tftx float, tfty float, tfjx float, tfjy float, "
		"btx float, bty float, bjx float, bjy float)";
	QString create_sql_single_seven = "create table positions (id int primary key, "
		"filename varchar(256), tlx float, tly float, brx float, bry float, "
		"iftx float, ifty float, ifjx float, ifjy float, "
		"tftx float, tfty float, tfjx float, tfjy float, "
		"btx float, bty float, bjx float, bjy float)";
	QString create_sql_single_eight = "create table positions (id int primary key, "
		"filename varchar(256), tlx float, tly float, brx float, bry float, "
		"iftx float, ifty float, ifjx float, ifjy float, "
		"btx float, bty float, bjx float, bjy float)";
	QString create_sql_single_nine = "create table positions (id int primary key, "
		"filename varchar(256), tlx float, tly float, brx float, bry float, "
		"iftx float, ifty float, ifjx float, ifjy float) ";
	QString create_sql_single_good = "create table positions (id int primary key, "
		"filename varchar(256), tlx float, tly float, brx float, bry float, "
		"btx float, bty float, bjx float, bjy float)";
	QString create_sql_single_bad = "create table positions (id int primary key, "
		"filename varchar(256), tlx float, tly float, brx float, bry float, "
		"btx float, bty float, bjx float, bjy float)";
	QString create_sql_pair_six = "create table positions (id int primary key, "
		"filename varchar(256), tlx float, tly float, brx float, bry float, "
		"iftx float, ifty float, ifjx float, ifjy float, "
		"mftx float, mfty float, mfjx float, mfjy float, "
		"rftx float, rfty float, rfjx float, rfjy float, "
		"tftx float, tfty float, tfjx float, tfjy float, "
		"btx float, bty float, bjx float, bjy float, "
		"tlx_l float, tly_l float, brx_l float, bry_l float, "
		"iftx_l float, ifty_l float, ifjx_l float, ifjy_l float) ";
	QString create_sql_pair_seven = "create table positions (id int primary key, "
		"filename varchar(256), tlx float, tly float, brx float, bry float, "
		"iftx float, ifty float, ifjx float, ifjy float, "
		"mftx float, mfty float, mfjx float, mfjy float, "
		"rftx float, rfty float, rfjx float, rfjy float, "
		"tftx float, tfty float, tfjx float, tfjy float, "
		"btx float, bty float, bjx float, bjy float, "
		"tlx_l float, tly_l float, brx_l float, bry_l float, "
		"iftx_l float, ifty_l float, ifjx_l float, ifjy_l float, "
		"mftx_l float, mfty_l float, mfjx_l float, mfjy_l float) ";
	QString create_sql_pair_eight = "create table positions (id int primary key, "
		"filename varchar(256), tlx float, tly float, brx float, bry float, "
		"iftx float, ifty float, ifjx float, ifjy float, "
		"mftx float, mfty float, mfjx float, mfjy float, "
		"rftx float, rfty float, rfjx float, rfjy float, "
		"tftx float, tfty float, tfjx float, tfjy float, "
		"btx float, bty float, bjx float, bjy float, "
		"tlx_l float, tly_l float, brx_l float, bry_l float, "
		"iftx_l float, ifty_l float, ifjx_l float, ifjy_l float, "
		"mftx_l float, mfty_l float, mfjx_l float, mfjy_l float, "
		"btx_l float, bty_l float, bjx_l float, bjy_l float) ";
	QString create_sql_pair_nine = "create table positions (id int primary key, "
		"filename varchar(256), tlx float, tly float, brx float, bry float, "
		"iftx float, ifty float, ifjx float, ifjy float, "
		"mftx float, mfty float, mfjx float, mfjy float, "
		"rftx float, rfty float, rfjx float, rfjy float, "
		"tftx float, tfty float, tfjx float, tfjy float, "
		"btx float, bty float, bjx float, bjy float, "
		"tlx_l float, tly_l float, brx_l float, bry_l float, "
		"iftx_l float, ifty_l float, ifjx_l float, ifjy_l float, "
		"mftx_l float, mfty_l float, mfjx_l float, mfjy_l float, "
		"rftx_l float, rfty_l float, rfjx_l float, rfjy_l float, "
		"tftx_l float, tfty_l float, tfjx_l float, tfjy_l float) ";
	QString create_sql_pair_ten = "create table positions (id int primary key, "
		"filename varchar(256), tlx float, tly float, brx float, bry float, "
		"iftx float, ifty float, ifjx float, ifjy float, "
		"mftx float, mfty float, mfjx float, mfjy float, "
		"rftx float, rfty float, rfjx float, rfjy float, "
		"tftx float, tfty float, tfjx float, tfjy float, "
		"btx float, bty float, bjx float, bjy float, "
		"tlx_l float, tly_l float, brx_l float, bry_l float, "
		"iftx_l float, ifty_l float, ifjx_l float, ifjy_l float, "
		"mftx_l float, mfty_l float, mfjx_l float, mfjy_l float, "
		"rftx_l float, rfty_l float, rfjx_l float, rfjy_l float, "
		"tftx_l float, tfty_l float, tfjx_l float, tfjy_l float, "
		"btx_l float, bty_l float, bjx_l float, bjy_l float) ";

	QString select_sql = "select * from positions where id = ?";

	//###针对不同的表格，insert不同的项目
	QString insert_sql_single_one = "insert into positions values ( "
		" :id, :filename, "
		" :tlx, :tly, :brx, :bry,"
		" :iftx, :ifty, :ifjx, :ifjy"
		" )";
	QString insert_sql_single_two = "insert into positions values ( "
		" :id, :filename, "
		" :tlx, :tly, :brx, :bry,"
		" :iftx, :ifty, :ifjx, :ifjy,"
		" :mftx, :mfty, :mfjx, :mfjy"
		" )";
	QString insert_sql_single_three = "insert into positions values ( "
		" :id, :filename, "
		" :tlx, :tly, :brx, :bry,"
		" :iftx, :ifty, :ifjx, :ifjy,"
		" :mftx, :mfty, :mfjx, :mfjy,"
		" :rftx, :rfty, :rfjx, :rfjy"
		" )";
	QString insert_sql_single_four = "insert into positions values ( "
		" :id, :filename, "
		" :tlx, :tly, :brx, :bry,"
		" :iftx, :ifty, :ifjx, :ifjy,"
		" :mftx, :mfty, :mfjx, :mfjy,"
		" :rftx, :rfty, :rfjx, :rfjy,"
		" :tftx, :tfty, :tfjx, :tfjy"
		" )";
	QString insert_sql_single_five = "insert into positions values ( "
		" :id, :filename, "
		" :tlx, :tly, :brx, :bry,"
		" :iftx, :ifty, :ifjx, :ifjy,"
		" :mftx, :mfty, :mfjx, :mfjy,"
		" :rftx, :rfty, :rfjx, :rfjy,"
		" :tftx, :tfty, :tfjx, :tfjy,"
		" :btx, :bty, :bjx, :bjy"
		" )";
	QString insert_sql_single_six = "insert into positions values ( "
		" :id, :filename, "
		" :tlx, :tly, :brx, :bry,"
		" :tftx, :tfty, :tfjx, :tfjy,"
		" :btx, :bty, :bjx, :bjy"
		" )";
	QString insert_sql_single_seven = "insert into positions values ( "
		" :id, :filename, "
		" :tlx, :tly, :brx, :bry,"
		" :iftx, :ifty, :ifjx, :ifjy,"
		" :tftx, :tfty, :tfjx, :tfjy,"
		" :btx, :bty, :bjx, :bjy"
		" )";
	QString insert_sql_single_eight = "insert into positions values ( "
		" :id, :filename, "
		" :tlx, :tly, :brx, :bry,"
		" :iftx, :ifty, :ifjx, :ifjy,"
		" :btx, :bty, :bjx, :bjy"
		" )";
	QString insert_sql_single_nine = "insert into positions values ( "
		" :id, :filename, "
		" :tlx, :tly, :brx, :bry,"
		" :iftx, :ifty, :ifjx, :ifjy"
		" )";
	QString insert_sql_single_good = "insert into positions values ( "
		" :id, :filename, "
		" :tlx, :tly, :brx, :bry,"
		" :btx, :bty, :bjx, :bjy"
		" )";
	QString insert_sql_single_bad = "insert into positions values ( "
		" :id, :filename, "
		" :tlx, :tly, :brx, :bry,"
		" :btx, :bty, :bjx, :bjy"
		" )";
	QString insert_sql_pair_six = "insert into positions values ( "
		" :id, :filename, "
		" :tlx, :tly, :brx, :bry,"
		" :iftx, :ifty, :ifjx, :ifjy,"
		" :mftx, :mfty, :mfjx, :mfjy,"
		" :rftx, :rfty, :rfjx, :rfjy,"
		" :tftx, :tfty, :tfjx, :tfjy,"
		" :btx, :bty, :bjx, :bjy,"
		" :tlx_l, :tly_l, :brx_l, :bry_l,"
		" :iftx_l, :ifty_l, :ifjx_l, :ifjy_l"
		" )";
	QString insert_sql_pair_seven = "insert into positions values ( "
		" :id, :filename, "
		" :tlx, :tly, :brx, :bry,"
		" :iftx, :ifty, :ifjx, :ifjy,"
		" :mftx, :mfty, :mfjx, :mfjy,"
		" :rftx, :rfty, :rfjx, :rfjy,"
		" :tftx, :tfty, :tfjx, :tfjy,"
		" :btx, :bty, :bjx, :bjy,"
		" :tlx_l, :tly_l, :brx_l, :bry_l,"
		" :iftx_l, :ifty_l, :ifjx_l, :ifjy_l,"
		" :mftx_l, :mfty_l, :mfjx_l, :mfjy_l"
		" )";
	QString insert_sql_pair_eight = "insert into positions values ( "
		" :id, :filename, "
		" :tlx, :tly, :brx, :bry,"
		" :iftx, :ifty, :ifjx, :ifjy,"
		" :mftx, :mfty, :mfjx, :mfjy,"
		" :rftx, :rfty, :rfjx, :rfjy,"
		" :tftx, :tfty, :tfjx, :tfjy,"
		" :btx, :bty, :bjx, :bjy,"
		" :tlx_l, :tly_l, :brx_l, :bry_l,"
		" :iftx_l, :ifty_l, :ifjx_l, :ifjy_l,"
		" :mftx_l, :mfty_l, :mfjx_l, :mfjy_l,"
		" :btx_l, :bty_l, :bjx_l, :bjy_l"
		" )";
	QString insert_sql_pair_nine = "insert into positions values ( "
		" :id, :filename, "
		" :tlx, :tly, :brx, :bry,"
		" :iftx, :ifty, :ifjx, :ifjy,"
		" :mftx, :mfty, :mfjx, :mfjy,"
		" :rftx, :rfty, :rfjx, :rfjy,"
		" :tftx, :tfty, :tfjx, :tfjy,"
		" :btx, :bty, :bjx, :bjy,"
		" :tlx_l, :tly_l, :brx_l, :bry_l,"
		" :iftx_l, :ifty_l, :ifjx_l, :ifjy_l,"
		" :mftx_l, :mfty_l, :mfjx_l, :mfjy_l,"
		" :rftx_l, :rfty_l, :rfjx_l, :rfjy_l,"
		" :tftx_l, :tfty_l, :tfjx_l, :tfjy_l"
		" )";
	QString insert_sql_pair_ten = "insert into positions values ( "
		" :id, :filename, "
		" :tlx, :tly, :brx, :bry,"
		" :iftx, :ifty, :ifjx, :ifjy,"
		" :mftx, :mfty, :mfjx, :mfjy,"
		" :rftx, :rfty, :rfjx, :rfjy,"
		" :tftx, :tfty, :tfjx, :tfjy,"
		" :btx, :bty, :bjx, :bjy,"
		" :tlx_l, :tly_l, :brx_l, :bry_l,"
		" :iftx_l, :ifty_l, :ifjx_l, :ifjy_l,"
		" :mftx_l, :mfty_l, :mfjx_l, :mfjy_l,"
		" :rftx_l, :rfty_l, :rfjx_l, :rfjy_l,"
		" :tftx_l, :tfty_l, :tfjx_l, :tfjy_l,"
		" :btx_l, :bty_l, :bjx_l, :bjy_l"
		" )";


	//###针对不同的表格，update不同的项目
	QString update_sql_single_one = "update positions set "
		" tlx = :tlx, tly = :tly, brx = :brx, bry = :bry,"
		" iftx = :iftx, ifty = :ifty, ifjx = :ifjx, ifjy = :ifjy"
		" where id = :id";
	QString update_sql_single_two = "update positions set "
		" tlx = :tlx, tly = :tly, brx = :brx, bry = :bry,"
		" iftx = :iftx, ifty = :ifty, ifjx = :ifjx, ifjy = :ifjy,"
		" mftx = :mftx, mfty = :mfty, mfjx = :mfjx, mfjy = :mfjy"
		" where id = :id";
	QString update_sql_single_three = "update positions set "
		" tlx = :tlx, tly = :tly, brx = :brx, bry = :bry,"
		" iftx = :iftx, ifty = :ifty, ifjx = :ifjx, ifjy = :ifjy,"
		" mftx = :mftx, mfty = :mfty, mfjx = :mfjx, mfjy = :mfjy,"
		" rftx = :rftx, rfty = :rfty, rfjx = :rfjx, rfjy = :rfjy"
		" where id = :id";
	QString update_sql_single_four = "update positions set "
		" tlx = :tlx, tly = :tly, brx = :brx, bry = :bry,"
		" iftx = :iftx, ifty = :ifty, ifjx = :ifjx, ifjy = :ifjy,"
		" mftx = :mftx, mfty = :mfty, mfjx = :mfjx, mfjy = :mfjy,"
		" rftx = :rftx, rfty = :rfty, rfjx = :rfjx, rfjy = :rfjy,"
		" tftx = :tftx, tfty = :tfty, tfjx = :tfjx, tfjy = :tfjy"
		" where id = :id";
	QString update_sql_single_five = "update positions set "
		" tlx = :tlx, tly = :tly, brx = :brx, bry = :bry,"
		" iftx = :iftx, ifty = :ifty, ifjx = :ifjx, ifjy = :ifjy,"
		" mftx = :mftx, mfty = :mfty, mfjx = :mfjx, mfjy = :mfjy,"
		" rftx = :rftx, rfty = :rfty, rfjx = :rfjx, rfjy = :rfjy,"
		" tftx = :tftx, tfty = :tfty, tfjx = :tfjx, tfjy = :tfjy,"
		" btx = :btx, bty = :bty, bjx = :bjx, bjy = :bjy"
		" where id = :id";
	QString update_sql_single_six = "update positions set "
		" tlx = :tlx, tly = :tly, brx = :brx, bry = :bry,"
		" tftx = :tftx, tfty = :tfty, tfjx = :tfjx, tfjy = :tfjy,"
		" btx = :btx, bty = :bty, bjx = :bjx, bjy = :bjy"
		" where id = :id";
	QString update_sql_single_seven = "update positions set "
		" tlx = :tlx, tly = :tly, brx = :brx, bry = :bry,"
		" iftx = :iftx, ifty = :ifty, ifjx = :ifjx, ifjy = :ifjy,"
		" tftx = :tftx, tfty = :tfty, tfjx = :tfjx, tfjy = :tfjy,"
		" btx = :btx, bty = :bty, bjx = :bjx, bjy = :bjy"
		" where id = :id";
	QString update_sql_single_eight = "update positions set "
		" tlx = :tlx, tly = :tly, brx = :brx, bry = :bry,"
		" iftx = :iftx, ifty = :ifty, ifjx = :ifjx, ifjy = :ifjy,"
		" btx = :btx, bty = :bty, bjx = :bjx, bjy = :bjy"
		" where id = :id";
	QString update_sql_single_nine = "update positions set "
		" tlx = :tlx, tly = :tly, brx = :brx, bry = :bry,"
		" iftx = :iftx, ifty = :ifty, ifjx = :ifjx, ifjy = :ifjy"
		" where id = :id";
	QString update_sql_single_good = "update positions set "
		" tlx = :tlx, tly = :tly, brx = :brx, bry = :bry,"
		" btx = :btx, bty = :bty, bjx = :bjx, bjy = :bjy"
		" where id = :id";
	QString update_sql_single_bad = "update positions set "
		" tlx = :tlx, tly = :tly, brx = :brx, bry = :bry,"
		" btx = :btx, bty = :bty, bjx = :bjx, bjy = :bjy"
		" where id = :id";
	QString update_sql_pair_six = "update positions set "
		" tlx = :tlx, tly = :tly, brx = :brx, bry = :bry,"
		" iftx = :iftx, ifty = :ifty, ifjx = :ifjx, ifjy = :ifjy,"
		" mftx = :mftx, mfty = :mfty, mfjx = :mfjx, mfjy = :mfjy,"
		" rftx = :rftx, rfty = :rfty, rfjx = :rfjx, rfjy = :rfjy,"
		" tftx = :tftx, tfty = :tfty, tfjx = :tfjx, tfjy = :tfjy,"
		" btx = :btx, bty = :bty, bjx = :bjx, bjy = :bjy,"
		" tlx_l = :tlx_l, tly_l = :tly_l, brx_l = :brx_l, bry_l = :bry_l,"
		" iftx_l = :iftx_l, ifty_l = :ifty_l, ifjx_l = :ifjx_l, ifjy_l = :ifjy_l"
		" where id = :id";
	QString update_sql_pair_seven = "update positions set "
		" tlx = :tlx, tly = :tly, brx = :brx, bry = :bry,"
		" iftx = :iftx, ifty = :ifty, ifjx = :ifjx, ifjy = :ifjy,"
		" mftx = :mftx, mfty = :mfty, mfjx = :mfjx, mfjy = :mfjy,"
		" rftx = :rftx, rfty = :rfty, rfjx = :rfjx, rfjy = :rfjy,"
		" tftx = :tftx, tfty = :tfty, tfjx = :tfjx, tfjy = :tfjy,"
		" btx = :btx, bty = :bty, bjx = :bjx, bjy = :bjy,"
		" tlx_l = :tlx_l, tly_l = :tly_l, brx_l = :brx_l, bry_l = :bry_l,"
		" iftx_l = :iftx_l, ifty_l = :ifty_l, ifjx_l = :ifjx_l, ifjy_l = :ifjy_l,"
		" mftx_l = :mftx_l, mfty_l = :mfty_l, mfjx_l = :mfjx_l, mfjy_l = :mfjy_l"
		" where id = :id";
	QString update_sql_pair_eight = "update positions set "
		" tlx = :tlx, tly = :tly, brx = :brx, bry = :bry,"
		" iftx = :iftx, ifty = :ifty, ifjx = :ifjx, ifjy = :ifjy,"
		" mftx = :mftx, mfty = :mfty, mfjx = :mfjx, mfjy = :mfjy,"
		" rftx = :rftx, rfty = :rfty, rfjx = :rfjx, rfjy = :rfjy,"
		" tftx = :tftx, tfty = :tfty, tfjx = :tfjx, tfjy = :tfjy,"
		" btx = :btx, bty = :bty, bjx = :bjx, bjy = :bjy,"
		" tlx_l = :tlx_l, tly_l = :tly_l, brx_l = :brx_l, bry_l = :bry_l,"
		" iftx_l = :iftx_l, ifty_l = :ifty_l, ifjx_l = :ifjx_l, ifjy_l = :ifjy_l,"
		" mftx_l = :mftx_l, mfty_l = :mfty_l, mfjx_l = :mfjx_l, mfjy_l = :mfjy_l,"
		" btx_l = :btx_l, bty_l = :bty_l, bjx_l = :bjx_l, bjy_l = :bjy_l"
		" where id = :id";
	QString update_sql_pair_nine = "update positions set "
		" tlx = :tlx, tly = :tly, brx = :brx, bry = :bry,"
		" iftx = :iftx, ifty = :ifty, ifjx = :ifjx, ifjy = :ifjy,"
		" mftx = :mftx, mfty = :mfty, mfjx = :mfjx, mfjy = :mfjy,"
		" rftx = :rftx, rfty = :rfty, rfjx = :rfjx, rfjy = :rfjy,"
		" tftx = :tftx, tfty = :tfty, tfjx = :tfjx, tfjy = :tfjy,"
		" btx = :btx, bty = :bty, bjx = :bjx, bjy = :bjy,"
		" tlx_l = :tlx_l, tly_l = :tly_l, brx_l = :brx_l, bry_l = :bry_l,"
		" iftx_l = :iftx_l, ifty_l = :ifty_l, ifjx_l = :ifjx_l, ifjy_l = :ifjy_l,"
		" mftx_l = :mftx_l, mfty_l = :mfty_l, mfjx_l = :mfjx_l, mfjy_l = :mfjy_l,"
		" rftx_l = :rftx_l, rfty_l = :rfty_l, rfjx_l = :rfjx_l, rfjy_l = :rfjy_l,"
		" tftx_l = :tftx_l, tfty_l = :tfty_l, tfjx_l = :tfjx_l, tfjy_l = :tfjy_l"
		" where id = :id";
	QString update_sql_pair_ten = "update positions set "
		" tlx = :tlx, tly = :tly, brx = :brx, bry = :bry,"
		" iftx = :iftx, ifty = :ifty, ifjx = :ifjx, ifjy = :ifjy,"
		" mftx = :mftx, mfty = :mfty, mfjx = :mfjx, mfjy = :mfjy,"
		" rftx = :rftx, rfty = :rfty, rfjx = :rfjx, rfjy = :rfjy,"
		" tftx = :tftx, tfty = :tfty, tfjx = :tfjx, tfjy = :tfjy,"
		" btx = :btx, bty = :bty, bjx = :bjx, bjy = :bjy,"
		" tlx_l = :tlx_l, tly_l = :tly_l, brx_l = :brx_l, bry_l = :bry_l,"
		" iftx_l = :iftx_l, ifty_l = :ifty_l, ifjx_l = :ifjx_l, ifjy_l = :ifjy_l,"
		" mftx_l = :mftx_l, mfty_l = :mfty_l, mfjx_l = :mfjx_l, mfjy_l = :mfjy_l,"
		" rftx_l = :rftx_l, rfty_l = :rfty_l, rfjx_l = :rfjx_l, rfjy_l = :rfjy_l,"
		" tftx_l = :tftx_l, tfty_l = :tfty_l, tfjx_l = :tfjx_l, tfjy_l = :tfjy_l,"
		" btx_l = :btx_l, bty_l = :bty_l, bjx_l = :bjx_l, bjy_l = :bjy_l"
		" where id = :id";


	QString delete_sql = "delete from positions where id = ?";

	QString clear_sql = "delete from positions";

	QString select_all_sql = "select * from positions order by id";

	switch (type)
	{
	case TypeCreate:	//###
		switch (getVideoType(videoType))
		{
		case SingleOne:
			return create_sql_single_one;
		case SingleTwo:
			return create_sql_single_two;
		case SingleThree:
			return create_sql_single_three;
		case SingleFour:
			return create_sql_single_four;
		case SingleFive:
			return create_sql_single_five;
		case SingleSix:
			return create_sql_single_six;
		case SingleSeven:
			return create_sql_single_seven;
		case SingleEight:
			return create_sql_single_eight;
		case SingleNine:
			return create_sql_single_nine;
		case SingleGood:
			return create_sql_single_good;
		case SingleBad:
			return create_sql_single_bad;
		case PairSix:
			return create_sql_pair_six;
		case PairSeven:
			return create_sql_pair_seven;
		case PairEight:
			return create_sql_pair_eight;
		case PairNine:
			return create_sql_pair_nine;
		case PairTen:
			return create_sql_pair_ten;
		default:
			break;
		}
		break;
	case TypeSelect:
		return select_sql;
		break;
	case TypeInsert:	//###
		switch (getVideoType(videoType))
		{
		case SingleOne:
			return insert_sql_single_one;
		case SingleTwo:
			return insert_sql_single_two;
		case SingleThree:
			return insert_sql_single_three;
		case SingleFour:
			return insert_sql_single_four;
		case SingleFive:
			return insert_sql_single_five;
		case SingleSix:
			return insert_sql_single_six;
		case SingleSeven:
			return insert_sql_single_seven;
		case SingleEight:
			return insert_sql_single_eight;
		case SingleNine:
			return insert_sql_single_nine;
		case SingleGood:
			return insert_sql_single_good;
		case SingleBad:
			return insert_sql_single_bad;
		case PairSix:
			return insert_sql_pair_six;
		case PairSeven:
			return insert_sql_pair_seven;
		case PairEight:
			return insert_sql_pair_eight;
		case PairNine:
			return insert_sql_pair_nine;
		case PairTen:
			return insert_sql_pair_ten;
		default:
			break;
		}
		break;
	case TypeUpdate:	//###
		switch (getVideoType(videoType))
		{
		case SingleOne:
			return update_sql_single_one;
		case SingleTwo:
			return update_sql_single_two;
		case SingleThree:
			return update_sql_single_three;
		case SingleFour:
			return update_sql_single_four;
		case SingleFive:
			return update_sql_single_five;
		case SingleSix:
			return update_sql_single_six;
		case SingleSeven:
			return update_sql_single_seven;
		case SingleEight:
			return update_sql_single_eight;
		case SingleNine:
			return update_sql_single_nine;
		case SingleGood:
			return update_sql_single_good;
		case SingleBad:
			return update_sql_single_bad;
		case PairSix:
			return update_sql_pair_six;
		case PairSeven:
			return update_sql_pair_seven;
		case PairEight:
			return update_sql_pair_eight;
		case PairNine:
			return update_sql_pair_nine;
		case PairTen:
			return update_sql_pair_ten;
		default:
			break;
		}
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

void Database::prepareDB(QString targetDir, QString videoType)
{
	db = QSqlDatabase::addDatabase("QSQLITE");
	QString dbpath = targetDir + "/database.db";
	db.setDatabaseName(dbpath);

	if (!db.open()){
		QMessageBox::information(NULL, "database", "database fail to create at: " + dbpath);
		return;
	}


	QSqlQuery query(db);
	//query.exec("drop table files");	//###感觉这一句代码貌似没有什么作用
	QString str = getSql(TypeCreate, videoType);

	if (!query.exec(str))
	{
		//创建一个表
		qDebug() << "create table fail!";
	}
}

//*****************
// Select语句
//*****************
vector<float> Database::execSelect(int index, QString currentImgName, QString videoType)
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
	const int query_result_end = query_result_start + getCorrectParamCcount(videoType);
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
void Database::execInsert(int index, QString fileName, vector<float> params, QString videoType)
{
	if (videoType == "SingleOne")
	{
		//analyze vector
		float tlx = params[0]; float tly = params[1];
		float brx = params[2]; float bry = params[3];
		float iftx = params[4]; float ifty = params[5];
		float ifjx = params[6]; float ifjy = params[7];

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
			QString str_insert = getSql(TypeInsert, videoType);
			qDebug() << str_insert << endl;
			query.prepare(str_insert);
			query.bindValue(":filename", fileName);
		}
		else
		{
			qDebug() << "Something on index: " << index << ". Need update.";
			//if exist, update
			QString str_update = getSql(TypeUpdate, videoType);
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

		if (!query.exec()){
			qDebug() << query.lastError();
		}
		else{
			qDebug() << "Update finish!";
		}
	}
	else if (videoType == "SingleTwo")
	{
		//analyze vector
		float tlx = params[0]; float tly = params[1];
		float brx = params[2]; float bry = params[3];
		float iftx = params[4]; float ifty = params[5];
		float ifjx = params[6]; float ifjy = params[7];
		float mftx = params[8]; float mfty = params[9];
		float mfjx = params[10]; float mfjy = params[11];

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
			QString str_insert = getSql(TypeInsert, videoType);
			query.prepare(str_insert);
			query.bindValue(":filename", fileName);
		}
		else
		{
			qDebug() << "Something on index: " << index << ". Need update.";
			//if exist, update
			QString str_update = getSql(TypeUpdate, videoType);
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
		query.bindValue(":mftx", mftx);
		query.bindValue(":mfty", mfty);
		query.bindValue(":mfjx", mfjx);
		query.bindValue(":mfjy", mfjy);

		if (!query.exec()){
			qDebug() << query.lastError();
		}
		else{
			qDebug() << "Update finish!";
		}
	}
	else if (videoType == "SingleThree")
	{
		//analyze vector
		float tlx = params[0]; float tly = params[1];
		float brx = params[2]; float bry = params[3];
		float iftx = params[4]; float ifty = params[5];
		float ifjx = params[6]; float ifjy = params[7];
		float mftx = params[8]; float mfty = params[9];
		float mfjx = params[10]; float mfjy = params[11];
		float rftx = params[12]; float rfty = params[13];
		float rfjx = params[14]; float rfjy = params[15];

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
			QString str_insert = getSql(TypeInsert, videoType);
			query.prepare(str_insert);
			query.bindValue(":filename", fileName);
		}
		else
		{
			qDebug() << "Something on index: " << index << ". Need update.";
			//if exist, update
			QString str_update = getSql(TypeUpdate, videoType);
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
		query.bindValue(":mftx", mftx);
		query.bindValue(":mfty", mfty);
		query.bindValue(":mfjx", mfjx);
		query.bindValue(":mfjy", mfjy);
		query.bindValue(":rftx", rftx);
		query.bindValue(":rfty", rfty);
		query.bindValue(":rfjx", rfjx);
		query.bindValue(":rfjy", rfjy);

		if (!query.exec()){
			qDebug() << query.lastError();
		}
		else{
			qDebug() << "Update finish!";
		}
	}
	else if (videoType == "SingleFour")
	{
		//analyze vector
		float tlx = params[0]; float tly = params[1];
		float brx = params[2]; float bry = params[3];
		float iftx = params[4]; float ifty = params[5];
		float ifjx = params[6]; float ifjy = params[7];
		float mftx = params[8]; float mfty = params[9];
		float mfjx = params[10]; float mfjy = params[11];
		float rftx = params[12]; float rfty = params[13];
		float rfjx = params[14]; float rfjy = params[15];
		float tftx = params[16]; float tfty = params[17];
		float tfjx = params[18]; float tfjy = params[19];

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
			QString str_insert = getSql(TypeInsert, videoType);
			query.prepare(str_insert);
			query.bindValue(":filename", fileName);
		}
		else
		{
			qDebug() << "Something on index: " << index << ". Need update.";
			//if exist, update
			QString str_update = getSql(TypeUpdate, videoType);
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
		query.bindValue(":mftx", mftx);
		query.bindValue(":mfty", mfty);
		query.bindValue(":mfjx", mfjx);
		query.bindValue(":mfjy", mfjy);
		query.bindValue(":rftx", rftx);
		query.bindValue(":rfty", rfty);
		query.bindValue(":rfjx", rfjx);
		query.bindValue(":rfjy", rfjy);
		query.bindValue(":tftx", tftx);
		query.bindValue(":tfty", tfty);
		query.bindValue(":tfjx", tfjx);
		query.bindValue(":tfjy", tfjy);

		if (!query.exec()){
			qDebug() << query.lastError();
		}
		else{
			qDebug() << "Update finish!";
		}
	}
	else if (videoType == "SingleFive")
	{
		//analyze vector
		float tlx = params[0]; float tly = params[1];
		float brx = params[2]; float bry = params[3];
		float iftx = params[4]; float ifty = params[5];
		float ifjx = params[6]; float ifjy = params[7];
		float mftx = params[8]; float mfty = params[9];
		float mfjx = params[10]; float mfjy = params[11];
		float rftx = params[12]; float rfty = params[13];
		float rfjx = params[14]; float rfjy = params[15];
		float tftx = params[16]; float tfty = params[17];
		float tfjx = params[18]; float tfjy = params[19];
		float btx = params[20]; float bty = params[21];
		float bjx = params[22]; float bjy = params[23];

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
			QString str_insert = getSql(TypeInsert, videoType);
			query.prepare(str_insert);
			query.bindValue(":filename", fileName);
		}
		else
		{
			qDebug() << "Something on index: " << index << ". Need update.";
			//if exist, update
			QString str_update = getSql(TypeUpdate, videoType);
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
		query.bindValue(":mftx", mftx);
		query.bindValue(":mfty", mfty);
		query.bindValue(":mfjx", mfjx);
		query.bindValue(":mfjy", mfjy);
		query.bindValue(":rftx", rftx);
		query.bindValue(":rfty", rfty);
		query.bindValue(":rfjx", rfjx);
		query.bindValue(":rfjy", rfjy);
		query.bindValue(":tftx", tftx);
		query.bindValue(":tfty", tfty);
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
	else if (videoType == "SingleSix")
	{
		//analyze vector
		float tlx = params[0]; float tly = params[1];
		float brx = params[2]; float bry = params[3];
		float tftx = params[4]; float tfty = params[5];
		float tfjx = params[6]; float tfjy = params[7];
		float btx = params[8]; float bty = params[9];
		float bjx = params[10]; float bjy = params[11];

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
			QString str_insert = getSql(TypeInsert, videoType);
			query.prepare(str_insert);
			query.bindValue(":filename", fileName);
		}
		else
		{
			qDebug() << "Something on index: " << index << ". Need update.";
			//if exist, update
			QString str_update = getSql(TypeUpdate, videoType);
			query.prepare(str_update);
		}

		//both insert and update need 
		query.bindValue(":id", index);
		query.bindValue(":tlx", tlx);
		query.bindValue(":tly", tly);
		query.bindValue(":brx", brx);
		query.bindValue(":bry", bry);
		query.bindValue(":tftx", tftx);
		query.bindValue(":tfty", tfty);
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
	else if (videoType == "SingleSeven")
	{
		//analyze vector
		float tlx = params[0]; float tly = params[1];
		float brx = params[2]; float bry = params[3];
		float iftx = params[4]; float ifty = params[5];
		float ifjx = params[6]; float ifjy = params[7];
		float tftx = params[8]; float tfty = params[9];
		float tfjx = params[10]; float tfjy = params[11];
		float btx = params[12]; float bty = params[13];
		float bjx = params[14]; float bjy = params[15];

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
			QString str_insert = getSql(TypeInsert, videoType);
			query.prepare(str_insert);
			query.bindValue(":filename", fileName);
		}
		else
		{
			qDebug() << "Something on index: " << index << ". Need update.";
			//if exist, update
			QString str_update = getSql(TypeUpdate, videoType);
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
		query.bindValue(":tftx", tftx);
		query.bindValue(":tfty", tfty);
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
	else if (videoType == "SingleEight")
	{
		//analyze vector
		float tlx = params[0]; float tly = params[1];
		float brx = params[2]; float bry = params[3];
		float iftx = params[4]; float ifty = params[5];
		float ifjx = params[6]; float ifjy = params[7];
		float btx = params[8]; float bty = params[9];
		float bjx = params[10]; float bjy = params[11];

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
			QString str_insert = getSql(TypeInsert, videoType);
			query.prepare(str_insert);
			query.bindValue(":filename", fileName);
		}
		else
		{
			qDebug() << "Something on index: " << index << ". Need update.";
			//if exist, update
			QString str_update = getSql(TypeUpdate, videoType);
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
	else if (videoType == "SingleNine")
	{
		//analyze vector
		float tlx = params[0]; float tly = params[1];
		float brx = params[2]; float bry = params[3];
		float iftx = params[4]; float ifty = params[5];
		float ifjx = params[6]; float ifjy = params[7];

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
			QString str_insert = getSql(TypeInsert, videoType);
			query.prepare(str_insert);
			query.bindValue(":filename", fileName);
		}
		else
		{
			qDebug() << "Something on index: " << index << ". Need update.";
			//if exist, update
			QString str_update = getSql(TypeUpdate, videoType);
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

		if (!query.exec()){
			qDebug() << query.lastError();
		}
		else{
			qDebug() << "Update finish!";
		}
	}
	else if (videoType == "SingleGood")
	{
		//analyze vector
		float tlx = params[0]; float tly = params[1];
		float brx = params[2]; float bry = params[3];
		float btx = params[4]; float bty = params[5];
		float bjx = params[6]; float bjy = params[7];

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
			QString str_insert = getSql(TypeInsert, videoType);
			query.prepare(str_insert);
			query.bindValue(":filename", fileName);
		}
		else
		{
			qDebug() << "Something on index: " << index << ". Need update.";
			//if exist, update
			QString str_update = getSql(TypeUpdate, videoType);
			query.prepare(str_update);
		}

		//both insert and update need 
		query.bindValue(":id", index);
		query.bindValue(":tlx", tlx);
		query.bindValue(":tly", tly);
		query.bindValue(":brx", brx);
		query.bindValue(":bry", bry);
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
	else if (videoType == "SingleBad")
	{
		//analyze vector
		float tlx = params[0]; float tly = params[1];
		float brx = params[2]; float bry = params[3];
		float btx = params[4]; float bty = params[5];
		float bjx = params[6]; float bjy = params[7];

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
			QString str_insert = getSql(TypeInsert, videoType);
			query.prepare(str_insert);
			query.bindValue(":filename", fileName);
		}
		else
		{
			qDebug() << "Something on index: " << index << ". Need update.";
			//if exist, update
			QString str_update = getSql(TypeUpdate, videoType);
			query.prepare(str_update);
		}

		//both insert and update need 
		query.bindValue(":id", index);
		query.bindValue(":tlx", tlx);
		query.bindValue(":tly", tly);
		query.bindValue(":brx", brx);
		query.bindValue(":bry", bry);
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
	else if (videoType == "PairSix")
	{
		//analyze vector
		float tlx = params[0]; float tly = params[1];
		float brx = params[2]; float bry = params[3];
		float iftx = params[4]; float ifty = params[5];
		float ifjx = params[6]; float ifjy = params[7];
		float mftx = params[8]; float mfty = params[9];
		float mfjx = params[10]; float mfjy = params[11];
		float rftx = params[12]; float rfty = params[13];
		float rfjx = params[14]; float rfjy = params[15];
		float tftx = params[16]; float tfty = params[17];
		float tfjx = params[18]; float tfjy = params[19];
		float btx = params[20]; float bty = params[21];
		float bjx = params[22]; float bjy = params[23];

		float tlx_l = params[24]; float tly_l = params[25];
		float brx_l = params[26]; float bry_l = params[27];
		float iftx_l = params[28]; float ifty_l = params[29];
		float ifjx_l = params[30]; float ifjy_l = params[31];

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
			QString str_insert = getSql(TypeInsert, videoType);
			query.prepare(str_insert);
			query.bindValue(":filename", fileName);
		}
		else
		{
			qDebug() << "Something on index: " << index << ". Need update.";
			//if exist, update
			QString str_update = getSql(TypeUpdate, videoType);
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
		query.bindValue(":mftx", mftx);
		query.bindValue(":mfty", mfty);
		query.bindValue(":mfjx", mfjx);
		query.bindValue(":mfjy", mfjy);
		query.bindValue(":rftx", rftx);
		query.bindValue(":rfty", rfty);
		query.bindValue(":rfjx", rfjx);
		query.bindValue(":rfjy", rfjy);
		query.bindValue(":tftx", tftx);
		query.bindValue(":tfty", tfty);
		query.bindValue(":tfjx", tfjx);
		query.bindValue(":tfjy", tfjy);
		query.bindValue(":btx", btx);
		query.bindValue(":bty", bty);
		query.bindValue(":bjx", bjx);
		query.bindValue(":bjy", bjy);

		query.bindValue(":tlx_l", tlx_l);
		query.bindValue(":tly_l", tly_l);
		query.bindValue(":brx_l", brx_l);
		query.bindValue(":bry_l", bry_l);
		query.bindValue(":iftx_l", iftx_l);
		query.bindValue(":ifty_l", ifty_l);
		query.bindValue(":ifjx_l", ifjx_l);
		query.bindValue(":ifjy_l", ifjy_l);

		if (!query.exec()){
			qDebug() << query.lastError();
		}
		else{
			qDebug() << "Update finish!";
		}
	}
	else if (videoType == "PairSeven")
	{
		//analyze vector
		float tlx = params[0]; float tly = params[1];
		float brx = params[2]; float bry = params[3];
		float iftx = params[4]; float ifty = params[5];
		float ifjx = params[6]; float ifjy = params[7];
		float mftx = params[8]; float mfty = params[9];
		float mfjx = params[10]; float mfjy = params[11];
		float rftx = params[12]; float rfty = params[13];
		float rfjx = params[14]; float rfjy = params[15];
		float tftx = params[16]; float tfty = params[17];
		float tfjx = params[18]; float tfjy = params[19];
		float btx = params[20]; float bty = params[21];
		float bjx = params[22]; float bjy = params[23];

		float tlx_l = params[24]; float tly_l = params[25];
		float brx_l = params[26]; float bry_l = params[27];
		float iftx_l = params[28]; float ifty_l = params[29];
		float ifjx_l = params[30]; float ifjy_l = params[31];
		float mftx_l = params[32]; float mfty_l = params[33];
		float mfjx_l = params[34]; float mfjy_l = params[35];

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
			QString str_insert = getSql(TypeInsert, videoType);
			query.prepare(str_insert);
			query.bindValue(":filename", fileName);
		}
		else
		{
			qDebug() << "Something on index: " << index << ". Need update.";
			//if exist, update
			QString str_update = getSql(TypeUpdate, videoType);
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
		query.bindValue(":mftx", mftx);
		query.bindValue(":mfty", mfty);
		query.bindValue(":mfjx", mfjx);
		query.bindValue(":mfjy", mfjy);
		query.bindValue(":rftx", rftx);
		query.bindValue(":rfty", rfty);
		query.bindValue(":rfjx", rfjx);
		query.bindValue(":rfjy", rfjy);
		query.bindValue(":tftx", tftx);
		query.bindValue(":tfty", tfty);
		query.bindValue(":tfjx", tfjx);
		query.bindValue(":tfjy", tfjy);
		query.bindValue(":btx", btx);
		query.bindValue(":bty", bty);
		query.bindValue(":bjx", bjx);
		query.bindValue(":bjy", bjy);

		query.bindValue(":tlx_l", tlx_l);
		query.bindValue(":tly_l", tly_l);
		query.bindValue(":brx_l", brx_l);
		query.bindValue(":bry_l", bry_l);
		query.bindValue(":iftx_l", iftx_l);
		query.bindValue(":ifty_l", ifty_l);
		query.bindValue(":ifjx_l", ifjx_l);
		query.bindValue(":ifjy_l", ifjy_l);
		query.bindValue(":mftx_l", mftx_l);
		query.bindValue(":mfty_l", mfty_l);
		query.bindValue(":mfjx_l", mfjx_l);
		query.bindValue(":mfjy_l", mfjy_l);

		if (!query.exec()){
			qDebug() << query.lastError();
		}
		else{
			qDebug() << "Update finish!";
		}
	}
	else if (videoType == "PairEight")
	{
		//analyze vector
		float tlx = params[0]; float tly = params[1];
		float brx = params[2]; float bry = params[3];
		float iftx = params[4]; float ifty = params[5];
		float ifjx = params[6]; float ifjy = params[7];
		float mftx = params[8]; float mfty = params[9];
		float mfjx = params[10]; float mfjy = params[11];
		float rftx = params[12]; float rfty = params[13];
		float rfjx = params[14]; float rfjy = params[15];
		float tftx = params[16]; float tfty = params[17];
		float tfjx = params[18]; float tfjy = params[19];
		float btx = params[20]; float bty = params[21];
		float bjx = params[22]; float bjy = params[23];

		float tlx_l = params[24]; float tly_l = params[25];
		float brx_l = params[26]; float bry_l = params[27];
		float iftx_l = params[28]; float ifty_l = params[29];
		float ifjx_l = params[30]; float ifjy_l = params[31];
		float mftx_l = params[32]; float mfty_l = params[33];
		float mfjx_l = params[34]; float mfjy_l = params[35];
		float btx_l = params[36]; float bty_l = params[37];
		float bjx_l = params[38]; float bjy_l = params[39];

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
			QString str_insert = getSql(TypeInsert, videoType);
			query.prepare(str_insert);
			query.bindValue(":filename", fileName);
		}
		else
		{
			qDebug() << "Something on index: " << index << ". Need update.";
			//if exist, update
			QString str_update = getSql(TypeUpdate, videoType);
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
		query.bindValue(":mftx", mftx);
		query.bindValue(":mfty", mfty);
		query.bindValue(":mfjx", mfjx);
		query.bindValue(":mfjy", mfjy);
		query.bindValue(":rftx", rftx);
		query.bindValue(":rfty", rfty);
		query.bindValue(":rfjx", rfjx);
		query.bindValue(":rfjy", rfjy);
		query.bindValue(":tftx", tftx);
		query.bindValue(":tfty", tfty);
		query.bindValue(":tfjx", tfjx);
		query.bindValue(":tfjy", tfjy);
		query.bindValue(":btx", btx);
		query.bindValue(":bty", bty);
		query.bindValue(":bjx", bjx);
		query.bindValue(":bjy", bjy);

		query.bindValue(":tlx_l", tlx_l);
		query.bindValue(":tly_l", tly_l);
		query.bindValue(":brx_l", brx_l);
		query.bindValue(":bry_l", bry_l);
		query.bindValue(":iftx_l", iftx_l);
		query.bindValue(":ifty_l", ifty_l);
		query.bindValue(":ifjx_l", ifjx_l);
		query.bindValue(":ifjy_l", ifjy_l);
		query.bindValue(":mftx_l", mftx_l);
		query.bindValue(":mfty_l", mfty_l);
		query.bindValue(":mfjx_l", mfjx_l);
		query.bindValue(":mfjy_l", mfjy_l);
		query.bindValue(":btx_l", btx_l);
		query.bindValue(":bty_l", bty_l);
		query.bindValue(":bjx_l", bjx_l);
		query.bindValue(":bjy_l", bjy_l);

		if (!query.exec()){
			qDebug() << query.lastError();
		}
		else{
			qDebug() << "Update finish!";
		}
	}
	else if (videoType == "PairNine")
	{
		//analyze vector
		float tlx = params[0]; float tly = params[1];
		float brx = params[2]; float bry = params[3];
		float iftx = params[4]; float ifty = params[5];
		float ifjx = params[6]; float ifjy = params[7];
		float mftx = params[8]; float mfty = params[9];
		float mfjx = params[10]; float mfjy = params[11];
		float rftx = params[12]; float rfty = params[13];
		float rfjx = params[14]; float rfjy = params[15];
		float tftx = params[16]; float tfty = params[17];
		float tfjx = params[18]; float tfjy = params[19];
		float btx = params[20]; float bty = params[21];
		float bjx = params[22]; float bjy = params[23];

		float tlx_l = params[24]; float tly_l = params[25];
		float brx_l = params[26]; float bry_l = params[27];
		float iftx_l = params[28]; float ifty_l = params[29];
		float ifjx_l = params[30]; float ifjy_l = params[31];
		float mftx_l = params[32]; float mfty_l = params[33];
		float mfjx_l = params[34]; float mfjy_l = params[35];
		float rftx_l = params[36]; float rfty_l = params[37];
		float rfjx_l = params[38]; float rfjy_l = params[39];
		float tftx_l = params[40]; float tfty_l = params[41];
		float tfjx_l = params[42]; float tfjy_l = params[43];

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
			QString str_insert = getSql(TypeInsert, videoType);
			query.prepare(str_insert);
			query.bindValue(":filename", fileName);
		}
		else
		{
			qDebug() << "Something on index: " << index << ". Need update.";
			//if exist, update
			QString str_update = getSql(TypeUpdate, videoType);
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
		query.bindValue(":mftx", mftx);
		query.bindValue(":mfty", mfty);
		query.bindValue(":mfjx", mfjx);
		query.bindValue(":mfjy", mfjy);
		query.bindValue(":rftx", rftx);
		query.bindValue(":rfty", rfty);
		query.bindValue(":rfjx", rfjx);
		query.bindValue(":rfjy", rfjy);
		query.bindValue(":tftx", tftx);
		query.bindValue(":tfty", tfty);
		query.bindValue(":tfjx", tfjx);
		query.bindValue(":tfjy", tfjy);
		query.bindValue(":btx", btx);
		query.bindValue(":bty", bty);
		query.bindValue(":bjx", bjx);
		query.bindValue(":bjy", bjy);

		query.bindValue(":tlx_l", tlx_l);
		query.bindValue(":tly_l", tly_l);
		query.bindValue(":brx_l", brx_l);
		query.bindValue(":bry_l", bry_l);
		query.bindValue(":iftx_l", iftx_l);
		query.bindValue(":ifty_l", ifty_l);
		query.bindValue(":ifjx_l", ifjx_l);
		query.bindValue(":ifjy_l", ifjy_l);
		query.bindValue(":mftx_l", mftx_l);
		query.bindValue(":mfty_l", mfty_l);
		query.bindValue(":mfjx_l", mfjx_l);
		query.bindValue(":mfjy_l", mfjy_l);
		query.bindValue(":rftx_l", rftx_l);
		query.bindValue(":rfty_l", rfty_l);
		query.bindValue(":rfjx_l", rfjx_l);
		query.bindValue(":rfjy_l", rfjy_l);
		query.bindValue(":tftx_l", tftx_l);
		query.bindValue(":tfty_l", tfty_l);
		query.bindValue(":tfjx_l", tfjx_l);
		query.bindValue(":tfjy_l", tfjy_l);

		if (!query.exec()){
			qDebug() << query.lastError();
		}
		else{
			qDebug() << "Update finish!";
		}
	}
	else if (videoType == "PairTen")
	{
		//analyze vector
		float tlx = params[0]; float tly = params[1];
		float brx = params[2]; float bry = params[3];
		float iftx = params[4]; float ifty = params[5];
		float ifjx = params[6]; float ifjy = params[7];
		float mftx = params[8]; float mfty = params[9];
		float mfjx = params[10]; float mfjy = params[11];
		float rftx = params[12]; float rfty = params[13];
		float rfjx = params[14]; float rfjy = params[15];
		float tftx = params[16]; float tfty = params[17];
		float tfjx = params[18]; float tfjy = params[19];
		float btx = params[20]; float bty = params[21];
		float bjx = params[22]; float bjy = params[23];

		float tlx_l = params[24]; float tly_l = params[25];
		float brx_l = params[26]; float bry_l = params[27];
		float iftx_l = params[28]; float ifty_l = params[29];
		float ifjx_l = params[30]; float ifjy_l = params[31];
		float mftx_l = params[32]; float mfty_l = params[33];
		float mfjx_l = params[34]; float mfjy_l = params[35];
		float rftx_l = params[36]; float rfty_l = params[37];
		float rfjx_l = params[38]; float rfjy_l = params[39];
		float tftx_l = params[40]; float tfty_l = params[41];
		float tfjx_l = params[42]; float tfjy_l = params[43];
		float btx_l = params[44]; float bty_l = params[45];
		float bjx_l = params[46]; float bjy_l = params[47];

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
			QString str_insert = getSql(TypeInsert, videoType);
			query.prepare(str_insert);
			query.bindValue(":filename", fileName);
		}
		else
		{
			qDebug() << "Something on index: " << index << ". Need update.";
			//if exist, update
			QString str_update = getSql(TypeUpdate, videoType);
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
		query.bindValue(":mftx", mftx);
		query.bindValue(":mfty", mfty);
		query.bindValue(":mfjx", mfjx);
		query.bindValue(":mfjy", mfjy);
		query.bindValue(":rftx", rftx);
		query.bindValue(":rfty", rfty);
		query.bindValue(":rfjx", rfjx);
		query.bindValue(":rfjy", rfjy);
		query.bindValue(":tftx", tftx);
		query.bindValue(":tfty", tfty);
		query.bindValue(":tfjx", tfjx);
		query.bindValue(":tfjy", tfjy);
		query.bindValue(":btx", btx);
		query.bindValue(":bty", bty);
		query.bindValue(":bjx", bjx);
		query.bindValue(":bjy", bjy);

		query.bindValue(":tlx_l", tlx_l);
		query.bindValue(":tly_l", tly_l);
		query.bindValue(":brx_l", brx_l);
		query.bindValue(":bry_l", bry_l);
		query.bindValue(":iftx_l", iftx_l);
		query.bindValue(":ifty_l", ifty_l);
		query.bindValue(":ifjx_l", ifjx_l);
		query.bindValue(":ifjy_l", ifjy_l);
		query.bindValue(":mftx_l", mftx_l);
		query.bindValue(":mfty_l", mfty_l);
		query.bindValue(":mfjx_l", mfjx_l);
		query.bindValue(":mfjy_l", mfjy_l);
		query.bindValue(":rftx_l", rftx_l);
		query.bindValue(":rfty_l", rfty_l);
		query.bindValue(":rfjx_l", rfjx_l);
		query.bindValue(":rfjy_l", rfjy_l);
		query.bindValue(":tftx_l", tftx_l);
		query.bindValue(":tfty_l", tfty_l);
		query.bindValue(":tfjx_l", tfjx_l);
		query.bindValue(":tfjy_l", tfjy_l);
		query.bindValue(":btx_l", btx_l);
		query.bindValue(":bty_l", bty_l);
		query.bindValue(":bjx_l", bjx_l);
		query.bindValue(":bjy_l", bjy_l);

		if (!query.exec()){
			qDebug() << query.lastError();
		}
		else{
			qDebug() << "Update finish!";
		}
	}
	else
	{
		abort();
	}

}

//*****************
// 转化db文件成为txt
//*****************
void Database::convertDBtoTxt(QString targetDir, QString videoType)
{
	Recorder rec;
	rec.initFileStream(targetDir);

	QSqlQuery query(db);

	QString selectall_str = getSql(TypeSelectAll);
	if (!query.exec(selectall_str)){
		qDebug() << "select all fail!";
	}

	if (videoType == "SingleOne")
	{
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

			//append data in recorder's list
			rec.appendStringList(fileName, params);
		}
	}
	else if (videoType == "SingleTwo")
	{
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
			float mftx = query.value(10).toFloat(); params.push_back(mftx);
			float mfty = query.value(11).toFloat(); params.push_back(mfty);
			float mfjx = query.value(12).toFloat(); params.push_back(mfjx);
			float mfjy = query.value(13).toFloat(); params.push_back(mfjy);

			//append data in recorder's list
			rec.appendStringList(fileName, params);

		}
	}
	else if (videoType == "SingleThree")
	{
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
			float mftx = query.value(10).toFloat(); params.push_back(mftx);
			float mfty = query.value(11).toFloat(); params.push_back(mfty);
			float mfjx = query.value(12).toFloat(); params.push_back(mfjx);
			float mfjy = query.value(13).toFloat(); params.push_back(mfjy);
			float rftx = query.value(14).toFloat(); params.push_back(rftx);
			float rfty = query.value(15).toFloat(); params.push_back(rfty);
			float rfjx = query.value(16).toFloat(); params.push_back(rfjx);
			float rfjy = query.value(17).toFloat(); params.push_back(rfjy);

			//append data in recorder's list
			rec.appendStringList(fileName, params);

		}
	}
	else if (videoType == "SingleFour")
	{
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
			float mftx = query.value(10).toFloat(); params.push_back(mftx);
			float mfty = query.value(11).toFloat(); params.push_back(mfty);
			float mfjx = query.value(12).toFloat(); params.push_back(mfjx);
			float mfjy = query.value(13).toFloat(); params.push_back(mfjy);
			float rftx = query.value(14).toFloat(); params.push_back(rftx);
			float rfty = query.value(15).toFloat(); params.push_back(rfty);
			float rfjx = query.value(16).toFloat(); params.push_back(rfjx);
			float rfjy = query.value(17).toFloat(); params.push_back(rfjy);
			float tftx = query.value(18).toFloat(); params.push_back(tftx);
			float tfty = query.value(19).toFloat(); params.push_back(tfty);
			float tfjx = query.value(20).toFloat(); params.push_back(tfjx);
			float tfjy = query.value(21).toFloat(); params.push_back(tfjy);

			//append data in recorder's list
			rec.appendStringList(fileName, params);

		}
	}
	else if (videoType == "SingleFive")
	{
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
			float mftx = query.value(10).toFloat(); params.push_back(mftx);
			float mfty = query.value(11).toFloat(); params.push_back(mfty);
			float mfjx = query.value(12).toFloat(); params.push_back(mfjx);
			float mfjy = query.value(13).toFloat(); params.push_back(mfjy);
			float rftx = query.value(14).toFloat(); params.push_back(rftx);
			float rfty = query.value(15).toFloat(); params.push_back(rfty);
			float rfjx = query.value(16).toFloat(); params.push_back(rfjx);
			float rfjy = query.value(17).toFloat(); params.push_back(rfjy);
			float tftx = query.value(18).toFloat(); params.push_back(tftx);
			float tfty = query.value(19).toFloat(); params.push_back(tfty);
			float tfjx = query.value(20).toFloat(); params.push_back(tfjx);
			float tfjy = query.value(21).toFloat(); params.push_back(tfjy);
			float btx = query.value(22).toFloat(); params.push_back(btx);
			float bty = query.value(23).toFloat(); params.push_back(bty);
			float bjx = query.value(24).toFloat(); params.push_back(bjx);
			float bjy = query.value(25).toFloat(); params.push_back(bjy);

			//append data in recorder's list
			rec.appendStringList(fileName, params);

		}
	}
	else if (videoType == "SingleSix")
	{
		while (query.next())//query.next()指向查找到的第一条记录，然后每次后移一条记录   
		{
			int id = query.value(0).toInt();//query.value(0)是id的值，将其转换为int型   
			QString fileName = query.value(1).toString();

			vector<float> params;
			float tlx = query.value(2).toFloat(); params.push_back(tlx);
			float tly = query.value(3).toFloat(); params.push_back(tly);
			float brx = query.value(4).toFloat(); params.push_back(brx);
			float bry = query.value(5).toFloat(); params.push_back(bry);
			float tftx = query.value(6).toFloat(); params.push_back(tftx);
			float tfty = query.value(7).toFloat(); params.push_back(tfty);
			float tfjx = query.value(8).toFloat(); params.push_back(tfjx);
			float tfjy = query.value(9).toFloat(); params.push_back(tfjy);
			float btx = query.value(10).toFloat(); params.push_back(btx);
			float bty = query.value(11).toFloat(); params.push_back(bty);
			float bjx = query.value(12).toFloat(); params.push_back(bjx);
			float bjy = query.value(13).toFloat(); params.push_back(bjy);

			//append data in recorder's list
			rec.appendStringList(fileName, params);

		}
	}
	else if (videoType == "SingleSeven")
	{
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
			float tftx = query.value(10).toFloat(); params.push_back(tftx);
			float tfty = query.value(11).toFloat(); params.push_back(tfty);
			float tfjx = query.value(12).toFloat(); params.push_back(tfjx);
			float tfjy = query.value(13).toFloat(); params.push_back(tfjy);
			float btx = query.value(14).toFloat(); params.push_back(btx);
			float bty = query.value(15).toFloat(); params.push_back(bty);
			float bjx = query.value(16).toFloat(); params.push_back(bjx);
			float bjy = query.value(17).toFloat(); params.push_back(bjy);

			//append data in recorder's list
			rec.appendStringList(fileName, params);

		}
	}
	else if (videoType == "SingleEight")
	{
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
			float btx = query.value(10).toFloat(); params.push_back(btx);
			float bty = query.value(11).toFloat(); params.push_back(bty);
			float bjx = query.value(12).toFloat(); params.push_back(bjx);
			float bjy = query.value(13).toFloat(); params.push_back(bjy);

			//append data in recorder's list
			rec.appendStringList(fileName, params);

		}
	}
	else if (videoType == "SingleNine")
	{
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

			//append data in recorder's list
			rec.appendStringList(fileName, params);

		}
	}
	else if (videoType == "SingleGood")
	{
		while (query.next())//query.next()指向查找到的第一条记录，然后每次后移一条记录   
		{
			int id = query.value(0).toInt();//query.value(0)是id的值，将其转换为int型   
			QString fileName = query.value(1).toString();

			vector<float> params;
			float tlx = query.value(2).toFloat(); params.push_back(tlx);
			float tly = query.value(3).toFloat(); params.push_back(tly);
			float brx = query.value(4).toFloat(); params.push_back(brx);
			float bry = query.value(5).toFloat(); params.push_back(bry);
			float btx = query.value(6).toFloat(); params.push_back(btx);
			float bty = query.value(7).toFloat(); params.push_back(bty);
			float bjx = query.value(8).toFloat(); params.push_back(bjx);
			float bjy = query.value(9).toFloat(); params.push_back(bjy);

			//append data in recorder's list
			rec.appendStringList(fileName, params);

		}
	}
	else if (videoType == "SingleBad")
	{
		while (query.next())//query.next()指向查找到的第一条记录，然后每次后移一条记录   
		{
			int id = query.value(0).toInt();//query.value(0)是id的值，将其转换为int型   
			QString fileName = query.value(1).toString();

			vector<float> params;
			float tlx = query.value(2).toFloat(); params.push_back(tlx);
			float tly = query.value(3).toFloat(); params.push_back(tly);
			float brx = query.value(4).toFloat(); params.push_back(brx);
			float bry = query.value(5).toFloat(); params.push_back(bry);
			float btx = query.value(6).toFloat(); params.push_back(btx);
			float bty = query.value(7).toFloat(); params.push_back(bty);
			float bjx = query.value(8).toFloat(); params.push_back(bjx);
			float bjy = query.value(9).toFloat(); params.push_back(bjy);

			//append data in recorder's list
			rec.appendStringList(fileName, params);

		}
	}
	else if (videoType == "PairSix")
	{
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
			float mftx = query.value(10).toFloat(); params.push_back(mftx);
			float mfty = query.value(11).toFloat(); params.push_back(mfty);
			float mfjx = query.value(12).toFloat(); params.push_back(mfjx);
			float mfjy = query.value(13).toFloat(); params.push_back(mfjy);
			float rftx = query.value(14).toFloat(); params.push_back(rftx);
			float rfty = query.value(15).toFloat(); params.push_back(rfty);
			float rfjx = query.value(16).toFloat(); params.push_back(rfjx);
			float rfjy = query.value(17).toFloat(); params.push_back(rfjy);
			float tftx = query.value(18).toFloat(); params.push_back(tftx);
			float tfty = query.value(19).toFloat(); params.push_back(tfty);
			float tfjx = query.value(20).toFloat(); params.push_back(tfjx);
			float tfjy = query.value(21).toFloat(); params.push_back(tfjy);
			float btx = query.value(22).toFloat(); params.push_back(btx);
			float bty = query.value(23).toFloat(); params.push_back(bty);
			float bjx = query.value(24).toFloat(); params.push_back(bjx);
			float bjy = query.value(25).toFloat(); params.push_back(bjy);

			float tlx_l = query.value(26).toFloat(); params.push_back(tlx_l);
			float tly_l = query.value(27).toFloat(); params.push_back(tly_l);
			float brx_l = query.value(28).toFloat(); params.push_back(brx_l);
			float bry_l = query.value(29).toFloat(); params.push_back(bry_l);
			float iftx_l = query.value(30).toFloat(); params.push_back(iftx_l);
			float ifty_l = query.value(31).toFloat(); params.push_back(ifty_l);
			float ifjx_l = query.value(32).toFloat(); params.push_back(ifjx_l);
			float ifjy_l = query.value(33).toFloat(); params.push_back(ifjy_l);

			//append data in recorder's list
			rec.appendStringList(fileName, params);

		}
	}
	else if (videoType == "PairSeven")
	{
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
			float mftx = query.value(10).toFloat(); params.push_back(mftx);
			float mfty = query.value(11).toFloat(); params.push_back(mfty);
			float mfjx = query.value(12).toFloat(); params.push_back(mfjx);
			float mfjy = query.value(13).toFloat(); params.push_back(mfjy);
			float rftx = query.value(14).toFloat(); params.push_back(rftx);
			float rfty = query.value(15).toFloat(); params.push_back(rfty);
			float rfjx = query.value(16).toFloat(); params.push_back(rfjx);
			float rfjy = query.value(17).toFloat(); params.push_back(rfjy);
			float tftx = query.value(18).toFloat(); params.push_back(tftx);
			float tfty = query.value(19).toFloat(); params.push_back(tfty);
			float tfjx = query.value(20).toFloat(); params.push_back(tfjx);
			float tfjy = query.value(21).toFloat(); params.push_back(tfjy);
			float btx = query.value(22).toFloat(); params.push_back(btx);
			float bty = query.value(23).toFloat(); params.push_back(bty);
			float bjx = query.value(24).toFloat(); params.push_back(bjx);
			float bjy = query.value(25).toFloat(); params.push_back(bjy);

			float tlx_l = query.value(26).toFloat(); params.push_back(tlx_l);
			float tly_l = query.value(27).toFloat(); params.push_back(tly_l);
			float brx_l = query.value(28).toFloat(); params.push_back(brx_l);
			float bry_l = query.value(29).toFloat(); params.push_back(bry_l);
			float iftx_l = query.value(30).toFloat(); params.push_back(iftx_l);
			float ifty_l = query.value(31).toFloat(); params.push_back(ifty_l);
			float ifjx_l = query.value(32).toFloat(); params.push_back(ifjx_l);
			float ifjy_l = query.value(33).toFloat(); params.push_back(ifjy_l);
			float mftx_l = query.value(34).toFloat(); params.push_back(mftx_l);
			float mfty_l = query.value(35).toFloat(); params.push_back(mfty_l);
			float mfjx_l = query.value(36).toFloat(); params.push_back(mfjx_l);
			float mfjy_l = query.value(37).toFloat(); params.push_back(mfjy_l);

			//append data in recorder's list
			rec.appendStringList(fileName, params);

		}
	}
	else if (videoType == "PairEight")
	{
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
			float mftx = query.value(10).toFloat(); params.push_back(mftx);
			float mfty = query.value(11).toFloat(); params.push_back(mfty);
			float mfjx = query.value(12).toFloat(); params.push_back(mfjx);
			float mfjy = query.value(13).toFloat(); params.push_back(mfjy);
			float rftx = query.value(14).toFloat(); params.push_back(rftx);
			float rfty = query.value(15).toFloat(); params.push_back(rfty);
			float rfjx = query.value(16).toFloat(); params.push_back(rfjx);
			float rfjy = query.value(17).toFloat(); params.push_back(rfjy);
			float tftx = query.value(18).toFloat(); params.push_back(tftx);
			float tfty = query.value(19).toFloat(); params.push_back(tfty);
			float tfjx = query.value(20).toFloat(); params.push_back(tfjx);
			float tfjy = query.value(21).toFloat(); params.push_back(tfjy);
			float btx = query.value(22).toFloat(); params.push_back(btx);
			float bty = query.value(23).toFloat(); params.push_back(bty);
			float bjx = query.value(24).toFloat(); params.push_back(bjx);
			float bjy = query.value(25).toFloat(); params.push_back(bjy);

			float tlx_l = query.value(26).toFloat(); params.push_back(tlx_l);
			float tly_l = query.value(27).toFloat(); params.push_back(tly_l);
			float brx_l = query.value(28).toFloat(); params.push_back(brx_l);
			float bry_l = query.value(29).toFloat(); params.push_back(bry_l);
			float iftx_l = query.value(30).toFloat(); params.push_back(iftx_l);
			float ifty_l = query.value(31).toFloat(); params.push_back(ifty_l);
			float ifjx_l = query.value(32).toFloat(); params.push_back(ifjx_l);
			float ifjy_l = query.value(33).toFloat(); params.push_back(ifjy_l);
			float mftx_l = query.value(34).toFloat(); params.push_back(mftx_l);
			float mfty_l = query.value(35).toFloat(); params.push_back(mfty_l);
			float mfjx_l = query.value(36).toFloat(); params.push_back(mfjx_l);
			float mfjy_l = query.value(37).toFloat(); params.push_back(mfjy_l);
			float btx_l = query.value(38).toFloat(); params.push_back(btx_l);
			float bty_l = query.value(39).toFloat(); params.push_back(bty_l);
			float bjx_l = query.value(40).toFloat(); params.push_back(bjx_l);
			float bjy_l = query.value(41).toFloat(); params.push_back(bjy_l);

			//append data in recorder's list
			rec.appendStringList(fileName, params);

		}
	}
	else if (videoType == "PairNine")
	{
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
			float mftx = query.value(10).toFloat(); params.push_back(mftx);
			float mfty = query.value(11).toFloat(); params.push_back(mfty);
			float mfjx = query.value(12).toFloat(); params.push_back(mfjx);
			float mfjy = query.value(13).toFloat(); params.push_back(mfjy);
			float rftx = query.value(14).toFloat(); params.push_back(rftx);
			float rfty = query.value(15).toFloat(); params.push_back(rfty);
			float rfjx = query.value(16).toFloat(); params.push_back(rfjx);
			float rfjy = query.value(17).toFloat(); params.push_back(rfjy);
			float tftx = query.value(18).toFloat(); params.push_back(tftx);
			float tfty = query.value(19).toFloat(); params.push_back(tfty);
			float tfjx = query.value(20).toFloat(); params.push_back(tfjx);
			float tfjy = query.value(21).toFloat(); params.push_back(tfjy);
			float btx = query.value(22).toFloat(); params.push_back(btx);
			float bty = query.value(23).toFloat(); params.push_back(bty);
			float bjx = query.value(24).toFloat(); params.push_back(bjx);
			float bjy = query.value(25).toFloat(); params.push_back(bjy);

			float tlx_l = query.value(26).toFloat(); params.push_back(tlx_l);
			float tly_l = query.value(27).toFloat(); params.push_back(tly_l);
			float brx_l = query.value(28).toFloat(); params.push_back(brx_l);
			float bry_l = query.value(29).toFloat(); params.push_back(bry_l);
			float iftx_l = query.value(30).toFloat(); params.push_back(iftx_l);
			float ifty_l = query.value(31).toFloat(); params.push_back(ifty_l);
			float ifjx_l = query.value(32).toFloat(); params.push_back(ifjx_l);
			float ifjy_l = query.value(33).toFloat(); params.push_back(ifjy_l);
			float mftx_l = query.value(34).toFloat(); params.push_back(mftx_l);
			float mfty_l = query.value(35).toFloat(); params.push_back(mfty_l);
			float mfjx_l = query.value(36).toFloat(); params.push_back(mfjx_l);
			float mfjy_l = query.value(37).toFloat(); params.push_back(mfjy_l);
			float rftx_l = query.value(38).toFloat(); params.push_back(rftx_l);
			float rfty_l = query.value(39).toFloat(); params.push_back(rfty_l);
			float rfjx_l = query.value(40).toFloat(); params.push_back(rfjx_l);
			float rfjy_l = query.value(41).toFloat(); params.push_back(rfjy_l);
			float tftx_l = query.value(42).toFloat(); params.push_back(tftx_l);
			float tfty_l = query.value(43).toFloat(); params.push_back(tfty_l);
			float tfjx_l = query.value(44).toFloat(); params.push_back(tfjx_l);
			float tfjy_l = query.value(45).toFloat(); params.push_back(tfjy_l);

			//append data in recorder's list
			rec.appendStringList(fileName, params);

		}
	}
	else if (videoType == "PairTen")
	{
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
			float mftx = query.value(10).toFloat(); params.push_back(mftx);
			float mfty = query.value(11).toFloat(); params.push_back(mfty);
			float mfjx = query.value(12).toFloat(); params.push_back(mfjx);
			float mfjy = query.value(13).toFloat(); params.push_back(mfjy);
			float rftx = query.value(14).toFloat(); params.push_back(rftx);
			float rfty = query.value(15).toFloat(); params.push_back(rfty);
			float rfjx = query.value(16).toFloat(); params.push_back(rfjx);
			float rfjy = query.value(17).toFloat(); params.push_back(rfjy);
			float tftx = query.value(18).toFloat(); params.push_back(tftx);
			float tfty = query.value(19).toFloat(); params.push_back(tfty);
			float tfjx = query.value(20).toFloat(); params.push_back(tfjx);
			float tfjy = query.value(21).toFloat(); params.push_back(tfjy);
			float btx = query.value(22).toFloat(); params.push_back(btx);
			float bty = query.value(23).toFloat(); params.push_back(bty);
			float bjx = query.value(24).toFloat(); params.push_back(bjx);
			float bjy = query.value(25).toFloat(); params.push_back(bjy);

			float tlx_l = query.value(26).toFloat(); params.push_back(tlx_l);
			float tly_l = query.value(27).toFloat(); params.push_back(tly_l);
			float brx_l = query.value(28).toFloat(); params.push_back(brx_l);
			float bry_l = query.value(29).toFloat(); params.push_back(bry_l);
			float iftx_l = query.value(30).toFloat(); params.push_back(iftx_l);
			float ifty_l = query.value(31).toFloat(); params.push_back(ifty_l);
			float ifjx_l = query.value(32).toFloat(); params.push_back(ifjx_l);
			float ifjy_l = query.value(33).toFloat(); params.push_back(ifjy_l);
			float mftx_l = query.value(34).toFloat(); params.push_back(mftx_l);
			float mfty_l = query.value(35).toFloat(); params.push_back(mfty_l);
			float mfjx_l = query.value(36).toFloat(); params.push_back(mfjx_l);
			float mfjy_l = query.value(37).toFloat(); params.push_back(mfjy_l);
			float rftx_l = query.value(38).toFloat(); params.push_back(rftx_l);
			float rfty_l = query.value(39).toFloat(); params.push_back(rfty_l);
			float rfjx_l = query.value(40).toFloat(); params.push_back(rfjx_l);
			float rfjy_l = query.value(41).toFloat(); params.push_back(rfjy_l);
			float tftx_l = query.value(42).toFloat(); params.push_back(tftx_l);
			float tfty_l = query.value(43).toFloat(); params.push_back(tfty_l);
			float tfjx_l = query.value(44).toFloat(); params.push_back(tfjx_l);
			float tfjy_l = query.value(45).toFloat(); params.push_back(tfjy_l);
			float btx_l = query.value(46).toFloat(); params.push_back(btx_l);
			float bty_l = query.value(47).toFloat(); params.push_back(bty_l);
			float bjx_l = query.value(48).toFloat(); params.push_back(bjx_l);
			float bjy_l = query.value(49).toFloat(); params.push_back(bjy_l);

			//append data in recorder's list
			rec.appendStringList(fileName, params);

		}
	}
	else
	{
		QMessageBox::information(NULL, QObject::tr("videoType"), QObject::tr("videoType Error!"));
		abort();
	}

	//write data into txt via recorder
	rec.writeDataFile();
}

//###
VideoType Database::getVideoType(QString videoType)
{
	if (videoType == "SingleOne")
	{
		return SingleOne;
	}
	if (videoType == "SingleTwo")
	{
		return SingleTwo;
	}
	if (videoType == "SingleThree")
	{
		return SingleThree;
	}
	if (videoType == "SingleFour")
	{
		return SingleFour;
	}
	if (videoType == "SingleFive")
	{
		return SingleFive;
	}
	if (videoType == "SingleSix")
	{
		return SingleSix;
	}
	if (videoType == "SingleSeven")
	{
		return SingleSeven;
	}
	if (videoType == "SingleEight")
	{
		return SingleEight;
	}
	if (videoType == "SingleNine")
	{
		return SingleNine;
	}
	if (videoType == "SingleGood")
	{
		return SingleGood;
	}
	if (videoType == "SingleBad")
	{
		return SingleBad;
	}
	if (videoType == "PairSix")
	{
		return PairSix;
	}
	if (videoType == "PairSeven")
	{
		return PairSeven;
	}
	if (videoType == "PairEight")
	{
		return PairEight;
	}
	if (videoType == "PairNine")
	{
		return PairNine;
	}
	if (videoType == "PairTen")
	{
		return PairTen;
	}
	QMessageBox::information(NULL, QObject::tr("videoType"), QObject::tr("videoType Error!"));
	return TypeError;
}

int Database::getCorrectParamCcount(QString videoType)
{
	if (videoType == "SingleOne")
	{
		return COLLECT_PARAM_SingleOne_COUNT;
	}
	if (videoType == "SingleTwo")
	{
		return COLLECT_PARAM_SingleTwo_COUNT;
	}
	if (videoType == "SingleThree")
	{
		return COLLECT_PARAM_SingleThree_COUNT;
	}
	if (videoType == "SingleFour")
	{
		return COLLECT_PARAM_SingleFour_COUNT;
	}
	if (videoType == "SingleFive")
	{
		return COLLECT_PARAM_SingleFive_COUNT;
	}
	if (videoType == "SingleSix")
	{
		return COLLECT_PARAM_SingleSix_COUNT;
	}
	if (videoType == "SingleSeven")
	{
		return COLLECT_PARAM_SingleSeven_COUNT;
	}
	if (videoType == "SingleEight")
	{
		return COLLECT_PARAM_SingleEight_COUNT;
	}
	if (videoType == "SingleNine")
	{
		return COLLECT_PARAM_SingleNine_COUNT;
	}
	if (videoType == "SingleGood")
	{
		return COLLECT_PARAM_SingleGood_COUNT;
	}
	if (videoType == "SingleBad")
	{
		return COLLECT_PARAM_SingleBad_COUNT;
	}
	if (videoType == "PairSix")
	{
		return COLLECT_PARAM_PairSix_COUNT;
	}
	if (videoType == "PairSeven")
	{
		return COLLECT_PARAM_PairSeven_COUNT;
	}
	if (videoType == "PairEight")
	{
		return COLLECT_PARAM_PairEight_COUNT;
	}
	if (videoType == "PairNine")
	{
		return COLLECT_PARAM_PairNine_COUNT;
	}
	if (videoType == "PairTen")
	{
		return COLLECT_PARAM_PairTen_COUNT;
	}
	QMessageBox::information(NULL, QObject::tr("videoType"), QObject::tr("videoType Error!"));
	abort();
}