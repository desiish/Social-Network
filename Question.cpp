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
Question::Question(const MyString& title, const User* author, const MyString& content, unsigned id):
	_title(title), _content(content)
{
	_author = author;
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
void Question::addComment(const MyString& content, const User* author)
{
	srand(time(NULL));
	unsigned id = rand();
	_comments.push_back(Comment(author, content, id));
}
void Question::printComments() const
{
	size_t count = _comments.size();
	for (int i = 0; i < count; i++)
		_comments[i].printCommentInfo(2);
}
void Question::addReplyToComment(unsigned id, const MyString& content, const User* author)
{
	Comment* current = nullptr;
	getComment(current, _comments, id);
	if (current == nullptr)
		throw std::invalid_argument("No such comment exists");

	current->addReply(content, author);
}
void Question::addUpVote(unsigned id, const User* author)
{
	Comment* current = nullptr;
	getComment(current, _comments, id);
	if (current == nullptr)
		throw std::invalid_argument("No such comment exists");

	current->addOrRemoveUpVote(author);
}
void Question::addDownVote(unsigned id, const User* author)
{
	Comment* current = nullptr;
	getComment(current, _comments, id);
	if (current == nullptr)
		throw std::invalid_argument("No such comment exists");

	current->addOrRemoveDownVote(author);
}
void Question::printQuestion() const
{
	std::cout << ">>" << _content << " {id:" << _id << "} " << std::endl;
}