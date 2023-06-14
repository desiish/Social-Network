#include "System.h"
#include "SocialNetwork.h"
#include "HelperFunctions.h"
void run()
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
			char buff[1024];
			std::cin.ignore();
			std::cin.getline(buff, 1024);
			MyString title = buff;
			std::cin.getline(buff, 1024);
			MyString desc = buff;
			s.create(title, desc);
			std::cout << "Topic successfully created!" << std::endl;
		}
		else if (command == "search")
		{
			char buff[1024];
			std::cin.ignore();
			std::cin.getline(buff, 1024);
			MyString text = buff;
			s.search(text);
		}
		else if (command == "open")
		{
			char buff[1024];
			std::cin.ignore();
			std::cin.getline(buff, 1024);
			MyString input = buff;
			if (isDigit(input[0]))
				s.open(getNumFromStr(input));
			else
				s.open(input);
		}
		else if (command == "post")
		{
			char buff[1024];
			std::cin.ignore();
			std::cin.getline(buff, 1024);
			MyString title = buff;
			std::cin.getline(buff, 1024);
			MyString content = buff;
			s.post(title, content);
			std::cout << "Post successfully created!" << std::endl;
		}
		else if (command == "p_open")
		{
			char buff[1024];
			std::cin.ignore();
			std::cin.getline(buff, 1024);
			MyString input = buff;
			if (isDigit(input[0]))
				s.p_open(getNumFromStr(input));
			else
				s.p_open(input);
		}
		else if (command == "comment")
		{
			char buff[1024];
			std::cin.ignore();
			std::cin.getline(buff, 1024);
			MyString content = buff;
			s.comment(content);
		}
		else if (command == "comments")
			s.comments();
		else if (command == "reply")
		{
			unsigned id;
			std::cin >> id;
			char buff[1024];
			std::cin.ignore();
			std::cin.getline(buff, 1024);
			MyString content = buff;
			s.reply(id, content);
		}
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
		else {
			throw std::invalid_argument("Invalid command");
		}
	}
}