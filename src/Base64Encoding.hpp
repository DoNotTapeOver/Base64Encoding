#ifndef Base64Encoding_h
#define Base64Encoding_h

// Masks for extracting ASCII octets from a 24-bit character grouping
#define BASE64ENCODING_OCTET1_MASK 0b111111110000000000000000
#define BASE64ENCODING_OCTET2_MASK 0b000000001111111100000000
#define BASE64ENCODING_OCTET3_MASK 0b000000000000000011111111

// Masks for extracting Base64 sextets from a 24-bit character grouping
#define BASE64ENCODING_SEXTET1_MASK 0b111111000000000000000000
#define BASE64ENCODING_SEXTET2_MASK 0b000000111111000000000000
#define BASE64ENCODING_SEXTET3_MASK 0b000000000000111111000000
#define BASE64ENCODING_SEXTET4_MASK 0b000000000000000000111111

#define BASE64ENCODING_BUFFER_OVERFLOW -1

#ifndef BIT_IS_SET
#define BIT_IS_SET(x, mask) (x & mask)
#endif // BIT_IS_SET

typedef enum
{
    Unpadded = 0x00,
    Padded = 0x80
} Base64EncodingOptions;

class Base64Encoding
{
    private:

        const char Character62;
        const char Character63;
        const Base64EncodingOptions Options;

        // Converts a Base64 sextet to its ASCII character
        char SextetToCharacter(uint8_t sextet)
        {
            // Check if character represents an uppercase letter
            if(sextet >= 0 && sextet <= 25)
            {
                return sextet + 65;
            }

            // Check if character represents a lowercase letter
            if(sextet >= 26 && sextet <= 51)
            {
                return sextet + 71;
            }

            // Check if character represents a digit
            if(sextet >= 52 && sextet <= 61)
            {
                return sextet - 4;
            }

            // 62nd character
            if(sextet == 62)
            {
                return Character62;
            }

            // 63rd character
            return Character63;
        }

        // Converts an ASCII character to a Base64 sextet
        uint8_t CharacterToSextet(char character)
        {
            // Check if character is an uppercase letter
            if(character >= 'A' && character <= 'Z')
            {
                return character - 65;
            }

            // Check if character is a lowercase letter
            if(character >= 'a' && character <= 'z')
            {
                return character - 71;
            }

            // Check if character is a digit
            if(character >= '0'  && character <= '9')
            {
                return character + 4;
            }

            // 62nd character
            if(character == Character62)
            {
                return 62;
            }

            // 63rd character
            return 63;
        }

    public:

        Base64Encoding(const char character62, const char character63, const Base64EncodingOptions options)
          : Character62(character62),
            Character63(character63),
            Options(options)
        {

        }

        uint32_t EncodedLength(uint32_t inputLength)
        {
            // Every set of three ASCII characters will be encoded into four base64 characters
            uint32_t encodedLength = (inputLength / 3) * 4;

            // Check if any ASCII characters were not grouped into a set of three
            uint8_t ungroupedCharacters = inputLength % 3;

            if(BIT_IS_SET(Options, Base64EncodingOptions::Padded))
            {
                if(ungroupedCharacters != 0)
                {
                    // Some ASCII characters were ungrouped
                    // With padding, an additional four Base64 characters are required to encode them
                    encodedLength += 4;
                }
            }
            else
            {
                if(ungroupedCharacters == 1)
                {
                    // A single ASCII character remains ungrouped
                    // Without padding, an additional two Base64 characters are required to encode it
                    encodedLength += 2;
                }
                else if(ungroupedCharacters == 2)
                {
                    // Two ASCII characters remain ungrouped
                    // Without padding, an additional three Base64 characters are required to encode them
                    encodedLength += 3;
                }
            }

            return encodedLength;
        }

        uint32_t DecodedLength(char* pInputBuffer, uint32_t inputLength)
        {
            // Every set of four Base64 characters will be decoded into three ASCII characters
            uint32_t decodedLength = (inputLength / 4) * 3;

            if(BIT_IS_SET(Options, Base64EncodingOptions::Padded))
            {
                // Check for Base64 padding characters at end of input
                if(pInputBuffer[inputLength - 1] == '=')
                {
                    if(pInputBuffer[inputLength - 2] == '=')
                    {
                        // Two Base64 padding characters found
                        decodedLength -= 2;
                    }
                    else
                    {
                        // One Base64 padding character found
                        decodedLength -= 1;
                    }
                }
            }
            else
            {
                // Check if any Base64 characters were not grouped into a set of four
                uint8_t ungroupedCharacters = inputLength % 4;

                if(ungroupedCharacters == 2)
                {
                    // Two Base64 characters remain ungrouped, they will be decoded into one additional ASCII character
                    decodedLength += 1;
                }
                else if(ungroupedCharacters == 3)
                {
                    // Three Base64 characters remain ungrouped, they will be decoded into two additional ASCII characters
                    decodedLength += 2;
                }
            }

            return decodedLength;
        }

        // Converts a ASCII string into a Base64 string
        // Returns the length of the encoded string or BASE64ENCODING_BUFFER_OVERFLOW if the output buffer is not large enough to hold the encoded string
        int32_t Encode(char* pInputBuffer, char* pOutputBuffer, uint32_t outputBufferLength)
        {
            uint32_t inputLength = strlen(pInputBuffer);
            uint32_t encodedLength = EncodedLength(inputLength);

            // Verify the output buffer is large enough to hold the encoded string and null terminator
            if(outputBufferLength < (encodedLength + 1))
            {
                return BASE64ENCODING_BUFFER_OVERFLOW;
            }

            uint32_t groupedCharacterSetCount = inputLength / 3;
            uint8_t ungroupedCharacterCount = inputLength % 3;
            uint32_t characterSet;

            // Loop through every grouping of three ASCII characters
            for (uint32_t i = 0; i < groupedCharacterSetCount; i++)
            {
                // Pack the three ASCII characters into a 24-bit integer
                characterSet = (pInputBuffer[0] << 16) | (pInputBuffer[1] << 8) | pInputBuffer[2];

                // Extract and encode each of the four Base64 sextets
                pOutputBuffer[0] = SextetToCharacter(characterSet >> 18);
                pOutputBuffer[1] = SextetToCharacter((characterSet & BASE64ENCODING_SEXTET2_MASK) >> 12);
                pOutputBuffer[2] = SextetToCharacter((characterSet & BASE64ENCODING_SEXTET3_MASK) >> 6);
                pOutputBuffer[3] = SextetToCharacter((characterSet & BASE64ENCODING_SEXTET4_MASK));

                // Advance buffer pointers
                pInputBuffer += 3;
                pOutputBuffer += 4;
            }

            // Process any ungrouped ASCII characters
            switch(ungroupedCharacterCount)
            {
                case 1:

                    // Pack the single remaining ASCII character into a 24-bit integer
                    characterSet = pInputBuffer[0] << 16;

                    // Extract and encode the two Base64 characters
                    pOutputBuffer[0] = SextetToCharacter(characterSet >> 18);
                    pOutputBuffer[1] = SextetToCharacter((characterSet & BASE64ENCODING_SEXTET2_MASK) >> 12);

                    if(BIT_IS_SET(Options, Base64EncodingOptions::Padded))
                    {
                        // Add Base64 padding characters
                        pOutputBuffer[2] = '=';
                        pOutputBuffer[3] = '=';

                        pOutputBuffer += 4;
                    }
                    else
                    {
                        pOutputBuffer += 2;
                    }

                    break;

                case 2:

                    // Pack the single remaining ASCII characters into a 24-bit integer
                    characterSet = (pInputBuffer[0] << 16) | (pInputBuffer[1] << 8);

                    // Extract and encode the three Base64 characters
                    pOutputBuffer[0] = SextetToCharacter(characterSet >> 18);
                    pOutputBuffer[1] = SextetToCharacter((characterSet & BASE64ENCODING_SEXTET2_MASK) >> 12);
                    pOutputBuffer[2] = SextetToCharacter((characterSet & BASE64ENCODING_SEXTET3_MASK) >> 6);
                    
                    if(BIT_IS_SET(Options, Base64EncodingOptions::Padded))
                    {
                        // Add Base64 padding characters
                        pOutputBuffer[3] = '=';

                        pOutputBuffer += 4;
                    }
                    else
                    {
                        pOutputBuffer += 3;
                    }

                    break;
            }

            // Terminate the output buffer            
            pOutputBuffer[0] = '\0';

            return encodedLength;
        }

        // Converts a Base64 string into a ASCII string
        // Returns the length of the encoded string or BASE64ENCODING_BUFFER_OVERFLOW if the output buffer is not large enough to hold the decoded string
        uint32_t Decode(char* pInputBuffer, char* pOutputBuffer, uint32_t outputBufferLength)
        {
            uint32_t inputLength = strlen(pInputBuffer);
            uint32_t decodedLength = DecodedLength(pInputBuffer, inputLength);

            // Verify the output buffer is large enough to hold the decoded string and null terminator
            if(outputBufferLength < (decodedLength + 1))
            {
                return BASE64ENCODING_BUFFER_OVERFLOW;
            }

            uint32_t groupedCharacterSetCount = decodedLength / 3;
            uint8_t ungroupedCharacterCount = decodedLength % 3;
            uint32_t characterSet;

            // Loop through every grouping of four Base64 characters
            for(uint32_t i = 0; i < groupedCharacterSetCount; i++)
            {
                // Pack the four Base64 characters into a 24-bit integer
                characterSet = (CharacterToSextet(pInputBuffer[0]) << 18) | (CharacterToSextet(pInputBuffer[1]) << 12) | (CharacterToSextet(pInputBuffer[2]) << 6) | CharacterToSextet(pInputBuffer[3]);

                // Extract and encode each of the three ASCII characters
                pOutputBuffer[0] = characterSet >> 16;
                pOutputBuffer[1] = (characterSet & BASE64ENCODING_OCTET2_MASK) >> 8;
                pOutputBuffer[2] = (characterSet & BASE64ENCODING_OCTET3_MASK);

                // Advance buffer pointers
                pInputBuffer += 4;
                pOutputBuffer += 3;
            }

            // Check if any Base64 characters were not grouped into a set of three
            switch(decodedLength % 3)
            {
                case 1:

                    // Pack the two remaining Base64 characters into a 24-bit integer
                    characterSet = (CharacterToSextet(pInputBuffer[0]) << 18) | (CharacterToSextet(pInputBuffer[1]) << 12);

                    // Extract and decode the single ASCII character
                    pOutputBuffer[0] = characterSet >> 16;

                    pOutputBuffer += 1;

                    break;

                case 2:

                    // Pack the three remaining Base64 characters into a 24-bit integer
                    characterSet = (CharacterToSextet(pInputBuffer[0]) << 18) | (CharacterToSextet(pInputBuffer[1]) << 12) | (CharacterToSextet(pInputBuffer[2]) << 6);

                    // Extract and decode the two ASCII characters
                    pOutputBuffer[0] = characterSet >> 16;
                    pOutputBuffer[1] = (characterSet & BASE64ENCODING_OCTET2_MASK) >> 8;
                    
                    pOutputBuffer += 2;

                    break;
            }

            // Terminate the output buffer    
            pOutputBuffer[0] = '\0';

            return decodedLength;
        }
};

#endif // Base64Encoding_h