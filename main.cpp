#include <iostream>
#include "SocialNetwork.h"
bool isDigit(char s)
{
	return s <= '9' && s >= '0';
}
unsigned getDigitFromChar(char s)
{
	if (!isDigit(s))
		return 10;
	return s - '0';
}
unsigned getNumFromStr(const MyString& str)
{
	size_t len = str.length();
	unsigned mult = 1;
	unsigned res = 0;
	for (int i = len - 1; i >= 0; i--)
	{
		res += mult * getDigitFromChar(str[i]);
		mult *= 10;
	}
	return res;
}
int main()
{
	SocialNetwork s;
	s.readFromFiLe();
	MyString command;
	while (1)
	{
		std::cin >> command;
		if (command == "signup")
		{
			MyString fn, ln, pass;
			std::cout << "Enter first name, last name and pass: ";
			std::cin >> fn >> ln >> pass;
			s.signup(fn, ln, pass);
			std::cout << "User successfully created!" << std::endl;
		}
		else if (command == "whoami")
		{
			s.whoami();
		}
		else if (command == "login")
		{
			MyString fn, pass;
			std::cin >> fn >> pass;
			s.login(fn, pass);
			std::cout << fn << ", welcome back!" << std::endl;
		}
		else if (command == "logout")
			s.logout();
		else if (command == "create")
		{
			MyString title, desc;
			std::cin >> title >> desc;
			s.create(title, desc);
			std::cout << "Topic successfully created!" << std::endl;
		}
		else if (command == "search")
		{
			MyString text;
			std::cin >> text;
			s.search(text);
		}
		else if (command == "open")
		{
			MyString input;
			std::cin >> input;
			if (isDigit(input[0]))
				s.open(getNumFromStr(input));
			else
				s.open(input);
		}
		else if (command == "post")
		{
			s.post();
			std::cout << "Post successfully created!" << std::endl;
		}
		else if (command == "p_open")
		{
			MyString input;
			std::cin >> input;
			if (isDigit(input[0]))
				s.p_open(getNumFromStr(input));
			else
				s.p_open(input);
		}
		else if (command == "comment")
			s.comment();
		else if (command == "comments")
			s.comments();
		else if (command == "reply")
			s.reply();
		else if (command == "upvote")
		{
			unsigned idx;
			std::cin >> idx;
			s.upvote(idx);
		}
		else if (command == "downvote")
		{
			unsigned idx;
			std::cin >> idx;
			s.downvote(idx);
		}
		else if (command == "p_close")
			s.p_close();
		else if (command == "quit")
			s.quit();
		else if (command == "exit")
		{
			s.exit();
			break;
		}
		else if (command == "about")
		{
			unsigned idx;
			std::cin >> idx;
			s.about(idx);
		}
		else if (command == "list")
			s.list();
		else
			std::cout << "Invalid command" << std::endl;
	}
}

