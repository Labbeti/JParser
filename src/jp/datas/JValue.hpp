#pragma once

#include "JArray.hpp"
#include "JNumber.hpp"
#include "JObject.hpp"
#include "JString.hpp"
#include <optional>
#include <string>

namespace jp
{
	class JValue
	{
	public: // Constructors
		JValue();
		JValue(JArray const& jsonArray);
		JValue(JNumber const& jsonNumber);
		JValue(JObject const& jsonObject);
		JValue(JString const& jsonString);
		JValue(std::nullptr_t nullp);
		explicit JValue(bool value);

	public: // Destructor
		~JValue();

	private: // Types
		enum class LiteralType
		{
			NONE,
			TRUE,
			FALSE,
			NULLPTR
		};

	public: // Methods operators
		JValue& operator=(std::nullptr_t nullp);
		JValue& operator=(bool value);
		JValue& operator=(std::string const& string);
		JValue& operator[](unsigned i);
		JValue& operator[](JString const& jsonString);
		bool operator==(JValue const& other) const;

		// Note: Use references for avoid copy of these structures
		operator JArray const&() const;
		operator JObject const&() const;
		operator JArray&();
		operator JObject&();
		operator JNumber() const;
		operator JString() const;
		operator std::nullptr_t() const;
		operator bool() const;
		operator std::string() const;
		operator Real() const;

	private: // Methods getters
		bool isArray() const;
		bool isNumber() const;
		bool isObject() const;
		bool isString() const;
		bool isLiteral() const;
		bool isTrue() const;
		bool isFalse() const;
		bool isNull() const;

	private: // Methods
		void clear();
		std::string debugState() const;

	public: // Friends
		friend std::ostream& operator<<(std::ostream& os, JValue const& jsonValue);

	private: // Attributes
		std::optional<JArray> array_;
		std::optional<JNumber> number_;
		std::optional<JObject> object_;
		std::optional<JString> string_;
		LiteralType literal_;
	};
}
