/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include <string>
#include "statement.h"
#include "parser.h"
#include "strlib.h"
using namespace std;

/* Implementation of the Statement class */

Statement::Statement() {
   /* Empty */
}

Statement::~Statement() {
   /* Empty */
}

/* Implementation of the RemStmt class */
RemStmt::RemStmt()
{ }

RemStmt::~RemStmt()
{ }

void RemStmt::execute(EvalState & context)
{ }

/* Implementation of the LetStmt class */
LetStmt::LetStmt(TokenScanner & scanner)
{
    string token = scanner.nextToken();
    if(scanner.getTokenType(token) != WORD)
    {
        error("Variable name \"" + token + "\" is not valid");
    }
    var = token;

    token = scanner.nextToken();
    if(token != "=")
    {
        error("Expecting a \"=\", got " + token);
    }

    exp = readE(scanner, 0);
    if (scanner.hasMoreTokens())
    {
        error("Extraneous token " + scanner.nextToken());
    }
}

LetStmt::~LetStmt()
{
    delete exp;
}

void LetStmt::execute(EvalState & context)
{
    context.setValue(var, exp->eval(context));
}

/* Implementation of the PrintStmt class */
PrintStmt::PrintStmt(TokenScanner & scanner)
{
    exp = readE(scanner, 0);
    if (scanner.hasMoreTokens())
    {
        error("Extraneous token " + scanner.nextToken());
    }
}

PrintStmt::~PrintStmt()
{
    delete exp;
}

void PrintStmt::execute(EvalState & context)
{
    cout << exp->eval(context) << endl;
}

/* Implementation of the InputStmt class */
InputStmt::InputStmt(TokenScanner & scanner)
{
    string token = scanner.nextToken();
    if(scanner.getTokenType(token) != WORD)
    {
        error("Variable name \"" + token + "\" is not valid");
    }
    var = token;

    if (scanner.hasMoreTokens())
    {
        error("Extraneous token " + scanner.nextToken());
    }
}

InputStmt::~InputStmt()
{ }

void InputStmt::execute(EvalState & context)
{
    int value;
    cout << "?";
    cin >> value;

    context.setValue(var, value);
}

/* Implementation of the GotoStmt class */
GotoStmt::GotoStmt(TokenScanner & scanner)
{
    string token = scanner.nextToken();
    if(scanner.getTokenType(token) != NUMBER)
    {
        error("Line number \"" + token + "\" is not valid");
    }
    line_number = stringToInteger(token);

    if (scanner.hasMoreTokens())
    {
        error("Extraneous token " + scanner.nextToken());
    }
}

GotoStmt::~GotoStmt()
{ }

void GotoStmt::execute(EvalState & context)
{
    context.setCurrentLine(line_number);
}

/* Implementation of the IfStmt class */
IfStmt::IfStmt(TokenScanner & scanner)
{
    exp1 = readE(scanner, 0);

    string token = scanner.nextToken();
    if(scanner.getTokenType(token) != OPERATOR  ||
            (token != ">" && token != "<" && token != "="))
    {
        error("\"" +  token + "\" is not a valid operator");
    }
    op = token;

    exp2 = readE(scanner, 0);


    token = scanner.nextToken();
    if (token != "THEN")
    {
        error("Expecting \"THEN\", got \"" +  token + "\"");
    }

    token = scanner.nextToken();
    if(scanner.getTokenType(token) != NUMBER)
    {
        error("Line number \"" + token + "\" is not valid");
    }
    line_number = stringToInteger(token);

    if (scanner.hasMoreTokens())
    {
        error("Extraneous token " + scanner.nextToken());
    }
}

IfStmt::~IfStmt()
{ }

void IfStmt::execute(EvalState & context)
{
    int value1 = exp1->eval(context);
    int value2 = exp2->eval(context);
    bool condition_true = false;

    if (op == ">")
        condition_true = value1 > value2;
    else if (op == "<")
        condition_true = value1 < value2;
    else if (op == "=")
        condition_true = value1 == value2;

    if(condition_true)
        context.setCurrentLine(line_number);
}

/* Implementation of the EndStmt class */
EndStmt::EndStmt(TokenScanner & scanner)
{ }

EndStmt::~EndStmt()
{ }

void EndStmt::execute(EvalState & context)
{
    context.setCurrentLine(-1);
}
