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
	int index = _users.size();
	_users.push_back(User(fn, ln, pass, id, index));
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
	_topics.push_back(Topic(title, _currentU->getIdxInSystem(), desc, id));
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

void SocialNetwork::post(const MyString& title, const MyString& content)
{
	if (_currentU == nullptr)
		throw "Not logged in!";

	if (_currentT == nullptr)
		throw "No topic chosen!";

	_currentT->addQuestion(_currentU->getIdxInSystem(), title, content);
}
void SocialNetwork::p_open(const MyString& title)
{
	if (_currentU == nullptr)
		throw "Not logged in!";

	if (_currentT == nullptr)
		throw "No topic chosen!";

	_currentT->getCurrentQ(title, _currentQ);
	std::cout << "Q: " << _currentQ->getTitle() << " {id:" << _currentQ->getId() << "} " << std::endl;
}
void SocialNetwork::p_open(unsigned id)
{
	if (_currentU == nullptr)
		throw "Not logged in!";

	if (_currentT == nullptr)
		throw "No topic chosen!";

	_currentT->getCurrentQ(id, _currentQ);
	std::cout << "Q: " << _currentQ->getTitle() << " {id:" << _currentQ->getId() << "} " << std::endl;
}
void SocialNetwork::comment(const MyString& content)
{
	if (_currentU == nullptr)
		throw "Not logged in!";

	if (_currentT == nullptr)
		throw "No topic chosen!";

	if (_currentQ == nullptr)
	throw "No question chosen!";

	_currentQ->addComment(content, _currentU->getIdxInSystem());
}
void SocialNetwork::comments() const
{
	if (_currentU == nullptr)
		throw "Not logged in!";

	if (_currentT == nullptr)
		throw "No topic chosen!";

	_currentQ->printComments();
}
void SocialNetwork::reply(unsigned id, const MyString& content)
{
	if (_currentU == nullptr)
		throw "Not logged in!";

	if (_currentT == nullptr)
		throw "No topic chosen!";

	if (_currentQ == nullptr)
	throw "No question chosen!";

	_currentQ->addReplyToComment(id, content, _currentU->getIdxInSystem());
}
void SocialNetwork::upvote(unsigned id)
{
	_currentQ->addUpVote(id, _currentU->getIdxInSystem());
	_currentU->setPoints(_currentU->getPoints() + 1);
}
void SocialNetwork::downvote(unsigned id)
{
	_currentQ->addDownVote(id, _currentU->getIdxInSystem());
	_currentU->setPoints(_currentU->getPoints() + 1);
}
void SocialNetwork::p_close()
{
	if (_currentQ == nullptr)
		throw "No post is currently opened";

	std::cout << "You just left " << _currentQ->getTitle() << std::endl;
	_currentQ = nullptr;
}
void SocialNetwork::quit()
{
	if (_currentT == nullptr)
		throw "No topic is currently chosen";
	if (_currentQ != nullptr)
		throw "A post is still opened for reading";

	std::cout << "You just left " << _currentT->getTitle() << std::endl;
	_currentT = nullptr;
}
void SocialNetwork::exit()
{
	_currentQ = nullptr;
	_currentT = nullptr;
	_currentU = nullptr;

	writeToFile();
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

	_topics[idx].printTopicData(_currentU);
}

void SocialNetwork::writeToFile() const
{
	std::ofstream ofs("SN.dat", std::ios::out | std::ios::binary);
	if (!ofs.is_open())
		throw "Error";

	size_t countOfUsers = _users.size();
	ofs.write((const char*)&countOfUsers, sizeof(size_t));
	for (int i = 0; i < countOfUsers; i++)
		_users[i].writeToFile(ofs);
	size_t countOfTopics = _topics.size();
	ofs.write((const char*)&countOfTopics, sizeof(size_t));
	for (int i = 0; i < countOfTopics; i++)
		_topics[i].writeToFile(ofs);

	ofs.clear();
	ofs.close();
}
void SocialNetwork::readFromFiLe()
{
	std::ifstream ifs("SN.dat", std::ios::in | std::ios::binary);
	if (!ifs.is_open())
		throw "Error";

	size_t countOfUsers;
	ifs.read((char*)&countOfUsers, sizeof(size_t));
	for (int i = 0; i < countOfUsers; i++)
	{
		User read;
		read.readFromFiLe(ifs);
		_users.push_back(read);
	}
	size_t countOfTopics;
	ifs.read((char*)&countOfTopics, sizeof(size_t));
	for (int i = 0; i < countOfTopics; i++)
	{
		Topic readT;
		readT.readFromFiLe(ifs);
		_topics.push_back(readT);
	}

	ifs.clear();
	ifs.close();
}