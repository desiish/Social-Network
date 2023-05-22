#include "Question.h"

void Question::getComment(Comment*& current, MyVector<Comment>& comments, unsigned id)
{
	size_t count = comments.size();
	for (int i = 0; i < count; i++)
	{
		if (comments[i].getId() == id)
		{
			current = &comments[i];
			return;
		}
		else if(comments[i].getReplies().size() != 0)
			getComment(current, comments[i].getReplies(), id);
	}
}
Question::Question(const MyString& title, unsigned idxOfAuthor, const MyString& content, unsigned id):
	_title(title), _content(content)
{
	_idxOfAuthor = idxOfAuthor;
	_id = id;
}
const MyString& Question::getTitle() const
{
	return _title;
}
const MyString& Question::getContent() const
{
	return _content;
}
unsigned Question::getId() const
{
	return _id;
}
void Question::addComment(const MyString& content, unsigned idxOfAuthor)
{
	srand(time(NULL));
	unsigned id = rand();
	_comments.push_back(Comment(idxOfAuthor, content, id));
}
void Question::printComments() const
{
	size_t count = _comments.size();
	for (int i = 0; i < count; i++)
		_comments[i].printCommentInfo(2);
}
void Question::addReplyToComment(unsigned id, const MyString& content, unsigned idxOfAuthor)
{
	Comment* current = nullptr;
	getComment(current, _comments, id);
	if (current == nullptr)
		throw std::invalid_argument("No such comment exists");

	current->addReply(content, idxOfAuthor);
}
void Question::addUpVote(unsigned id, unsigned idxOfAuthor)
{
	Comment* current = nullptr;
	getComment(current, _comments, id);
	if (current == nullptr)
		throw std::invalid_argument("No such comment exists");

	current->addOrRemoveUpVote(idxOfAuthor);
}
void Question::addDownVote(unsigned id, unsigned idxOfAuthor)
{
	Comment* current = nullptr;
	getComment(current, _comments, id);
	if (current == nullptr)
		throw std::invalid_argument("No such comment exists");

	current->addOrRemoveDownVote(idxOfAuthor);
}
void Question::printQuestion() const
{
	std::cout << ">>" << _content << " {id:" << _id << "} " << std::endl;
}

void Question::writeToFile(std::ofstream& ofs) const
{
	writeStringToFile(ofs, _title);
	ofs.write((const char*)&_idxOfAuthor, sizeof(unsigned));
	writeStringToFile(ofs, _content);
	ofs.write((const char*)&_id, sizeof(unsigned));
	size_t countOfComments = _comments.size();
	ofs.write((const char*)&countOfComments, sizeof(size_t));
	for (int i = 0; i < countOfComments; i++)
		_comments[i].writeToFile(ofs);
}
void Question::readFromFiLe(std::ifstream& ifs)
{
	_title = readStringFromFile(ifs);
	ifs.read((char*)&_idxOfAuthor, sizeof(unsigned));
	_content = readStringFromFile(ifs);
	ifs.read((char*)&_id, sizeof(unsigned));
	size_t countOfComments;
	ifs.read((char*)&countOfComments, sizeof(size_t));
	for (int i = 0; i < countOfComments; i++)
	{
		Comment read;
		read.readFromFiLe(ifs);
		_comments.push_back(read);
	}
}