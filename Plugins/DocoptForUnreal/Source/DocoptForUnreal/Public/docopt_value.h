//
//  value.h
//  docopt
//
//  Created by Jared Grubb on 2013-10-14.
//  Copyright (c) 2013 Jared Grubb. All rights reserved.
//

#ifndef docopt__value_h_
#define docopt__value_h_

#include <stdexcept>
#include <string>
#include <vector>
#include <functional> // std::hash
#include <iosfwd>
#include "CoreMinimal.h"

namespace docopt {

	/// A generic type to hold the various types that can be produced by docopt.
	///
	/// This type can be one of: {bool, long, string, vector<string>}, or empty.
	struct value {
		/// An empty value
		value() {}

		value(std::string);
		value(std::vector<std::string>);
		
		explicit value(bool);
		explicit value(long);
		explicit value(int v) : value(static_cast<long>(v)) {}

		~value();
		value(value const&);
		value(value&&) noexcept;
		value& operator=(value const&);
		value& operator=(value&&) noexcept;
		
		// Test if this object has any contents at all
		explicit operator bool() const { return kind != Kind::Empty; }
		
		// Test the type contained by this value object
		bool isBool()       const { return kind==Kind::Bool; }
		bool isString()     const { return kind==Kind::String; }
		bool isLong()       const { return kind==Kind::Long; }
		bool isStringList() const { return kind==Kind::StringList; }

		// Throws std::invalid_argument if the type does not match
		bool asBool() const;
		long asLong() const;
		std::string const& asString() const;
		std::vector<std::string> const& asStringList() const;

		size_t hash() const noexcept;
		
		// equality is based on hash-equality
		friend bool operator==(value const&, value const&);
		friend bool operator!=(value const&, value const&);

	private:
		enum class Kind {
			Empty,
			Bool,
			Long,
			String,
			StringList
		};
		
		static const char* kindAsString(Kind kind) {
			switch (kind) {
				case Kind::Empty: return "empty";
				case Kind::Bool: return "bool";
				case Kind::Long: return "long";
				case Kind::String: return "string";
				case Kind::StringList: return "string-list";
			}
			return "unknown";
		}

		void throwIfNotKind(Kind expected) const {
			if (kind == expected)
				return;

			std::string error = "Illegal cast to ";
			error += kindAsString(expected);
			error += "; type is actually ";
			error += kindAsString(kind);
			throw std::runtime_error(std::move(error));
		}

	private:
		Kind kind = Kind::Empty;
		bool boolValue;
		long longValue;
		std::string strValue;
		std::vector<std::string> strList;
	};

	/// Write out the contents to the ostream
	std::ostream& operator<<(std::ostream&, value const&);
}

namespace std {
	template <>
	struct hash<docopt::value> {
		size_t operator()(docopt::value const& val) const noexcept {
			return val.hash();
		}
	};
}

namespace docopt {
	inline
	value::value(bool v)
	: kind(Kind::Bool)
	{
		boolValue = v;
	}

	inline
	value::value(long v)
	: kind(Kind::Long)
	{
		longValue = v;
	}

	inline
	value::value(std::string v)
	: kind(Kind::String)
	{
		strValue = std::move(v);
	}

	inline
	value::value(std::vector<std::string> v)
	: kind(Kind::StringList)
	{
		strList = std::move(v);
	}

	inline
	value::value(value const& other)
	: kind(other.kind)
	{
		switch (kind) {
			case Kind::String:
				strValue = other.strValue;
				break;

			case Kind::StringList:
				strList = other.strList;
				break;

			case Kind::Bool:
				boolValue = other.boolValue;
				break;

			case Kind::Long:
				longValue = other.longValue;
				break;

			case Kind::Empty:
			default:
				break;
		}
	}

	inline
	value::value(value&& other) noexcept
	: kind(other.kind)
	{
		switch (kind) {
			case Kind::String:
				strValue = std::move(other.strValue);
				break;

			case Kind::StringList:
				strList = std::vector<std::string>(std::move(other.strList));
				break;

			case Kind::Bool:
				boolValue = other.boolValue;
				break;

			case Kind::Long:
				longValue = other.longValue;
				break;

			case Kind::Empty:
			default:
				break;
		}
	}

	inline
	value::~value()
	{
		switch (kind) {
			case Kind::String:
				strValue.~basic_string();
				break;

			case Kind::StringList:
				strList.~vector();
				break;

			case Kind::Empty:
			case Kind::Bool:
			case Kind::Long:
			default:
				// trivial dtor
				break;
		}
	}

	inline
	value& value::operator=(value const& other) {
		// make a copy and move from it; way easier.
		return *this = value{other};
	}

	inline
	value& value::operator=(value&& other) noexcept {
		// move of all the types involved is noexcept, so we dont have to worry about 
		// these two statements throwing, which gives us a consistency guarantee.
		this->~value();
		new (this) value(std::move(other));

		return *this;
	}

	template <class T>
	void hash_combine(std::size_t& seed, const T& v);

	inline
	size_t value::hash() const noexcept
	{
		switch (kind) {
			case Kind::String:
				return std::hash<std::string>()(strValue);

			case Kind::StringList: {
				size_t seed = std::hash<size_t>()(strList.size());
				for(auto const& str : strList) {
					hash_combine(seed, str);
				}
				return seed;
			}

			case Kind::Bool:
				return std::hash<bool>()(boolValue);

			case Kind::Long:
				return std::hash<long>()(longValue);

			case Kind::Empty:
			default:
				return std::hash<void*>()(nullptr);
		}
	}

	inline
	bool value::asBool() const
	{
		check(kind == Kind::Bool);
		return boolValue;
	}

	inline
	long value::asLong() const
	{
		// Attempt to convert a string to a long
		if (kind == Kind::String) {
			const std::string& str = strValue;
			std::size_t pos;
			const long ret = stol(str, &pos); // Throws if it can't convert
			if (pos != str.length()) {
				// The string ended in non-digits.
				return 0;
			}
			return ret;
		}
		check(kind == Kind::Long);
		return longValue;
	}

	inline
	std::string const& value::asString() const
	{
		check(kind == Kind::String);
		return strValue;
	}

	inline
	std::vector<std::string> const& value::asStringList() const
	{
		check(kind == Kind::StringList);
		return strList;
	}

	inline
	bool operator==(value const& v1, value const& v2)
	{
		if (v1.kind != v2.kind)
			return false;
		
		switch (v1.kind) {
			case value::Kind::String:
				return v1.strValue==v2.strValue;

			case value::Kind::StringList:
				return v1.strList==v2.strList;

			case value::Kind::Bool:
				return v1.boolValue==v2.boolValue;

			case value::Kind::Long:
				return v1.longValue==v2.longValue;

			case value::Kind::Empty:
			default:
				return true;
		}
	}

	inline
	bool operator!=(value const& v1, value const& v2)
	{
		return !(v1 == v2);
	}
}

#endif /* defined(docopt__value_h_) */
