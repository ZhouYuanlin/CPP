//
//  Parser.h
//  C－Minus
//
//  Created by 木木同学 on 15/6/9.
//  Copyright (c) 2015年 木木同学. All rights reserved.
//

#ifndef C_Minus_Parser_h
#define C_Minus_Parser_h

#include "Scanner.h"

using namespace std;

/*
 19中节点类型
 节点类型          描述                   子节点组成
 IntK             变量或返回值类型（int）   无
 IdK              标识符（id)             无
 VoidK            变量或返回值类型（void）  无
 ConstK           数值                   无
 Var_DeclK        变量声明                变量类型＋变量名
 Arry_DeclK       数组声明                数组名＋数组大小
 FunK             函数声明                返回类型＋函数名＋参数列表＋函数体
 ParamsK          函数声明参数列表          参数（如果有多个参数，则之间为兄弟节点）
 ParamK           函数声明参数             参数类型＋参数名
 CompK            复合语句体               变量声明列表＋语句列表
 Selection_StmtK  if                     条件表达式＋IF体＋［ELES体］
 Iteration_StmtK  while                  条件表达式＋循环体
 Return_StmtK     return                ［表达式］
 AssignK          赋值                   被赋值变量＋赋值变量
 OpK              运算                   运算符左值＋运算符右值
 Arry_ElemK       数组元素                数组名＋下标
 CallK            函数调用                函数名＋参数列表
 ArgsK            函数调用参数列表         ［表达式］（如果有多个表达式，则之间为兄弟节点）
 UnkownK          未知节点                 无
 */
typedef enum {IntK, IdK, VoidK, ConstK, Var_DeclK, Arry_DeclK, FunK, ParamsK, ParamK, CompK, Selection_StmtK, Iteration_StmtK, Return_StmtK, AssignK, OpK, Arry_ElemK, CallK, ArgsK, UnkownK} Nodekind;

//
typedef enum {Void,Integer} ExpType;

ofstream fout_Tree("tokenTree.txt");                      //输出语法树到文件

const int MAXCHILDREN = 4;                                //最大子节点个数

//treeNode定义包括子节点、兄弟节点、所处行号、节点类型、属性、表达式返回类型
typedef struct treeNode
{
    struct treeNode * child[MAXCHILDREN];                 //子节点
    struct treeNode * sibling;                            //兄弟节点
    int lineno;                                           //行号
    Nodekind nodekind;                                    //节点类型
    
    //属性
    union
    {
        TokenType op;
        int val;
        const char * name;
    } attr;
    
    ExpType type;                                         //表达式返回值类型
}TreeNode;

class Parser
{
public:
    Parser();
    TreeNode * parse(void);
    TreeNode * syntaxTree;                                //语法树根节点
    
private:
    Scanner scanner;
    Token currentToken;                                   //当前获取的Token
    Token lastToken;                                      //前一个Token
    int tokenIndex;                                       //配合getToken使用，每获取一次，tokenIndex自增
    bool Error;                                           //语法分析是否出错
    int step;                                             //用于节点输出时表征节点的先行空格

    //获取保存在scanner中TokenList数组中的Token，每次获取完之后数组下标指向下一个
    Token getToken();
    //打印n个空格
    void printSpace(int n);
    //报错的函数，报告出错位置（行号）、出错位置附近的Token
    void syntaxError(string s);
    //与目标Token类型ex匹配，如果匹配成功则获取下一个Token（为currentToken赋值），否则报错
    void match(TokenType ex);
    //打印生成的语法树
    void printTree(TreeNode * t);
    
    TreeNode * newNode(Nodekind k);                        //根据节点类型新建节点
    TreeNode * declaration_list(void);
    TreeNode * declaration(void);
    TreeNode * params(void);
    TreeNode * param_list(TreeNode * k);
    TreeNode * param(TreeNode * k);
    TreeNode * compound_stmt(void);
    TreeNode * local_declaration(void);
    TreeNode * statement_list(void);
    TreeNode * statement(void);
    TreeNode * expression_stmt(void);
    TreeNode * selection_stmt(void);
    TreeNode * iteration_stmt(void);
    TreeNode * return_stmt(void);
    TreeNode * expression(void);
    TreeNode * var(void);
    TreeNode * simple_expression(TreeNode * k);
    TreeNode * additive_expression(TreeNode * k);
    TreeNode * term(TreeNode * k);
    TreeNode * factor(TreeNode * k);
    TreeNode * call(TreeNode * k);
    TreeNode * args(void);
};

Parser::Parser()
{
    step = 0;
    tokenIndex = 0;
    Error = false;
    string path = "测试程序.txt";
    scanner.getSourseFile(path);
    scanner.deleteComments();
    if (scanner.scanSuccess) {
        scanner.scan();
        if (scanner.scanSuccess) {
            cout << "Parser starting..." << endl;
            syntaxTree = parse();
            printTree(syntaxTree);
            if (Error)
                cout << "Parser error!" << endl;
            else
                cout << "Parser success!" << endl;
        }
    }
}

Token Parser::getToken()
//获取保存在scanner中TokenList数组中的Token，每次获取完之后数组下标指向下一个
{
    lastToken = currentToken;
    currentToken = scanner.getTokenAt(tokenIndex++);
    return currentToken;
}

void Parser::syntaxError(string s)
{
    fout_Tree << s << "--> Syntax error at line" << lastToken.lineNo << "出错附近Token："
    <<lastToken.tokenString << "Token类型：" << tokenTypeString[lastToken.tokenType] << endl;
    Error = true;
}

void Parser::match(TokenType ex)
{
    if (currentToken.tokenType == ex)
    {
        getToken();
    }
    else
    {
        syntaxError("匹配"+tokenTypeString[ex]+"出错");
    }
}

void Parser::printSpace(int n)
{
    for (int i = 0; i < n; i++) {
        fout_Tree << "      ";
    }
}

void Parser::printTree(TreeNode * t)
{
    int i;
    while (t != NULL)
    {
        printSpace(step);
        switch (t -> nodekind) {
            case VoidK:
                fout_Tree << "VoidK" << endl;
                break;
            case IntK:
                fout_Tree << "IntK" << endl;
                break;
            case IdK:
                fout_Tree << "IdK: " << t -> attr.name << endl;
                break;
            case ConstK:
                fout_Tree << "ConstK: " << t -> attr.val << endl;
                break;
            case Var_DeclK:
                fout_Tree << "Var_DeclK" << endl;
                break;
            case Arry_DeclK:
                fout_Tree << "Arry_DeclK" << endl;
                break;
            case FunK:
                fout_Tree << "FunK" << endl;
                break;
            case ParamsK:
                fout_Tree << "ParamsK" << endl;
                break;
            case ParamK:
                fout_Tree << "ParamK" << endl;
                break;
            case CompK:
                fout_Tree << "CompK" << endl;
                break;
            case Selection_StmtK:
                fout_Tree << "If" << endl;
                break;
            case Iteration_StmtK:
                fout_Tree << "While" << endl;
                break;
            case Return_StmtK:
                fout_Tree << "Return" << endl;
                break;
            case AssignK:
                fout_Tree << "AssignK" << endl;
                break;
            case OpK:
                fout_Tree << "Op: ®";
                fout_Tree << tokenTypeString[t -> attr.op] << endl;
                break;
            case Arry_ElemK:
                fout_Tree << "Arry_ElemK" << endl;
                break;
            case CallK:
                fout_Tree << "CallK" << endl;
                break;
            case ArgsK:
                fout_Tree << "ArgsK" << endl;
                break;
            default:
                fout_Tree << "UnknowK: Unknow exp kind" << endl;
                break;
        }
        
        step++;                                      //进入子节点多输出空格
        for (i = 0; i < MAXCHILDREN; i++) {
            if (t -> child[i] != NULL) {
                printTree(t -> child[i]);
            }
        }
        step--;                                     //进入兄弟节点时，由于进入子节点时n++了，所以要n--回来，从而输出一样的空格
        
        t = t -> sibling;
    }
}

TreeNode * Parser::newNode(Nodekind kind)
{
    TreeNode * p = (TreeNode *)malloc(sizeof(TreeNode));
    int k;
    if (p == NULL)
    {
        cout << "内存分配出错！" << endl;
    }
    else
    {
        for (k = 0; k < MAXCHILDREN; k++) {
            p -> child[k] = NULL;
        }
        p -> sibling = NULL;
        p -> nodekind = kind;
        p -> lineno = currentToken.lineNo;
        if (kind == OpK || kind == IntK || kind == IdK) {
            p -> type = Integer;
        }
        if (kind == IdK) {
            p -> attr.name = "";
        }
        if (kind == ConstK) {
            p -> attr.val = 0;
        }
    }
    return p;
}

TreeNode * Parser :: parse(void)
{
    TreeNode * t;
    currentToken = getToken();
    lastToken = currentToken;
    t = declaration_list();
    if(currentToken.tokenType!=ENDFILE)
    {
        syntaxError("结束错误");
    }
    return t;
}

TreeNode * Parser :: declaration_list()
{
    TreeNode * t = declaration();
    TreeNode * p = t;  //在开始语法分析出错的情况下找到int和void型，过滤掉int和void之前的所有Token，防止在开始时出错后面一错百错
    while((currentToken.tokenType!=INT)&&(currentToken.tokenType!=VOID)
          &&(currentToken.tokenType!=ENDFILE))
    {
        syntaxError("");
        getToken();
        if(currentToken.tokenType==ENDFILE)
            break;
    }
    //寻找语法分析的入口，即找到int和void
    while((currentToken.tokenType==INT)||(currentToken.tokenType==VOID))
    {
        TreeNode * q;
        q = declaration();
        if(q!=NULL)
        {
            if(t==NULL)
            {
                t = p = q;
            }
            else
            {
                p->sibling = q;
                p = q;
            }
        }
    }
    match(ENDFILE);
    return t;
}

TreeNode * Parser :: declaration(void)
{
    TreeNode * t = NULL;
    TreeNode * p = NULL;
    TreeNode * q = NULL;
    TreeNode * s = NULL;
    if(currentToken.tokenType==INT)
    {
        p = newNode(IntK);
        match(INT);
    }
    else if(currentToken.tokenType==VOID)
    {
        p = newNode(VoidK);
        match(VOID);
    }
    else
    {
        syntaxError("类型匹配错误");
    }
    if((p!=NULL)&&(currentToken.tokenType==ID))
    {
        q = newNode(IdK);
        q->attr.name = currentToken.tokenString.c_str();
        match(ID);
        if(currentToken.tokenType==LPAREN)//'('：函数情况
        {
            t = newNode(FunK);
            t->child[0] = p;
            t->child[1] = q;
            match(LPAREN);
            t->child[2] = params();
            match(RPAREN);
            t->child[3] = compound_stmt();
        }
        else if(currentToken.tokenType==LMBRACKET)//'['：数组声明
        {
            t = newNode(Var_DeclK);
            TreeNode * m = newNode(Arry_DeclK);
            match(LMBRACKET);
            match(NUM);
            s = newNode(ConstK);
            s->attr.val = atoi(lastToken.tokenString.c_str());
            m->child[0] = q;
            m->child[1] = s;
            t->child[0] = p;
            t->child[1] = m;
            match(RMBRACKET);
            match(SEMI);
        }
        else if(currentToken.tokenType==SEMI)//';'结尾：普通变量声明
        {
            t = newNode(Var_DeclK);
            t->child[0] = p;
            t->child[1] = q;
            match(SEMI);
        }
        else
        {
            syntaxError("");
        }
    }
    else
    {
        syntaxError("");
    }
    return t;
}

TreeNode * Parser :: params(void)
{
    TreeNode * t = newNode(ParamsK);
    TreeNode * p = NULL;
    if(currentToken.tokenType==VOID)//开头为void，参数列表可能是(void)和(void id,[……])两种情况
    {
        p = newNode(VoidK);
        match(VOID);
        if(currentToken.tokenType==RPAREN)//参数列表为(void)
        {
            if(t!=NULL)
                t->child[0] = p;
        }
        else//参数列表为(void id,[……])  ->void类型的变量
        {
            t->child[0] = param_list(p);
        }
    }
    else if(currentToken.tokenType==INT)//参数列表为(int id,[……])
    {
        t->child[0] = param_list(p);
    }
    else
    {
        syntaxError("");
    }
    return t;
}

TreeNode * Parser :: param_list(TreeNode * k)//k可能是已经被取出来的VoidK，但又不是(void)类型的参数列表，所以一直传到param中去，作为其一个子节点
{
    TreeNode * t = param(k);
    TreeNode * p = t;
    k = NULL;//没有要传给param的VoidK，所以将k设为NULL
    while(currentToken.tokenType==COMMA)
    {
        TreeNode * q = NULL;
        match(COMMA);
        q = param(k);
        if(q!=NULL)
        {
            if(t==NULL)
            {
                t = p = q;
            }
            else
            {
                p->sibling = q;
                p = q;
            }
        }
    }
    return t;
}

TreeNode * Parser :: param(TreeNode * k)
{
    TreeNode * t = newNode(ParamK);
    TreeNode * p = NULL;//ParamK的第一个子节点
    TreeNode * q = NULL;//ParamK的第二个子节点
    if(k==NULL&&currentToken.tokenType==INT)
    {
        p = newNode(IntK);
        match(INT);
    }
    else if(k!=NULL)
    {
        p = k;
    }
    if(p!=NULL)
    {
        t->child[0] = p;
        if(currentToken.tokenType==ID)
        {
            q = newNode(IdK);
            q->attr.name = currentToken.tokenString.c_str();
            t->child[1] = q;
            match(ID);
        }
        else
        {
            syntaxError("");
        }
        if((currentToken.tokenType==LMBRACKET)&&(t->child[1]!=NULL))
        {
            match(LMBRACKET);
            t->child[2] = newNode(IdK);
            match(RMBRACKET);
        }
        else
        {
            return t;
        }
    }
    else
    {
        syntaxError("");
    }
    return t;
}

TreeNode * Parser :: compound_stmt(void)
{
    TreeNode * t = newNode(CompK);
    match(LBBRACKET);
    t->child[0] = local_declaration();
    t->child[1] = statement_list();
    match(RBBRACKET);
    return t;
}

TreeNode * Parser :: local_declaration(void)
{
    TreeNode * t = NULL;
    TreeNode * q = NULL;
    TreeNode * p = NULL;
    while(currentToken.tokenType==INT || currentToken.tokenType==VOID)
    {
        p = newNode(Var_DeclK);
        if(currentToken.tokenType==INT)
        {
            TreeNode * q1 = newNode(IntK);
            p->child[0] = q1;
            match(INT);
        }
        else if(currentToken.tokenType==VOID)
        {
            TreeNode * q1 = newNode(VoidK);
            p->child[0] = q1;
            match(INT);
        }
        if((p!=NULL)&&(currentToken.tokenType==ID))
        {
            TreeNode * q2 = newNode(IdK);
            q2->attr.name = currentToken.tokenString.c_str();
            p->child[1] = q2;
            match(ID);
            if(currentToken.tokenType==LMBRACKET)
            {
                TreeNode * q3 = newNode(Var_DeclK);
                p->child[3] = q3;
                match(LMBRACKET);
                match(RMBRACKET);
                match(SEMI);
            }
            else if(currentToken.tokenType==SEMI)
            {
                match(SEMI);
            }
            else
            {
                match(SEMI);
            }
        }
        else
        {
            syntaxError("");
        }
        if(p!=NULL)
        {
            if(t==NULL)
                t = q = p;
            else
            {
                q->sibling = p;
                q = p;
            }
        }
    }
    return t;
}

TreeNode * Parser :: statement_list(void)
{
    TreeNode * t = statement();
    TreeNode * p = t;
    while (IF==currentToken.tokenType || LBBRACKET==currentToken.tokenType || ID==currentToken.tokenType || WHILE==currentToken.tokenType || RETURN ==currentToken.tokenType || SEMI==currentToken.tokenType || LPAREN==currentToken.tokenType || NUM==currentToken.tokenType)
    {
        TreeNode * q;
        q = statement();
        if(q!=NULL)
        {
            if(t==NULL)
            {
                t = p = q;
            }
            else
            {
                p->sibling = q;
                p = q;
            }
        }
    }
    return t;
}

TreeNode * Parser :: statement(void)
{
    TreeNode * t = NULL;
    switch(currentToken.tokenType)
    {
        case IF:
            t = selection_stmt();
            break;
        case WHILE:
            t = iteration_stmt();
            break;
        case RETURN:
            t = return_stmt();
            break;
        case LBBRACKET:
            t = compound_stmt();
            break;
        case ID: case SEMI: case LPAREN: case NUM:
            t = expression_stmt();
            break;
        default:
            syntaxError("");
            currentToken = getToken();
            break;
    }
    return t;
}

TreeNode * Parser :: selection_stmt(void)
{
    TreeNode * t = newNode(Selection_StmtK);
    match(IF);
    match(LPAREN);
    if(t!=NULL)
    {
        t->child[0] = expression();
    }
    match(RPAREN);
    t->child[1] = statement();
    if(currentToken.tokenType==ELSE)
    {
        match(ELSE);
        if(t!=NULL)
        {
            t->child[2] = statement();
        }
    }
    return t;
}

TreeNode * Parser :: expression_stmt(void)
{
    TreeNode * t = NULL;
    if(currentToken.tokenType==SEMI)
    {
        match(SEMI);
        return t;
    }
    else
    {
        t = expression();
        match(SEMI);
    }
    return t;
}

TreeNode * Parser :: iteration_stmt(void)
{
    TreeNode * t = newNode(Iteration_StmtK);
    match(WHILE);
    match(LPAREN);
    if(t!=NULL)
    {
        t->child[0] = expression();
    }
    match(RPAREN);
    if(t!=NULL)
    {
        t->child[1] = statement();
    }
    return t;
}

TreeNode * Parser :: return_stmt(void)
{
    TreeNode * t = newNode(Return_StmtK);
    match(RETURN);
    if (currentToken.tokenType==SEMI)
    {
        match(SEMI);
        return t;
    }
    else
    {
        if(t!=NULL)
        {
            t->child[0] = expression();
        }
    }
    match(SEMI);
    return t;
}

TreeNode * Parser :: expression(void)
{
    TreeNode * t = var();
    if(t==NULL)//不是以ID开头，只能是simple_expression情况
    {
        t = simple_expression(t);
    }
    else//以ID开头，可能是赋值语句，或simple_expression中的var和call类型的情况
    {
        TreeNode * p = NULL;
        if(currentToken.tokenType==ASSIGN)//赋值语句
        {
            p = newNode(AssignK);
            p->attr.name = lastToken.tokenString.c_str();
            match(ASSIGN);
            p->child[0] = t;
            p->child[1] = expression();
            return p;
        }
        else //simple_expression中的var和call类型的情况
        {
            t = simple_expression(t);
        }
    }
    return t;
}

TreeNode * Parser :: simple_expression(TreeNode * k)
{
    TreeNode * t = additive_expression(k);
    k = NULL;
    if(EQ==currentToken.tokenType || GT==currentToken.tokenType ||  GEQ==currentToken.tokenType
       || LT==currentToken.tokenType || LEQ==currentToken.tokenType || NEQ==currentToken.tokenType)
    {
        TreeNode * q = newNode(OpK);
        q->attr.op = currentToken.tokenType;
        q->child[0] = t;
        t = q;
        match(currentToken.tokenType);
        t->child[1] = additive_expression(k);
        return t;
    }
    return t;
}

TreeNode * Parser :: additive_expression(TreeNode * k)
{
    TreeNode * t = term(k);
    k = NULL;
    
    while((currentToken.tokenType==PLUS)||(currentToken.tokenType==MINUS))
    {
        TreeNode * q = newNode(OpK);
        q->attr.op = currentToken.tokenType;
        q->child[0] = t;
        match(currentToken.tokenType);
        q->child[1] = term(k);
        t = q;
    }
    return t;
}

TreeNode * Parser :: term(TreeNode * k)
{
    TreeNode * t = factor(k);
    k = NULL;
    
    while((currentToken.tokenType==TIMES)||(currentToken.tokenType==OVER))
    {
        TreeNode * q = newNode(OpK);
        q->attr.op = currentToken.tokenType;
        q->child[0] = t;
        t = q;
        match(currentToken.tokenType);
        q->child[1] = factor(k);
    }
    return t;
}

TreeNode * Parser :: factor(TreeNode * k)
{
    TreeNode * t = NULL;
    if(k!=NULL)//k为上面传下来的已经解析出来的以ID开头的var,可能为call或var
    {
        if(currentToken.tokenType==LPAREN && k->nodekind!=Arry_ElemK) //call
        {
            t = call(k);
        }
        else
        {
            t = k;
        }
    }
    else//没有从上面传下来的var
    {
        switch(currentToken.tokenType)
        {
            case LPAREN:
                match(LPAREN);
                t = expression();
                match(RPAREN);
                break;
            case ID:
                k = var();
                if(LPAREN==currentToken.tokenType && k->nodekind!=Arry_ElemK)
                {
                    t = call(k);
                }
                break;
            case NUM:
                t = newNode(ConstK);
                if((t!=NULL)&&(currentToken.tokenType==NUM))
                {
                    t->attr.val = atoi(currentToken.tokenString.c_str());
                }
                match(NUM);
                break;
            default:
                syntaxError("");
                currentToken = getToken();
                break;
        }
    }
    return t;
}

TreeNode * Parser :: var(void)
{
    TreeNode * t = NULL;
    TreeNode * p = NULL;
    TreeNode * q = NULL;
    if(currentToken.tokenType==ID)
    {
        p = newNode(IdK);
        p->attr.name = currentToken.tokenString.c_str();
        match(ID);
        if(currentToken.tokenType==LMBRACKET)
        {
            match(LMBRACKET);
            q = expression();
            match(RMBRACKET);
            t = newNode(Arry_ElemK);
            t->child[0] = p;
            t->child[1] = q;
        }
        else
        {
            t = p;
        }
    }
    return t;
}

TreeNode * Parser :: call(TreeNode * k)
{
    TreeNode * t = newNode(CallK);
    
    if(k!=NULL)
        t->child[0] = k;
    
    match(LPAREN);
    
    if(currentToken.tokenType==RPAREN)
    {
        match(RPAREN);
        return t;
    }
    else if(k!=NULL)
    {
        t->child[1] = args();
        match(RPAREN);
    }
    return t;
}

TreeNode * Parser :: args(void)
{
    TreeNode * t = newNode(ArgsK);
    TreeNode * s = NULL;
    TreeNode * p = NULL;
    if(currentToken.tokenType!=RPAREN)
    {
        s = expression();
        p = s;
        while(currentToken.tokenType==COMMA)
        {
            TreeNode * q;
            
            match(COMMA);
            q = expression();
            if(q!=NULL)
            {
                if(s==NULL)
                {
                    s = p = q;
                }
                else
                {
                    p->sibling = q;
                    p = q;
                }
            }
        }
    }
    
    if(s!=NULL)
    {
        t->child[0] = s;
    }
    return t;
}

#endif
