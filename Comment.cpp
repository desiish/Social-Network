#include "Comment.h"
#include <fstream>
#include "SerializeFunctions.h"
Comment::Comment(unsigned idxOfAuthor, const MyString& content, unsigned id): _content(content)
{
	_indexOfAuthor = idxOfAuthor;
	_id = id;
}
unsigned Comment::getId() const
{
	return _id;
}
MyVector<Comment>& Comment::getReplies()
{
	return _replies;
}
void Comment::printCommentInfo(size_t countOfSpaces) const
{
	for (int i = 0; i < countOfSpaces; i++)
		std::cout << " ";
	std::cout << ">>" << _content << " {id:" << _id << "} ";
	if (!_upvotes.empty() || !_downvotes.empty())
		std::cout << " {upvotes: " << _upvotes.size() << "; downvotes: " << _downvotes.size() << "} ";
	std::cout << std::endl;
	if (!_replies.empty())
	{
		size_t count = _replies.size();
		for (int i = 0; i < count; i++)
			_replies[i].printCommentInfo(countOfSpaces + 2);
	}
}
void Comment::addReply(const MyString& content, unsigned idxOfAuthor)
{
	srand(time(NULL));
	unsigned id = rand();
	_replies.push_back(Comment(idxOfAuthor, content, id));
}
void Comment::addOrRemoveUpVote(unsigned idxOfAuthor)
{
	size_t count = _upvotes.size();
	for (int i = 0; i < count; i++)
	{
		if (idxOfAuthor == _upvotes[i])
		{
			_upvotes.erase(i);
			return;
		}
	}
	size_t other_count = _downvotes.size();
	for (int i = 0; i < other_count; i++)
	{
		if (idxOfAuthor == _downvotes[i])
			_downvotes.erase(i);
	}
	_upvotes.push_back(idxOfAuthor);
}
void Comment::addOrRemoveDownVote(unsigned idxOfAuthor)
{
	size_t count = _downvotes.size();
	for (int i = 0; i < count; i++)
	{
		if (idxOfAuthor == _downvotes[i])
		{
			_downvotes.erase(i);
			return;
		}
	}
	size_t other_count = _upvotes.size();
	for (int i = 0; i < other_count; i++)
	{
		if (idxOfAuthor == _upvotes[i])
			_upvotes.erase(i);
	}
	_downvotes.push_back(idxOfAuthor);
}
void Comment::writeToFile(std::ofstream& ofs) const
{
	ofs.write((const char*)&_indexOfAuthor, sizeof(unsigned));
	writeStringToFile(ofs, _content);
	ofs.write((const char*)&_id, sizeof(unsigned));

	size_t countOfUpv = _upvotes.size();
	ofs.write((const char*)&countOfUpv, sizeof(size_t));

	for (int i = 0; i < countOfUpv; i++)
		ofs.write((const char*)&_upvotes[i], sizeof(unsigned));

	size_t countOfDownv = _downvotes.size();
	ofs.write((const char*)&countOfDownv, sizeof(size_t));

	for (int i = 0; i < countOfDownv; i++)
		ofs.write((const char*)&_downvotes[i], sizeof(unsigned));

	size_t sizeOfRepl = _replies.size();
	ofs.write((const char*)&sizeOfRepl, sizeof(size_t));

	for (int i = 0; i < sizeOfRepl; i++)
		_replies[i].writeToFile(ofs);
}
void Comment::readFromFiLe(std::ifstream& ifs)
{
	ifs.read((char*)&_indexOfAuthor, sizeof(unsigned));
	_content = readStringFromFile(ifs);
	ifs.read((char*)&_id, sizeof(_id));
	size_t countOfUpv;
	ifs.read((char*)&countOfUpv, sizeof(size_t));
	unsigned read;
	for (int i = 0; i < countOfUpv; i++)
	{
		ifs.read((char*)&read, sizeof(unsigned));
		_upvotes.push_back(read);
	}
	size_t countOfDownv;
	ifs.read((char*)&countOfDownv, sizeof(size_t));
	for (int i = 0; i < countOfDownv; i++)
	{
		ifs.read((char*)&read, sizeof(unsigned));
		_downvotes.push_back(read);
	}
	size_t sizeOfRepl;
	ifs.read((char*)&sizeOfRepl, sizeof(size_t));
	for (int i = 0; i < sizeOfRepl; i++)
	{
		Comment readC;
		readC.readFromFiLe(ifs);
		_replies.push_back(readC);
	}
}