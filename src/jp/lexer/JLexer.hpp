#pragma once

#include <istream>
#include <string>
#include <vector>

using Token = std::string;
using TokenContainer = std::vector<Token>;

namespace jp
{
	class JLexer
	{
	public:
		JLexer();

	public:
		void setStream(std::istream& is);
		Token nextToken();
		bool end() const;
		TokenContainer getTokens() const;

	private:
		void clear();
		void addToBuffer(char chr);
		void emptyBuffer();
		bool streamEmpty() const;

	private:
		std::vector<char> const seps_;
		std::vector<char> const ignored_;
		std::istream* is_;
		TokenContainer tokens_;
		Token buffer_;
		unsigned currentIndex_;
		bool inString_;
		bool comment_;
		char previous_;
	};
}
