#include "JsonLexer.hpp"
#include <iostream>
#include <util/col_fct/vector_fct.hpp>

// begin class JsonParser
JsonLexer::JsonLexer() :
	seps_{ '{', '}', '[', ']', ':', ',' },
	ignored_{ ' ', '\n' },
	is_{nullptr},
	tokens_{},
	buffer_{},
	currentIndex_{0},
	inString_{false},
	comment_{false},
	previous_{ '#' }
{};

void JsonLexer::setStream(std::istream& is)
{
	clear();
	is_ = &is;
}
Token JsonLexer::nextToken()
{
	char chr;
	while (not streamEmpty() and tokens_.size() < currentIndex_ + 2)
	{
		*is_ >> std::noskipws >> chr;

		if (not in(ignored_, chr))
		{
			if (not inString_ and chr == '*' and previous_ == '/')
			{
				buffer_.pop_back(); // delete previous char '/' in buffer

				bool endComment{ false };
				previous_ = chr;
				while (not streamEmpty() and not endComment)
				{
					*is_ >> chr;
					endComment = (chr == '/' and previous_ == '*');
					previous_ = chr;
				}
			}
			else
			{
				if (chr == '"' and previous_ != '\\')
				{
					inString_ = not inString_;
				}

				if (not inString_ and in(seps_, chr))
				{
					emptyBuffer();
					addToBuffer(chr);
					emptyBuffer();
				}
				else
				{
					addToBuffer(chr);
				}
				previous_ = chr;
			}
		}
	}

	if (streamEmpty())
	{
		emptyBuffer();
	}

	currentIndex_++;
	return tokens_.at(currentIndex_ - 1);
}
bool JsonLexer::end() const
{
	return streamEmpty() and buffer_.empty() and currentIndex_ >= tokens_.size();
}
TokenContainer JsonLexer::getTokens() const
{
	return tokens_;
}

void JsonLexer::clear()
{
	is_ = nullptr;
	tokens_.clear();
	buffer_.clear();
	currentIndex_ = 0;
	inString_ = false;
	comment_ = false;
	previous_ = '#';
}
void JsonLexer::addToBuffer(char chr)
{
	if (chr != ' ' or inString_)
	{
		buffer_ += chr;
	}
}
void JsonLexer::emptyBuffer()
{
	if (not buffer_.empty())
	{
		tokens_.push_back(buffer_);
		buffer_.clear();
	}
}
bool JsonLexer::streamEmpty() const
{
	return is_ == nullptr or is_->eof() or is_->peek() == std::char_traits<char>::eof();
}
// end class JsonParser