#pragma once
#include "User.h"
#include "Topic.h"
class SocialNetwork
{
	MyVector<User> _users;
	MyVector<Topic> _topics;
	User* _currentU = nullptr;
	Topic* _currentT = nullptr;
	Question* _currentQ = nullptr;

	int getUserIdx(const MyString& fn, const MyString& pass) const;
	int getTopicIdx(const MyString& title) const;
	int getTopicIdx(unsigned id) const;

public:
	SocialNetwork() = default;
	//login menu
	void signup(const MyString& fn, const MyString& ln, const MyString& pass);
	void login(const MyString& fn, const MyString& pass);
	void logout();

	void create(const MyString& title, const MyString& desc); // creates topic
	void search(const MyString& text) const;
	void open(const MyString& title);
	void open(unsigned idx);
	void list() const;

	void post(const MyString& title, const MyString& content);
	void p_open(const MyString& title);
	void p_open(unsigned id);
	void comment(const MyString& content);
	void comments() const;
	void reply(unsigned id, const MyString& content);
	void upvote(unsigned id);
	void downvote(unsigned id);

	void p_close();
	void quit();
	void exit();

	void whoami() const;
	void about(unsigned id) const;

	void writeToFile() const;
	void readFromFiLe();
};

