//
//  Header.h
//  ManageCompany
//
//  Created by 木木同学 on 15/2/14.
//  Copyright (c) 2015年 木木同学. All rights reserved.
//

#ifndef ManageCompany_Header_h
#define ManageCompany_Header_h

#include <iostream>
#include <string>

using namespace std;

const int LEN = 50;                           //定义一个常量，表示字符数组长度

//教育背景类的声明
class CEducation
{
public:
    CEducation(){};                           //构造函数
    CEducation(char cSchool[], char cDegree)  //重载构造函数
    {
        strcpy(m_cShool, cSchool);
        m_cDegree = cDegree;
    }
    void GetEdu(void);                        //输入教育背景的相关数据
    void PutEdu(void);                        //输出教育背景的相关信息
    
private:
    char *m_cShool;                           //毕业学校
    char m_cDegree;                           //最高学历：专科 H、本科 B、硕研 M、博研 D
};

//定义一个员工类
class CCompanyStaff
{
public:
    CCompanyStaff(void) {};                   //构造函数
    ~CCompanyStaff(void) {};                  //析构函数
    void CalculateSal(void) {};               //计算实发工资
    void OutPut(void);                        //输出员工基本信息的接口
    void InPut(void);                         //输入员工基本信息的接口
    
protected:
    CEducation Edu;                           //内嵌对象（教育背景）
    int m_iStaffNum;                          //工作编号
    char m_cName[20];                         //姓名
    float m_fRateOfAttend;                    //出勤率
    float m_fBasicSal;                        //基本工资
    float m_fPrize;                           //奖金
    static int s_iCount;                      //静态累加器
};

//定义派生类：CAdminStaff（行政人员）
class CAdminStaff : public CCompanyStaff
{
public:
    CAdminStaff() {};                         //构造函数
    ~CAdminStaff() {};                        //析构函数
    
    //计算行政人员的实际发放工资：基本工资 ＋ 奖金 x 当月出勤率
    void CalculateSal(void)
    {
        cout << endl << "当月实发工资："
        << m_fBasicSal + m_fPrize * m_fRateOfAttend << "元" << endl;
    }
};

//定义派生类：CManager（经理）
class CManager : virtual public CCompanyStaff
{
public:
    CManager() {};                            //构造函数
    ~CManager() {};                           //析构函数
    void SetMData(void)
    {
        cout << endl <<"公司总销售额：";
        cin  >> m_fTAmount;
        cout << endl << "提成比例：";
        cin  >> m_fDeductTRate;
    }
    //计算经理的实际发放工资：基本工资 ＋ 总销售额 x 提成比例
    void CalculateSal(void)
    {
        cout << endl << "当月实发工资："
        << m_fBasicSal + m_fTAmount * m_fDeductTRate << "元" << endl;
    }
    
protected:
    float m_fDeductTRate;                     //经理提成比例
    float m_fTAmount;                         //总销售额
};

//定义派生类：CSaleman（销售人员）
class CSaleman : virtual public CCompanyStaff
{
public:
    CSaleman() {};                            //构造函数
    void SetSData(void)                        //设置销售人员数据
    {
        cout << endl <<"个人销售额：";
        cin  >> m_fPersonAmount;
        cout << endl << "提成比例：";
        cin  >> m_fDeductRate;
    }
    
    //计算销售人员的实际发放工资：基本工资 ＋ 个人销售额 x 提成比例
    void CalculateSal(void)
    {
        cout << endl << "当月实发工资："
        << m_fBasicSal + m_fPersonAmount * m_fDeductRate << "元" << endl;
    }
    
protected:
    float m_fDeductRate;                       //销售员提成比例
    float m_fPersonAmount;                     //个人销售额
};

//定义派生类：CSaleManager（销售经理）
class CSaleManager : public CSaleman, public CManager
{
public:
    CSaleManager() {};                         //构造函数
    
    /* 计算销售经理的实际发放工资：
     基本工资 ＋ 个人销售额 x 销售人员提成比例 ＋ 总销售额 x 经理提成比例 */
    void CalculateSal(void)
    {
        cout << endl << "当月实发工资："
        << m_fBasicSal + m_fPersonAmount * m_fDeductRate
        + m_fTAmount * m_fDeductTRate << "元" << endl;
    }
};

#endif