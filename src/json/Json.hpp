#pragma once

#include "JsonDatas.hpp"
#include "lexer/JsonLexer.hpp"
#include <istream>
#include <memory>
#include <ostream>

// TODO: implementer les commentaires d'une ligne !
class Json
{
public: // Constructors
	Json(std::string const& filepath = "");

public: // Methods
	bool readFromStream(std::istream& is);
	void writeInStream(std::ostream& os) const;
	void clear();
	JsonObject::iterator begin() const;
	JsonObject::iterator end() const;
	bool empty() const;
	JsonObject const& content() const;
	JsonObject& content();

public: // Friends
	friend std::ostream& operator<<(std::ostream& os, Json const& json);

private: // Attributes
	std::unique_ptr<JsonObject> data_;
	JsonLexer lexer_;
	std::string filepath_;
};

std::ostream& operator<<(std::ostream& os, Json const& json);