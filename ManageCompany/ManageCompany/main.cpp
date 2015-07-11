//
//  main.cpp
//  ManageCompany
//
//  Created by 木木同学 on 15/2/14.
//  Copyright (c) 2015年 木木同学. All rights reserved.
//

#include "Header.h"

int main(int argc, const char * argv[]) {
    // insert code here...

    char flag = 'Y';                 //设置判断是否继续录入的标志并初始化为‘Y’
    while (toupper(flag) == 'Y') {
        cout << "请选择录入类别（1.经理 2.销售员 3.销售经理 4.行政人员）";
        int n;
        cin  >> n;
        
        switch (n) {
            case 1:
            {
                CManager staff;      //创建一个经理类对象
                staff.InPut();
                staff.SetMData();
                staff.OutPut();
                staff.CalculateSal();
                break;
            }
            case 2:
            {
                CSaleman staff;      //创建一个销售人员类对象
                staff.InPut();
                staff.SetSData();
                staff.OutPut();
                staff.CalculateSal();
                break;
            }
            case 3:
            {
                CSaleManager staff;  //创建一个销售经理类对象
                staff.InPut();
                staff.SetMData();
                staff.SetSData();
                staff.OutPut();
                staff.CalculateSal();
                break;
            }
            case 4:
            {
                CAdminStaff staff;   //创建一个经理行政人员类对象
                staff.InPut();
                staff.OutPut();
                staff.CalculateSal();
                break;
            }

            default:
                cout << "选择有误！" << endl;
                break;
        }
        cout << endl << "是否继续录入信息？（Y／N）";
        cin  >> flag;
    }
    
}
