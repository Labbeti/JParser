#pragma once

#include "AllJDatas.hpp"
#include "lexer/JLexer.hpp"
#include <istream>
#include <memory>
#include <ostream>

// TODO: implementer les commentaires d'une ligne !
namespace jp
{
	class JFile
	{
	public: // Constructors
		JFile(std::string const& filepath = "");

	public: // Methods
		bool readFromStream(std::istream& is);
		void writeInStream(std::ostream& os) const;
		void saveInFile(std::string const& filepath) const;
		void clear();
		bool empty() const;
		JObject const& content() const;
		JObject& content();

	public: // Friends
		friend std::ostream& operator<<(std::ostream& os, jp::JFile const& json);

	private: // Attributes
		std::unique_ptr<JObject> data_;
		JLexer lexer_;
		std::string filepath_;
	};
}