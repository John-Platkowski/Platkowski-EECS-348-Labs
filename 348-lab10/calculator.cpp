#include <iostream>
#include <fstream>


int main() 
{
    char filename[200];
    
    // Prompt user for filename and open file
    std::cout << "Enter the filename: ";
    std::cin.getline(filename, 200);
    std::ifstream file(filename);
    
    // Read each line
    char line[1024];
    while (file.getline(line, 1024)) 
    {
        // Find the index of the space between the nums
        int spaceIndex = -1;
        for (int i = 0; line[i] != '\0'; i++)
        {
            if (line[i] == ' ')
            {
                spaceIndex = i;
                break;
            }
        }
        if (spaceIndex != -1)
        {
            char left[512];
            char right[512];
            // Copy left part
            int j = 0;
            for (int i = 0; i < spaceIndex; i++) 
            {
                left[j++] = line[i];
            }
            left[j] = '\0';

            // Copy right part
            j = 0;
            for (int i = spaceIndex + 1; line[i] != '\0'; i++) 
            {
                right[j++] = line[i];
            }
            right[j] = '\0';
            
            int leftDecimalIndex = -1;
            int leftLength = 0;
            bool leftNegative = false;

            int rightDecimalIndex = -1;
            int rightLength = 0;
            bool rightNegative = false;

            bool invalid = false;

            // Validate right string
            for (int i = 0; right[i] != '\0'; i++)
            {
                if (i == 0)    
                {
                    if (right[i] == '-' || right[i] == '+') 
                    {
                        rightNegative = right[i] == '-';
                        continue;
                    }
                }

                // If the current char is . and there isn't a decimal yet and that there is a value following the decimal
                if (right[i] == '.' && rightDecimalIndex == -1 && right[i + 1] != '\0') {
                    // Set the index to this one
                    rightDecimalIndex = i;
                    continue;
                } else if (right[i] < '0' || right[i] > '9') {
                    // Break the loop here, this line can't be computed
                    invalid = true;
                    break;
                }
                rightLength ++;
            }

            // Validate left string
            for (int i = 0; left[i] != '\0'; i++)
            {
                if (i == 0)    
                {
                    if (left[i] == '-' || left[i] == '+') 
                    {
                        leftNegative = left[i] == '-';
                        continue;
                    }
                }

                // If the current char is . and there isn't a decimal yet and that there is a value following the decimal
                if (left[i] == '.' && leftDecimalIndex == -1 && left[i + 1] != '\0') 
                {
                    // Set the index to this one
                    leftDecimalIndex = i;
                    continue;
                } else if (left[i] < '0' || left[i] > '9') {
                    // Break the loop here, this line can't be computed
                    invalid = true;
                    break;
                }
                leftLength ++;
            }
            if (invalid) continue; // Skip the line if invalid
            
            // Normalize the strings by padding with 0s until they're the same length
            int leftIntCount = leftLength;
            int rightIntCount = rightLength;
            int leftFracCount = 0;
            int rightFracCount = 0;

            if (leftDecimalIndex != -1)
            {
                leftIntCount = leftDecimalIndex;
                leftFracCount = leftLength - leftIntCount;
            }
            if (rightDecimalIndex != -1)
            {
                rightIntCount = rightDecimalIndex;
                rightFracCount = rightLength - rightIntCount;
            }
            // Pad to the left of the decimal
            int leftIntPad = (rightIntCount > leftIntCount) ? (rightIntCount - leftIntCount) : 0;
            int rightIntPad = (leftIntCount > rightIntCount) ? (leftIntCount - rightIntCount) : 0;
            // Pad to the right of the decimal
            int leftFracPad = (rightFracCount > leftFracCount) ? (rightFracCount - leftFracCount) : 0;
            int rightFracPad = (leftFracCount > rightFracCount) ? (leftFracCount - rightFracCount) : 0;

            char normLeft[600];
            char normRight[600];
            // Both numbers may not have a decimal
            bool anyDecimal = (leftFracCount > 0 || rightFracCount > 0);

            // Normalize left

            int i = 0;
            int j = 0;

            // Copy sign if any
            if (left[i] == '+' || left[i] == '-')
            {
                normLeft[j++] = left[i++];
            }

            // Add leading zeros
            for (int k = 0; k < leftIntPad; k++)
            {
                normLeft[j++] = '0';
            }

            // Copy digits up to decimal
            while (left[i] != '\0' && left[i] != '.')
            {
                normLeft[j++] = left[i++];
            }

            // Add decimal point if needed
            if (left[i] == '.' || anyDecimal)
            {
                if (left[i] == '.') i++; // skip existing
                normLeft[j++] = '.';
            }

            // Copy fractional digits
            while (left[i] != '\0')
            {
                normLeft[j++] = left[i++];
            }

            // Add trailing zeros
            for (int k = 0; k < leftFracPad; k++)
            {
                normLeft[j++] = '0';
            }
            normLeft[j] = '\0';

            // Normalize right

            i = 0; 
            j = 0;

            // Copy sign if any
            if (right[i] == '+' || right[i] == '-')
            {
                normRight[j++] = right[i++];
            }

            // Add leading zeros
            for (int k = 0; k < rightIntPad; k++)
            {
                normRight[j++] = '0';
            }

            // Copy digits up to decimal
            while (right[i] != '\0' && right[i] != '.')
            {
                normRight[j++] = right[i++];
            }

            // Add decimal point if needed
            if (right[i] == '.' || anyDecimal)
            {
                if (right[i] == '.') i++; // skip existing
                normRight[j++] = '.';
            }

            // Copy fractional digits
            while (right[i] != '\0')
            {
                normRight[j++] = right[i++];
            }

            // Add trailing zeros
            for (int k = 0; k < rightFracPad; k++)
            {
                normRight[j++] = '0';
            }

            normRight[j] = '\0';


            // Determine operation and the result's sign
            bool shouldSubtract = (leftNegative != rightNegative);
            bool resultNegative = false;

            if (shouldSubtract)
            {
                // Determine the larger number by comparing digit-wise
                bool leftLarger = false;
                int compareIndex = 0;

                // Skip signs if present
                int leftStart = (normLeft[0] == '-' || normLeft[0] == '+') ? 1 : 0;
                int rightStart = (normRight[0] == '-' || normRight[0] == '+') ? 1 : 0;
                char lDigit = normLeft[leftStart + compareIndex];
                char rDigit = normRight[rightStart + compareIndex];
                while (lDigit != '\0' && rDigit != '\0')
                {
                    if (lDigit == '.')
                    {
                        compareIndex++;
                        continue;
                    }
                    if (lDigit > rDigit)
                    {
                        leftLarger = true;
                        break;
                    } else if (rDigit > lDigit) {
                        leftLarger = false;
                        break;
                    } // Continue only if equal
                    compareIndex++;
                }

                // Result takes the sign of the larger number
                resultNegative = leftLarger ? leftNegative : rightNegative;

                // If the right is larger, the left and right need to be swapped for subtraction
                if (!leftLarger)
                {
                    // Swap by constructing new strings
                    char temp[600];
                    int index = 0;
                    while (normLeft[index] != '\0')
                    {
                        temp[index] = normLeft[index];
                        index++;
                    }
                    temp[index] = '\0';

                    index = 0;
                    while (normRight[index] != '\0') 
                    {
                        normLeft[index] = normRight[index];
                        index++;
                    }
                    normLeft[index] = '\0';
                    
                    index = 0;
                    while (temp[index] != '\0') 
                    {
                        normRight[index] = temp[index];
                        index++;
                    }
                    normRight[index] = '\0';
                }
            } else {
                // Both have the same sign, result keeps the sign
                resultNegative = leftNegative;
            }

            
            // Perform sum
            char result[1000];
            // Carry for add, borrow for subtract
            int carry = 0;
            int borrow = 0;
            int resultIndex = 0;

            // Skip signs when processing
            int leftStart = (normLeft[0] == '-' || normLeft[0] == '+') ? 1 : 0;
            int rightStart = (normRight[0] == '-' || normRight[0] == '+') ? 1 : 0;
            // Get full lengths of the left and right strings
            int leftFullLength = 0;
            while (normLeft[leftFullLength] != '\0') leftFullLength++;
            int rightFullLength = 0;
            while (normRight[rightFullLength] != '\0') rightFullLength++;
            
            // Current sum indices
            int l = leftFullLength - 1; 
            int r = rightFullLength - 1;

            // Sum/subtract by digit
            while (l >= leftStart || r >= rightStart)
            {
                char cL = normLeft[l--];
                char cR = normRight[r--];

                if (cL == '.' || cR == '.')
                {
                    result[resultIndex] = '.';
                    resultIndex++;
                    continue;
                }
                if (!shouldSubtract)
                {
                    // Convert to the integer value by subtracting the ascii value of 0 from the ascii value of n
                    int sum = (cL - '0') + (cR - '0') + carry;
                    carry = sum / 10;
                    // Convert back to a char
                    result[resultIndex] = (sum % 10) + '0';
                    resultIndex++;
                } else {
                    int diff = (cL - '0') - (cR - '0') - borrow;
                    if (diff < 0)
                    {
                        diff += 10;
                        borrow = 1;
                    } else {
                        borrow = 0;
                    }
                    result[resultIndex] = diff + '0';
                }
            }
            // If carry remains
            if (carry)
            {
                result[resultIndex] = carry + '0';
                resultIndex++;
            }
            

            // Reverse the result
            for (int a = 0, b = resultIndex - 1; a < b; a++, b--)
            {
                char temp = result[a];
                result[a] = result[b];
                result[b] = temp;
            }

            // Add the negative sign if necessary
            if (resultNegative)
            {
                // Shift everything right and add - to the front
                for (int i = resultIndex; i > 0; i--)
                {
                    result[i] = result[i - 1];
                }
                result[0] = '-';
                resultIndex++;
            }
            
            result[resultIndex] = '\0';

            std::cout << result << std::endl;
        }
    }
    
    // Close the file
    file.close();
    
    return 0;
}