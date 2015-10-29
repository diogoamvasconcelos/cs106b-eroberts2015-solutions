/*
 * File: Basic.cpp
 * ---------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the BASIC interpreter from
 * Assignment #6.
 * [TODO: extend and correct the documentation]
 */

#include <cctype>
#include <iostream>
#include <string>
#include "console.h"
#include "exp.h"
#include "parser.h"
#include "program.h"
#include "tokenscanner.h"
#include "simpio.h"
#include "strlib.h"
using namespace std;

/* Function prototypes */

void processLine(string line, Program & program, EvalState & state);
Statement *createStatement(string initial_token, TokenScanner & scanner);
void runProgram(Program & program, EvalState & state);

/* Main program */

int main() {
   EvalState state;
   Program program;
   cout << "Stub implementation of BASIC" << endl;
   while (true) {
      try {
           string line = getLine();
           if (line != "QUIT")
           {
               processLine(line, program, state);
           }
           else
           {
               break;
           }
      } catch (ErrorException & ex) {
         cerr << "Error: " << ex.getMessage() << endl;
      }
   }
   return 0;
}

/*
 * Function: processLine
 * Usage: processLine(line, program, state);
 * -----------------------------------------
 * Processes a single line entered by the user.  In this version,
 * the implementation does exactly what the interpreter program
 * does in Chapter 19: read a line, parse it as an expression,
 * and then print the result.  In your implementation, you will
 * need to replace this method with one that can respond correctly
 * when the user enters a program line (which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 *
 * prev:
    TokenScanner scanner;
   scanner.ignoreWhitespace();
   scanner.scanNumbers();
   scanner.setInput(line);
   Expression *exp = parseExp(scanner);
   int value = exp->eval(state);
   cout << value << endl;
   delete exp;
 */

void processLine(string line, Program & program, EvalState & state)
{
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(line);

    string token = scanner.nextToken();
    TokenType type = scanner.getTokenType(token);
    if (type == NUMBER)
    {
        if (scanner.hasMoreTokens())
        {
            int line_number = stringToInteger(token);
            program.addSourceLine(line_number, line);
            program.setParsedStatement(line_number, createStatement(scanner.nextToken(), scanner));
        }
        else
        {
            program.removeSourceLine(stringToInteger(token));
        }
    }
    else if (type == WORD)
    {
        if (token == "HELP")
        {
            //TODO
            cout << "Control commands" << endl;
            cout << "HELP: displays help" << endl;
            cout << "LIST: lists the program statements source lines" << endl;
            cout << "RUN: runs the program" << endl;
            cout << "QUIT: terminates application" << endl;
            cout << "Statements" << endl;
            cout << "REM: comment" << endl;
            cout << "LET: assignemnt " << endl;
            cout << "PRINT: print" << endl;
            cout << "INPUT: asks the user for an input" << endl;
            cout << "GOTO: go to a specific line" << endl;
            cout << "IF: if condition then go to line" << endl;
            cout << "END: terminates program execution" << endl;
        }
        else if (token == "LIST")
        {
            int line_number = program.getFirstLineNumber();

            while(line_number != -1)
            {
                cout << program.getSourceLine(line_number) << endl;
                line_number = program.getNextLineNumber(line_number);
            }
        }
        else if (token == "CLEAR")
        {
            program.clear();
        }
        else if (token == "RUN")
        {
            runProgram(program, state);
        }
        else
        {
            Statement *statement = createStatement(token, scanner);

            if(statement != NULL)
            {
                statement->execute(state);
            }
            else
            {
                error ("Statement not valid");
            }
        }
    }
}

Statement *createStatement(string initial_token, TokenScanner &scanner)
{
    Statement *statement = NULL;

    if (initial_token == "REM")
    {
        statement = new RemStmt();
    }
    else if (initial_token == "LET")
    {
        statement = new LetStmt(scanner);
    }
    else if (initial_token == "PRINT")
    {
        statement = new PrintStmt(scanner);
    }
    else if (initial_token == "INPUT")
    {
        statement = new InputStmt(scanner);
    }
    else if (initial_token == "GOTO")
    {
        statement = new GotoStmt(scanner);
    }
    else if (initial_token == "IF")
    {
        statement = new IfStmt(scanner);
    }
    else if (initial_token == "END")
    {
        statement = new EndStmt(scanner);
    }

    return statement;
}

void runProgram(Program & program, EvalState & state)
{
    state.setCurrentLine(program.getFirstLineNumber());
    Statement *currentStatement;
    while(state.getCurrentLine() != -1)
    {
        currentStatement = program.getParsedStatement(state.getCurrentLine());
        state.setCurrentLine(program.getNextLineNumber(state.getCurrentLine()));
        currentStatement->execute(state);
    }
}
