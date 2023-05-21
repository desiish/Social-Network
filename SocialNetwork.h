#pragma once
#include "User.h"
#include "Topic.h"
class SocialNetwork
{
	MyVector<User> _users;
	MyVector<Topic> _topics;
	User* _currentU = nullptr;
	Topic* _currentT = nullptr;

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

	void post();
	void p_open(const MyString& title) const;
	void p_open(unsigned id) const;
	void comment();
	void comments() const;
	void reply();
	void upvote(unsigned id);
	void downvote(unsigned id);

	void p_close() const;
	void quit();
	void exit();

	void whoami() const;
	void about(unsigned id) const;

};

