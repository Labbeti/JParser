#pragma once

#include <global.hpp>
#include <ostream>

namespace jp
{
	class JNumber
	{
	public: // Constructors & Destructor
		JNumber(Real number);
		explicit JNumber(unsigned number);
		~JNumber();

	public: // Methods
		JNumber& operator=(Real number);
		bool operator==(JNumber const& other) const;
		operator Real() const;
		operator unsigned() const;
		operator int() const;
		operator float() const;

	public: // Friends
		friend std::ostream& operator<<(std::ostream& os, JNumber const& jsonNumber);

	private: // Attributes
		Real number_;
	};
}
