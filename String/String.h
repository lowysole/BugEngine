#ifndef STRING_H
#define STRING_H

class String
{

	public:
		// Constructors
		String();
		String(const char* _char);
		String(const String& other);
		//String(const String&& other);
		~String();

		String operator+(const String& other) const;
		bool operator==(const String& other) const;

		void Clear();
		size_t GetLength() const { return len; };

	private:
		char* _char;
		size_t len;
};

#endif STRING_H

