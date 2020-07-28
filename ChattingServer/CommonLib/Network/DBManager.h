#pragma once

#include "../framework.h"

class DBManager : public Singleton<DBManager>
{
private:
	std::recursive_mutex m_rm;

private:
	bool isConnect() { return isconnect; }
	bool CheckQueryErr(const char* query);
public:
	int InitDBManager(std::string dbName);
	void CloseDBManager();
	int ProcessQuery(const char* query, ...);
	std::string GetQuery(const char* query, ...);
	MYSQL_ROW GetsqlRow()const { return sql_row; }
	MYSQL_RES* GetsqlRes()const;
	MYSQL* GetConn()const { return connection; }
private:
	MYSQL* connection;
	MYSQL conn;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;
	bool isconnect;
public:
	~DBManager();
public:
	DBManager() {}
};