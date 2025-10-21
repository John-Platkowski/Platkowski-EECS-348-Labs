#include <stdio.h>

int main()
{
    float temp;
    char input;
    char target;
    printf("\nEnter the temperature value: ");
    scanf(" %f", &temp);
    printf("\nEnter the original scale (C, F, or K): ");
    scanf(" %c", &input);
    // Validate input
    while(!(input == 'C' || input == 'F' || input == 'K'))
    {
        printf("\nInvalid input. Enter the original scale (C, F, or K): ");
        scanf(" %c", &input);    
    }
    printf("\nEnter the scale to convert to (C, F, or K): ");
    scanf(" %c", &target);
    // Validate input
    while(!(target == 'C' || target == 'F' || target == 'K'))
    {
        printf("\nInvalid input. Enter the scale to convert to (C, F, or K): ");
        scanf(" %c", &target);    
    }

    // Since C is the objective scale for advisory, all temps should be converted to C first
    // Then the actual conversion is performed and printed
    float C_temp;
    float converted_temp;
    if(input == 'C')
    {
        C_temp = temp;
        if (target == 'C')
        {
            converted_temp = temp;
        } else if (target == 'F') {
            converted_temp = (temp * 1.8f) + 32;
        } else {
            converted_temp = temp + 273.15f;
        }
    } else if (input == 'F') {
        C_temp = (temp - 32) / (1.8f);
        if (target == 'C')
        {
            converted_temp = C_temp;
        } else if (target == 'F') {
            converted_temp = temp;
        } else {
            converted_temp = C_temp + 273.15f;
        }
    } else if (input == 'K') {
        C_temp = temp - 273.15f;
        if (target == 'C')
        {
            converted_temp = C_temp;
        } else if (target == 'F') {
            converted_temp = (C_temp * 1.8f) + 32;
        } else {
            converted_temp = temp;
        }
    }
    printf("\nConverted temperature: %f %c", converted_temp, target);
    if (C_temp < 0)
    {
        printf("\nTemperature category: Freezing");
        printf("\nStay indoors!");
    } else if (C_temp < 10) {
        printf("\nTemperature category: Cold");
        printf("\nWear a jacket.");
    } else if (C_temp < 25) {
        printf("\nTemperature category: Comfortable");
        printf("\nEnjoy the weather.");
    } else if (C_temp < 35) {
        printf("\nTemperature category: Hot");
        printf("\nDrink lots of water!");
    } else {
        printf("\nTemperature category: Extreme Heat");
        printf("\nJump in your freezer!");
    }
    return 0;
}