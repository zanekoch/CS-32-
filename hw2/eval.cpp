using namespace std;
#include <iostream>
#include <string>
#include <assert.h>
#include <stack>


/*operator precedence (decreasing): !, &, |. operators of equal precedence evaluate left to right*/
string removeSpaces(string infix);
bool isValid(string infix);
string convertToPost(string infix, string& postfix);
int evaluate(string infix, string& postfix, bool& result);

int evaluate(string infix, string& postfix, bool& result)
{
	if (!isValid(infix)) //check valid input
		return 1;
	postfix = "";
	convertToPost(infix, postfix);//postfix is now correct


	stack<bool> tAndF; //operand stack is empty

	for (size_t i = 0; i < postfix.length(); i++)
	{
		if (postfix[i] == 'T')
		{
			tAndF.push(true);
		}
		else if (postfix[i] == 'F')
			tAndF.push(false);
		else if (postfix[i] == '!')
		{//push back opposite of top
			bool topp = tAndF.top();
			tAndF.pop();
			tAndF.push(!topp);
		}
		else
		{
			bool operand2 = tAndF.top();
			tAndF.pop();
			if (tAndF.empty())
				return 1;
			bool operand1 = tAndF.top();
			tAndF.pop();
			if (postfix[i] == '&')
			{
				if (operand1 && operand2)
					tAndF.push(true);
				else
					tAndF.push(false);
			}
			if (postfix[i] == '|')
			{
				if (operand1 || operand2)
					tAndF.push(true);
				else
					tAndF.push(false);
			}
		}
	}
	result = tAndF.top();
	return 0;
}


/////////////////////////////////////////////////////////

int main()
{
	string pf;
	bool answer;
	assert(evaluate("T| F", pf, answer) == 0 && pf == "TF|"  &&  answer);
	assert(evaluate("T|", pf, answer) == 1);
	assert(evaluate("F F", pf, answer) == 1);
	assert(evaluate("TF", pf, answer) == 1);
	assert(evaluate("()", pf, answer) == 1);
	assert(evaluate("T(F|T)", pf, answer) == 1);
	assert(evaluate("T(&T)", pf, answer) == 1);
	assert(evaluate("(T&(F|F)", pf, answer) == 1);
	assert(evaluate("", pf, answer) == 1);
	
	assert((evaluate("F|!F&(T&F)", pf, answer) == 0));  //&& pf == "FF!TF&&|" && !answer);
	
	assert(evaluate(" F  ", pf, answer) == 0 && pf == "F" && !answer);
	assert(evaluate("((T))", pf, answer) == 0 && pf == "T"  &&  answer);
}

/////////////////////////////////////////////////////////


string removeSpaces(string infix)
{
	string nospaces = "";
	for (size_t i = 0; i < infix.size(); i++)
	{
		if (infix[i] != ' ')
		{
			nospaces += infix[i];
		}

	}
	return nospaces;
}

bool isValid(string infix)
{
	string spaceLessInfix = removeSpaces(infix);  

	if (spaceLessInfix == "")
		return false;

	int openparen = 0;
	int endparen = 0;

	for (size_t i = 0; i < spaceLessInfix.size(); i++) 
	{
		if (infix[i] == '(')
			openparen++;
		if (infix[i] == ')')
			endparen++;
		if (i >= 1)
		{
			if (spaceLessInfix[i] == ')')
			{
				if (spaceLessInfix[i - 1] == '(')
					return false;
			}
			if (spaceLessInfix[i] == 'T' || spaceLessInfix[i] == 'F')
			{
				if (spaceLessInfix[i - 1] == 'T' || spaceLessInfix[i - 1] == 'F')
					return false;
				if (spaceLessInfix[i - 1] == ')')
					return false;
			}
			if (spaceLessInfix[i] == '|' || spaceLessInfix[i] == '&')
			{
				if (spaceLessInfix[i - 1] != 'T' && spaceLessInfix[i - 1] != 'F' && spaceLessInfix[i - 1] != ')')
					return false;
			}
		}
		if (spaceLessInfix[i] == '|' || spaceLessInfix[i] == '&')
		{
			if (spaceLessInfix[i + 1] != 'T' && spaceLessInfix[i + 1] != 'F' && spaceLessInfix[i + 1] != '(' && spaceLessInfix[i + 1] != '!')
				return false;
		}
		if (spaceLessInfix[i] == 'T' || spaceLessInfix[i] == 'F')
		{
			if (spaceLessInfix[i + 1] == 'T' || spaceLessInfix[i + 1] == 'F')
				return false;
			if (spaceLessInfix[i + 1] == '(')
				return false;
		}
		if (spaceLessInfix[i] == '(')
		{
			if (spaceLessInfix[i + 1] == ')')
				return false;
		}
	}
	if (endparen != openparen)
		return false;
	return true;
}

string convertToPost(string infix, string& postfix)
{
	//initialize postfix to empty
	postfix = (removeSpaces(postfix));
	stack<char> opStack;
	for (size_t i = 0; i < infix.size(); i++)
	{
		char ch = infix[i];
		switch (ch)
		{
		case ' ':
			break;
		case 'T':
			postfix += 'T';
			break;
		case 'F':
			postfix += 'F';
			break;
		case '(':
			opStack.push('(');
			break;
		case ')':
			while (!opStack.empty() && opStack.top() != '(')
			{
				postfix += opStack.top();
				opStack.pop();
			}
			opStack.pop();
			break;
		case '!':
			while (!opStack.empty() && opStack.top() != '(' && opStack.top() != '&'&&opStack.top() != '|')
			{
				postfix += opStack.top();
				opStack.pop();
			}
			opStack.push('!');
			break;
		case '&':
			while (!opStack.empty() && opStack.top() != '(' && opStack.top() != '|')
			{
				postfix += opStack.top();
				opStack.pop();
			}
			opStack.push('&');
			break;
		case '|':
			while (!opStack.empty() && opStack.top() != '(')
			{
				postfix += opStack.top();
				opStack.pop();
			}
			opStack.push('|');
			break;
		default:
			break;
		}
	}
	while (!opStack.empty())
	{
		postfix += opStack.top();
		opStack.pop();
	}
	return postfix;
}
