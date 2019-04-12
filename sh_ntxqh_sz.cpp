#include "sh_ntxqh.h"
#include"dictionary.h"
#include<QDateTime>
#include<QFile>
#include<QTextStream>
#include <QCoreApplication>
#include<QDir>
//获取业务号
int GetServiceTypeID()
{
	return 8;
}

//获取业务名称
QString GetServiceTypeName()
{
	QString name = QString::fromLocal8Bit("湿地农田小气候水质业务");
	return name;
}
//获取端口号
int GetPort()
{
	return 23001;
}

//获取版本号
QString GetVersionNo()
{
	QString Version = QString::fromLocal8Bit("1.0");
	return Version;
}

//解析数据
LRESULT Char2Json(QString &buff, QJsonObject &json)
{
	int Count = 0;//数据个数
	int Current_P = buff.length();//当前数据指

								  //遍历查找数据
	try
	{
		for (int i = 0; i < buff.length() - 2; i++)
		{
			if (buff[i].toUpper() == 'B' && buff[i + 1].toUpper() == 'G'&&buff[i + 2] == ',')
			{
				Current_P = i;//指针指向帧头
				for (int j = i + 2; j < buff.length() - 2; j++)
				{
					if (buff[j] == ','&&buff[j + 1].toUpper() == 'E'&&buff[j + 2].toUpper() == 'D')
					{
						Current_P = j + 3;//指针移动到帧尾下一个字符

						Dictionary dic;
						QString strBuff = buff.mid(i, j - i + 3);
						QStringList strlist = strBuff.split(",");
						QJsonObject SubJson;
						//数据类型 观测数据
						SubJson.insert("DataType", 1);
						 //区站号
						SubJson.insert("StationID", strlist.at(1));
						//业务员类型 08农田小气候
						SubJson.insert("ServiceTypeID", SH_NTXQH_SZ);
						//数据存储类型
						SubJson.insert("DataSourceID", 11);
						//设备号
						SubJson.insert("DeviceID", strlist.at(2));
						//时间
						QString time = Convert2Time(strlist.at(3));
						SubJson.insert("ObserveTime", time);
						//观察要素个数
						int CountOfFeature = strlist.at(4).toInt();
						SubJson.insert("CountOfFeature", CountOfFeature);
						int CountOfFacilitiesStatus = strlist.at(5).toInt();
						SubJson.insert("CountOfFacilitiesStatus", CountOfFacilitiesStatus);
						//判断数据完整性
						if (strlist.count() < CountOfFeature * 2 + CountOfFacilitiesStatus * 2 + 7)
						{
							i = j + 2;//当前循环
							continue;
						}
						//数据个数
						Count += 1;
						 //观察要素
						QString strFeatureName;
						for (int i = 6; i < CountOfFeature * 2 + 6; i += 2)
						{
							QString SrcKey = QString(strlist.at(i)).toLower();
							QString key = dic.Find(SrcKey);
							if (key != NULL)
							{
								//需要处理的数据 除以10
								if (SrcKey == "afc" || SrcKey == "afd" || SrcKey == "afda" || SrcKey == "afa" || SrcKey == "afaa" || SrcKey == "afae" || SrcKey == "aaa" || SrcKey == "aaaa" || SrcKey == "aaac" || SrcKey == "ada" || SrcKey == "adac" || SrcKey == "adc" || SrcKey == "adb" ||
									SrcKey == "aaa1" || SrcKey == "aaa1a" || SrcKey == "aaa1c" || SrcKey == "ada1" || SrcKey == "ada1c" || SrcKey == "adc1" || SrcKey == "adb1" || SrcKey == "aaa2" || SrcKey == "aaa2a" || SrcKey == "aaa2c" || SrcKey == "ada2" || SrcKey == "ada2c" ||
									SrcKey == "adc2" || SrcKey == "adb2" || SrcKey == "aaa3" || SrcKey == "aaa3a" || SrcKey == "aaa3c" || SrcKey == "ada3" || SrcKey == "ada3c" || SrcKey == "adc3" || SrcKey == "adb3" || SrcKey == "aaa4" || SrcKey == "aaa4a" || SrcKey == "aaa4c" ||
									SrcKey == "ada4" || SrcKey == "ada4c" || SrcKey == "adc4" || SrcKey == "adb4" || SrcKey == "ab5" || SrcKey == "ab5a" || SrcKey == "ab5c" || SrcKey == "ab10" || SrcKey == "ab10a" || SrcKey == "ab10c" || SrcKey == "ab15" || SrcKey == "ab15a" ||
									SrcKey == "ab15c" || SrcKey == "ab20" || SrcKey == "ab20a" || SrcKey == "ab20c" || SrcKey == "ab30" || SrcKey == "ab30a" || SrcKey == "ab30c" || SrcKey == "ab40" || SrcKey == "ab40a" || SrcKey == "ab40c" || SrcKey == "ab50" || SrcKey == "ab50a" || SrcKey == "ab50c" || SrcKey == "ab80" || SrcKey == "ab80a" || SrcKey == "ab80c" || SrcKey == "ab160" || SrcKey == "ab160a" ||
									SrcKey == "ab160c" || SrcKey == "ab320" || SrcKey == "ab320a" || SrcKey == "ab320c" || SrcKey == "ab480" || SrcKey == "ab480a" || SrcKey == "ab480c" || SrcKey == "ab640" || SrcKey == "ab640a" || SrcKey == "ab640c" || SrcKey == "aba" || SrcKey == "abaa" ||
									SrcKey == "abac" || SrcKey == "abb" || SrcKey == "abba" || SrcKey == "abbc" || SrcKey == "abc" || SrcKey == "abca" || SrcKey == "abcc" || SrcKey == "abd" || SrcKey == "abda" || SrcKey == "abdc" || SrcKey == "abe" || SrcKey == "abea" || SrcKey == "abec" ||
									SrcKey == "arb10" || SrcKey == "arg10" || SrcKey == "arb20" || SrcKey == "arg20" || SrcKey == "arb30" || SrcKey == "arg30" || SrcKey == "arb40" || SrcKey == "arg40" || SrcKey == "arb50" || SrcKey == "arg50" || SrcKey == "arb60" || SrcKey == "arg60" ||
									SrcKey == "arb80" || SrcKey == "arg80" || SrcKey == "arb100" || SrcKey == "arg100" || SrcKey == "aha" || SrcKey == "ahb" || SrcKey == "aab" || SrcKey == "aaba" || SrcKey == "aabc" || SrcKey == "aia")
								{
									float f = strlist.at(i + 1).toFloat();
									f /= 10;
									SubJson.insert(key, f);
								}
								//除以100
								else if (SrcKey == "ajia")
								{
									float f = strlist.at(i + 1).toFloat();
									f /= 100;
									SubJson.insert(key, f);
								}
								//除以1000
								else if (SrcKey == "ajaa")
								{
									float f = strlist.at(i + 1).toFloat();
									f /= 1000;
									SubJson.insert(key, f);
								}
								else
								{
									SubJson.insert(key, strlist.at(i + 1));
								}
								//质量控制码
								if (i == 8)
								{
									strFeatureName = key;
								}
								else
								{
									strFeatureName += ",";
									strFeatureName += key;
								}
							}

						}
						SubJson.insert("StatusBitName", strFeatureName);
						//状态位
						SubJson.insert("StatusBit", strlist.at(CountOfFeature * 2 + 6));

						//设备状态

						for (int i = CountOfFeature * 2 + 7; i < CountOfFeature * 2 + CountOfFacilitiesStatus * 2 + 7; i += 2)
						{
							QString SrcKey = QString(strlist.at(i)).toLower();
							QString key = dic.Find(SrcKey);
							if (key != NULL)
							{
								SubJson.insert(key, strlist.at(i + 1));
							}
						}
						//备份数据
						QDateTime current_date_time = QDateTime::currentDateTime();
						QString current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss");
						QString current_day = current_date_time.toString("yyyy-MM-dd");
						QString fileName = QCoreApplication::applicationDirPath() + "\\SH\\NTXQH_SZ\\" + strlist.at(1) + "\\" + current_day;
						QDir dir(fileName);
						if (!dir.exists())
							dir.mkpath(fileName);//创建多级目录
						fileName += "\\data.txt";
						QFile file(fileName);

						if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
						{
						}
						QTextStream in(&file);
						in << current_date << "\r\n" << strBuff << "\r\n";
						file.close();
						json.insert(QString::number(Count), SubJson);
						i = j + 2;//当前循环
						break;
					}
				}
			}
			else if (buff[i] == '<')
			{
				Current_P = i;//指针指向帧头
				for (int j = i + 1; j < buff.length(); j++)
				{
					if (buff[j] == '>')
					{
						Current_P = j + 1;//指针移动到帧尾
						Count += 1;//数据个数
						QString subStr = buff.mid(i + 1, j - i - 1);
						QStringList strlist = subStr.split(",");
						QJsonObject SubJson;
					
						i = j;
						switch (strlist.count())
						{
						case 5://返回值
						{
							SubJson.insert("DataType", 2);//数据类型 2操作数据
							SubJson.insert("ValueCount", 5);
							SubJson.insert("ServiceTypeID", strlist.at(0));
							SubJson.insert("StationID", strlist.at(1));
							SubJson.insert("DeviceID", strlist.at(2));
							SubJson.insert("Command", strlist.at(3));
							SubJson.insert("RecvValue1", strlist.at(4));
							json.insert(QString::number(Count), SubJson);
							break;
						}
						case 3://心跳
						{
							SubJson.insert("DataType", 3);//数据类型3 心跳
							SubJson.insert("ServiceTypeID", SH_NTXQH_SZ);
							SubJson.insert("StationID", strlist.at(1));
							SubJson.insert("DeviceID", strlist.at(2));
							json.insert(QString::number(Count), SubJson);
						}
						//无效数据
						default:
							break;
						}
						break;
					}
				}
			}
		}
		json.insert("DataLength", Count);//JSON数据个数
	}
	catch (const std::exception& ex)
	{

	}

	if (Current_P >= buff.length())//判断当前指针位置
	{
		buff.clear();
	}//清除内存
	else
	{
		buff.remove(0, Current_P);
	}//将剩余字节存入缓存
	return 1;
}

//字符串转成显示时间格式
QString Convert2Time(QString strTime)
{
	QString tmp;
	tmp = strTime.mid(0, 4) + "-" + strTime.mid(4, 2) + "-" + strTime.mid(6, 2) + " " + strTime.mid(8, 2) + ":" + strTime.mid(10, 2) + ":" + strTime.mid(12, 2);
	return tmp;
}

//调试窗体
void  GetControlWidget(QString StationID, uint Socket, QWidget* parent)
{
	if (isActive)
	{
		return;
	}
	control_ui = new ControlUI();
	isActive = true;
	control_ui->Socket = Socket;
	control_ui->isActive = &isActive;
	control_ui->show();
}
//矫正时钟
void SetTime(QString StationID, uint Socket)
{
	QDateTime nowtime = QDateTime::currentDateTime();
	QString datetime = nowtime.toString("yyyy-MM-dd hh:mm:ss");
	//设置时钟
	QString Comm = "DATETIME " + datetime + "\r\n";
	QByteArray ba = Comm.toLatin1();
	LPCSTR ch = ba.data();
	int len = Comm.length();
	::send(Socket, ch, len, 0);
}
//返回值反馈
void SetValueToControlWidget(QStringList list)
{
	if (control_ui == nullptr)
		return;
	if (isActive)
		control_ui->setValue(list);
}
//发送命令
void SetCommand(uint Socket, int CommandType, QString Params1, QString Params2, QString StationID)
{
	//设备终端命令
	QString Comm;
	int len = Comm.length();
	switch (CommandType)
	{
	case 1101:
		//读取ID
		Comm = "ID\r\n";
		break;
	case 1102:
		//设置ID
		Comm = "ID " + Params1 + "\r\n";
		break;
	case 1103:
		//读取时钟
		Comm = "DATETIME\r\n";
		break;
	case 1104:
	{
		//设置时钟
		QDateTime nowtime = QDateTime::currentDateTime();
		QString datetime = nowtime.toString("yyyy-MM-dd hh:mm:ss");
		Comm = Comm = "DATETIME " + datetime + "\r\n";
	}
	break;
	case 1105:
		//读取高度
		 Comm = "ALT\r\n";
		break;
	case 1106:
		
		//设置高度
		 Comm = "ALT " + Params1 + "\r\n";
		break;
	case 1107:
		//读取纬度
		 Comm = "LAT\r\n";
		break;
	case 1108:
		//设置纬度
		 Comm = "LAT " + Params1 + "\r\n";
		break;
	case 1109:
		//读取经度
		 Comm = "LONG\r\n";
		break;
	case 1110:
		//设置经度
		 Comm = "LONG " + Params1 + "\r\n";
		break;
	case 1111:
		//重启采集器
		 Comm = "RESET\r\n";
		break;
	case 1112:
		//远程升级
		 Comm = "UPDATE\r\n";
		break;
	case 1113:
	{
		//补抄
		QString Comm = "DMTD " + Params1 + " 1\r\n";
	}
	break;
	default:
		break;
	}
	QByteArray ba = Comm.toLatin1();
	LPCSTR ch = ba.data();
	::send(Socket, ch, len, 0);
}


