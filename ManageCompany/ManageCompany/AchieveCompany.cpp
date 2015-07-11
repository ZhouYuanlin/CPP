//
//  AchieveCompany.cpp
//  ManageCompany
//
//  Created by 木木同学 on 15/2/14.
//  Copyright (c) 2015年 木木同学. All rights reserved.
//

#include "Header.h"

int CCompanyStaff::s_iCount = 1000;                 //初始化静态数据成员

//实现类CEducation的成员函数GetEdu(),输入信息
void CEducation::GetEdu(void)
{
    cout << endl << "毕业学校：";
    cin  >> m_cShool;
    cout <<endl << "最高学历：（专科 H、本科 B、硕研 M、博研 D）";
    cin  >> m_cDegree;
    
    //用toupper()函数将用户输入的学历规范为大写字符
    m_cDegree = toupper(m_cDegree);
}

//实现类CEducation的成员函数PutEdu(),输出信息
void CEducation::PutEdu()
{
    cout << endl << "毕业学校：" << m_cShool << endl;
    cout << endl << "最高学历：";
    switch (m_cDegree) {
        case 'H':
            cout << "专科" << endl;
            break;
        case 'B':
            cout << "本科" << endl;
            break;
        case 'M':
            cout << "硕研" << endl;
            break;
        case 'D':
            cout << "博研" << endl;
            break;
        default:
            cout << "空" << endl;                   //输入的学历在选项之外
            break;
    }
}

//接收从键盘输入的数据，并赋给相应的数据成员
void CCompanyStaff::InPut(void)
{
    m_iStaffNum = ++s_iCount;                      //静态累加器自加1后赋给工作编号
    cout << "请输入编号为" <<m_iStaffNum << "号员工的名字";
    cin  >> m_cName;
    Edu.GetEdu();
    cout << endl << "基本工资：";
    cin  >> m_fBasicSal;
    cout << endl << "奖金";
    cin  >> m_fPrize;
    cout << endl <<"出勤率";
    cin  >> m_fRateOfAttend;

//规范用户输入的出勤率的值在［0，1］范围内
    if(m_fRateOfAttend > 1.0)
    {
        m_fRateOfAttend = 1.0;
    }
    else if(m_fRateOfAttend < 0)
    {
        m_fRateOfAttend = 0;
    }
}

//输出各数据成员的值
void CCompanyStaff::OutPut(void)
{
    cout << endl << "显示员工" << m_cName << "的基本数据";
    cout << endl << "工作编号：" << m_iStaffNum;
    Edu.PutEdu();
    cout << endl << "基本工资：" << m_fBasicSal;
    cout << endl << "奖金：" << m_fPrize;
    cout << endl << "出勤率：" << m_fRateOfAttend * 100 << "%";
    
}