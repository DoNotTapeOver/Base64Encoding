#include "CppUnitTest.h"
#include "../src/Base64Encoding.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Base64EncodingTests
{
	TEST_CLASS(Base64EncodingTests)
	{
	public:

		TEST_METHOD(Decode1CharacterWithoutPadding)
		{
			Base64Encoding base64('+', '/', Base64EncodingOptions::Unpadded);

			char* testString = "YQ";
			int testStringLength = strlen(testString);
			int decodeBufferRequiredLength;
			char* decodeBuffer;

			// Decode
			decodeBufferRequiredLength = base64.DecodedLength(testString, testStringLength) + 1;
			decodeBuffer = new char[decodeBufferRequiredLength];

			int encodeLength = base64.Decode(testString, decodeBuffer, decodeBufferRequiredLength);

			Assert::AreEqual(1, encodeLength);
			Assert::AreEqual("a", decodeBuffer);

			delete[] decodeBuffer;
		}

		TEST_METHOD(Decode1CharacterWithPadding)
		{
			Base64Encoding base64('+', '/', Base64EncodingOptions::Padded);

			char* testString = "YQ==";
			int testStringLength = strlen(testString);
			int decodeBufferRequiredLength;
			char* decodeBuffer;

			// Decode
			decodeBufferRequiredLength = base64.DecodedLength(testString, testStringLength) + 1;
			decodeBuffer = new char[decodeBufferRequiredLength];

			int decodeLength = base64.Decode(testString, decodeBuffer, decodeBufferRequiredLength);

			Assert::AreEqual(1, decodeLength);
			Assert::AreEqual("a", decodeBuffer);

			delete[] decodeBuffer;
		}

		TEST_METHOD(Decode2CharactersWithoutPadding)
		{
			Base64Encoding base64('+', '/', Base64EncodingOptions::Unpadded);

			char* testString = "YWI";
			int testStringLength = strlen(testString);
			int decodeBufferRequiredLength;
			char* decodeBuffer;

			// Decode
			decodeBufferRequiredLength = base64.DecodedLength(testString, testStringLength) + 1;
			decodeBuffer = new char[decodeBufferRequiredLength];

			int encodeLength = base64.Decode(testString, decodeBuffer, decodeBufferRequiredLength);

			Assert::AreEqual(2, encodeLength);
			Assert::AreEqual("ab", decodeBuffer);

			delete[] decodeBuffer;
		}

		TEST_METHOD(Decode2CharactersWithPadding)
		{
			Base64Encoding base64('+', '/', Base64EncodingOptions::Padded);

			char* testString = "YWI=";
			int testStringLength = strlen(testString);
			int decodeBufferRequiredLength;
			char* decodeBuffer;

			// Decode
			decodeBufferRequiredLength = base64.DecodedLength(testString, testStringLength) + 1;
			decodeBuffer = new char[decodeBufferRequiredLength];

			int decodeLength = base64.Decode(testString, decodeBuffer, decodeBufferRequiredLength);

			Assert::AreEqual(2, decodeLength);
			Assert::AreEqual("ab", decodeBuffer);

			delete[] decodeBuffer;
		}

		TEST_METHOD(Decode3CharactersWithoutPadding)
		{
			Base64Encoding base64('+', '/', Base64EncodingOptions::Unpadded);

			char* testString = "YWJj";
			int testStringLength = strlen(testString);
			int decodeBufferRequiredLength;
			char* decodeBuffer;

			// Decode
			decodeBufferRequiredLength = base64.DecodedLength(testString, testStringLength) + 1;
			decodeBuffer = new char[decodeBufferRequiredLength];

			int encodeLength = base64.Decode(testString, decodeBuffer, decodeBufferRequiredLength);

			Assert::AreEqual(3, encodeLength);
			Assert::AreEqual("abc", decodeBuffer);

			delete[] decodeBuffer;
		}

		TEST_METHOD(Decode3CharactersWithPadding)
		{
			Base64Encoding base64('+', '/', Base64EncodingOptions::Padded);

			char* testString = "YWJj";
			int testStringLength = strlen(testString);
			int decodeBufferRequiredLength;
			char* decodeBuffer;

			// Decode
			decodeBufferRequiredLength = base64.DecodedLength(testString, testStringLength) + 1;
			decodeBuffer = new char[decodeBufferRequiredLength];

			int decodeLength = base64.Decode(testString, decodeBuffer, decodeBufferRequiredLength);

			Assert::AreEqual(3, decodeLength);
			Assert::AreEqual("abc", decodeBuffer);

			delete[] decodeBuffer;
		}

		TEST_METHOD(Decode4CharactersWithoutPadding)
		{
			Base64Encoding base64('+', '/', Base64EncodingOptions::Unpadded);

			char* testString = "YWJjZA";
			int testStringLength = strlen(testString);
			int decodeBufferRequiredLength;
			char* decodeBuffer;

			// Decode
			decodeBufferRequiredLength = base64.DecodedLength(testString, testStringLength) + 1;
			decodeBuffer = new char[decodeBufferRequiredLength];

			int encodeLength = base64.Decode(testString, decodeBuffer, decodeBufferRequiredLength);

			Assert::AreEqual(4, encodeLength);
			Assert::AreEqual("abcd", decodeBuffer);

			delete[] decodeBuffer;
		}

		TEST_METHOD(Decode4CharactersWithPadding)
		{
			Base64Encoding base64('+', '/', Base64EncodingOptions::Padded);

			char* testString = "YWJjZA==";
			int testStringLength = strlen(testString);
			int decodeBufferRequiredLength;
			char* decodeBuffer;

			// Decode
			decodeBufferRequiredLength = base64.DecodedLength(testString, testStringLength) + 1;
			decodeBuffer = new char[decodeBufferRequiredLength];

			int decodeLength = base64.Decode(testString, decodeBuffer, decodeBufferRequiredLength);

			Assert::AreEqual(4, decodeLength);
			Assert::AreEqual("abcd", decodeBuffer);

			delete[] decodeBuffer;
		}

		TEST_METHOD(Encode1CharacterWithoutPadding)
		{
			Base64Encoding base64('+', '/', Base64EncodingOptions::Unpadded);

			char* testString = "a";
			int testStringLength = strlen(testString);
			int encodeBufferRequiredLength;
			char* encodeBuffer;

			// Encode
			encodeBufferRequiredLength = base64.EncodedLength(testStringLength) + 1;
			encodeBuffer = new char[encodeBufferRequiredLength];

			int encodeLength = base64.Encode(testString, encodeBuffer, encodeBufferRequiredLength);

			Assert::AreEqual(2, encodeLength);
			Assert::AreEqual("YQ", encodeBuffer);

			delete[] encodeBuffer;
		}

		TEST_METHOD(Encode1CharacterWithPadding)
		{
			Base64Encoding base64('+', '/', Base64EncodingOptions::Padded);

			char* testString = "a";
			int testStringLength = strlen(testString);
			int encodeBufferRequiredLength;
			char* encodeBuffer;

			// Encode
			encodeBufferRequiredLength = base64.EncodedLength(testStringLength) + 1;
			encodeBuffer = new char[encodeBufferRequiredLength];

			int encodeLength = base64.Encode(testString, encodeBuffer, encodeBufferRequiredLength);

			Assert::AreEqual(4, encodeLength);
			Assert::AreEqual("YQ==", encodeBuffer);

			delete[] encodeBuffer;
		}

		TEST_METHOD(Encode2CharactersWithoutPadding)
		{
			Base64Encoding base64('+', '/', Base64EncodingOptions::Unpadded);

			char* testString = "ab";
			int testStringLength = strlen(testString);
			int encodeBufferRequiredLength;
			char* encodeBuffer;

			// Encode
			encodeBufferRequiredLength = base64.EncodedLength(testStringLength) + 1;
			encodeBuffer = new char[encodeBufferRequiredLength];

			int encodeLength = base64.Encode(testString, encodeBuffer, encodeBufferRequiredLength);

			Assert::AreEqual(3, encodeLength);
			Assert::AreEqual("YWI", encodeBuffer);

			delete[] encodeBuffer;
		}

		TEST_METHOD(Encode2CharactersWithPadding)
		{
			Base64Encoding base64('+', '/', Base64EncodingOptions::Padded);

			char* testString = "ab";
			int testStringLength = strlen(testString);
			int encodeBufferRequiredLength;
			char* encodeBuffer;

			// Encode
			encodeBufferRequiredLength = base64.EncodedLength(testStringLength) + 1;
			encodeBuffer = new char[encodeBufferRequiredLength];

			int encodeLength = base64.Encode(testString, encodeBuffer, encodeBufferRequiredLength);

			Assert::AreEqual(4, encodeLength);
			Assert::AreEqual("YWI=", encodeBuffer);

			delete[] encodeBuffer;
		}

		TEST_METHOD(Encode3CharactersWithoutPadding)
		{
			Base64Encoding base64('+', '/', Base64EncodingOptions::Unpadded);

			char* testString = "abc";
			int testStringLength = strlen(testString);
			int encodeBufferRequiredLength;
			char* encodeBuffer;

			// Encode
			encodeBufferRequiredLength = base64.EncodedLength(testStringLength) + 1;
			encodeBuffer = new char[encodeBufferRequiredLength];

			int encodeLength = base64.Encode(testString, encodeBuffer, encodeBufferRequiredLength);

			Assert::AreEqual(4, encodeLength);
			Assert::AreEqual("YWJj", encodeBuffer);

			delete[] encodeBuffer;
		}

		TEST_METHOD(Encode3CharactersWithPadding)
		{
			Base64Encoding base64('+', '/', Base64EncodingOptions::Padded);

			char* testString = "abc";
			int testStringLength = strlen(testString);
			int encodeBufferRequiredLength;
			char* encodeBuffer;

			// Encode
			encodeBufferRequiredLength = base64.EncodedLength(testStringLength) + 1;
			encodeBuffer = new char[encodeBufferRequiredLength];

			int encodeLength = base64.Encode(testString, encodeBuffer, encodeBufferRequiredLength);

			Assert::AreEqual(4, encodeLength);
			Assert::AreEqual("YWJj", encodeBuffer);

			delete[] encodeBuffer;
		}

		TEST_METHOD(Encode4CharactersWithoutPadding)
		{
			Base64Encoding base64('+', '/', Base64EncodingOptions::Unpadded);

			char* testString = "abcd";
			int testStringLength = strlen(testString);
			int encodeBufferRequiredLength;
			char* encodeBuffer;

			// Encode
			encodeBufferRequiredLength = base64.EncodedLength(testStringLength) + 1;
			encodeBuffer = new char[encodeBufferRequiredLength];

			int encodeLength = base64.Encode(testString, encodeBuffer, encodeBufferRequiredLength);

			Assert::AreEqual(6, encodeLength);
			Assert::AreEqual("YWJjZA", encodeBuffer);

			delete[] encodeBuffer;
		}

		TEST_METHOD(Encode4CharactersWithPadding)
		{
			Base64Encoding base64('+', '/', Base64EncodingOptions::Padded);

			char* testString = "abcd";
			int testStringLength = strlen(testString);
			int encodeBufferRequiredLength;
			char* encodeBuffer;

			// Encode
			encodeBufferRequiredLength = base64.EncodedLength(testStringLength) + 1;
			encodeBuffer = new char[encodeBufferRequiredLength];

			int encodeLength = base64.Encode(testString, encodeBuffer, encodeBufferRequiredLength);

			Assert::AreEqual(8, encodeLength);
			Assert::AreEqual("YWJjZA==", encodeBuffer);

			delete[] encodeBuffer;
		}

		TEST_METHOD(EncodeAndDecodeSameStringWithoutPadding)
		{
			Base64Encoding base64('+', '/', Base64EncodingOptions::Unpadded);

			char* testString = "The Quick Brown Fox Jumps Over The Lazy Dog.";
			int testStringLength = strlen(testString);
			int encodeBufferRequiredLength;
			char* encodeBuffer;
			int decodeBufferRequiredLength;
			char* decodeBuffer;

			// Encode
			encodeBufferRequiredLength = base64.EncodedLength(testStringLength) + 1;
			encodeBuffer = new char[encodeBufferRequiredLength];

			int encodeLength = base64.Encode(testString, encodeBuffer, encodeBufferRequiredLength);

			// Decode - Decode is the problem...
			decodeBufferRequiredLength = base64.DecodedLength(encodeBuffer, strlen(encodeBuffer)) + 1;
			decodeBuffer = new char[decodeBufferRequiredLength];

			int decodeLength = base64.Decode(encodeBuffer, decodeBuffer, decodeBufferRequiredLength);

			Assert::AreNotEqual(encodeLength, BASE64ENCODING_BUFFER_OVERFLOW);
			Assert::AreEqual(encodeLength, encodeBufferRequiredLength - 1);
			Assert::AreEqual(encodeLength, (int)strlen(encodeBuffer));
			Assert::AreEqual("VGhlIFF1aWNrIEJyb3duIEZveCBKdW1wcyBPdmVyIFRoZSBMYXp5IERvZy4", encodeBuffer);

			Assert::AreNotEqual(decodeLength, BASE64ENCODING_BUFFER_OVERFLOW);
			Assert::AreEqual(decodeLength, decodeBufferRequiredLength - 1);

			for (int i = 0; i < decodeBufferRequiredLength; ++i)
			{
				Assert::AreEqual(decodeBuffer[i], testString[i]);
			}

			delete[] encodeBuffer;
			delete[] decodeBuffer;
		}

		TEST_METHOD(EncodeAndDecodeSameStringWithPadding)
		{
			Base64Encoding base64('+', '/', Base64EncodingOptions::Padded);

			char* testString = "The Quick Brown Fox Jumps Over The Lazy Dog.";
			//char* testString = "abcd";
			int testStringLength = strlen(testString);
			int encodeBufferRequiredLength;
			char* encodeBuffer;
			int decodeBufferRequiredLength;
			char* decodeBuffer;

			// Encode
			encodeBufferRequiredLength = base64.EncodedLength(testStringLength) + 1;
			encodeBuffer = new char[encodeBufferRequiredLength];

			int encodeLength = base64.Encode(testString, encodeBuffer, encodeBufferRequiredLength);

			// Decode
			decodeBufferRequiredLength = base64.DecodedLength(encodeBuffer, strlen(encodeBuffer)) + 1;
			decodeBuffer = new char[decodeBufferRequiredLength];

			int decodeLength = base64.Decode(encodeBuffer, decodeBuffer, decodeBufferRequiredLength);

			Assert::AreNotEqual(encodeLength, BASE64ENCODING_BUFFER_OVERFLOW);
			Assert::AreEqual(encodeLength, encodeBufferRequiredLength - 1);
			Assert::AreEqual("VGhlIFF1aWNrIEJyb3duIEZveCBKdW1wcyBPdmVyIFRoZSBMYXp5IERvZy4=", encodeBuffer);

			Assert::AreNotEqual(decodeLength, BASE64ENCODING_BUFFER_OVERFLOW);
			Assert::AreEqual(decodeLength, decodeBufferRequiredLength - 1);

			for (int i = 0; i < decodeBufferRequiredLength; ++i)
			{
				Assert::AreEqual(decodeBuffer[i], testString[i]);
			}

			delete[] encodeBuffer;
			delete[] decodeBuffer;
		}
	};
}
