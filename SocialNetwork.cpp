#include "SocialNetwork.h"
#include <time.h>
#include <stdlib.h>

int SocialNetwork::getUserIdx(const MyString& fn, const MyString& pass) const
{
	int idx = -1;
	unsigned usersCount = _users.size();
	for (int i = 0; i < usersCount; i++)
	{
		if (_users[i].isName(fn) && _users[i].isPass(pass))
			return i;
	}
	return -1;
}
int SocialNetwork::getTopicIdx(const MyString& title) const
{
	int idx = -1;
	unsigned tCount = _topics.size();
	for (int i = 0; i < tCount; i++)
	{
		if (_topics[i].getTitle() == title)
			return i;
	}
	return -1;
}
int SocialNetwork::getTopicIdx(unsigned id) const
{
	int idx = -1;
	unsigned tCount = _topics.size();
	for (int i = 0; i < tCount; i++)
	{
		if (_topics[i].getId() == id)
			return i;
	}
	return -1;
}
void SocialNetwork::signup(const MyString& fn, const MyString& ln, const MyString& pass)
{
	srand(time(NULL));
	unsigned id = rand();
	std::cout << id << std::endl;
	_users.push_back(User(fn, ln, pass, id));
}
void SocialNetwork::login(const MyString& fn, const MyString& pass)
{
	int idx = getUserIdx(fn, pass);
	if (idx == -1)
		throw std::invalid_argument("No such user exists");
	_currentU = &_users[idx];
}
void SocialNetwork::logout()
{
	_currentU = nullptr;
	_currentT = nullptr;
}

void SocialNetwork::create(const MyString& title, const MyString& desc)
{
	if (_currentU == nullptr)
		throw "Not logged in!";

	srand(time(NULL));
	unsigned id = rand();
	_topics.push_back(Topic(title, _currentU, desc, id));
}

void SocialNetwork::search(const MyString& text) const
{
	if (_currentU == nullptr)
		throw "Not logged in!";

	unsigned topicsCount = _topics.size();
	for (int i = 0; i < topicsCount; i++)
	{
		if (_topics[i].containsText(text))
			_topics[i].printTopicInfo();
	}
}
void SocialNetwork::open(const MyString& title)
{
	if (_currentU == nullptr)
		throw "Not logged in!";

	int index = getTopicIdx(title);
	if (index == -1)
		throw std::invalid_argument("No such topic exists");

	_currentT = &_topics[index];
	std::cout << "Welcome to " << _topics[index].getTitle() << '!' << std::endl;
}
void SocialNetwork::open(unsigned idx) 
{
	if (_currentU == nullptr)
		throw "Not logged in!";

	int index = getTopicIdx(idx);
	if (index == -1)
		throw std::invalid_argument("No such topic exists");

	_currentT = &_topics[index];
	std::cout << "Welcome to " << _topics[index].getTitle() << '!' << std::endl;
}
void SocialNetwork::list() const
{
	if (_currentU == nullptr)
		throw "Not logged in!";

	if (_currentT == nullptr)
		throw "No topic chosen!";

	_currentT->printQuestions();
}

void SocialNetwork::post()
{
	if (_currentU == nullptr)
		throw "Not logged in!";

	if (_currentT == nullptr)
		throw "No topic chosen!";

	MyString title, content;
	std::cin >> title >> content;
	_currentT->addQuestion(_currentU, title, content);
}
void SocialNetwork::p_open(const MyString& title) const
{
	if (_currentU == nullptr)
		throw "Not logged in!";

	if (_currentT == nullptr)
		throw "No topic chosen!";

	std::cout << "Q: " << _currentT->getCurrentQ(title).getContent();
	std::cout << " {id:" << _currentT->getCurrentQ().getId() << "} " << std::endl;
}
void SocialNetwork::p_open(unsigned id) const
{
	if (_currentU == nullptr)
		throw "Not logged in!";

	if (_currentT == nullptr)
		throw "No topic chosen!";

	std::cout << "Q: " << _currentT->getCurrentQ(id).getContent();
	std::cout << " {id:" << _currentT->getCurrentQ().getId() << "} " << std::endl;
}
void SocialNetwork::comment()
{
	if (_currentU == nullptr)
		throw "Not logged in!";

	if (_currentT == nullptr)
		throw "No topic chosen!";

	MyString content;
	std::cin >> content;
	_currentT->addCommentToCurrentQ(content, _currentU);
}
void SocialNetwork::comments() const
{
	if (_currentU == nullptr)
		throw "Not logged in!";

	if (_currentT == nullptr)
		throw "No topic chosen!";

	_currentT->getCurrentQ().printComments();
}
void SocialNetwork::reply()
{
	if (_currentU == nullptr)
		throw "Not logged in!";

	if (_currentT == nullptr)
		throw "No topic chosen!";

	unsigned id;
	std::cin >> id;
	MyString content;
	std::cin >> content;
	_currentT->addReplyToCurrentQ(id, content, _currentU);
}
void SocialNetwork::upvote(unsigned id)
{
	_currentT->addUpvoteToCommentOnQ(id, _currentU);
}
void SocialNetwork::downvote(unsigned id)
{
	_currentT->addDownvoteToCommentOnQ(id, _currentU);
}
void SocialNetwork::p_close() const
{
	if (&_currentT->getCurrentQ() == nullptr)
		throw "No post is currently opened";

	std::cout << "You just left " << _currentT->getCurrentQ().getTitle() << std::endl;
	_currentT->closePost();
}
void SocialNetwork::quit()
{
	if (_currentT == nullptr)
		throw "No topic is currently chosen";
	if (&_currentT->getCurrentQ() != nullptr)
		throw "A post is still opened for reading";

	std::cout << "You just left " << _currentT->getTitle() << std::endl;
	_currentT = nullptr;
}
void SocialNetwork::exit()
{
	_currentT->closePost();
	_currentT = nullptr;
	_currentU = nullptr;

	//serialize
}

void SocialNetwork::whoami() const
{
	if (_currentU == nullptr)
		throw "Not logged in";

	_currentU->printUserInfo();
}
void SocialNetwork::about(unsigned id) const
{
	int idx = getTopicIdx(id);
	if (idx == -1)
		throw std::invalid_argument("No such topic exists");

	_currentT->printTopicData();
}