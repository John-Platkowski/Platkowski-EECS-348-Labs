#include <stdio.h>

int main()
{
    int input = 0;
    while(input != 1)
    {
        printf("Enter the NFL score (Enter 1 to stop): ");
        scanf("%d", &input);
        while(input <= 0)
        {
            printf("Invalid input. Enter the NFL score (Enter 1 to stop): ");
            scanf("%d", &input);
        }
        printf("\nPossible combinations of scoring plays if a team's score is %d\n", input);
        // Iterate across every possible count of each type of score
        // For example, a safety can at maximum exist input / 2 times
        for (int s2 = 0; s2 <= input / 2; s2++)
        {
            for (int s3 = 0; s3 <= input / 3; s3++)
            {
                for (int s6 = 0; s6 <= input / 6; s6++)
                {
                    for (int s7 = 0; s7 <= input / 7; s7++)
                    {
                        for (int s8 = 0; s8 <= input / 8; s8++)
                        {
                            // Check whether the combination adds up to the input target
                            if (2 * s2 + 3 * s3 + 6 * s6 + 7 * s7 + 8 * s8 == input)
                            {
                                // Print every value
                                printf("%d TD + 2pt, %d TD + FG, %d TD, %d 3pt FG, %d Safety\n", s8, s7, s6, s3, s2);
                            }
                        }
                    }
                }
            }
        }
        printf("\n");
    }
    return 0;
}