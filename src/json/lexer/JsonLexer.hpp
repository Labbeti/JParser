#pragma once

#include <istream>
#include <string>
#include <vector>

using Token = std::string;
using TokenContainer = std::vector<Token>;

class JsonLexer
{
public: // Constructor
	JsonLexer();

public: // Methods
	void setStream(std::istream& is);
	Token nextToken();
	bool end() const;
	TokenContainer getTokens() const;

private: // Methods
	void clear();
	void addToBuffer(char chr);
	void emptyBuffer();
	bool streamEmpty() const;

private: // Attributes
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